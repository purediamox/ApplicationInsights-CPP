#include "TelemetryChannel.h"
#include "../TelemetryContext.h"
#include "../Contracts/Contracts.h"
#include "../Common/Utils.hpp"
#include "../Common/StringWriter.hpp"
#include "../Common/JsonWriter.hpp"
#include <stdlib.h> 
#include <time.h>
#include <locale>
#include <codecvt>
using namespace ApplicationInsights::core;

#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
#include <TraceLoggingProvider.h>  
#include <TraceLoggingActivity.h>  

#ifdef __cplusplus  
extern "C" {
#endif  
	TRACELOGGING_DECLARE_PROVIDER(g_hAppInsightsProvider);
#ifdef __cplusplus  
}
#endif  

#define TraceLoggingOptionMicrosoftTelemetry() \
TraceLoggingOptionGroup(0x4f50731a, 0x89cf, 0x4782, 0xb3, 0xe0, 0xdc, 0xe8, 0xc9, 0x4, 0x76, 0xba)

#define MICROSOFT_KEYWORD_TELEMETRY     0x0000200000000000 

TRACELOGGING_DEFINE_PROVIDER(
	g_hAppInsightsProvider,
	"ApplicationInsightsProvider",
	(0x1FFB0DCF, 0x15A6, 0x42FA, 0x83, 0x9B, 0x1F, 0xB1, 0x83, 0xAF, 0x7B, 0x0A),// {1FFB0DCF-15A6-42FA-839B-1FB183AF7B0A}
	TraceLoggingOptionMicrosoftTelemetry());

#endif

TelemetryChannel* TelemetryChannel::instance = nullptr;
const int MAX_BUFFER_SIZE = 50;

/// <summary>
/// Initializes this instance.
/// </summary>
/// <returns></returns>
TelemetryChannel* TelemetryChannel::Initialize()
{
	if (instance == nullptr)
	{
		instance = new TelemetryChannel();
	}
	return instance;
}

/// <summary>
/// Gets the instance.
/// </summary>
/// <returns></returns>
TelemetryChannel* TelemetryChannel::GetInstance()
{
	return instance;
}

/// <summary>
/// Initializes a new instance of the <see cref="TelemetryChannel"/> class.
/// </summary>
/// <param name="config">The configuration.</param>
TelemetryChannel::TelemetryChannel()
{
	srand((int)time(0));
	m_channelId = rand();
	m_seqNum = 0;
	m_maxBufferSize = MAX_BUFFER_SIZE;
	
	InitializeCriticalSectionEx(&cs, 0, 0);
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
	hRespRecv = CreateEventEx(nullptr, L"RecvResp", 0, EVENT_MODIFY_STATE | SYNCHRONIZE);

	HRESULT hResult = TraceLoggingRegister(g_hAppInsightsProvider);
#endif
}

/// <summary>
/// Finalizes an instance of the <see cref="TelemetryChannel"/> class.
/// </summary>
TelemetryChannel::~TelemetryChannel()
{
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
	TraceLoggingUnregister(g_hAppInsightsProvider);
#endif
	DeleteCriticalSection(&cs);
}

/// <summary>
/// Enqueues the specified context.
/// </summary>
/// <param name="context">The context.</param>
/// <param name="telemetry">The telemetry.</param>
void TelemetryChannel::Enqueue(std::wstring &iKey, TelemetryContext &context, Domain &telemetry)
{
	Data data;
	data.SetBaseData(telemetry);
	data.SetBaseType(telemetry.GetBaseType());

	std::wstring buffer;
	StringWriter content(&buffer);
	JsonWriter json(content);

#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
	//if (TraceLoggingProviderEnabled(g_hAppInsightsProvider, 0, 0))
	if(false)
	{
		//Assumption: UTC is available
		json.WriteObjectValue(&data);
		auto partB = content.ToString();
		TraceLoggingWrite(
			g_hAppInsightsProvider, 
			"Part B data",
			TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY),
			TraceLoggingWideString(partB.c_str()));
	}
	else
	{
#endif
		EnterCriticalSection(&cs);

		Envelope envelope;
		envelope.SetData(data);
		envelope.SetIKey(iKey);
		envelope.SetTime(Utils::GetCurrentDateTime());
		envelope.SetName(telemetry.GetEnvelopeName());
		envelope.SetSeq(std::to_wstring(m_channelId) + L":" + std::to_wstring(m_seqNum++));

		wstring_wstring_map tags;
		context.GetContextTags(tags);
		envelope.SetTags(tags);

		json.WriteObjectValue(&envelope);

		m_buffer.push_back(content.ToString());
		
		if (context.GetSession().GetIsNew().HasValue() && context.GetSession().GetIsNew().GetValue() == L"True")
		{
			Nullable<std::wstring> strFalse = std::wstring(L"False");
			context.GetSession().SetIsFirst(strFalse);
			context.GetSession().SetIsNew(strFalse);
		}
		
		LeaveCriticalSection(&cs);

		if ((int)m_buffer.size() >= m_maxBufferSize)
		{
			Send();
		}
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
	}
#endif
}

/// <summary>
/// Sends this instance.
/// </summary>
void TelemetryChannel::Send()
{
	
	if (m_buffer.size() > 0)
	{
		EnterCriticalSection(&cs);
		std::wstring buffer;
		std::vector<std::wstring> sendBuffer;

		buffer += L"[";
		for (auto &buf : m_buffer) {
			buffer += buf + L",";
			sendBuffer.push_back(buffer);
		}
		buffer += L"]";

		m_buffer.clear();
		LeaveCriticalSection(&cs);
		m_persist.save(buffer);
	}
}

void TelemetryChannel::InitializePersistance(PERSISTCONFIG &config)
{
	m_persist.Initialize(&config);
}

Persistence* TelemetryChannel::GetPersistance()
{
	return &m_persist;
}