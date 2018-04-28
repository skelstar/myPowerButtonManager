#ifndef myPowerButtonManager_h
#define myPowerButtonManager_h

#include <Arduino.h>

class myPowerButtonManager 
{
	public:

		enum StateCode {
			TN_TO_POWERING_UP = 0,
			STATE_POWERING_UP,
			TN_TO_POWERED_UP_WAIT_RELEASE,
			STATE_POWERED_UP_WAIT_RELEASE,
			TN_TO_RUNNING,
			STATE_RUNNING,
			TN_TO_POWERING_DOWN,
			STATE_POWERING_DOWN,
			TN_TO_POWERING_DOWN_WAIT_RELEASE,
			STATE_POWERING_DOWN_WAIT_RELEASE,
			TN_TO_POWER_OFF,
			STATE_POWER_OFF
		};


		typedef void ( *PowerUpEventCallback )( int state );

		myPowerButtonManager( int button, int activeState, long powerupMillis, long powerDownMillis, PowerUpEventCallback callback );
		void begin();
		void serviceButton(bool debug);
		bool isRunning();
		void setState(uint8_t state);
		uint8_t getState();

	private:

		bool wakeupCausedByButton();
		bool isPressed();

		// params
		uint8_t _buttonPin;
		uint8_t _state;
		uint8_t _activeState;
		long _powerUpMillis;
		long _powerDownMillis;

		long _heldDownStarted;

		PowerUpEventCallback _callback;

};

#endif