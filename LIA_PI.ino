//if we want to use the LCD display we must inclued a library 
#include <LiquidCrystal.h>
//We must then define the pins we will use for the LCD
LiquidCrystal lcd(7,8,9,10,11,12);

//here we define all the values we will use inclduign all our math variables along with where we will store out button values
int PBState = LOW;
int lastButtonState;
int currentButtonState;
int Select = 0;
int PV=0;
int Setpoint=500;

int CO=0;
float moreCO;
int error=0;
float pgain = 0.1;
float igain=0.2;
int integralaction;
unsigned long prevMill=0;
const long interval = 50;
unsigned long currentmills;
void setup() {
 // we must define the funtion of the pins becuase htye have multiple states they can be in
pinMode(3,OUTPUT);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
//we must begin the serial monitor to diplay all values we need
Serial.begin(9600);
//we must define the limits of our lcd display 
lcd.begin(16,2);
 // we must define the funtion of the pins becuase htye have multiple states they can be in
pinMode(6,INPUT_PULLUP);
currentButtonState = digitalRead(6);
}

void loop() {
//all this opration will allow us to use one button to toggle between all the different screen we want to use
lastButtonState    = currentButtonState;      // save the last state
currentButtonState = digitalRead(6);
//if the button is pressed it will increase the counter by 1
  if(lastButtonState == 1 && currentButtonState == 0) {

    Select = Select+1;
  
 
// since we only have 4 screens after 3 we want the counter to reset to 0
if (Select>3){
Select=0;  


} 
}
//here we will read all the values from our digital and analog pins and storing there values for easy recall later
int PV=analogRead(A0);
bool btUP = digitalRead(4);
bool btDOWN = digitalRead(5);


// this is the first screen where we select our set point
if(Select==0){
  //on every screen we do the math so that no matter our screen we can see the pv change 
   currentmills=millis(); // we are using the millis function to chekc for intervals because if we use Delay our code would be puased during that time not allowing us to change anything
  if (currentmills - prevMill >= interval) {

    prevMill = currentmills;
// here is the math explained in the report 
error=Setpoint-PV;
integralaction= (integralaction+error);
CO = (pgain*error)+(igain*integralaction);
moreCO=CO/10;
//we must cap off CO since its possible for it to exceed or go below its max or min states 
if(CO>255){
  CO=255;
}
if (CO<0){
  CO=0;
}
  }
// here we print our values onto the LCD 
lcd.setCursor(0, 0);
lcd.print("Set SP:");
lcd.print(Setpoint);
lcd.print(" ");
//using the up and down push buttons we can change the Set point up and down
if(btUP==0){
Setpoint=Setpoint+5;
delay(50);
//we once again restrict the systme to not exceed or go below it max and min values
if(Setpoint>1000){
  Setpoint=1000;
}
}
if(btDOWN==0){
Setpoint=Setpoint-5;
delay(50);
if(Setpoint<0){
  Setpoint=0;
}
}
//here we will write the CO we calculated and print all our values so we can see them in the serial monitor and plotter
analogWrite(3, CO);
Serial.print(PV);
Serial.print("\t");
Serial.print(CO);
Serial.print("\t");
Serial.print(error);
Serial.print("\t");
Serial.println(Setpoint);
}
//all the rest of the screen are iednetical to the first except the values they change are different but the math and Serial printing is the same
//(except the PV screen wehre the PV is not modified but only observed)
if(Select==1){
lcd.setCursor(0, 0);
lcd.print("Set Kp:");
lcd.print(pgain);
lcd.print(" ");
if(btUP==0){
pgain=pgain+0.01;
delay(50);

}
if(btDOWN==0){
pgain=pgain-0.01;
delay(50);
if(pgain<0){
  pgain=0;
}

}

}

if(Select==2){
lcd.setCursor(0, 0);
lcd.print("Set Ki:");
lcd.print(igain);
lcd.print(" ");
if(btUP==0){
igain=igain+0.01;
delay(50);

}
if(btDOWN==0){
igain=igain-0.01;
delay(50);
if(igain<0){
  igain=0;
}

}

}
if(Select==3){
  currentmills=millis();
  if (currentmills - prevMill >= interval) {

    prevMill = currentmills;
error=Setpoint-PV;
integralaction= (integralaction+error);
CO = (pgain*error)+(igain*integralaction);
moreCO=CO/10;
if(CO>255){
  CO=255;
}
if (CO<0){
  CO=0;
}
  }

lcd.setCursor(0, 0);
lcd.print( "PV:");
lcd.print(PV);
lcd.print("      ");
analogWrite(3, CO);

Serial.print(PV);
Serial.print("\t");
Serial.print(CO);
Serial.print("\t");
Serial.print(error);
Serial.print("\t");
Serial.println(Setpoint);

}

}
//pot value broken
// higest value is 950 