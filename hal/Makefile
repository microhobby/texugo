CFLAGS 		= -O0 -g -o
MAIN_BATT 	= battery-app.cpp
APP_BATT 	= texugo-battery
MAIN_SOUND	= sound-sensor-app.cpp
APP_SOUND 	= texugo-sound-sensor
MAIN_GPIO	= texugo-gpio-app.cpp
APP_GPIO	= texugo-gpio-test
LIBS 		= -ludev -Ilib -Igpio
FILES_LIB 	= lib/FuelGauge.cpp lib/UdevListener.cpp gpio/GpioLib.cpp

compile:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP_BATT) $(LIBS) $(FILES_LIB) $(MAIN_BATT)
	$(CXX) $(CFLAGS) $(APP_SOUND) $(LIBS) $(FILES_LIB) $(MAIN_SOUND)

debug:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP_BATT) $(LIBS) $(FILES_LIB) $(MAIN_BATT) -DDEBUG
	$(CXX) $(CFLAGS) $(APP_SOUND) $(LIBS) $(FILES_LIB) $(MAIN_SOUND) -DDEBUG

tests:
	ulimit -c unlimited
	$(CXX) $(CFLAGS) $(APP_GPIO) $(LIBS) $(FILES_LIB) $(MAIN_GPIO)

clean:
	rm $(APP_BATT) $(APP_SOUND)

clean-tests:
	rm $(APP_GPIO)