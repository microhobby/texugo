CFLAGS 		= -O0 -g -o
MAIN_BATT 	= battery-app.cpp
APP_BATT 	= texugo-battery
MAIN_SOUND	= sound-sensor-app.cpp
APP_SOUND 	= texugo-sound-sensor
MAIN_GPIO	= texugo-gpio-app.cpp
APP_GPIO	= texugo-gpio-test
LIBS 		= -ludev -Ilib -Igpio
FILES_LIB 	= lib/FuelGauge.cpp lib/UdevListener.cpp gpio/GpioLib.cpp
ARGS		= -DDEBUG

compile:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP_BATT) $(FILES_LIB) $(MAIN_BATT) $(LIBS)
	$(CXX) $(CFLAGS) $(APP_SOUND) $(FILES_LIB) $(MAIN_SOUND) $(LIBS)

debug:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP_BATT) $(FILES_LIB) $(MAIN_BATT) $(ARGS) $(LIBS)
	$(CXX) $(CFLAGS) $(APP_SOUND) $(FILES_LIB) $(MAIN_SOUND) $(ARGS) $(LIBS)

tests:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP_GPIO) $(FILES_LIB) $(MAIN_GPIO) $(LIBS)

clean:
	rm $(APP_BATT) $(APP_SOUND)

clean-tests:
	rm $(APP_GPIO)
