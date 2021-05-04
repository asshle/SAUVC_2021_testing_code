#include <Servo.h>

enum motorState{Off , Idle , Running};
struct PropelsionMotor
{
  int pinNo;
  int armingAngle;
  int speedFreq ; 
  motorState motorState = Off; 
  Servo motor; 
};

PropelsionMotor motors[4];


//=========Function Header=====================
//void motorSetParam(PropelsionMotor motor ,int _pinNo ,int _armingAngle , int _speedFreq );
//void initMotor(); 
//void motorSetSpeed(PropelsionMotor motor);



//===========TEMP HOLDING VALUE================
int value=map(89,0,180,1000,2000);

//=========== MAIN INIT LOOP===================
void setup() {
  // put your setup code here, to run once:
  
  /*motors[0].pinNo = 11 ;
  motors[0].armingAngle = 89;
  motors[0].speedFreq = map(89,0,180,1000,2000);*/

  Serial.begin(9600);
  motorSetParam(motors[0] ,11,89, map(89,0,180,1000,2000) );
  //TODO: switch to this once testing for 5 motors 
  /*for(int i =0 ; i<=motors.length(); i++)
  {
    initMotor(motors[i]);
  }*/
  
  initMotor(motors[0]);
}

//============== MAIN CONTROL LOOP ===============
void loop() 
{
  //TODO : IMPLEMENT TIME SLICING CODE HERE : 
 motorSetSpeed(motors[0],value);
}

//====================INIT CODE===========================================
void motorSetParam(PropelsionMotor _motor ,int _pinNo ,int _armingAngle , int _speedFreq )
{
  _motor.pinNo = _pinNo;
  _motor.motor.attach(_pinNo);
  _motor.armingAngle = _armingAngle;
  _motor.speedFreq = _speedFreq;
}
void initMotor(PropelsionMotor _motor)
{
  delay(2000); // allow for ESC side(pre built) code to settle
  Serial.println("initMotor : Motor Arming");
  _motor.motor.write(_motor.armingAngle);
  delay(500);
  Serial.println("initMotor : Motor Armed ");
}

//============================COMMS CODE ==================================
void serialEvent()
{
  //!WARNING : TEMP CODE REPLACE WITH LOOK UP FUCNTION FOR DYNAMIC COMMS METHOD
  String readValue = Serial.readString(); 
  //readValue.flush();
  value = readValue.toInt(); 
  Serial.print("ReadValue : ");Serial.println(readValue);
  Serial.print("ActualValue : ");Serial.println(value);
}

//============================MOTOR CONTROL CODE ==================================
void motorSetSpeed(PropelsionMotor _motor,int _speedFreq)
{
  //TODO:SCALE THIS UP TO 4 MOTORS FOR EASE OF CONTROL 
  _motor.speedFreq  = _speedFreq;
  _motor.motor.writeMicroseconds(_speedFreq);
  Serial.print("Motor Speed change : ");Serial.println(_motor.speedFreq);
}
