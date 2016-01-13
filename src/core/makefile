    EXE = myexe
#    OBJS = TelemetryClient.o
    CPPFLAGS = -Iinclude
    SRCS=TelemetryClient.cpp BaseTelemetryContext.cpp TelemetryContextOther.cpp \
			common/JsonWriter.cpp common/StreamWriter.cpp common/StringWriter.cpp common/Utils.h \
			channel/TelemetryChannel.cpp  \
			channel/utils/HttpHeaderField.cpp channel/utils/HttpRequest.cpp channel/utils/HttpResponse.cpp \
			contracts/Application.cpp contracts/CrashData.cpp contracts/CrashDataBinary.cpp contracts/CrashDataHeaders.cpp \
			contracts/CrashDataThread.cpp contracts/CrashDataThreadFrame.cpp contracts/Data.cpp \
			contracts/DataPoint.cpp contracts/Device.cpp contracts/Domain.cpp\
			contracts/Envelope.cpp contracts/EventData.cpp contracts/ExceptionData.cpp
			
    OBJS=$(SRCS: .cpp=.o)
        
$(EXE): $(OBJS)
	g++ -o $@  $(OBJS)
        
depend: 
	makedepend -- $(CPPFLAGS) -- $(SRCS)
        
        


# DO NOT DELETE

