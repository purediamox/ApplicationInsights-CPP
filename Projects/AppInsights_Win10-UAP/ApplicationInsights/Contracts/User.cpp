#include "User.h"
#include "../../../src/core/common/Utils.hpp"
#include <collection.h>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace ApplicationInsights::CX;

User::User()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	if (values->HasKey("UserAcqDate") == false)
	{
		Platform::String^ acqDate = ref new Platform::String(ApplicationInsights::core::Utils::GetCurrentDateTime().c_str());
		values->Insert("UserAcqDate", dynamic_cast<PropertyValue^>(PropertyValue::CreateString(acqDate)));
	}

	if (values->HasKey("userId") == false)
	{
		Platform::String^ id = ref new Platform::String(ApplicationInsights::core::Utils::GenerateRandomUUID().c_str());
		values->Insert("userId", dynamic_cast<PropertyValue^>(PropertyValue::CreateString(id)));
	}
}

Platform::String^ User::AccountAcquisitionDate::get()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	bool hasKey = values->HasKey("UserAcqDate");
	if (hasKey)
	{
		String^ acqDate = safe_cast<String^>(values->Lookup("UserAcqDate"));
		return acqDate;
	}
	else
	{
		return nullptr;
	}
}

Platform::String^ User::Id::get()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	String^ userId = safe_cast<String^>(values->Lookup("userId"));
	if (userId != nullptr)
	{
		return userId;
	}
	else
	{
		return nullptr;
	}
}
