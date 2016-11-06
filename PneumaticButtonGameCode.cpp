/*
 *	The code for pneumatic button game (the training study)
 *  Author: Zhentao Xu (UM Unique Name: frankxu; ID: 86137077)
 *  Date: Nov. 6th, 2016
 */




#define STATECODE_BEGIN						0
#define STATECODE_END						1
#define STATECODE_CALIBRATION_1				2
#define STATECODE_CALIBRATION_2				3
#define STATECODE_CONFIGURATION				4
#define STATECODE_G1_INITDATA				5
#define STATECODE_G1_WAITUSERINPUT			6
#define STATECODE_G1_SHOWRESULT				7
#define STATECODE_G1_DATASAVING				8




#define USERINPUTCODE_CALIBEATION_1 0
#define USERINPUT_CALIBEATION_1 'C'

#define USERINPUTCODE_CALIBEATION_2 1
#define USERINPUT_CALIBEATION_2 'D'



#define PIN_VALVE_0				0
#define PIN_VALVE_1				1
#define PIN_VALVE_2				2
#define PIN_VALVE_3				3
#define PIN_VALVE_4				4
#define PIN_VALVE_5				5
#define PIN_VALVE_6				6
#define PIN_VALVE_7				7


class StateManager{
public:
	StateManager(void){
		//Set current state
		currentState = STATECODE_BEGIN;

		//initilize state counter.
		for (int ii = 0; ii < 100; ii++){stateCounter[ii] = 0;}
	}
	int getCurrentState(){
		return currentState;

	}
	void gotoNextState(void){

		if (currentState == STATECODE_BEGIN){

			gotoState(STATECODE_CALIBRATION_1);

		}else if (currentState == STATECODE_CALIBRATION_1){

			if (getCurrentStateCounter() == 1){
				Serial.print("Input 'C' to do the first calibration\n");
				gotoState(STATECODE_CALIBRATION_1);
			}else{
				
				if (readUserInputFromSerial()== USERINPUTCODE_CALIBEATION_1){
					func_CalibrateForcePlate_1();
					gotoState(STATECODE_CALIBRATION_2);
				}

			}


		}else if (currentState == STATECODE_CALIBRATION_2){
			
			if (getCurrentStateCounter() == 1){
				Serial.print("Input 'D' to do the first calibration\n");
				gotoState(STATECODE_CALIBRATION_2);
			}else{

				if (readUserInputFromSerial() == USERINPUTCODE_CALIBEATION_2){
					func_CalibrateForcePlate_2();
					gotoState(STATECODE_CONFIGURATION);
				}
			}

		}else if (currentState == STATECODE_CONFIGURATION){
			valveNumber = PIN_VALVE_0;
			gotoState(STATECODE_G1_INITDATA);
		}else if (currentState == STATECODE_G1_INITDATA){

			pneuFunc_TurnOnVolve(valveNumber);

			gotoState(STATECODE_G1_WAITUSERINPUT);

		}else if (currentState == STATECODE_G1_WAITUSERINPUT){
			gotoState(STATECODE_G1_SHOWRESULT);
		}else if (currentState == STATECODE_G1_SHOWRESULT){
			gotoState(STATECODE_G1_DATASAVING);
		}else if (currentState == STATECODE_G1_DATASAVING){
			gotoState(STATECODE_G1_INITDATA);
			
		}
	}
	/*
		BEGIN ---> CALIBRATION1 ---> CALIBRATION2 ---> CONFIGURATION ---> G1_INITDATA ---> WAITUSERINPUT  --->.  G1_SHOWRESULT ----> G1_DATASAVING ------
		                                                                                         ^ 														|
		                                                                                         | 														|
		                                                                                         | 														|
		                                                                                         --------------------------------------------------------
	*/

	void init_Pin_Valve(){
		pinMode(PIN_VALVE_0,OUTPUT);
		pinMode(PIN_VALVE_1,OUTPUT);
		pinMode(PIN_VALVE_2,OUTPUT);
		pinMode(PIN_VALVE_3,OUTPUT);
		pinMode(PIN_VALVE_4,OUTPUT);
		pinMode(PIN_VALVE_5,OUTPUT);
		pinMode(PIN_VALVE_6,OUTPUT);
		pinMode(PIN_VALVE_7,OUTPUT);
	}



private:
	int currentState;
	void setCurrentState(int statecode){
		currentState = statecode;
	}


	void printCurrentStateToSerial(){
		Serial.print("[Curr State:]");
		Serial.print(currentState);
		Serial.println("");
	}
	int readUserInputFromSerial(){
		char ch = Serial.read();
		if (ch == USERINPUT_CALIBEATION_1){
			return USERINPUTCODE_CALIBEATION_1;
		}else if (ch == USERINPUT_CALIBEATION_2){
			return USERINPUTCODE_CALIBEATION_2;
		}
	}
	void gotoState(int statecode){
		currentState = statecode;
		printCurrentStateToSerial();
		stateCounter[currentState] += 1;
	}

	int stateCounter[100];
	
	int valveNumber;

	int getCurrentStateCounter(){
		return stateCounter[currentState];
	}


	void func_CalibrateForcePlate_1(){
			//TODO: Calibrate force plate.
		Serial.print("TODO:CALibration Force 1\n");
	}

	
	void func_CalibrateForcePlate_2(){
			//TODO: Calibrate force plate.
		Serial.print("TODO:CALibration Force 2\n");
	}

	void pneuFunc_TurnOnVolve(int valvepin){
		digitalWrite(valvepin,HIGH);
	}

	

};
StateManager sm;




void setup(){	
	Serial.begin(9600);
	sm.init_Pin_Valve();

}

void loop(){
	while(1){
		sm.gotoNextState();
		Serial.println(sm.getCurrentState());

		//Serial.print("IMHERE\n");
	}
}