TelemetryClient.o: TelemetryClient.h contracts/Contracts.h contracts/Domain.h
TelemetryClient.o: common/Common.h /usr/include/stdlib.h
TelemetryClient.o: /usr/include/features.h /usr/include/stdc-predef.h
TelemetryClient.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
TelemetryClient.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
TelemetryClient.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
TelemetryClient.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
TelemetryClient.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
TelemetryClient.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
TelemetryClient.o: /usr/include/time.h /usr/include/sys/select.h
TelemetryClient.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
TelemetryClient.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
TelemetryClient.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
TelemetryClient.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
TelemetryClient.o: common/Serializer.h common/Nullable.h contracts/Base.h
TelemetryClient.o: contracts/Data.h contracts/Envelope.h
TelemetryClient.o: contracts/DependencyKind.h contracts/SeverityLevel.h
TelemetryClient.o: contracts/CrashDataHeaders.h
TelemetryClient.o: contracts/CrashDataThreadFrame.h
TelemetryClient.o: contracts/CrashDataThread.h contracts/CrashDataBinary.h
TelemetryClient.o: contracts/CrashData.h contracts/DataPoint.h
TelemetryClient.o: contracts/DataPointType.h contracts/MetricData.h
TelemetryClient.o: contracts/RemoteDependencyData.h contracts/PageViewData.h
TelemetryClient.o: contracts/EventData.h contracts/DependencySourceType.h
TelemetryClient.o: contracts/RequestData.h contracts/StackFrame.h
TelemetryClient.o: contracts/ExceptionDetails.h contracts/ExceptionData.h
TelemetryClient.o: contracts/MessageData.h contracts/PageViewPerfData.h
TelemetryClient.o: contracts/Application.h contracts/Device.h
TelemetryClient.o: contracts/Location.h contracts/Operation.h
TelemetryClient.o: contracts/Session.h contracts/User.h contracts/Internal.h
TelemetryClient.o: contracts/SessionStateData.h contracts/SessionState.h
TelemetryClient.o: TelemetryClientConfig.h common/Common.h TelemetryContext.h
TelemetryClient.o: BaseTelemetryContext.h channel/TelemetryChannel.h
TelemetryClient.o: TelemetryClientConfig.h TelemetryContext.h
TelemetryClient.o: contracts/Contracts.h channel/utils/HttpRequest.h
TelemetryClient.o: channel/utils/HttpResponse.h common/Common.h
TelemetryClient.o: channel/utils/HttpHeaderFields.h
TelemetryClient.o: channel/utils/HttpHeaderField.h common/Utils.h
BaseTelemetryContext.o: BaseTelemetryContext.h TelemetryClientConfig.h
BaseTelemetryContext.o: common/Common.h contracts/Contracts.h
BaseTelemetryContext.o: contracts/Domain.h common/Common.h
BaseTelemetryContext.o: /usr/include/stdlib.h /usr/include/features.h
BaseTelemetryContext.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
BaseTelemetryContext.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
BaseTelemetryContext.o: /usr/include/bits/waitflags.h
BaseTelemetryContext.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
BaseTelemetryContext.o: /usr/include/bits/endian.h
BaseTelemetryContext.o: /usr/include/bits/byteswap.h
BaseTelemetryContext.o: /usr/include/bits/types.h
BaseTelemetryContext.o: /usr/include/bits/typesizes.h
BaseTelemetryContext.o: /usr/include/bits/byteswap-16.h
BaseTelemetryContext.o: /usr/include/sys/types.h /usr/include/time.h
BaseTelemetryContext.o: /usr/include/sys/select.h /usr/include/bits/select.h
BaseTelemetryContext.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
BaseTelemetryContext.o: /usr/include/sys/sysmacros.h
BaseTelemetryContext.o: /usr/include/bits/pthreadtypes.h
BaseTelemetryContext.o: /usr/include/alloca.h
BaseTelemetryContext.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
BaseTelemetryContext.o: common/Serializer.h common/Nullable.h
BaseTelemetryContext.o: contracts/Base.h contracts/Data.h
BaseTelemetryContext.o: contracts/Envelope.h contracts/DependencyKind.h
BaseTelemetryContext.o: contracts/SeverityLevel.h
BaseTelemetryContext.o: contracts/CrashDataHeaders.h
BaseTelemetryContext.o: contracts/CrashDataThreadFrame.h
BaseTelemetryContext.o: contracts/CrashDataThread.h
BaseTelemetryContext.o: contracts/CrashDataBinary.h contracts/CrashData.h
BaseTelemetryContext.o: contracts/DataPoint.h contracts/DataPointType.h
BaseTelemetryContext.o: contracts/MetricData.h
BaseTelemetryContext.o: contracts/RemoteDependencyData.h
BaseTelemetryContext.o: contracts/PageViewData.h contracts/EventData.h
BaseTelemetryContext.o: contracts/DependencySourceType.h
BaseTelemetryContext.o: contracts/RequestData.h contracts/StackFrame.h
BaseTelemetryContext.o: contracts/ExceptionDetails.h
BaseTelemetryContext.o: contracts/ExceptionData.h contracts/MessageData.h
BaseTelemetryContext.o: contracts/PageViewPerfData.h contracts/Application.h
BaseTelemetryContext.o: contracts/Device.h contracts/Location.h
BaseTelemetryContext.o: contracts/Operation.h contracts/Session.h
BaseTelemetryContext.o: contracts/User.h contracts/Internal.h
BaseTelemetryContext.o: contracts/SessionStateData.h contracts/SessionState.h
BaseTelemetryContext.o: common/Utils.h
TelemetryContextOther.o: TelemetryContext.h BaseTelemetryContext.h
TelemetryContextOther.o: TelemetryClientConfig.h common/Common.h
TelemetryContextOther.o: contracts/Contracts.h contracts/Domain.h
TelemetryContextOther.o: common/Common.h /usr/include/stdlib.h
TelemetryContextOther.o: /usr/include/features.h /usr/include/stdc-predef.h
TelemetryContextOther.o: /usr/include/sys/cdefs.h
TelemetryContextOther.o: /usr/include/bits/wordsize.h
TelemetryContextOther.o: /usr/include/gnu/stubs.h
TelemetryContextOther.o: /usr/include/bits/waitflags.h
TelemetryContextOther.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
TelemetryContextOther.o: /usr/include/bits/endian.h
TelemetryContextOther.o: /usr/include/bits/byteswap.h
TelemetryContextOther.o: /usr/include/bits/types.h
TelemetryContextOther.o: /usr/include/bits/typesizes.h
TelemetryContextOther.o: /usr/include/bits/byteswap-16.h
TelemetryContextOther.o: /usr/include/sys/types.h /usr/include/time.h
TelemetryContextOther.o: /usr/include/sys/select.h /usr/include/bits/select.h
TelemetryContextOther.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
TelemetryContextOther.o: /usr/include/sys/sysmacros.h
TelemetryContextOther.o: /usr/include/bits/pthreadtypes.h
TelemetryContextOther.o: /usr/include/alloca.h
TelemetryContextOther.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
TelemetryContextOther.o: common/Serializer.h common/Nullable.h
TelemetryContextOther.o: contracts/Base.h contracts/Data.h
TelemetryContextOther.o: contracts/Envelope.h contracts/DependencyKind.h
TelemetryContextOther.o: contracts/SeverityLevel.h
TelemetryContextOther.o: contracts/CrashDataHeaders.h
TelemetryContextOther.o: contracts/CrashDataThreadFrame.h
TelemetryContextOther.o: contracts/CrashDataThread.h
TelemetryContextOther.o: contracts/CrashDataBinary.h contracts/CrashData.h
TelemetryContextOther.o: contracts/DataPoint.h contracts/DataPointType.h
TelemetryContextOther.o: contracts/MetricData.h
TelemetryContextOther.o: contracts/RemoteDependencyData.h
TelemetryContextOther.o: contracts/PageViewData.h contracts/EventData.h
TelemetryContextOther.o: contracts/DependencySourceType.h
TelemetryContextOther.o: contracts/RequestData.h contracts/StackFrame.h
TelemetryContextOther.o: contracts/ExceptionDetails.h
TelemetryContextOther.o: contracts/ExceptionData.h contracts/MessageData.h
TelemetryContextOther.o: contracts/PageViewPerfData.h contracts/Application.h
TelemetryContextOther.o: contracts/Device.h contracts/Location.h
TelemetryContextOther.o: contracts/Operation.h contracts/Session.h
TelemetryContextOther.o: contracts/User.h contracts/Internal.h
TelemetryContextOther.o: contracts/SessionStateData.h
TelemetryContextOther.o: contracts/SessionState.h
common/JsonWriter.o: common/StreamWriter.h common/Common.h
common/JsonWriter.o: /usr/include/stdlib.h /usr/include/features.h
common/JsonWriter.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
common/JsonWriter.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
common/JsonWriter.o: /usr/include/bits/waitflags.h
common/JsonWriter.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
common/JsonWriter.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
common/JsonWriter.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
common/JsonWriter.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
common/JsonWriter.o: /usr/include/time.h /usr/include/sys/select.h
common/JsonWriter.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
common/JsonWriter.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
common/JsonWriter.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
common/JsonWriter.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
common/JsonWriter.o: common/Common.h common/Serializer.h
common/StreamWriter.o: /usr/include/wchar.h /usr/include/features.h
common/StreamWriter.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
common/StreamWriter.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
common/StreamWriter.o: /usr/include/stdio.h /usr/include/bits/wchar.h
common/StreamWriter.o: /usr/include/xlocale.h common/StreamWriter.h
common/StreamWriter.o: common/Common.h /usr/include/stdlib.h
common/StreamWriter.o: /usr/include/bits/waitflags.h
common/StreamWriter.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
common/StreamWriter.o: /usr/include/bits/endian.h
common/StreamWriter.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
common/StreamWriter.o: /usr/include/bits/typesizes.h
common/StreamWriter.o: /usr/include/bits/byteswap-16.h
common/StreamWriter.o: /usr/include/sys/types.h /usr/include/time.h
common/StreamWriter.o: /usr/include/sys/select.h /usr/include/bits/select.h
common/StreamWriter.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
common/StreamWriter.o: /usr/include/sys/sysmacros.h
common/StreamWriter.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
common/StreamWriter.o: /usr/include/bits/stdlib-float.h /usr/include/string.h
common/StringWriter.o: common/StringWriter.h common/StreamWriter.h
common/StringWriter.o: common/Common.h /usr/include/stdlib.h
common/StringWriter.o: /usr/include/features.h /usr/include/stdc-predef.h
common/StringWriter.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
common/StringWriter.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
common/StringWriter.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
common/StringWriter.o: /usr/include/bits/endian.h
common/StringWriter.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
common/StringWriter.o: /usr/include/bits/typesizes.h
common/StringWriter.o: /usr/include/bits/byteswap-16.h
common/StringWriter.o: /usr/include/sys/types.h /usr/include/time.h
common/StringWriter.o: /usr/include/sys/select.h /usr/include/bits/select.h
common/StringWriter.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
common/StringWriter.o: /usr/include/sys/sysmacros.h
common/StringWriter.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
common/StringWriter.o: /usr/include/bits/stdlib-float.h common/Utils.h
common/StringWriter.o: common/Common.h /usr/include/stdio.h
common/Utils.o: common/Common.h /usr/include/stdlib.h /usr/include/features.h
common/Utils.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
common/Utils.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
common/Utils.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
common/Utils.o: /usr/include/endian.h /usr/include/bits/endian.h
common/Utils.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
common/Utils.o: /usr/include/bits/typesizes.h /usr/include/bits/byteswap-16.h
common/Utils.o: /usr/include/sys/types.h /usr/include/time.h
common/Utils.o: /usr/include/sys/select.h /usr/include/bits/select.h
common/Utils.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
common/Utils.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
common/Utils.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
channel/TelemetryChannel.o: channel/TelemetryChannel.h
channel/TelemetryChannel.o: TelemetryClientConfig.h TelemetryContext.h
channel/TelemetryChannel.o: contracts/Contracts.h contracts/Domain.h
channel/TelemetryChannel.o: common/Common.h /usr/include/stdlib.h
channel/TelemetryChannel.o: /usr/include/features.h
channel/TelemetryChannel.o: /usr/include/stdc-predef.h
channel/TelemetryChannel.o: /usr/include/sys/cdefs.h
channel/TelemetryChannel.o: /usr/include/bits/wordsize.h
channel/TelemetryChannel.o: /usr/include/gnu/stubs.h
channel/TelemetryChannel.o: /usr/include/bits/waitflags.h
channel/TelemetryChannel.o: /usr/include/bits/waitstatus.h
channel/TelemetryChannel.o: /usr/include/endian.h /usr/include/bits/endian.h
channel/TelemetryChannel.o: /usr/include/bits/byteswap.h
channel/TelemetryChannel.o: /usr/include/bits/types.h
channel/TelemetryChannel.o: /usr/include/bits/typesizes.h
channel/TelemetryChannel.o: /usr/include/bits/byteswap-16.h
channel/TelemetryChannel.o: /usr/include/sys/types.h /usr/include/time.h
channel/TelemetryChannel.o: /usr/include/sys/select.h
channel/TelemetryChannel.o: /usr/include/bits/select.h
channel/TelemetryChannel.o: /usr/include/bits/sigset.h
channel/TelemetryChannel.o: /usr/include/bits/time.h
channel/TelemetryChannel.o: /usr/include/sys/sysmacros.h
channel/TelemetryChannel.o: /usr/include/bits/pthreadtypes.h
channel/TelemetryChannel.o: /usr/include/alloca.h
channel/TelemetryChannel.o: /usr/include/bits/stdlib-float.h
channel/TelemetryChannel.o: common/JsonWriter.h common/Serializer.h
channel/TelemetryChannel.o: common/Nullable.h contracts/Base.h
channel/TelemetryChannel.o: contracts/Data.h contracts/Envelope.h
channel/TelemetryChannel.o: contracts/DependencyKind.h
channel/TelemetryChannel.o: contracts/SeverityLevel.h
channel/TelemetryChannel.o: contracts/CrashDataHeaders.h
channel/TelemetryChannel.o: contracts/CrashDataThreadFrame.h
channel/TelemetryChannel.o: contracts/CrashDataThread.h
channel/TelemetryChannel.o: contracts/CrashDataBinary.h contracts/CrashData.h
channel/TelemetryChannel.o: contracts/DataPoint.h contracts/DataPointType.h
channel/TelemetryChannel.o: contracts/MetricData.h
channel/TelemetryChannel.o: contracts/RemoteDependencyData.h
channel/TelemetryChannel.o: contracts/PageViewData.h contracts/EventData.h
channel/TelemetryChannel.o: contracts/DependencySourceType.h
channel/TelemetryChannel.o: contracts/RequestData.h contracts/StackFrame.h
channel/TelemetryChannel.o: contracts/ExceptionDetails.h
channel/TelemetryChannel.o: contracts/ExceptionData.h contracts/MessageData.h
channel/TelemetryChannel.o: contracts/PageViewPerfData.h
channel/TelemetryChannel.o: contracts/Application.h contracts/Device.h
channel/TelemetryChannel.o: contracts/Location.h contracts/Operation.h
channel/TelemetryChannel.o: contracts/Session.h contracts/User.h
channel/TelemetryChannel.o: contracts/Internal.h contracts/SessionStateData.h
channel/TelemetryChannel.o: contracts/SessionState.h
channel/TelemetryChannel.o: channel/utils/HttpRequest.h
channel/TelemetryChannel.o: channel/utils/HttpResponse.h common/Common.h
channel/TelemetryChannel.o: channel/utils/HttpHeaderFields.h
channel/TelemetryChannel.o: channel/utils/HttpHeaderField.h common/Utils.h
channel/TelemetryChannel.o: common/StringWriter.h common/StreamWriter.h
channel/TelemetryChannel.o: common/Common.h
channel/utils/HttpHeaderField.o: channel/utils/HttpHeaderField.h
channel/utils/HttpHeaderField.o: common/Common.h
channel/utils/HttpRequest.o: channel/utils/HttpRequest.h
channel/utils/HttpRequest.o: channel/utils/HttpResponse.h common/Common.h
channel/utils/HttpRequest.o: channel/utils/HttpHeaderFields.h
channel/utils/HttpRequest.o: channel/utils/HttpHeaderField.h common/Utils.h
channel/utils/HttpRequest.o: common/Common.h /usr/include/stdlib.h
channel/utils/HttpRequest.o: /usr/include/features.h
channel/utils/HttpRequest.o: /usr/include/stdc-predef.h
channel/utils/HttpRequest.o: /usr/include/sys/cdefs.h
channel/utils/HttpRequest.o: /usr/include/bits/wordsize.h
channel/utils/HttpRequest.o: /usr/include/gnu/stubs.h
channel/utils/HttpRequest.o: /usr/include/bits/waitflags.h
channel/utils/HttpRequest.o: /usr/include/bits/waitstatus.h
channel/utils/HttpRequest.o: /usr/include/endian.h /usr/include/bits/endian.h
channel/utils/HttpRequest.o: /usr/include/bits/byteswap.h
channel/utils/HttpRequest.o: /usr/include/bits/types.h
channel/utils/HttpRequest.o: /usr/include/bits/typesizes.h
channel/utils/HttpRequest.o: /usr/include/bits/byteswap-16.h
channel/utils/HttpRequest.o: /usr/include/sys/types.h /usr/include/time.h
channel/utils/HttpRequest.o: /usr/include/sys/select.h
channel/utils/HttpRequest.o: /usr/include/bits/select.h
channel/utils/HttpRequest.o: /usr/include/bits/sigset.h
channel/utils/HttpRequest.o: /usr/include/bits/time.h
channel/utils/HttpRequest.o: /usr/include/sys/sysmacros.h
channel/utils/HttpRequest.o: /usr/include/bits/pthreadtypes.h
channel/utils/HttpRequest.o: /usr/include/alloca.h
channel/utils/HttpRequest.o: /usr/include/bits/stdlib-float.h
channel/utils/HttpResponse.o: channel/utils/HttpResponse.h common/Common.h
contracts/Application.o: contracts/Application.h common/Common.h
contracts/Application.o: /usr/include/stdlib.h /usr/include/features.h
contracts/Application.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
contracts/Application.o: /usr/include/bits/wordsize.h
contracts/Application.o: /usr/include/gnu/stubs.h
contracts/Application.o: /usr/include/bits/waitflags.h
contracts/Application.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/Application.o: /usr/include/bits/endian.h
contracts/Application.o: /usr/include/bits/byteswap.h
contracts/Application.o: /usr/include/bits/types.h
contracts/Application.o: /usr/include/bits/typesizes.h
contracts/Application.o: /usr/include/bits/byteswap-16.h
contracts/Application.o: /usr/include/sys/types.h /usr/include/time.h
contracts/Application.o: /usr/include/sys/select.h /usr/include/bits/select.h
contracts/Application.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
contracts/Application.o: /usr/include/sys/sysmacros.h
contracts/Application.o: /usr/include/bits/pthreadtypes.h
contracts/Application.o: /usr/include/alloca.h
contracts/Application.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/Application.o: common/Serializer.h common/Nullable.h
contracts/CrashData.o: contracts/CrashData.h common/Common.h
contracts/CrashData.o: /usr/include/stdlib.h /usr/include/features.h
contracts/CrashData.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
contracts/CrashData.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
contracts/CrashData.o: /usr/include/bits/waitflags.h
contracts/CrashData.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/CrashData.o: /usr/include/bits/endian.h
contracts/CrashData.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
contracts/CrashData.o: /usr/include/bits/typesizes.h
contracts/CrashData.o: /usr/include/bits/byteswap-16.h
contracts/CrashData.o: /usr/include/sys/types.h /usr/include/time.h
contracts/CrashData.o: /usr/include/sys/select.h /usr/include/bits/select.h
contracts/CrashData.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
contracts/CrashData.o: /usr/include/sys/sysmacros.h
contracts/CrashData.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
contracts/CrashData.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/CrashData.o: common/Serializer.h common/Nullable.h
contracts/CrashData.o: contracts/CrashDataBinary.h
contracts/CrashData.o: contracts/CrashDataHeaders.h
contracts/CrashData.o: contracts/CrashDataThread.h
contracts/CrashData.o: contracts/CrashDataThreadFrame.h contracts/Domain.h
contracts/CrashDataBinary.o: contracts/CrashDataBinary.h common/Common.h
contracts/CrashDataBinary.o: /usr/include/stdlib.h /usr/include/features.h
contracts/CrashDataBinary.o: /usr/include/stdc-predef.h
contracts/CrashDataBinary.o: /usr/include/sys/cdefs.h
contracts/CrashDataBinary.o: /usr/include/bits/wordsize.h
contracts/CrashDataBinary.o: /usr/include/gnu/stubs.h
contracts/CrashDataBinary.o: /usr/include/bits/waitflags.h
contracts/CrashDataBinary.o: /usr/include/bits/waitstatus.h
contracts/CrashDataBinary.o: /usr/include/endian.h /usr/include/bits/endian.h
contracts/CrashDataBinary.o: /usr/include/bits/byteswap.h
contracts/CrashDataBinary.o: /usr/include/bits/types.h
contracts/CrashDataBinary.o: /usr/include/bits/typesizes.h
contracts/CrashDataBinary.o: /usr/include/bits/byteswap-16.h
contracts/CrashDataBinary.o: /usr/include/sys/types.h /usr/include/time.h
contracts/CrashDataBinary.o: /usr/include/sys/select.h
contracts/CrashDataBinary.o: /usr/include/bits/select.h
contracts/CrashDataBinary.o: /usr/include/bits/sigset.h
contracts/CrashDataBinary.o: /usr/include/bits/time.h
contracts/CrashDataBinary.o: /usr/include/sys/sysmacros.h
contracts/CrashDataBinary.o: /usr/include/bits/pthreadtypes.h
contracts/CrashDataBinary.o: /usr/include/alloca.h
contracts/CrashDataBinary.o: /usr/include/bits/stdlib-float.h
contracts/CrashDataBinary.o: common/JsonWriter.h common/Serializer.h
contracts/CrashDataBinary.o: common/Nullable.h
contracts/CrashDataHeaders.o: contracts/CrashDataHeaders.h common/Common.h
contracts/CrashDataHeaders.o: /usr/include/stdlib.h /usr/include/features.h
contracts/CrashDataHeaders.o: /usr/include/stdc-predef.h
contracts/CrashDataHeaders.o: /usr/include/sys/cdefs.h
contracts/CrashDataHeaders.o: /usr/include/bits/wordsize.h
contracts/CrashDataHeaders.o: /usr/include/gnu/stubs.h
contracts/CrashDataHeaders.o: /usr/include/bits/waitflags.h
contracts/CrashDataHeaders.o: /usr/include/bits/waitstatus.h
contracts/CrashDataHeaders.o: /usr/include/endian.h
contracts/CrashDataHeaders.o: /usr/include/bits/endian.h
contracts/CrashDataHeaders.o: /usr/include/bits/byteswap.h
contracts/CrashDataHeaders.o: /usr/include/bits/types.h
contracts/CrashDataHeaders.o: /usr/include/bits/typesizes.h
contracts/CrashDataHeaders.o: /usr/include/bits/byteswap-16.h
contracts/CrashDataHeaders.o: /usr/include/sys/types.h /usr/include/time.h
contracts/CrashDataHeaders.o: /usr/include/sys/select.h
contracts/CrashDataHeaders.o: /usr/include/bits/select.h
contracts/CrashDataHeaders.o: /usr/include/bits/sigset.h
contracts/CrashDataHeaders.o: /usr/include/bits/time.h
contracts/CrashDataHeaders.o: /usr/include/sys/sysmacros.h
contracts/CrashDataHeaders.o: /usr/include/bits/pthreadtypes.h
contracts/CrashDataHeaders.o: /usr/include/alloca.h
contracts/CrashDataHeaders.o: /usr/include/bits/stdlib-float.h
contracts/CrashDataHeaders.o: common/JsonWriter.h common/Serializer.h
contracts/CrashDataHeaders.o: common/Nullable.h
contracts/CrashDataThread.o: contracts/CrashDataThread.h common/Common.h
contracts/CrashDataThread.o: /usr/include/stdlib.h /usr/include/features.h
contracts/CrashDataThread.o: /usr/include/stdc-predef.h
contracts/CrashDataThread.o: /usr/include/sys/cdefs.h
contracts/CrashDataThread.o: /usr/include/bits/wordsize.h
contracts/CrashDataThread.o: /usr/include/gnu/stubs.h
contracts/CrashDataThread.o: /usr/include/bits/waitflags.h
contracts/CrashDataThread.o: /usr/include/bits/waitstatus.h
contracts/CrashDataThread.o: /usr/include/endian.h /usr/include/bits/endian.h
contracts/CrashDataThread.o: /usr/include/bits/byteswap.h
contracts/CrashDataThread.o: /usr/include/bits/types.h
contracts/CrashDataThread.o: /usr/include/bits/typesizes.h
contracts/CrashDataThread.o: /usr/include/bits/byteswap-16.h
contracts/CrashDataThread.o: /usr/include/sys/types.h /usr/include/time.h
contracts/CrashDataThread.o: /usr/include/sys/select.h
contracts/CrashDataThread.o: /usr/include/bits/select.h
contracts/CrashDataThread.o: /usr/include/bits/sigset.h
contracts/CrashDataThread.o: /usr/include/bits/time.h
contracts/CrashDataThread.o: /usr/include/sys/sysmacros.h
contracts/CrashDataThread.o: /usr/include/bits/pthreadtypes.h
contracts/CrashDataThread.o: /usr/include/alloca.h
contracts/CrashDataThread.o: /usr/include/bits/stdlib-float.h
contracts/CrashDataThread.o: common/JsonWriter.h common/Serializer.h
contracts/CrashDataThread.o: common/Nullable.h
contracts/CrashDataThread.o: contracts/CrashDataThreadFrame.h
contracts/CrashDataThreadFrame.o: contracts/CrashDataThreadFrame.h
contracts/CrashDataThreadFrame.o: common/Common.h /usr/include/stdlib.h
contracts/CrashDataThreadFrame.o: /usr/include/features.h
contracts/CrashDataThreadFrame.o: /usr/include/stdc-predef.h
contracts/CrashDataThreadFrame.o: /usr/include/sys/cdefs.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/wordsize.h
contracts/CrashDataThreadFrame.o: /usr/include/gnu/stubs.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/waitflags.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/waitstatus.h
contracts/CrashDataThreadFrame.o: /usr/include/endian.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/endian.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/byteswap.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/types.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/typesizes.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/byteswap-16.h
contracts/CrashDataThreadFrame.o: /usr/include/sys/types.h
contracts/CrashDataThreadFrame.o: /usr/include/time.h
contracts/CrashDataThreadFrame.o: /usr/include/sys/select.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/select.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/sigset.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/time.h
contracts/CrashDataThreadFrame.o: /usr/include/sys/sysmacros.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/pthreadtypes.h
contracts/CrashDataThreadFrame.o: /usr/include/alloca.h
contracts/CrashDataThreadFrame.o: /usr/include/bits/stdlib-float.h
contracts/CrashDataThreadFrame.o: common/JsonWriter.h common/Serializer.h
contracts/CrashDataThreadFrame.o: common/Nullable.h
contracts/Data.o: contracts/Data.h common/Common.h /usr/include/stdlib.h
contracts/Data.o: /usr/include/features.h /usr/include/stdc-predef.h
contracts/Data.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
contracts/Data.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
contracts/Data.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/Data.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
contracts/Data.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
contracts/Data.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
contracts/Data.o: /usr/include/time.h /usr/include/sys/select.h
contracts/Data.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
contracts/Data.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
contracts/Data.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
contracts/Data.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/Data.o: common/Serializer.h common/Nullable.h contracts/Base.h
contracts/Data.o: contracts/Domain.h
contracts/DataPoint.o: contracts/DataPoint.h common/Common.h
contracts/DataPoint.o: /usr/include/stdlib.h /usr/include/features.h
contracts/DataPoint.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
contracts/DataPoint.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
contracts/DataPoint.o: /usr/include/bits/waitflags.h
contracts/DataPoint.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/DataPoint.o: /usr/include/bits/endian.h
contracts/DataPoint.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
contracts/DataPoint.o: /usr/include/bits/typesizes.h
contracts/DataPoint.o: /usr/include/bits/byteswap-16.h
contracts/DataPoint.o: /usr/include/sys/types.h /usr/include/time.h
contracts/DataPoint.o: /usr/include/sys/select.h /usr/include/bits/select.h
contracts/DataPoint.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
contracts/DataPoint.o: /usr/include/sys/sysmacros.h
contracts/DataPoint.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
contracts/DataPoint.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/DataPoint.o: common/Serializer.h common/Nullable.h
contracts/DataPoint.o: contracts/DataPointType.h
contracts/Device.o: contracts/Device.h common/Common.h /usr/include/stdlib.h
contracts/Device.o: /usr/include/features.h /usr/include/stdc-predef.h
contracts/Device.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
contracts/Device.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
contracts/Device.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/Device.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
contracts/Device.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
contracts/Device.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
contracts/Device.o: /usr/include/time.h /usr/include/sys/select.h
contracts/Device.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
contracts/Device.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
contracts/Device.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
contracts/Device.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/Device.o: common/Serializer.h common/Nullable.h
contracts/Domain.o: contracts/Domain.h common/Common.h /usr/include/stdlib.h
contracts/Domain.o: /usr/include/features.h /usr/include/stdc-predef.h
contracts/Domain.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
contracts/Domain.o: /usr/include/gnu/stubs.h /usr/include/bits/waitflags.h
contracts/Domain.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/Domain.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
contracts/Domain.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
contracts/Domain.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
contracts/Domain.o: /usr/include/time.h /usr/include/sys/select.h
contracts/Domain.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
contracts/Domain.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
contracts/Domain.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
contracts/Domain.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/Domain.o: common/Serializer.h common/Nullable.h
contracts/Envelope.o: contracts/Envelope.h common/Common.h
contracts/Envelope.o: /usr/include/stdlib.h /usr/include/features.h
contracts/Envelope.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
contracts/Envelope.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
contracts/Envelope.o: /usr/include/bits/waitflags.h
contracts/Envelope.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/Envelope.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
contracts/Envelope.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
contracts/Envelope.o: /usr/include/bits/byteswap-16.h
contracts/Envelope.o: /usr/include/sys/types.h /usr/include/time.h
contracts/Envelope.o: /usr/include/sys/select.h /usr/include/bits/select.h
contracts/Envelope.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
contracts/Envelope.o: /usr/include/sys/sysmacros.h
contracts/Envelope.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
contracts/Envelope.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/Envelope.o: common/Serializer.h common/Nullable.h contracts/Base.h
contracts/EventData.o: contracts/EventData.h common/Common.h
contracts/EventData.o: /usr/include/stdlib.h /usr/include/features.h
contracts/EventData.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
contracts/EventData.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
contracts/EventData.o: /usr/include/bits/waitflags.h
contracts/EventData.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
contracts/EventData.o: /usr/include/bits/endian.h
contracts/EventData.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
contracts/EventData.o: /usr/include/bits/typesizes.h
contracts/EventData.o: /usr/include/bits/byteswap-16.h
contracts/EventData.o: /usr/include/sys/types.h /usr/include/time.h
contracts/EventData.o: /usr/include/sys/select.h /usr/include/bits/select.h
contracts/EventData.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
contracts/EventData.o: /usr/include/sys/sysmacros.h
contracts/EventData.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
contracts/EventData.o: /usr/include/bits/stdlib-float.h common/JsonWriter.h
contracts/EventData.o: common/Serializer.h common/Nullable.h
contracts/EventData.o: contracts/Domain.h
contracts/ExceptionData.o: contracts/ExceptionData.h common/Common.h
contracts/ExceptionData.o: /usr/include/stdlib.h /usr/include/features.h
contracts/ExceptionData.o: /usr/include/stdc-predef.h
contracts/ExceptionData.o: /usr/include/sys/cdefs.h
contracts/ExceptionData.o: /usr/include/bits/wordsize.h
contracts/ExceptionData.o: /usr/include/gnu/stubs.h
contracts/ExceptionData.o: /usr/include/bits/waitflags.h
contracts/ExceptionData.o: /usr/include/bits/waitstatus.h
contracts/ExceptionData.o: /usr/include/endian.h /usr/include/bits/endian.h
contracts/ExceptionData.o: /usr/include/bits/byteswap.h
contracts/ExceptionData.o: /usr/include/bits/types.h
contracts/ExceptionData.o: /usr/include/bits/typesizes.h
contracts/ExceptionData.o: /usr/include/bits/byteswap-16.h
contracts/ExceptionData.o: /usr/include/sys/types.h /usr/include/time.h
contracts/ExceptionData.o: /usr/include/sys/select.h
contracts/ExceptionData.o: /usr/include/bits/select.h
contracts/ExceptionData.o: /usr/include/bits/sigset.h
contracts/ExceptionData.o: /usr/include/bits/time.h
contracts/ExceptionData.o: /usr/include/sys/sysmacros.h
contracts/ExceptionData.o: /usr/include/bits/pthreadtypes.h
contracts/ExceptionData.o: /usr/include/alloca.h
contracts/ExceptionData.o: /usr/include/bits/stdlib-float.h
contracts/ExceptionData.o: common/JsonWriter.h common/Serializer.h
contracts/ExceptionData.o: common/Nullable.h contracts/Domain.h
contracts/ExceptionData.o: contracts/ExceptionDetails.h
contracts/ExceptionData.o: contracts/StackFrame.h contracts/SeverityLevel.h
