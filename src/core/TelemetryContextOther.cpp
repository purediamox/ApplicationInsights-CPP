#include "TelemetryContext.h"
#ifndef WINAPI_FAMILY_PARTITION // Not Windows
#include "common/Utils.h"

#ifdef linux			// real linux
#include <sys/utsname.h>		// this is only available on real Posix OS
#endif

using namespace ApplicationInsights::core;

/// <summary>
/// Stores the context.
/// </summary>
/// <returns></returns>
TelemetryContext::TelemetryContext(const std::wstring& iKey) :
BaseTelemetryContext(iKey)
{
}

/// <summary>
/// Finalizes an instance of the <see cref=""/> class.
/// </summary>
/// <returns></returns>
TelemetryContext::~TelemetryContext()
{
}


// Helper function for converting values of char * to Nullable<std::wstring>
Nullable<std::wstring> GetNullableWString(const std::string& value)
{
	Nullable<std::wstring> ret;
	std::wstring str = Utils::ConvertToUtf16(value);
	wprintf(L"%ls\n", str.c_str());
	ret.SetValue(str);
	return ret;
}

/// <summary>
/// Initializes the device.
/// </summary>
void TelemetryContext::InitDevice()
{
	//Nullable<std::wstring> strDevId = L"TODO";
	//device.SetId(strDevId);
	//device.SetLanguage();
	//device.SetLocale();
	//device.SetMachineName();
	//device.SetModel();
	//device.SetNetwork();
	//device.SetOemName();
	Nullable<std::wstring> strType;
	strType.SetValue(L"Other");
	device.SetType(strType);

	std::string sysname = "sysname";   
	std::string release = "release";
	std::string machine = "machine";

#ifdef linux
	struct utsname uts;
	uname(&uts);
	sysname = uts.sysname;
	release = uts.release;
	machine = uts.machine;
#endif
	device.SetOsVersion(GetNullableWString(sysname + " " + release));
	device.SetType(GetNullableWString(machine));
	//device.SetOsVersion();
	//device.SetScreenResolution();

}

/// <summary>
/// Initializes the application.
/// </summary>
void TelemetryContext::InitApplication()
{
	//TODO
}

/// <summary>
/// Initializes the user.
/// </summary>
void TelemetryContext::InitUser()
{
	//TODO
}

/// <summary>
/// Initializes the session.
/// </summary>
void TelemetryContext::InitSession()
{
	//TODO
}

#endif