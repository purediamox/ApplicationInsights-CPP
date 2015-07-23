#include "TelemetryClient.h"
#include "../../../src/core/contracts/Contracts.h"
#include "../../../src/core/common/utils.hpp"

#include <collection.h>
#include "Windows.h"

using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace ApplicationInsights::CX;
using namespace Platform;
using namespace Platform::Collections;

/// <summary>
/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
/// </summary>
/// <param name="iKey">The iKey.</param>
TelemetryClient::TelemetryClient(String^ iKey)
{
	m_iKey = iKey;
	m_globalProperties = ref new Platform::Collections::Map<Platform::String^, Platform::String^>();
	m_context = ref new TelemetryContext();
	m_context->InitContext();
}

/// <summary>
/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
/// </summary>
/// <param name="context">The context.</param>
/// <param name="iKey">The iKey.</param>
TelemetryClient::TelemetryClient(TelemetryContext^ context, String^ iKey)
{
	m_iKey = iKey;
	m_globalProperties = ref new Platform::Collections::Map<Platform::String^, Platform::String^>();
	if (context == nullptr)
	{
		m_context = ref new TelemetryContext();
	}
	else
	{
		m_context = context;
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="" /> class.
/// </summary>
/// <returns></returns>
TelemetryClient::~TelemetryClient()
{
}

/// <summary>
/// Tracks the event.
/// </summary>
/// <param name="eventName">Name of the event.</param>
void TelemetryClient::TrackEvent(String^ eventName)
{
	TrackEvent(eventName, nullptr, nullptr);
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

	ApplicationInsights::core::EventData telemetry;
	telemetry.SetName(eventName->Data());
	if (props.size() > 0)
	{
		telemetry.SetProperties(props);
	}
	if (measures.size() > 0)
	{
		telemetry.SetMeasurements(measures);
	}

	Track(telemetry);
}

/// <summary>
/// Tracks the trace.
/// </summary>
/// <param name="message">The message.</param>
void TelemetryClient::TrackTrace(String^ message)
{
	TrackTrace(message, nullptr);
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

	ApplicationInsights::core::MessageData telemetry;
	telemetry.SetMessage(message->Data());
	if (props.size() > 0)
	{
		telemetry.SetProperties(props);
	}

	Track(telemetry);
}

/// <summary>
/// Tracks the metric.
/// </summary>
/// <param name="name">The name.</param>
/// <param name="value">The value.</param>
void TelemetryClient::TrackMetric(String^ name, double value)
{
	TrackMetric(name, value, nullptr);
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

	ApplicationInsights::core::MetricData telemetry;
	ApplicationInsights::core::DataPoint data;
	data.SetCount(1);
	data.SetKind(ApplicationInsights::core::Measurement);
	data.SetMax(value);
	data.SetMax(value);
	data.SetName(name->Data());
	data.SetValue(value);
	std::vector<ApplicationInsights::core::DataPoint*> metricsList;
	metricsList.push_back(&data);

	telemetry.SetMetrics(metricsList);

	if (props.size() > 0)
	{
		telemetry.SetProperties(props);
	}

	Track(telemetry);
}

/// <summary>
/// Tracks the page view.
/// </summary>
/// <param name="pageName">Name of the page.</param>
void TelemetryClient::TrackPageView(String^ pageName)
{
	TrackPageView(pageName, nullptr, nullptr);
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
	TrackPageView(pageName, L"", nullptr, nullptr);
}

/// <summary>
/// Tracks the page view.
/// </summary>
/// <param name="pageName">Name of the page.</param>
/// <param name="duration">The duration.</param>
void TelemetryClient::TrackPageView(String^ pageName, String^ duration)
{
	TrackPageView(pageName, duration, nullptr, nullptr);
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

	ApplicationInsights::core::PageViewData telemetry;
	telemetry.SetName(pageName->Data());
	telemetry.SetUrl(pageName->Data());
	if (duration != nullptr)
	{
		telemetry.SetDuration(duration->Data());
	}

	if (props.size() > 0)
	{
		telemetry.SetProperties(props);
	}
	if (measures.size() > 0)
	{
		telemetry.SetMeasurements(measures);
	}

	Track(telemetry);
}



/// <summary>
/// Tracks the session start.
/// </summary>
void TelemetryClient::TrackSessionStart()
{
	ApplicationInsights::core::SessionStateData session;
	session.SetState(ApplicationInsights::core::SessionState::Start);

	Track(session);
}

/// <summary>
/// Tracks the session end.
/// </summary>
void TelemetryClient::TrackSessionEnd()
{
	ApplicationInsights::core::SessionStateData session;
	session.SetState(ApplicationInsights::core::SessionState::End);

	Track(session);
}

/// <summary>
/// Renews the session.
/// </summary>
void TelemetryClient::RenewSession()
{
	//Send end session
	TrackSessionEnd();

	m_context->RenewSession();
}

/// <summary>
/// Disables all tracking.
/// </summary>
void TelemetryClient::DisableTracking()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	values->Insert("Tracking", dynamic_cast<PropertyValue^>(PropertyValue::CreateString("Disable")));
}

/// <summary>
/// Enables all tracking.
/// </summary>
void TelemetryClient::EnableTracking()
{
	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();
	values->Remove("Tracking");
}

/// <summary>
/// Gets the global properties.
/// </summary>
Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ TelemetryClient::GetGlobalProperties()
{
	return m_globalProperties;
}

/// <summary>
/// Tracks the specified telemetry.
/// </summary>
/// <param name="telemetry">The telemetry.</param>
void TelemetryClient::Track(ApplicationInsights::core::Domain& telemetry)
{
	if (IsTrackingEnabled())
	{
		std::map<std::wstring, std::wstring> tags;
		ConvertTagsToStdMap(tags);
		m_etwLogger.LogData(m_iKey->Data(), tags, telemetry);
	}
}

/// <summary>
/// Determines whether [is tracking enabled].
/// </summary>
/// <returns>True if the tracking is enabled, otherwise false</returns>
bool TelemetryClient::IsTrackingEnabled()
{
	bool enabled = true;

	auto values = ApplicationInsights::core::Utils::GetLocalSettingsContainer();

	enabled = !(values->HasKey("Tracking"));

	return enabled;
}

/// <summary>
/// Converts the tags to standard map.
/// </summary>
/// <param name="tags">The std::map to build.</tags>
void TelemetryClient::ConvertTagsToStdMap(std::map<std::wstring, std::wstring> &tags)
{
	if (m_context != nullptr)
	{
		Windows::Foundation::Collections::IMap<String^, String^>^ tagMap = ref new Map<String^, String^>();
		m_context->GetContextTags(tagMap);

		for (auto tagPair : tagMap)
		{
			tags[tagPair->Key->Data()] = tagPair->Value->Data();
		}
	}
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

	if (properties != nullptr)
	{
		if (properties->Size > 0)
		{
			for (auto propPair : properties)
			{
				props[propPair->Key->Data()] = propPair->Value->Data();
			}
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
	if (measurements != nullptr)
	{
		if (measurements->Size > 0)
		{
			for (auto measurePair : measurements)
			{
				measures[measurePair->Key->Data()] = measurePair->Value;
			}
		}
	}
}


