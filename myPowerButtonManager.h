#ifndef myPowerButtonManager_h
#define myPowerButtonManager_h

#include <Arduino.h>

class myPowerButtonManager 
{
	public:

		enum StateCode {
			ST_POWERING_UP = 0,
			ST_POWERED_UP_WAIT_RELEASE,
			ST_TR_RUNNING,
			ST_RUNNING,
			ST_POWERING_DOWN,
			ST_POWERING_DOWN_WAIT_RELEASE,
			ST_POWER_OFF
		};


		typedef void ( *PowerUpEventCallback )( int state );

		myPowerButtonManager( int button, int activeState, long powerupMillis, long powerDownMillis, PowerUpEventCallback callback );
		void begin();
		void serviceButton();
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