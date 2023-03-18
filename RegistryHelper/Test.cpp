#include "RegistryHelper.h"
#include <format>

#ifdef  UNICODE
#define PrintOutResult(X, Y) Y == true ? \
 std::wcout << std::format(L"Function {}: PASS", X) << std::endl : std::wcout << std::format(L"Function {}: FAIL", X) << std::endl
#else
#define PrintOutResult(X, Y) Y == true ? \
 std::cout << std::format("Function {}: PASS", X) << std::endl : std::cout << std::format("Function {}: FAIL", X) << std::endl
#endif

namespace Test
{
	HKEY k = HKEY_CURRENT_USER;

#ifdef UNICODE
	QString subKey = L"SOFTWARE\\QTT";
#else
	QString subKey = "SOFTWARE\\QTT";
#endif

	extern void GetSetString()
	{
		bool result = true;

#ifdef UNICODE
		const QString subKeyValue = L"GetSetString";
		const QString defaultValue = L"none";
		const QString dataIn = L"ABCDEGH";
		QString dataOut = L"";
#else
		const QString subKeyValue = "GetSetString";
		const QString defaultValue = "none";
		const QString dataIn = "ABCDEGH";
		QString dataOut = "";
#endif

		auto r = RegistryHeper::RegSetString(k, subKey, subKeyValue, dataIn);
		if (!r) result = false;

		r = RegistryHeper::RegGetString(k, subKey, subKeyValue, defaultValue, dataOut);
		if (!r) result = false;

		if (dataOut != dataIn) result = false;

		PrintOutResult(subKeyValue, result);
	}

	extern void GetSetFloat()
	{
		bool result = true;

#ifdef UNICODE
		QString subKeyValue = L"GetSetFloat";
#else
		QString subKeyValue = "GetSetFloat";
#endif
		constexpr float dataIn = std::numeric_limits<float>::max();

		auto r = RegistryHeper::RegSetFloat(k, subKey, subKeyValue, dataIn);
		if (!r) result = false;

		const float defaultValue = 10.2;
		float dataOut;

		r = RegistryHeper::RegGetFloat(k, subKey, subKeyValue, defaultValue, dataOut);
		if (!r) result = false;

		if (dataOut != dataIn) result = false;

		PrintOutResult(subKeyValue, result);
	}

	extern void GetSetDouble()
	{
		bool result = true;

#ifdef UNICODE
		QString subKeyValue = L"GetSetDouble";
#else
		QString subKeyValue = "GetSetDouble";
#endif
		constexpr double dataIn = std::numeric_limits<double>::max();
		auto r = RegistryHeper::RegSetDouble(k, subKey, subKeyValue, dataIn);
		if (!r) result = false;

		const double defaultValue = 10.2;
		double dataOut;

		r = RegistryHeper::RegGetDouble(k, subKey, subKeyValue, defaultValue, dataOut);
		if (!r) result = false;

		if (dataOut != dataIn) result =  false;

		PrintOutResult(subKeyValue, result);
	}

	extern void GetSetInt32()
	{
		bool result = true;

#ifdef UNICODE
		QString subKeyValue = L"GetSetInt32";
#else
		QString subKeyValue = "GetSetInt32";
#endif
		constexpr int32_t dataIn = std::numeric_limits<int32_t>::max();
		auto r = RegistryHeper::RegSetIn32(k, subKey, subKeyValue, dataIn);
		if (!r) result = false;

		const int32_t defaultValue = 1000;
		int32_t dataOut;

		r = RegistryHeper::RegGetInt32(k, subKey, subKeyValue, defaultValue, dataOut);
		if (!r) result = false;

		if (dataOut != dataIn) result = false;

		PrintOutResult(subKeyValue, result);
	}

	extern void GetSetInt64()
	{
		bool result = true;

#ifdef UNICODE
		QString subKeyValue = L"GetSetInt64";
#else
		QString subKeyValue = "GetSetInt64";
#endif

		constexpr int64_t dataIn = std::numeric_limits<int64_t>::max();
		auto r = RegistryHeper::RegSetIn64(k, subKey, subKeyValue, dataIn);
		if (!r) result = false;

		const int64_t defaultValue = 1000;
		int64_t dataOut;

		r = RegistryHeper::RegGetInt64(k, subKey, subKeyValue, defaultValue, dataOut);
		if (!r) result = false;

		if (dataOut != dataIn) result = false;

		PrintOutResult(subKeyValue, result);
	}

	extern void GetSetBinary()
	{
		bool result = true;

#ifdef UNICODE
		QString subKeyValue = L"GetSetBinary";
#else
		QString subKeyValue = "GetSetBinary";
#endif
		const std::vector<byte> dataIn{ 0x0A, 0x1F, 0xFF };
		auto r = RegistryHeper::RegSetBinary(k, subKey, subKeyValue, dataIn);
		if (!r) result = false;

		const std::vector<byte> defaultValue{0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		std::vector<byte> dataOut;

		r = RegistryHeper::RegGetBinary(k, subKey, subKeyValue, defaultValue, dataOut);
		if (!r) result = false;

		if (dataOut != dataIn) result = false;

		PrintOutResult(subKeyValue, result);
	}
}