#include "User.h"
#include "../common/Utils.hpp"

using namespace ApplicationInsights::core;

#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
#endif

User::User()
{
}

User::~User()
{
}

const Nullable<std::wstring>& User::GetAccountAcquisitionDate()
{
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("UserAcqDate"))
	{
		String^ sessionId = safe_cast<String^>(values->Lookup("UserAcqDate"));
		if (!sessionId)
		{
			m_accountAcquisitionDate.ClearValue();
		}
		else
		{
			std::wstring sessionIdwstr(sessionId->Data());
			m_accountAcquisitionDate.SetValue(sessionIdwstr);
		}
	}
	else
	{
		m_accountAcquisitionDate.ClearValue();
	}
#endif
	return m_accountAcquisitionDate; 
}

void User::SetAccountAcquisitionDate(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ acqDate = ref new String(value.GetValue().c_str());
		values->Insert("UserAcqDate", acqDate);
	}
#endif
	m_accountAcquisitionDate = value; 
}

const Nullable<std::wstring>& User::GetAccountId()
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("UserAcctId"))
	{
		String^ acctId = safe_cast<String^>(values->Lookup("UserAcctId"));
		if (!acctId)
		{
			m_accountId.ClearValue();
		}
		else
		{
			std::wstring sessionIdwstr(acctId->Data());
			m_accountId.SetValue(sessionIdwstr);
		}
	}
	else
	{
		m_accountId.ClearValue();
	}
#endif
	return m_accountId; 
}

void User::SetAccountId(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ acctId = ref new String(value.GetValue().c_str());
		values->Insert("UserAcctId", acctId);
	}
#endif
	m_accountId = value; 
}

const Nullable<std::wstring>& User::GetUserAgent()
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("UserAgent"))
	{
		String^ agent = safe_cast<String^>(values->Lookup("UserAgent"));
		if (!agent)
		{
			m_userAgent.ClearValue();
		}
		else
		{
			std::wstring sessionIdwstr(agent->Data());
			m_userAgent.SetValue(sessionIdwstr);
		}
	}
	else
	{
		m_userAgent.ClearValue();
	}
#endif
	return m_userAgent; 
}

void User::SetUserAgent(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ agent = ref new String(value.GetValue().c_str());
		values->Insert("UserAgent", agent);
	}
#endif
	m_userAgent = value; 
}

const Nullable<std::wstring>& User::GetId()
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("UserId"))
	{
		String^ id = safe_cast<String^>(values->Lookup("UserId"));
		if (!id)
		{
			m_id.ClearValue();
		}
		else
		{
			std::wstring sessionIdwstr(id->Data());
			m_id.SetValue(sessionIdwstr);
		}		
	}
	else
	{
		m_id.ClearValue();
	}
#endif
	return m_id;
}

void User::SetId(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ id = ref new String(value.GetValue().c_str());
		values->Insert("UserId", id);
	}
#endif
	m_id = value; 
}

const Nullable<std::wstring>& User::GetStoreRegion()
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("UserStoreRegion"))
	{
		String^ storeRegion = safe_cast<String^>(values->Lookup("UserStoreRegion"));
		if (!storeRegion)
		{
			m_storeRegion.ClearValue();
		}
		else
		{
			std::wstring sessionIdwstr(storeRegion->Data());
			m_storeRegion.SetValue(sessionIdwstr);
		}
	}
	else
	{
		m_storeRegion.ClearValue();
	}
#endif
	return m_storeRegion; 
}

void User::SetStoreRegion(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ storeRegion = ref new String(value.GetValue().c_str());
		values->Insert("UserStoreRegion", storeRegion);
	}
#endif
	m_storeRegion = value; 
}

void User::Serialize(Serializer& serializer) const
{
    if (m_accountAcquisitionDate.HasValue())
    {
        serializer.WritePropertyName(L"ai.user.accountAcquisitionDate");
        serializer.WriteStringValue(m_accountAcquisitionDate.GetValue());
    }
    
    if (m_accountId.HasValue())
    {
        serializer.WritePropertyName(L"ai.user.accountId");
        serializer.WriteStringValue(m_accountId.GetValue());
    }
    
    if (m_userAgent.HasValue())
    {
        serializer.WritePropertyName(L"ai.user.userAgent");
        serializer.WriteStringValue(m_userAgent.GetValue());
    }
    
    if (m_id.HasValue())
    {
        serializer.WritePropertyName(L"ai.user.id");
        serializer.WriteStringValue(m_id.GetValue());
    }
    
    if (m_storeRegion.HasValue())
    {
        serializer.WritePropertyName(L"ai.user.storeRegion");
        serializer.WriteStringValue(m_storeRegion.GetValue());
    }
}

