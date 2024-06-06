#include <PS2X_lib.h> 
#include <SparkFun_TB6612.h>
#include <Servo.h>

Servo servo1,servo2,servo3;

int pos1=0;
int pos2=0;
int pos3=0;

#define PS2_DAT        10  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        13  //16  這是ATT
#define PS2_CLK        12  //17

const int In1=52;
const int In2=50;
const int ENA=A14;
const int In3=48;
const int In4=46;
const int ENB=A15;

#define pressures   false
#define rumble      false

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {

  Serial.begin(57600);
  delay(300);
  Serial.println("Start.");

  servo2.attach(3);
  servo2.write(0);
  servo3.attach(4);
  servo3.write(0);
  servo1.attach(2);
  servo1.write(0);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    ; // Serial.print("Found Controller, configured successful ");
    ; // Serial.print("pressures = ");
	if (pressures)
	  ; // Serial.println("true ");
	else
	  ; // Serial.println("false");
	; // Serial.print("rumble = ");
	if (rumble)
	  ; // Serial.println("true)");
	else
	  ; // Serial.println("false");
    ; // Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    ; // Serial.println("holding L1 or R1 will print out the analog stick values.");
    ; // Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    ; // Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    ; // Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    ; // Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  ; // Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      ; // Serial.print("Unknown Controller type found ");
      break;
    case 1:
      ; // Serial.print("DualShock Controller found ");
      break;
    case 2:
      ; // Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      ; // Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
  

  
  //servo1.write(0);
  
  

  delay(3000);
}

bool PadPressed=0;

void Stop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void Forward(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void Backward(){
  digitalWrite(In2, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In3, LOW);
}

void Left(){
  digitalWrite(In2, HIGH);
  digitalWrite(In1, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void Right(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In4, HIGH);
  digitalWrite(In3, LOW);
}




void loop() {
  
  if(error == 1) {//skip loop if no controller found
  
  setup();
  
  Left();
  delay(100);
  Stop();
    return; 
  }
  
  

  ps2x.read_gamepad(false, vibrate);
  PadPressed=0;
  
  if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
      ; // Serial.print("Up\n");
      Forward();
      PadPressed=1;
    }
  if(ps2x.Button(PSB_PAD_RIGHT)){
      Right();
    ; // Serial.print("Right\n");
    
    PadPressed=1;
  }
  if(ps2x.Button(PSB_PAD_LEFT)){
    Left();
    ; //Serial.print("LEFT\n");
    
    PadPressed=1;
  }
  if(ps2x.Button(PSB_PAD_DOWN)){
    ; // Serial.print("DOWN\n");
    Backward();
    PadPressed=1;
  } 
  if(!PadPressed){
    
    Stop();
    
  }

  

  if(ps2x.Button(PSB_L1)){
    pos1+=3;
    if(pos1>180){
      pos1=180;
    }
    servo1.write(pos1);
    Serial.print("pos1: ");
    Serial.println(pos1);

  }
  if(ps2x.Button(PSB_L2)){
    pos1-=3;
    if(pos1<0){
      pos1=0;
    }
    servo1.write(pos1);
    Serial.print("pos1: ");
    Serial.println(pos1);
  }

  if(ps2x.Button(PSB_R1)){
    pos2+=3;
    if(pos2>180){
      pos2=180;
    }
    servo2.write(pos2);
    Serial.print("pos2: ");
    Serial.println(pos2);

  }
  if(ps2x.Button(PSB_R2)){
    pos2-=3;
    if(pos2<0){
      pos2=0;
    }
    servo2.write(pos2);
    Serial.print("pos2: ");
    Serial.println(pos2);
  }

  if(ps2x.Button(PSB_TRIANGLE)){
    pos3+=3;
    if(pos3>180){
      pos3=180;
    }
    servo3.write(pos3);
    Serial.print("pos3: ");
    Serial.println(pos3);

  }
  if(ps2x.Button(PSB_CROSS)){
    pos3-=3;
    if(pos3<0){
      pos3=0;
    }
    servo3.write(pos3);
    Serial.print("pos3: ");
    Serial.println(pos3);
  }
  


 
  delay(50);
}
