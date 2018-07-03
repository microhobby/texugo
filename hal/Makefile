CFLAGS 		= -O0 -g -o
MAIN_BATT 	= battery-app.cpp
APP_BATT 	= texugo-battery
MAIN_SOUND	= sound-sensor-app.cpp
APP_SOUND 	= texugo-sound-sensor
LIBS 		= -ludev -Ilib
FILES_LIB 	= lib/FuelGauge.cpp lib/UdevListener.cpp

compile:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP_BATT) $(LIBS) $(FILES_LIB) $(MAIN_BATT)
	$(CXX) $(CFLAGS) $(APP_SOUND) $(LIBS) $(FILES_LIB) $(MAIN_SOUND)

clean:
	rm $(APP_BATT) $(APP_SOUND)
