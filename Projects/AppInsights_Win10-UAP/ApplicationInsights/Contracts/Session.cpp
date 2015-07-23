#include "Session.h"
#include "../../../src/core/common/Utils.hpp"
#include <collection.h>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace ApplicationInsights::CX;

Session::Session()
{
	Id = ref new String(ApplicationInsights::core::Utils::GenerateRandomUUID().c_str());
	IsNew = L"True";
	IsFirst = L"True";
}

Platform::String^ Session::Id::get()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();

	if (values->HasKey("SessionId"))
	{
		String^ id = (String^)(values->Lookup("SessionId"));
		return id;
	}
	return nullptr;
}

void Session::Id::set(Platform::String^ value)
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	if (value != nullptr)
	{
		values->Insert("SessionId", value);
	}
}

Platform::String^ Session::IsFirst::get()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();

	if (values->HasKey("SessionIsFirst"))
	{
		String^ isFirst = (String^)(values->Lookup("SessionIsFirst"));
		return isFirst;
	}
	return nullptr;
}

void Session::IsFirst::set(Platform::String^ value)
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	if (value != nullptr)
	{
		values->Insert("SessionIsFirst", value);
	}
}

Platform::String^ Session::IsNew::get()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();

	if (values->HasKey("SessionIsNew"))
	{
		String^ isNew = (String^)(values->Lookup("SessionIsNew"));
		return isNew;
	}
	return nullptr;
}

void Session::IsNew::set(Platform::String^ value)
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	if (value != nullptr)
	{
		values->Insert("SessionIsNew", value);
	}
}