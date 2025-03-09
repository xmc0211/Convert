// Convert.cpp by XMC

#include "Convert.h"

// std::string与std::wstring互转（更安全）
std::wstring LPC2LPW(const std::string str) {
	INT size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	if (size == 0) return L"";

	std::vector<WCHAR> buffer(size + 1);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer.data(), size);
	buffer[size] = '\0';

	return std::wstring(buffer.data(), size - 1); // 排除 null 终止符
}
std::string LPW2LPC(const std::wstring wstr) {
	INT size = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (size == 0) return "";

	std::vector<CHAR> buffer(size + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, buffer.data(), size, nullptr, nullptr);
	buffer[size] = '\0';

	return std::string(buffer.data(), size - 1); // 排除 null 终止符
}

// UCHAR*的strlen
size_t ustrlen(const UCHAR* str) {
	size_t length = 0;
	while (*str != 0) { // 以0作为终止条件
		++length;
		++str;
	}
	return length;
}

// char*与unsigned char*互转
void CH2UCH(const char* str, UCHAR* res, size_t sz) {
	for (size_t i = 0; i < sz + 1; i++) {
		res[i] = static_cast<UCHAR>(str[i]);
	}
	return;
}
void UCH2CH(const UCHAR* str, char* res, size_t sz) {
	for (size_t i = 0; i < sz + 1; i++) {
		res[i] = static_cast<CHAR>(str[i]);
	}
	return;
}

// UL与std::string互转（确保在范围内）
std::_tstring UL2TSTR(const ULONG res) {
	if (res == 0) return TEXT("0");
	std::_tstring ans = TEXT("");
	ULONG tmp = res;
	while (tmp) {
		ans = TCHAR((tmp % 10) + TCHAR('0')) + ans;
		tmp /= 10;
	}
	return ans;
}
ULONG TSTR2UL(const std::_tstring str) {
	size_t sz = str.size();
	ULONG ans = 0;
	for (UINT indx = 0; indx < sz; indx++) {
		ans = ans * 10 + (str[indx] - TCHAR('0'));
	}
	return ans;
}

// UCHAR*与string互转
void UCH2TSTR(const UCHAR* data, TCHAR* res, size_t sz, size_t res_sz) {
	for (size_t i = 0; i < sz; i++) {
		_sntprintf_s(res + i * 2, res_sz - i * 2, _TRUNCATE, TEXT("%02x"), data[i]);
	}
	return;
}
void TSTR2UCH(const TCHAR* hexStr, UCHAR* data, size_t sz) {
	for (size_t i = 0; i < sz * 2; i += 2) {
		TCHAR byteStr[] = {hexStr[i], hexStr[i + 1], TCHAR('\0')};
		data[i / 2] = (UCHAR)_tcstol(byteStr, NULL, 16);
	}
    return;
}
