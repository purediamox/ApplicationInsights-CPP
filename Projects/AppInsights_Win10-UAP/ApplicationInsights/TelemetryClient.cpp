#include "TelemetryClient.h"
#include "../../../src/core/contracts/SessionStateData.h"
#include <collection.h>

using namespace ApplicationInsights::CX;
using namespace Platform;
using namespace Platform::Collections;

/// <summary>
/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
/// </summary>
/// <param name="iKey">The iKey.</param>
TelemetryClient::TelemetryClient(String^ iKey)
{
	std::wstring iKeyString = iKey->Data();
	m_tc = new ApplicationInsights::core::TelemetryClient(iKeyString);
	m_globalProperties = ref new Platform::Collections::Map<Platform::String^, Platform::String^>();
}

/// <summary>
/// Finalizes an instance of the <see cref="" /> class.
/// </summary>
/// <returns></returns>
TelemetryClient::~TelemetryClient()
{
	delete m_tc;
}

/// <summary>
/// Tracks the event.
/// </summary>
/// <param name="eventName">Name of the event.</param>
void TelemetryClient::TrackEvent(String^ eventName)
{
	m_tc->TrackEvent(eventName->Data());
}

/// <summary>
/// Tracks the event.
/// </summary>
/// <param name="eventName">Name of the event.</param>
/// <param name="properties">The properties.</param>
/// <param name="measurements">The measurements.</param>
void TelemetryClient::TrackEvent(Platform::String^ eventName,
	Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties,
	Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements)
{
	std::map<std::wstring, std::wstring> props;
	std::map<std::wstring, double> measures;

	ConvertPropertiesToStdMap(properties, props);
	ConvertMeasurementsToStdMap(measurements, measures);

	m_tc->TrackEvent(eventName->Data(), props, measures);
}

/// <summary>
/// Tracks the trace.
/// </summary>
/// <param name="message">The message.</param>
void TelemetryClient::TrackTrace(String^ message)
{
	m_tc->TrackTrace(message->Data());
}

/// <summary>
/// Tracks the trace.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="properties">The properties.</param>
void TelemetryClient::TrackTrace(Platform::String^ message,
	Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties)
{
	std::map<std::wstring, std::wstring> props;
	ConvertPropertiesToStdMap(properties, props);

	m_tc->TrackTrace(message->Data(), props);
}

/// <summary>
/// Tracks the metric.
/// </summary>
/// <param name="name">The name.</param>
/// <param name="value">The value.</param>
void TelemetryClient::TrackMetric(String^ name, double value)
{
	m_tc->TrackMetric(name->Data(), value);
}

/// <summary>
/// Tracks the metric.
/// </summary>
/// <param name="name">The name.</param>
/// <param name="value">The value.</param>
/// <param name="properties">The properties.</param>
void TelemetryClient::TrackMetric(Platform::String^ name, double value,
	Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties)
{
	std::map<std::wstring, std::wstring> props;
	ConvertPropertiesToStdMap(properties, props);

	m_tc->TrackMetric(name->Data(), value, props);
}

/// <summary>
/// Tracks the page view.
/// </summary>
/// <param name="pageName">Name of the page.</param>
void TelemetryClient::TrackPageView(String^ pageName)
{
	m_tc->TrackPageView(pageName->Data());
}

/// <summary>
/// Tracks the page view.
/// </summary>
/// <param name="pageName">Name of the page.</param>
/// <param name="properties">The properties.</param>
/// <param name="measurements">The measurements.</param>
void TelemetryClient::TrackPageView(Platform::String^ pageName,
	Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties,
	Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements)
{
	std::map<std::wstring, std::wstring> props;
	std::map<std::wstring, double> measures;

	ConvertPropertiesToStdMap(properties, props);
	ConvertMeasurementsToStdMap(measurements, measures);

	m_tc->TrackPageView(pageName->Data(), L"", props, measures);
}

/// <summary>
/// Tracks the page view.
/// </summary>
/// <param name="pageName">Name of the page.</param>
/// <param name="duration">The duration.</param>
void TelemetryClient::TrackPageView(String^ pageName, String^ duration)
{
	m_tc->TrackPageView(pageName->Data(), duration->Data());
}

/// <summary>
/// Tracks the page view.
/// </summary>
/// <param name="pageName">Name of the page.</param>
/// <param name="duration">The duration.</param>
/// <param name="properties">The properties.</param>
/// <param name="measurements">The measurements.</param>
void TelemetryClient::TrackPageView(Platform::String^ pageName, Platform::String^ duration,
	Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties,
	Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements)

{
	std::map<std::wstring, std::wstring> props;
	std::map<std::wstring, double> measures;

	ConvertPropertiesToStdMap(properties, props);
	ConvertMeasurementsToStdMap(measurements, measures);

	m_tc->TrackPageView(pageName->Data(), duration->Data(), props, measures);
}



/// <summary>
/// Tracks the session start.
/// </summary>
void TelemetryClient::TrackSessionStart()
{
	//Send start session
	m_tc->TrackSessionStart();
}

/// <summary>
/// Tracks the session end.
/// </summary>
void TelemetryClient::TrackSessionEnd()
{
	//Send end session
	m_tc->TrackSessionEnd();
}

/// <summary>
/// Renews the session.
/// </summary>
void TelemetryClient::RenewSession()
{
	//Send end session
	m_tc->TrackSessionEnd();

	m_tc->GetContext()->RenewSession();
}

/// <summary>
/// Flushes this queue.
/// </summary>
void TelemetryClient::Flush()
{
	m_tc->Flush();
}

/// <summary>
/// Disables all tracking.
/// </summary>
void TelemetryClient::DisableTracking()
{
	m_tc->DisableTracking();
}

/// <summary>
/// Enables all tracking.
/// </summary>
void TelemetryClient::EnableTracking()
{
	m_tc->EnableTracking();
}

/// <summary>
/// Gets the global properties.
/// </summary>
Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ TelemetryClient::GetGlobalProperties()
{
	return m_globalProperties;
}

/// <summary>
/// Converts the properties to standard map.
/// </summary>
/// <param name="properties">The properties.</param>
/// <param name="props">The props.</param>
void TelemetryClient::ConvertPropertiesToStdMap(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties, std::map<std::wstring, std::wstring> &props)
{
	if (m_globalProperties->Size > 0)
	{
		for (auto globalPropPair : m_globalProperties)
		{
			props[globalPropPair->Key->Data()] = globalPropPair->Value->Data();
		}
	}

	if (properties->Size > 0)
	{
		for (auto propPair : properties)
		{
			props[propPair->Key->Data()] = propPair->Value->Data();
		}
	}
}

/// <summary>
/// Converts the measurements to standard map.
/// </summary>
/// <param name="measurements">The measurements.</param>
/// <param name="measures">The measures.</param>
void TelemetryClient::ConvertMeasurementsToStdMap(Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements, std::map<std::wstring, double> &measures)
{
	if (measurements->Size > 0)
	{
		for (auto measurePair : measurements)
		{
			measures[measurePair->Key->Data()] = measurePair->Value;
		}
	}
}


