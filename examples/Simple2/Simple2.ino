#include <myPowerButtonManager.h>


void powerupEvent(int state);
int powerButtonIsPressed();

#define POWER_WAKE_BUTTON_PIN	13
#define POWER_OTHER_BUTTON_PIN	22

myPowerButtonManager powerButton(POWER_WAKE_BUTTON_PIN, HIGH, 3000, 3000, powerupEvent, powerButtonIsPressed);

int powerButtonIsPressed() {
	return digitalRead(POWER_WAKE_BUTTON_PIN) == 0 && 
			digitalRead(POWER_OTHER_BUTTON_PIN) == 0;
}

void powerupEvent(int state) {

	Serial.printf("State: %d\n", state);

	switch (state) {
		case powerButton.TN_TO_POWERING_UP:
			Serial.println("TN_TO_POWERING_UP");
			break;
		case powerButton.TN_TO_POWERED_UP_WAIT_RELEASE:
			Serial.println("TN_TO_POWERED_UP_WAIT_RELEASE");
			break;
		case powerButton.TN_TO_RUNNING:
			Serial.println("TN_TO_RUNNING");
			break;
		case powerButton.TN_TO_POWERING_DOWN:
			Serial.println("TN_TO_POWERING_DOWN");
			break;
		case powerButton.TN_TO_POWERING_DOWN_WAIT_RELEASE:
			Serial.println("TN_TO_POWERING_DOWN_WAIT_RELEASE");
			break;
		case powerButton.TN_TO_POWER_OFF:
			Serial.println("TN_TO_POWER_OFF");
			esp_deep_sleep_start();
			Serial.println("This will never be printed");
			break;
	}
}

void setup() {
	Serial.begin(9600);
	Serial.printf("Ready\n");

	pinMode(POWER_WAKE_BUTTON_PIN, INPUT_PULLUP);
	pinMode(POWER_OTHER_BUTTON_PIN, INPUT_PULLUP);
//	digitalWrite(POWER_BUTTON_PIN, HIGH);

	powerButton.begin(0);
}

void loop() {
	powerButton.serviceButton();
}