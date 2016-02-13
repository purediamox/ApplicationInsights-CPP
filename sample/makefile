#makefile for sample.cpp
    EXE = sample

    CPPFLAGS = -Iinclude -std=gnu++11 -fPIC -g  -L./../src/core/ 
    SRCS=sample.cpp
			
    OBJS=$(SRCS:.cpp=.o)
        
$(EXE): $(OBJS)
	g++ $(CPPFLAGS) -o $@  $(OBJS)  -lappinsights -lcurl 
        
depend: cd 
	makedepend -- $(CPPFLAGS) -- $(SRCS)

clean:
	rm -f $(EXE) $(OBJS)        
        
# DO NOT DELETE

sample.o: ../src/core/TelemetryClient.h ../src/core/contracts/Contracts.h
sample.o: ../src/core/contracts/Domain.h ../src/core/common/Common.h
sample.o: /usr/include/stdlib.h /usr/include/features.h
sample.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
sample.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
sample.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
sample.o: /usr/include/endian.h /usr/include/bits/endian.h
sample.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
sample.o: /usr/include/bits/typesizes.h /usr/include/bits/byteswap-16.h
sample.o: /usr/include/sys/types.h /usr/include/time.h
sample.o: /usr/include/sys/select.h /usr/include/bits/select.h
sample.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
sample.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
sample.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
sample.o: ../src/core/common/JsonWriter.h ../src/core/common/Serializer.h
sample.o: ../src/core/common/Nullable.h ../src/core/contracts/Base.h
sample.o: ../src/core/contracts/Data.h ../src/core/contracts/Envelope.h
sample.o: ../src/core/contracts/DependencyKind.h
sample.o: ../src/core/contracts/SeverityLevel.h
sample.o: ../src/core/contracts/CrashDataHeaders.h
sample.o: ../src/core/contracts/CrashDataThreadFrame.h
sample.o: ../src/core/contracts/CrashDataThread.h
sample.o: ../src/core/contracts/CrashDataBinary.h
sample.o: ../src/core/contracts/CrashData.h ../src/core/contracts/DataPoint.h
sample.o: ../src/core/contracts/DataPointType.h
sample.o: ../src/core/contracts/MetricData.h
sample.o: ../src/core/contracts/RemoteDependencyData.h
sample.o: ../src/core/contracts/PageViewData.h
sample.o: ../src/core/contracts/EventData.h
sample.o: ../src/core/contracts/DependencySourceType.h
sample.o: ../src/core/contracts/RequestData.h
sample.o: ../src/core/contracts/StackFrame.h
sample.o: ../src/core/contracts/ExceptionDetails.h
sample.o: ../src/core/contracts/ExceptionData.h
sample.o: ../src/core/contracts/MessageData.h
sample.o: ../src/core/contracts/PageViewPerfData.h
sample.o: ../src/core/contracts/Application.h ../src/core/contracts/Device.h
sample.o: ../src/core/contracts/Location.h ../src/core/contracts/Operation.h
sample.o: ../src/core/contracts/Session.h ../src/core/contracts/User.h
sample.o: ../src/core/contracts/Internal.h
sample.o: ../src/core/contracts/SessionStateData.h
sample.o: ../src/core/contracts/SessionState.h
sample.o: ../src/core/TelemetryClientConfig.h ../src/core/common/Common.h
sample.o: ../src/core/TelemetryContext.h ../src/core/BaseTelemetryContext.h
sample.o: ../src/core/channel/TelemetryChannel.h
sample.o: ../src/core/TelemetryClientConfig.h ../src/core/TelemetryContext.h
sample.o: ../src/core/contracts/Contracts.h
sample.o: ../src/core/channel/utils/HttpRequest.h
sample.o: ../src/core/channel/utils/HttpResponse.h
sample.o: ../src/core/common/Common.h
sample.o: ../src/core/channel/utils/HttpHeaderFields.h
sample.o: ../src/core/channel/utils/HttpHeaderField.h
