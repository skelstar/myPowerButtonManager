#ifndef myPowerButtonManager_h
#define myPowerButtonManager_h

#include <Arduino.h>

class myPowerButtonManager 
{
	public:

		enum StateCode {
			TR_POWERING_UP = 0,
			ST_POWERING_UP,
			TR_POWERED_UP_WAIT_RELEASE,
			ST_POWERED_UP_WAIT_RELEASE,
			TR_RUNNING,
			ST_RUNNING,
			TR_POWERING_DOWN,
			ST_POWERING_DOWN,
			TR_POWERING_DOWN_WAIT_RELEASE,
			ST_POWERING_DOWN_WAIT_RELEASE,
			TR_POWER_OFF,
			ST_POWER_OFF
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

		long _startPoweringUp;
		long _startPoweringDown;

		PowerUpEventCallback _callback;

};

#endif