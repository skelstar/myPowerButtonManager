#include <myPowerButtonManager.h>

#define POWER_UP_BUTTON 13

void powerupEvent(int state);

myPowerButtonManager powerButton(POWER_UP_BUTTON, HIGH, 3000, 3000, powerupEvent);

void powerupEvent(int state) {

	switch (state) {
		case powerButton.ST_POWERING_UP:
			Serial.printf("State: ST_POWERING_UP\n");
			break;
		case powerButton.ST_POWERED_UP_WAIT_RELEASE:
			Serial.printf("State: ST_POWERED_UP_WAIT_RELEASE\n");
			break;
		case powerButton.ST_RUNNING:
			Serial.printf("State: ST_RUNNING\n");
			break;
		case powerButton.ST_POWERING_DOWN:
			Serial.printf("State: ST_POWERING_DOWN\n");
			break;
		case powerButton.ST_POWERING_DOWN_WAIT_RELEASE:
			Serial.printf("State: ST_POWERING_DOWN_WAIT_RELEASE\n");
			break;
		case powerButton.ST_POWER_OFF:
			Serial.printf("State: ST_POWER_OFF\n");
			delay(100);
			esp_deep_sleep_start();
			Serial.println("This will never be printed");
			break;
	}
}

//--------------------------------------------------------------------------------
void setup() {
	Serial.begin(9600);
	Serial.printf("\nmyPowerButtonManager\n");

	powerButton.begin();
}
//--------------------------------------------------------------------------------
void loop() {
	powerButton.serviceButton();

	delay(500);
}
//--------------------------------------------------------------------------------