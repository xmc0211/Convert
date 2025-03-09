// Convert.h by XMC
#ifndef CONVERT_H
#define CONVERT_H

#include <windows.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tchar.h>

#if defined(UNICODE)
#define _tstring wstring
#else
#define _tstring string
#endif

// std::string��std::wstring��ת������ȫ��
std::wstring LPC2LPW(const std::string str);
std::string LPW2LPC(const std::wstring wstr);

#ifdef UNICODE
#define LPT2LPW(str) (str)
#define LPT2LPC(str) LPW2LPC(str)
#define LPW2LPT(str) (str)
#define LPC2LPT(str) LPC2LPW(str)
#else
#define LPT2LPW(str) LPC2LPW(str)
#define LPT2LPC(str) (str)
#define LPW2LPT(str) LPW2LPC(str)
#define LPC2LPT(str) (str)
#endif

// UCHAR*��strlen
size_t ustrlen(const UCHAR* str);

// char*��unsigned char*��ת
void CH2UCH(const char* str, UCHAR* res, size_t sz);
void UCH2CH(const UCHAR* str, char* res, size_t sz);

// UL��std::_tstring��ת��ȷ���ڷ�Χ�ڣ�
std::_tstring UL2TSTR(const ULONG res);
ULONG TSTR2UL(const std::_tstring str);

// UCHAR*��ʮ�������ַ�����ת
void UCH2TSTR(const UCHAR* data, TCHAR* res, size_t sz, size_t res_sz);
void TSTR2UCH(const TCHAR* hexStr, UCHAR* data, size_t sz);

#endif
