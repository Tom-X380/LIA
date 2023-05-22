//if we want to use the LCD display we must inclued a library 
#include <LiquidCrystal.h>
//We must then define the pins we will use for the LCD
LiquidCrystal lcd(7,8,9,10,11,12);
//here we define all the values we will use inclduign all our math variables along with where we will store out button values
int CO =0;
int PBState = LOW;
int lastButtonState;
int currentButtonState;
int Select = 0;
int Setpoint;
int Hyst;
int CO = 0;
int error= 0;
float pgain =2.0;

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
  
  }
// since we only have 3 screens after 2 we want the counter to reset to 0
if (Select>2){
Select=0;  
}
//here we will read all the values from our digital and analog pins and storing there values for easy recall later

int PV=analogRead(A0);
bool btUP = digitalRead(4);
bool btDOWN = digitalRead(5);
Serial.println("\t");

int pot_bit = analogRead(A5);
CO = map(pot_bit,0,1023,0,255);
// this is the first screen where we select our set point
if(Select==0){
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
if(Setpoint>950){
  Setpoint=950;
}
}
if(btDOWN==0){
Setpoint=Setpoint-5;
delay(50);
if(Setpoint<0){
  Setpoint=0;
}
}
// here we print all our values so we can see them in the serial monitor and plotter
Serial.print(PV);
Serial.print("\t");
Serial.print(Hyst);
Serial.print("\t");
Serial.println(Setpoint);
//here we will write the CO we calculated 
if(PV <=Setpoint-Hyst){

analogWrite(3, 255);

}
if(PV>=Setpoint+Hyst){
    
analogWrite(3, 0);

}
}
//all the rest of the screen are iednetical to the first except the values they change are different but the math and Serial printing is the same
//(except the PV screen wehre the PV is not modified but only observed)
if(Select==1){
lcd.setCursor(0, 0);
lcd.print("Set HYST:");
lcd.print(Hyst);
lcd.print(" ");
if(btUP==0){
Hyst=Hyst+1;
delay(50);

}
if(btDOWN==0){
Hyst=Hyst-1;
delay(50);
if(Hyst<0){
  Hyst=0;
}
}
Serial.print(PV);
Serial.print("\t");
Serial.print(Hyst);
Serial.print("\t");
Serial.println(Setpoint);
if(PV <=Setpoint-Hyst){

analogWrite(3, 255);

}
if(PV>=Setpoint+Hyst){
    
analogWrite(3, 0);

}
}

if(Select==2){
int Set2 = Setpoint/10;
lcd.setCursor(0, 0);
lcd.print( "PV:");
lcd.print(PV);
lcd.print("      ");
if(PV <=Setpoint-Hyst){

analogWrite(3, 255);

}
if(PV>=Setpoint+Hyst){
    
analogWrite(3, 0);

}


Serial.print(PV);
Serial.print("\t");
Serial.print(Hyst);
Serial.print("\t");
Serial.print(Set2);


}

}
//pot value broken
// higest value is 950 and lowest 