#include "RegistryHelper.h"

bool RegistryHeper::RegGetString(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ const QString& defaultValue,
	_Out_ QString& dataOut)
{
	//Assume default value
	dataOut = defaultValue;

	//Find out the size of buffer
	DWORD dataSize = 0;
	auto retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_SZ,
		NULL,
		NULL,
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	if (!(dataSize > 0)) return false;

	QString result;
	result.resize(dataSize);

	retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		result.data(),
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	dataOut = result;
	//Remove null character
	dataOut.erase(std::find(dataOut.begin(), dataOut.end(), '\0'), dataOut.end());

	return true;
}

bool RegistryHeper::RegGetFloat(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ float defaultValue,
	_Out_ float& dataOut)
{
	//Assume default value
	dataOut = defaultValue;

	//Find out the size of buffer
	DWORD dataSize = 0;
	auto retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_SZ,
		NULL,
		NULL,
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	if (!(dataSize > 0)) return false;

	QString result;
	result.resize(dataSize);

	retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		result.data(),
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	float num = 0;

	try
	{
		//Remove null character
		result.erase(std::find(result.begin(), result.end(), '\0'), result.end());

		num = std::move(std::stof(result));
	}
	catch (std::exception ex)
	{
		return false;
	}

	dataOut = num;

	return true;
}

bool RegistryHeper::RegGetDouble(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ double defaultValue,
	_Out_ double& dataOut)
{
	//Assume default value
	dataOut = defaultValue;

	//Find out the size of buffer
	DWORD dataSize = 0;
	auto retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_SZ,
		NULL,
		NULL,
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	if (!(dataSize > 0)) return false;

	QString result;
	result.resize(dataSize);

	retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		result.data(),
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	double num = 0;

	try
	{
		//Remove null character
		result.erase(std::find(result.begin(), result.end(), '\0'), result.end());

		num = std::move(std::stod(result));
	}
	catch (std::exception ex)
	{
		return false;
	}

	dataOut = num;

	return true;
}

bool RegistryHeper::RegGetInt32(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ int32_t defaultValue,
	_Out_ int32_t& dataOut)
{
	//Assume default value
	dataOut = defaultValue;

	int32_t result = 0;
	DWORD dataSize = sizeof(result);

	auto retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_DWORD,
		nullptr,
		&result,
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;


	dataOut = result;

	return true;
}

bool RegistryHeper::RegGetInt64(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ int64_t defaultValue,
	_Out_ int64_t& dataOut)
{
	//Assume default value
	dataOut = defaultValue;

	int64_t result = 0;
	DWORD dataSize = sizeof(result);

	auto retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_QWORD,
		nullptr,
		&result,
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	dataOut = result;

	return true;
}

//_Success_(return == true)
bool RegistryHeper::RegGetBinary(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ const std::vector<byte>& defaultValue,
	_Out_ std::vector<byte>& dataOut)
{
	//Assume default value
	dataOut = defaultValue;

	//Find out the size of buffer
	DWORD dataSize = 0;
	LONG retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_BINARY,
		NULL,
		NULL,
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	if (!(dataSize > 0)) return false;


	dataOut.resize(dataSize);

	retCode = ::RegGetValue(
		hKey,
		subKey.c_str(),
		subKeyValue.c_str(),
		RRF_RT_REG_BINARY,
		NULL,
		dataOut.data(),
		&dataSize);

	if (retCode != ERROR_SUCCESS) return false;

	return true;
}

bool RegistryHeper::RegSetString(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ const QString& dataIn)
{

	bool result = false;
	HKEY inspectionKey = nullptr;
	DWORD disposition;


	DWORD size = (dataIn.size()) * (sizeof(QString::traits_type::char_type));

	__try
	{

		//If not exist, will create
		//If existed, just open
		auto retCode = RegCreateKeyEx(hKey,
			subKey.c_str(),
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,
			&inspectionKey,
			&disposition);

		if (retCode != ERROR_SUCCESS)
			__leave;


		retCode = RegSetValueEx(inspectionKey,
			subKeyValue.c_str(),
			0,
			REG_SZ,
			reinterpret_cast<const BYTE*>(dataIn.c_str()),
			size);

		if (retCode != ERROR_SUCCESS)
			__leave;

		result = true;
	}
	__finally
	{
		RegCloseKey(inspectionKey);
	}

	return result;
}

