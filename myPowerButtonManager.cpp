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

}
//--------------------------------------------------------------------------------
void myPowerButtonManager::begin() {

	pinMode(_buttonPin, INPUT_PULLUP);

	switch (_buttonPin) {
		// case 1: esp_sleep_enable_ext0_wakeup(GPIO_NUM_1, activeState); break;
		case 2: esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, _activeState == 1 ? 0 : 1); break;
		case 3: esp_sleep_enable_ext0_wakeup(GPIO_NUM_3, _activeState == 1 ? 0 : 1); break;
		case 4: esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, _activeState == 1 ? 0 : 1); break;
		case 5: esp_sleep_enable_ext0_wakeup(GPIO_NUM_5, _activeState == 1 ? 0 : 1); break;
		case 6: esp_sleep_enable_ext0_wakeup(GPIO_NUM_6, _activeState == 1 ? 0 : 1); break;
		case 7: esp_sleep_enable_ext0_wakeup(GPIO_NUM_7, _activeState == 1 ? 0 : 1); break;
		case 8: esp_sleep_enable_ext0_wakeup(GPIO_NUM_8, _activeState == 1 ? 0 : 1); break;
		// case 9: esp_sleep_enable_ext0_wakeup(GPIO_NUM_9, _activeState == 1 ? 0 : 1); break;	// flash
		// case 10: esp_sleep_enable_ext0_wakeup(GPIO_NUM_10, _activeState == 1 ? 0 : 1); break;	// flash
		// case 11: esp_sleep_enable_ext0_wakeup(GPIO_NUM_11, _activeState == 1 ? 0 : 1); break;	// flash
		case 12: esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, _activeState == 1 ? 0 : 1); break;
		case 13: esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, _activeState == 1 ? 0 : 1); break;
		case 14: esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, _activeState == 1 ? 0 : 1); break;
		case 15: esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, _activeState == 1 ? 0 : 1); break;
		case 16: esp_sleep_enable_ext0_wakeup(GPIO_NUM_16, _activeState == 1 ? 0 : 1); break;
		case 17: esp_sleep_enable_ext0_wakeup(GPIO_NUM_17, _activeState == 1 ? 0 : 1); break;
		case 18: esp_sleep_enable_ext0_wakeup(GPIO_NUM_18, _activeState == 1 ? 0 : 1); break;	//SPI
		case 19: esp_sleep_enable_ext0_wakeup(GPIO_NUM_19, _activeState == 1 ? 0 : 1); break;	//SPI
		// case 20: esp_sleep_enable_ext0_wakeup(GPIO_NUM_20, activeState); break;	// illegal
		case 21: esp_sleep_enable_ext0_wakeup(GPIO_NUM_21, _activeState == 1 ? 0 : 1); break;	//i2c
		case 22: esp_sleep_enable_ext0_wakeup(GPIO_NUM_22, _activeState == 1 ? 0 : 1); break;	//i2c
		case 23: esp_sleep_enable_ext0_wakeup(GPIO_NUM_23, _activeState == 1 ? 0 : 1); break;	// didnt work
		// case 24: esp_sleep_enable_ext0_wakeup(GPIO_NUM_24,_activeState == 1 ? 0 : 1); break;
		case 25: esp_sleep_enable_ext0_wakeup(GPIO_NUM_25, _activeState == 1 ? 0 : 1); break;
		case 26: esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, _activeState == 1 ? 0 : 1); break;
		case 27: esp_sleep_enable_ext0_wakeup(GPIO_NUM_27, _activeState == 1 ? 0 : 1); break;
		// case 28: esp_sleep_enable_ext0_wakeup(GPIO_NUM_28,_activeState == 1 ? 0 : 1); break;
		// case 29: esp_sleep_enable_ext0_wakeup(GPIO_NUM_29,_activeState == 1 ? 0 : 1); break;
		// case 30: esp_sleep_enable_ext0_wakeup(GPIO_NUM_30,_activeState == 1 ? 0 : 1); break;
		// case 31: esp_sleep_enable_ext0_wakeup(GPIO_NUM_31,_activeState == 1 ? 0 : 1); break;
		case 32: esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, _activeState == 1 ? 0 : 1); break;
		case 33: esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, _activeState == 1 ? 0 : 1); break;
		case 34: esp_sleep_enable_ext0_wakeup(GPIO_NUM_34, _activeState == 1 ? 0 : 1); break;
		case 35: esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, _activeState == 1 ? 0 : 1); break;
		case 36: esp_sleep_enable_ext0_wakeup(GPIO_NUM_36, _activeState == 1 ? 0 : 1); break;
		case 37: esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, _activeState == 1 ? 0 : 1); break;
		case 38: esp_sleep_enable_ext0_wakeup(GPIO_NUM_38, _activeState == 1 ? 0 : 1); break;
		case 39: esp_sleep_enable_ext0_wakeup(GPIO_NUM_39, _activeState == 1 ? 0 : 1); break;
	}

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
				_state = ST_TR_RUNNING;
				_callback(_state);
			}
			break;
		case ST_TR_RUNNING:
			_state = ST_RUNNING;
			_callback(_state);
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
				_state = ST_TR_RUNNING;
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
bool myPowerButtonManager::isRunning() {
	return _state == ST_RUNNING;
}
//--------------------------------------------------------------------------------
void myPowerButtonManager::setState(uint8_t state) {
	// make sure state exists
	if (state == ST_POWERING_UP ||
		state == ST_POWERED_UP_WAIT_RELEASE ||
		state == ST_TR_RUNNING ||
		state == ST_RUNNING ||
		state == ST_POWERING_DOWN ||
		state == ST_POWERING_DOWN_WAIT_RELEASE ||
		state == ST_POWER_OFF) {
		_state = state;
		_callback(_state);
	}
}
//--------------------------------------------------------------------------------
uint8_t myPowerButtonManager::getState() {
	return _state;
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