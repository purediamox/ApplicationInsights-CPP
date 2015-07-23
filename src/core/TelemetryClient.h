#ifndef TELEMETRYCLIENT_H
#define TELEMETRYCLIENT_H

#include "Contracts/Contracts.h"
#include "TelemetryContext.h"
#include "Channel/TelemetryChannel.h"
#include <string>
#include <map>
#include <ctime>
#include <memory>

namespace ApplicationInsights
{
	namespace core
	{
		class TELEMETRYCLIENT_API TelemetryClient
		{
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
			/// </summary>
			/// <param name="iKey">The ikey.</param>
			TelemetryClient(std::wstring& iKey);

			/// <summary>
			/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
			/// </summary>
			/// <param name="context">The context.</param>
			/// <param name="iKey">The ikey.</param>
			TelemetryClient(TelemetryContext &context, std::wstring& iKey);

			/// <summary>
			/// Finalizes an instance of the <see cref="TelemetryClient"/> class.
			/// </summary>
			virtual ~TelemetryClient();

			/// <summary>
			/// Gets the context.
			/// </summary>
			/// <returns>the context</returns>
			TelemetryContext *GetContext() const { return m_context; }

			/// <summary>
			/// Tracks the event.
			/// </summary>
			/// <param name="eventName">Name of the event.</param>
			void TrackEvent(const std::wstring& eventName);

			/// <summary>
			/// Tracks the event.
			/// </summary>
			/// <param name="eventName">Name of the event.</param>
			/// <param name="properties">The properties.</param>
			void TrackEvent(const std::wstring& eventName, const wstring_wstring_map& properties);

			/// <summary>
			/// Tracks the event.
			/// </summary>
			/// <param name="eventName">Name of the event.</param>
			/// <param name="properties">The properties.</param>
			/// <param name="measurements">The measurements.</param>
			void TrackEvent(const std::wstring& eventName, const wstring_wstring_map& properties, const std::map<std::wstring, double>& measurements);

			/// <summary>
			/// Tracks the trace.
			/// </summary>
			/// <param name="message">The message.</param>
			void TrackTrace(const std::wstring& message);

			/// <summary>
			/// Tracks the trace.
			/// </summary>
			/// <param name="message">The message.</param>
			/// <param name="properties">The properties.</param>
			void TrackTrace(const std::wstring& message, const wstring_wstring_map& properties);

			/// <summary>
			/// Tracks the metric.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			void TrackMetric(const std::wstring& name, const double& value);

			/// <summary>
			/// Tracks the metric.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			/// <param name="properties">The properties.</param>
			void TrackMetric(const std::wstring& name, const double& value, const wstring_wstring_map& properties);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			void TrackPageView(const std::wstring& pageName);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			/// <param name="duration">The duration.</param>
			void TrackPageView(const std::wstring& pageName, const std::wstring& duration);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			/// <param name="duration">The duration.</param>
			/// <param name="properties">The properties.</param>
			void TrackPageView(const std::wstring& pageName, const std::wstring& duration, const wstring_wstring_map& properties);

			/// <summary>
			/// Tracks the page view.
			/// </summary>
			/// <param name="pageName">Name of the page.</param>
			/// <param name="duration">The duration.</param>
			/// <param name="properties">The properties.</param>
			/// <param name="measurements">The measurements.</param>
			void TrackPageView(const std::wstring& pageName, const std::wstring& duration, const wstring_wstring_map& properties, const std::map<std::wstring, double>& measurements);

			/// <summary>
			/// Tracks the session start.
			/// </summary>
			void TrackSessionStart();

			/// <summary>
			/// Tracks the session end.
			/// </summary>
			void TrackSessionEnd();

			/// <summary>
			/// Tracks the specified telemetry.
			/// </summary>
			/// <param name="telemetry">The telemetry.</param>
			void Track(Domain& telemetry);

			/// <summary>
			/// Flushes this instance.
			/// </summary>
			void Flush();

			/// <summary>
			/// Disables all tracking.
			/// </summary>
			void DisableTracking();

			/// <summary>
			/// Enables all tracking.
			/// </summary>
			void EnableTracking();

		protected:
			/// <summary>
			/// Initializes a new instance of the <see cref="TelemetryClient"/> class.
			/// </summary>
			/// <param name="context">The context.</param>
			TelemetryClient();

			/// <summary>
			/// Determines whether [is tracking enabled].
			/// </summary>
			/// <returns>True if the tracking is enabled, otherwise false</returns>
			bool IsTrackingEnabled();

			// The telemetry telemetryContext object.
			TelemetryContext *m_context;

			// The telemetry channel for this client.
			TelemetryChannel *m_channel;

			// The instrumentation key for this client.
			std::wstring m_instrumentationKey;
		};
	}
}
#endif
