CPPFLAGS = -std=c++11
SRCS = main.cpp risk_WTH.cpp risk_BMI.cpp risk_BFP.cpp
OBJS = main.o
DEPS = $(SRCS:.cpp=.d)

all: HealthCheck_WTH.exe HealthCheck_BMI.exe HealthCheck_BFP.exe

HealthCheck_%.exe: $(OBJS) risk_%.o
	g++ -o $@ $(CPPFLAGS) $^

%.o: %.cpp
	g++ -o $@ $(CPPFLAGS) -MMD -MP -c $<

-include $(DEPS)

clean:
	rm -f *.o *.exe *.d
# On Windows, use: del *.o *.exe *.d
# On Linux or MacOS, use: rm -f *.o *.exe *.d

.PRECIOUS: $(OBJS) risk_WTH.o risk_BMI.o risk_BFP.o