bool RegistryHeper::RegSetFloat(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ float dataIn)
{
	bool result = false;
	HKEY inspectionKey = nullptr;
	DWORD disposition;
	QString strData;

	try
	{
		strData = ConvertToString(dataIn);

	}
	catch (std::exception ex)
	{
		return result;
	}

	DWORD size = (strData.size()) * (sizeof(QString::traits_type::char_type));

	//If not exist, will create
	//If existed, just open
	auto retCode = RegCreateKeyEx(hKey,
		subKey.c_str(),
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&inspectionKey,
		&disposition);

	if (retCode != ERROR_SUCCESS)
	{
		RegCloseKey(inspectionKey);
		return result;
	}

	retCode = RegSetValueEx(inspectionKey,
		subKeyValue.c_str(),
		0,
		REG_SZ,
		reinterpret_cast<const BYTE*>(strData.c_str()),
		size);

	if (retCode != ERROR_SUCCESS)
	{
		RegCloseKey(inspectionKey);
		return result;
	}


	result = true;
	RegCloseKey(inspectionKey);

	return result;
}

bool RegistryHeper::RegSetDouble(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ double dataIn)
{
	bool result = false;
	HKEY inspectionKey = nullptr;
	DWORD disposition;

	//Convert to string type
	QString strData;

	try
	{
		strData = ConvertToString(dataIn);
	}
	catch (std::exception ex)
	{
		return result;
	}

	DWORD size = (strData.size()) * (sizeof(QString::traits_type::char_type));

	//If not exist, will create
	//If existed, just open
	auto retCode = RegCreateKeyEx(hKey,
		subKey.c_str(),
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&inspectionKey,
		&disposition);

	if (retCode != ERROR_SUCCESS)
	{
		RegCloseKey(inspectionKey);
		return result;
	}

	retCode = RegSetValueEx(inspectionKey,
		subKeyValue.c_str(),
		0,
		REG_SZ,
		reinterpret_cast<const BYTE*>(strData.c_str()),
		size);

	if (retCode != ERROR_SUCCESS)
	{
		RegCloseKey(inspectionKey);
		return result;
	}

	result = true;
	RegCloseKey(inspectionKey);

	return result;
}

bool RegistryHeper::RegSetIn32(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ int32_t dataIn)
{
	bool result = false;
	HKEY inspectionKey = nullptr;
	DWORD disposition;

	__try
	{

		//If not exist, will create
		//If existed, just open
		auto retCode = RegCreateKeyEx(hKey,
			subKey.c_str(),
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,
			&inspectionKey,
			&disposition);

		if (retCode != ERROR_SUCCESS)
			__leave;

		retCode = RegSetValueEx(inspectionKey,
			subKeyValue.c_str(),
			0,
			REG_DWORD,
			reinterpret_cast<const BYTE*>(&dataIn),
			sizeof(dataIn));

		if (retCode != ERROR_SUCCESS)
			__leave;

		result = true;
	}
	__finally
	{
		RegCloseKey(inspectionKey);
	}

	return result;
}

bool RegistryHeper::RegSetIn64(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ int64_t dataIn)
{
	bool result = false;
	HKEY inspectionKey = nullptr;
	DWORD disposition;

	__try
	{

		//If not exist, will create
		//If existed, just open
		auto retCode = RegCreateKeyEx(hKey,
			subKey.c_str(),
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,
			&inspectionKey,
			&disposition);

		if (retCode != ERROR_SUCCESS)
			__leave;

		retCode = RegSetValueEx(inspectionKey,
			subKeyValue.c_str(),
			0,
			REG_QWORD,
			reinterpret_cast<const BYTE*>(&dataIn),
			sizeof(dataIn));

		if (retCode != ERROR_SUCCESS)
			__leave;

		result = true;
	}
	__finally
	{
		RegCloseKey(inspectionKey);
	}

	return result;
}

bool RegistryHeper::RegSetBinary(_In_ const HKEY& hKey,
	_In_ const QString& subKey,
	_In_ const QString& subKeyValue,
	_In_ const std::vector<byte>& dataIn)
{
	bool result = false;
	HKEY inspectionKey = nullptr;
	DWORD disposition;

	__try
	{
		//If not exist, will create
		//If existed, just open
		auto retCode = RegCreateKeyEx(hKey,
			subKey.c_str(),
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,
			&inspectionKey,
			&disposition);

		if (retCode != ERROR_SUCCESS)
			__leave;

		retCode = RegSetValueEx(inspectionKey,
			subKeyValue.c_str(),
			0,
			REG_BINARY,
			dataIn.data(),
			dataIn.size());

		if (retCode != ERROR_SUCCESS)
			__leave;

		result = true;
	}
	__finally
	{
		RegCloseKey(inspectionKey);
	}

	return result;

}

