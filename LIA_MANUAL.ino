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




void setup() {
 
// we must define the funtion of the pins becuase htye have multiple states they can be in
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
// since we only have 2 screens after 1 we want the counter to reset to 0
if (Select>1){
Select=0;  
}

//here we will read all the values from our digital and analog pins and storing there values for easy recall later


int Setpoint = 0;
bool btUP = digitalRead(4);
bool btDOWN = digitalRead(5);

int pot_bit = analogRead(A5);
//We map the CO value to our input potentiometer because they need to scale at the same rate but their max values are different
CO = map(pot_bit,0,1023,0,255);
// this is the first screen where we select our set point
if(Select==0){
// here we print our values onto the LCD 
lcd.setCursor(0, 0);
lcd.print("Set SP:");
//using the up and down push buttons we can change the Set point up and down
if(btUP=0){
Setpoint=Setpoint+10;
lcd.setCursor(0, 0);
lcd.print("Set SP:");
lcd.print(Setpoint);
Serial.println(Setpoint);
}
if(btDOWN=0){

Setpoint=Setpoint-10;
lcd.setCursor(0, 0);
lcd.print("Set SP:");
lcd.print(Setpoint);
Serial.println(Setpoint);
}
if(SP<0){
  SP=0;
}

}
if(Select==1){
//On this screen we print the PV which needs to no modification since its a value we read
lcd.setCursor(0, 0);
lcd.print("PV:");
lcd.print(PV);


}
analogWrite(3, 255);
float potvalue = (pot_bit/1023.0)*5.0;
int PV_raw = analogRead(A0);
//Serial.print(PV_raw);
//Serial.print("\t");
//Serial.println(pot_bit);




}
//pot value broken
// higest value is 950 and lowest 