#include "TelemetryContext.h"
#include "../../../src/core/common/Utils.hpp"
#include <collection.h>

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Globalization;
using namespace Windows::Graphics::Display;
using namespace Windows::Networking::Connectivity;
using namespace Windows::Security::Cryptography;
using namespace Windows::Security::Cryptography::Core;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::System::Profile;
using namespace ApplicationInsights::CX;

/// <summary>
/// Initializes a new instance of the <see cref="TelemetryContext"/> class.
/// </summary>
TelemetryContext::TelemetryContext()
{
	m_user = ref new User();
	m_device = ref new Device();
	m_app = ref new Application();
	m_session = ref new Session();
}

/// <summary>
/// Initializes the context.
/// </summary>
void TelemetryContext::InitContext()
{
	InitUser();
	InitDevice();
	InitApplication();
	InitSession();
}

/// <summary>
/// Initializes the user.
/// </summary>
void TelemetryContext::InitUser()
{

}

/// <summary>
/// Initializes the device.
/// </summary>
void TelemetryContext::InitDevice()
{
	HardwareToken^ packageSpecificToken = HardwareIdentification::GetPackageSpecificToken(nullptr);
	IBuffer^ hardwareId = packageSpecificToken->Id;
	HashAlgorithmProvider^ algProv = HashAlgorithmProvider::OpenAlgorithm(HashAlgorithmNames::Sha256);
	IBuffer^ hardwareIdHashed = algProv->HashData(hardwareId);
	Array<unsigned char>^ buffer = ref new Array<unsigned char>(hardwareIdHashed->Length);
	CryptographicBuffer::CopyToByteArray(hardwareIdHashed, &buffer);
	std::wstring strDevId = L"";

	for (int i = 0; i < (int)hardwareIdHashed->Length; i++)
	{
		wchar_t hex[10];
		swprintf_s(hex, 10, L"%02X", buffer[i]);
		strDevId += hex;
	}
	m_device->Id = ref new String(strDevId.c_str());

	m_device->Language = Language::CurrentInputMethodLanguageTag;

	GeographicRegion geographicRegion;
	m_device->Locale = geographicRegion.DisplayName;

	ConnectionProfile^ connectionProfile = NetworkInformation::GetInternetConnectionProfile();
	m_device->Network = connectionProfile->ProfileName;

	m_device->Os = L"Windows";

	m_device->Type = L"Store";
}

/// <summary>
/// Initializes the application.
/// </summary>
void TelemetryContext::InitApplication()
{
	PackageId^ appId = Package::Current->Id;
	PackageVersion version = appId->Version;
	wchar_t strVerNumber[256];
	swprintf_s(strVerNumber, 256, L"%d.%d.%d.%d", version.Build, version.Major, version.Minor, version.Revision);
	String^ ver = appId->Name + " (" + ref new String(strVerNumber) + ")";

	m_app->Ver = ver;
}

/// <summary>
/// Initializes the session.
/// </summary>
void TelemetryContext::InitSession()
{
}

/// <summary>
/// Renews the session.
/// </summary>
void TelemetryContext::RenewSession()
{
	m_session->Id = ref new String(ApplicationInsights::core::Utils::GenerateRandomUUID().c_str());

	m_session->IsFirst = L"True";
	m_session->IsNew = L"True";
}

/// <summary>
/// Gets the context tags.
/// </summary>
void TelemetryContext::GetContextTags(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ tags)
{
	tags->Insert(L"ai.user.accountAcquisitionDate", m_user->AccountAcquisitionDate);
	tags->Insert(L"ai.user.accountId", m_user->AccountId);
	tags->Insert(L"ai.user.userAgent", m_user->UserAgent);
	tags->Insert(L"ai.user.id", m_user->Id);

	tags->Insert(L"ai.device.id", m_device->Id);
	tags->Insert(L"ai.device.ip", m_device->Ip);
	tags->Insert(L"ai.device.language", m_device->Language);
	tags->Insert(L"ai.device.locale", m_device->Locale);
	tags->Insert(L"ai.device.model", m_device->Model);
	tags->Insert(L"ai.device.network", m_device->Network);
	tags->Insert(L"ai.device.oemName", m_device->OemName);
	tags->Insert(L"ai.device.os", m_device->Os);
	tags->Insert(L"ai.device.osVersion", m_device->OsVersion);
	tags->Insert(L"ai.device.roleInstance", m_device->RoleInstance);
	tags->Insert(L"ai.device.roleName", m_device->RoleName);
	tags->Insert(L"ai.device.screenResolution", m_device->ScreenResolution);
	tags->Insert(L"ai.device.type", m_device->Type);
	tags->Insert(L"ai.device.machineName", m_device->MachineName);

	tags->Insert(L"ai.application.ver", m_app->Ver);

	tags->Insert(L"ai.session.id", m_session->Id);
	tags->Insert(L"ai.session.isFirst", m_session->IsFirst);
	tags->Insert(L"ai.session.isNew", m_session->IsNew);
}