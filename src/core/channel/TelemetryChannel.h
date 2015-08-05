#ifndef TELEMETRYCHANNEL_H
#define TELEMETRYCHANNEL_H
#include "Utils/HttpRequest.hpp"
#include "../common/Common.hpp"
#include "Utils/Persistence.hpp"
#include <Windows.h>
#include <string>
#include <vector>

namespace ApplicationInsights
{
	namespace core
	{
		class TelemetryContext;
		class Domain;

		class TELEMETRYCLIENT_API TelemetryChannel
		{
		public:
			/// <summary>
			/// Initializes this instance.
			/// </summary>
			/// <returns></returns>
			static TelemetryChannel* Initialize();
			

			/// <summary>
			/// Gets the instance.
			/// </summary>
			/// <returns></returns>
			static TelemetryChannel* GetInstance();

			/// <summary>
			/// Finalizes an instance of the <see cref="TelemetryChannel"/> class.
			/// </summary>
			virtual ~TelemetryChannel();

			/// <summary>
			/// Enqueues the specified context.
			/// </summary>
			/// <param name="iKey">The iKey.</param>
			/// <param name="context">The context.</param>
			/// <param name="telemetry">The telemetry.</param>
			void TelemetryChannel::Enqueue(std::wstring &iKey, TelemetryContext &context, Domain &telemetry);

			/// <summary>
			/// Sends this instance.
			/// </summary>
			void Send();

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Win32
			void InitializePersistance(PERSISTCONFIG &config);
			Persistence* GetPersistance();
#endif

		protected:
			int m_channelId;
			int m_seqNum;
			int m_maxBufferSize;
			std::vector<std::wstring> m_buffer;
			HttpResponse resp;
			bool TelemetryChannel::IsUTCAvailable();
			std::wstring TraceLoggingSanitizer(std::wstring data);
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Win32
			Persistence m_persist;
#endif	

#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
			HANDLE hRespRecv;
#endif		

		private:
			/// <summary>
			/// Initializes a new instance of the <see cref="TelemetryChannel"/> class.
			/// </summary>
			/// <param name="config">The configuration.</param>
			TelemetryChannel();

			/// <summary>
			/// removing the copy constructor and assignment operator
			/// </summary>
			TelemetryChannel(TelemetryChannel const&) = delete;
			void operator =(TelemetryChannel const&) = delete;

			static TelemetryChannel* instance;
			CRITICAL_SECTION cs;
		};
	}
}


#endif