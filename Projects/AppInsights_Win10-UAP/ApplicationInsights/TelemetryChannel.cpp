#include "TelemetryChannel.h"
#include "../../../src/core/common/utils.hpp"
#include <stdlib.h> 
#include <time.h>
#include <collection.h>
#include "Windows.h"

using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace ApplicationInsights::CX;
using namespace Platform;
using namespace Platform::Collections;

const int DEFAULT_BUFFER_SIZE = 100;
TelemetryChannel::TelemetryChannel()
{
	srand((int)time(0));
	m_channelId = rand();
	m_seqNum = 0;
	m_maxBufferSize = DEFAULT_BUFFER_SIZE;
	m_buffer = ref new Platform::Collections::Vector<Platform::String^>();
	InitializeCriticalSectionEx(&cs, 0, 0);
}

/// <summary>
/// Finalizes an instance of the <see cref="TelemetryChannel"/> class.
/// </summary>
TelemetryChannel::~TelemetryChannel()
{
	DeleteCriticalSection(&cs);
}

int TelemetryChannel::incrementSeqenceNum()
{
	EnterCriticalSection(&cs);
	int currentNum = m_seqNum;
	m_seqNum++;
	LeaveCriticalSection(&cs);
	return currentNum;
}

/// <summary>
/// Enqueues the specified context.
/// </summary>
/// <param name="telemetryJson">The json represenation of the telemetry.</param>
void TelemetryChannel::Enqueue(Platform::String^ telemetryJson)
{
	EnterCriticalSection(&cs);
	m_buffer->Append(telemetryJson);
	if ((int)m_buffer->Size >= m_maxBufferSize)
	{
		Save();
	}
	LeaveCriticalSection(&cs);
}

/// <summary>
/// Saves all data to local storage. Data will wait to be picked up by the next send event.
/// </summary>
void Save()
{
	m_persist.Save();
}

