#include "Session.h"
#include "../common/Utils.hpp"

using namespace ApplicationInsights::core;

#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
#endif

Session::Session()
{
}

Session::~Session()
{
}

const Nullable<std::wstring>& Session::GetId()
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("SessionId"))
	{
		String^ sessionId = (String^)(values->Lookup("SessionId"));
		if (!sessionId)
		{
			m_id.ClearValue();
		}
		else
		{
			std::wstring sessionIdwstr(sessionId->Data());
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

void Session::SetId(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ id = ref new String(value.GetValue().c_str());
		values->Insert("SessionId", id);
	}
#endif
	m_id = value; 
}

const Nullable<std::wstring>& Session::GetIsFirst()
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("SessionIsFirst"))
	{
		String^ isFirst = (String^)(values->Lookup("SessionIsFirst"));
		if (!isFirst)
		{
			m_isFirst.ClearValue();
		}
		else
		{
			std::wstring isFirstWstr(isFirst->Data());
			m_isFirst.SetValue(isFirstWstr);
		}
	}
	else
	{
		m_isFirst.ClearValue();
	}
#endif
	return m_isFirst; 
}

void Session::SetIsFirst(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ isFirst = ref new String(value.GetValue().c_str());
		values->Insert("SessionIsFirst", isFirst);
	}
#endif
	m_isFirst = value; 
}

const Nullable<std::wstring>& Session::GetIsNew()
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();

	if (values->HasKey("SessionIsNew"))
	{
		String^ isNew = (String^)(values->Lookup("SessionIsNew"));
		if (!isNew)
		{
			m_isNew.ClearValue();
		}
		else
		{
			std::wstring isNewWstr(isNew->Data());
			m_isNew.SetValue(isNewWstr);
		}
	}
	else
	{
		m_isNew.ClearValue();
	}
#endif
	return m_isNew; 
}

void Session::SetIsNew(const Nullable<std::wstring>& value)
{ 
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
	auto values = Utils::GetLocalSettingsContainer();
	if (value.HasValue())
	{
		Platform::String^ isNew = ref new String(value.GetValue().c_str());
		values->Insert("SessionIsNew", isNew);
	}
#endif
	m_isNew = value; 
}

void Session::Serialize(Serializer& serializer) const
{
    if (m_id.HasValue())
    {
        serializer.WritePropertyName(L"ai.session.id");
        serializer.WriteStringValue(m_id.GetValue());
    }
    
    if (m_isFirst.HasValue())
    {
        serializer.WritePropertyName(L"ai.session.isFirst");
        serializer.WriteStringValue(m_isFirst.GetValue());
    }
    
    if (m_isNew.HasValue())
    {
        serializer.WritePropertyName(L"ai.session.isNew");
        serializer.WriteStringValue(m_isNew.GetValue());
    }
}

