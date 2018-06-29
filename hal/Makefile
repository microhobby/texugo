CFLAGS = -O0 -g -o
APP = texugo-app
LIBS = -ludev -Ilib
FILES_LIB = lib/FuelGauge.cpp lib/UdevListener.cpp
MAIN = texugo-app.cpp

fuel-gauge:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP) $(LIBS) $(FILES_LIB) $(MAIN)

debug:
	gdb $(APP) core

clean:
	rm texugo-app
	rm core
