#include "Arduino.h"
#include "myPowerButtonManager.h"
/*
enum StateCode {
	ST_POWERING_UP = 0,
	ST_POWERED_UP_WAIT_RELEASE,
	ST_RUNNING,
	ST_POWERING_DOWN,
	ST_POWERING_DOWN_WAIT_RELEASE,
	ST_POWER_OFF
};
*/

myPowerButtonManager::myPowerButtonManager( int button, int activeState, long powerUpMillis, long powerDownMillis, PowerUpEventCallback callback ) {
	_buttonPin = button;
	_callback = callback;
	_activeState = activeState;
	_powerUpMillis = powerUpMillis;
	_powerDownMillis = powerDownMillis;

	esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, activeState); //1 = High, 0 = Low
}
//--------------------------------------------------------------------------------
void myPowerButtonManager::begin() {

	pinMode(_buttonPin, INPUT_PULLUP);

	if (wakeupCausedByButton()) {
		_state = ST_POWERING_UP;
		_callback(_state);
	}
	else {
		_state = ST_RUNNING;
		_callback(_state);
		_startPoweringUp = millis();
	}
}
//--------------------------------------------------------------------------------
void myPowerButtonManager::serviceButton() {

	switch (_state) {
		
		case ST_POWERING_UP:
			if (isPressed() == false) {
				_state = ST_POWER_OFF;
				_callback(_state);
			}
			else if (millis() - _startPoweringUp > _powerUpMillis) {
				_state = ST_POWERED_UP_WAIT_RELEASE;
				_callback(_state);
			}
			break;
		case ST_POWERED_UP_WAIT_RELEASE:
			if (isPressed() == false) {
				_state = ST_RUNNING;
				_callback(_state);
			}
			break;
		case ST_RUNNING:
			if (isPressed()) {
				_state = ST_POWERING_DOWN;
				_callback(_state);
				_startPoweringDown = millis();
			}
			break;
		case ST_POWERING_DOWN:
			if (isPressed() == false) {
				_state = ST_RUNNING;
				_callback(_state);
			}
			else if (millis() - _startPoweringDown > _powerDownMillis) {
				_state = ST_POWERING_DOWN_WAIT_RELEASE;
				_callback(_state);
			}
			break;
		case ST_POWERING_DOWN_WAIT_RELEASE:
			if (isPressed() == false) {
				_state = ST_POWER_OFF;
				_callback(_state);
			}
			break;
	}
}
//--------------------------------------------------------------------------------
bool myPowerButtonManager::wakeupCausedByButton() {

	esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
	return wakeup_reason >= 1 && wakeup_reason <= 5;
}
//--------------------------------------------------------------------------------
bool myPowerButtonManager::isPressed() {
	return digitalRead(_buttonPin) != _activeState;
}