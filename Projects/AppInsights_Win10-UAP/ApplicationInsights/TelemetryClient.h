#pragma once
#include "TelemetryContext.h"
#include "TelemetryChannel.h"
#include "../../../src/core/channel/utils/TraceLoggingHelper.h"

namespace ApplicationInsights
{
	namespace CX
	{
		public ref class TelemetryClient sealed
		{
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
			/// </summary>
			/// <param name="iKey">The iKey.</param>
			TelemetryClient(Platform::String^ iKey);

			/// <summary>
			/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
			/// </summary>
			/// <param name="context">The context.</param>
			TelemetryClient(TelemetryContext^ context, Platform::String^ iKey);

			/// <summary>
			/// Finalizes an instance of the <see cref="" /> class.
			/// </summary>
			/// <returns></returns>
			virtual ~TelemetryClient();

			property TelemetryContext^ Context {
				TelemetryContext^ get() {
					return m_context;
				}
			}
			
			 property Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ GlobalProperties {
				 Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ get()
				 {
					 return m_globalProperties;
				 }
				  
				 void set(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties)
				 {
					 m_globalProperties = properties;
				 }
			 }

			/// <summary>
			/// Tracks the event.
			/// </summary>
			/// <param name="eventName">Name of the event.</param>
			void TrackEvent(Platform::String^ eventName);
			
			/// <summary>
			/// Tracks the event.
			/// </summary>
			/// <param nae="eventName">Name of the event.</param>
			/// <param name="properties">The properties.</param>
			/// <param name="measurements">The measurements.</param>
			void TrackEvent(Platform::String^ eventName,
				Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties,
				Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements);

			/// <summary>
			/// Tracks the trace.
			/// </summary>
			/// <param name="message">The message.</param>
			void TrackTrace(Platform::String^ message);
			
			/// <summary>
			/// Tracks the trace.
			/// </summary>
			/// <param name="message">The message.</param>
			/// <param name="properties">The properties.</param>
			void TrackTrace(Platform::String^ message,
				Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties);

			/// <summary>
			/// Tracks the metric.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			void TrackMetric(Platform::String^ name, double value);

			/// <summary>
			/// Tracks the metric.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			/// <param name="properties">The properties.</param>
			void TrackMetric(Platform::String^ name, double value,
				Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			void TrackPageView(Platform::String^ pageName);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			/// <param name="properties">The properties.</param>
			/// <param name="measurements">The measurements.</param>
			void TrackPageView(Platform::String^ pageName,
				Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties,
				Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			/// <param name="duration">The duration.</param>
			void TrackPageView(Platform::String^ pageName, Platform::String^ duration);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			/// <param name="duration">The duration.</param>
			/// <param name="properties">The properties.</param>
			/// <param name="measurements">The measurements.</param>
			void TrackPageView(Platform::String^ pageName, Platform::String^ duration,
				Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties,
				Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements);

			/// <summary>
			/// Tracks the session start.
			/// </summary>
			void TrackSessionStart();

			/// <summary>
			/// Tracks the session end.
			/// </summary>
			void TrackSessionEnd();

			/// <summary>
			/// Disables all tracking.
			/// </summary>
			void DisableTracking();

			/// <summary>
			/// Enables all tracking.
			/// </summary>
			void EnableTracking();

			
		private:
			/// <summary>
			/// Tracks the specified telemetry.
			/// </summary>
			/// <param name="telemetry">The telemetry.</param>
			void TelemetryClient::Track(ApplicationInsights::core::Domain& telemetry);

			/// <summary>
			/// Determines whether [is tracking enabled].
			/// </summary>
			/// <returns>True if the tracking is enabled, otherwise false</returns>
			bool TelemetryClient::IsTrackingEnabled();

			/// <summary>
			/// Converts the properties to standard map.
			/// </summary>
			/// <param name="properties">The properties.</param>
			/// <param name="props">The props.</param>
			void ConvertPropertiesToStdMap(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ properties, std::map<std::wstring, std::wstring> &props);

			/// <summary>
			/// Converts the measurements to standard map.
			/// </summary>
			/// <param name="measurements">The measurements.</param>
			/// <param name="measures">The measures.</param>
			void ConvertMeasurementsToStdMap(Windows::Foundation::Collections::IMap<Platform::String^, double>^ measurements, std::map<std::wstring, double> &measures);

			/// <summary>
			/// Converts the tags to standard map.
			/// </summary>
			/// <param name="tags">The std::map to build.</tags>
			void ConvertTagsToStdMap(std::map<std::wstring, std::wstring> &tags);

			Platform::String^ m_iKey;
			TelemetryContext^ m_context;
			TelemetryChannel^ m_channel;
			//ApplicationInsights::core::TraceLoggingHelper m_etwLogger;


			Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ m_globalProperties;

		};
	}
}
