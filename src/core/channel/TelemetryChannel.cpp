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
}

/// <summary>
/// Finalizes an instance of the <see cref="TelemetryChannel"/> class.
/// </summary>
TelemetryChannel::~TelemetryChannel()
{
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