#pragma once

//The references
//https://learn.microsoft.com/en-us/archive/msdn-magazine/2017/may/c-use-modern-c-to-access-the-windows-registry
//
//Define at here to avoid namespace pollution
//So that we can use the function from <limits> instead in minwindef.h
#define NOMINMAX

#include <iostream>
#include <format>
#include <string>
#include <windows.h>
#include <vector>

#ifdef  UNICODE
typedef std::wstring QString;
#define STRING_SIZE sizeof(wchar_t)
#define ConvertToString(X) std::to_wstring(X)
#else
typedef std::string QString;
#define STRING_SIZE sizeof(char_t)
#define ConvertToString(X) std::to_string(X)
#endif


class RegistryHeper
{
/// <summary>
///Get Functions
/// </summary>
public:
	static bool RegGetString(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ const QString& defaultValue,
		_Out_ QString& dataOut);

	static bool RegGetFloat(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ float defaultValue,
		_Out_ float& dataOut);

	static bool RegGetDouble(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ double defaultValue,
		_Out_ double& dataOut);

	static bool RegGetInt32(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ int32_t defaultValue,
		_Out_ int32_t& dataOut);

	static bool RegGetInt64(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ int64_t defaultValue,
		_Out_ int64_t& dataOut);

	static bool RegGetBinary(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ const std::vector<byte>& defaultValue,
		_Out_ std::vector<byte>& dataOut);
/// <summary>
/// Set Functions
/// </summary>
public:
	static bool RegSetString(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ const QString& dataIn);

	static bool RegSetFloat(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ float dataIn);

	static bool RegSetDouble(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ double dataIn);

	static bool RegSetIn32(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ int32_t dataIn);

	static bool RegSetIn64(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ int64_t dataIn);

	static bool RegSetBinary(_In_ const HKEY& hKey,
		_In_ const QString& subKey,
		_In_ const QString& subKeyValue,
		_In_ const std::vector<byte>& dataIn);

};
