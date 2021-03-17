#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 8, 9, 10, 11); //Creates a lcd object and defines the pins used on the Arduino

 const int buttonUp = 5; //Up button is digital pin 5
 const int buttonDown = 6; //Down button is digital pin 6
 const int buttonConf = 7; //Confirmation button is digital pin 7
 const int buttonStop = 12; //Emergency stop button is digital pin 13


 const int ledPin = 4;
 const int pumpPin = 3;

 int buttonStateUp = 0;
 int buttonStateDown = 0;
 int buttonStateConf = 0;
 int buttonStateStop = 0;

 boolean upButtonPressed;
 boolean downButtonPressed;
 boolean Toggle;

 int hours = 0;

 unsigned long cur_time;
 unsigned long prev_time = 0;
 unsigned long interval = 0;

 boolean confirmation;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); //Starts the lcd and defines the dimensions

  //Setting the buttons as input sources
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonConf, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Enter Hours");

   
   
  
 
}

void loop() {

  cur_time = millis();

  //Button states are checked every loop
  buttonStateUp = digitalRead(buttonUp);
  buttonStateDown = digitalRead(buttonDown);
  buttonStateConf = digitalRead(buttonConf);
  buttonStateStop = digitalRead(buttonStop);


  if (buttonStateStop == HIGH){


    confirmation = false;
    hours = 0;
    interval = 0;
    
  }
 
  

// These if statements are used for determining which button has been pressed
  if (buttonStateUp == HIGH){
    
    upButtonPressed = true;
  
  }
  else if (buttonStateDown ==HIGH){

    downButtonPressed = true;
     
  }
  else if(buttonStateConf == HIGH){
    
    confirmation = true;
    
  }
  else {
    
    upButtonPressed = false;
    downButtonPressed = false;
    Toggle = false;
    
  }


  //These if statements are used to prevent 'bouncing' which allows us to get an accurate hours reading from the user
  if (upButtonPressed == true && Toggle == false && confirmation == false)
  {
    downButtonPressed = false;
    Toggle = true;
    toggle();
  }
  else if(downButtonPressed == true && Toggle == false && confirmation == false){
     upButtonPressed = false;
     Toggle = true;
     toggle();
  }



    
    lcd.setCursor(0, 0);
    lcd.print("Hours = ");
    lcd.setCursor(9, 0);
    lcd.print(hours, DEC);

    if(confirmation == true){
      digitalWrite(ledPin, HIGH);
      
    }
    else{
      digitalWrite(ledPin, LOW);
    }


    if ((cur_time - prev_time >= interval) && confirmation == true){

    prev_time = cur_time;

    digitalWrite(3, HIGH); // Turns on pump when time is elapsed
    delay(2000);            // waits for 2 seconds


  }
  else{

   digitalWrite(3, LOW); // Pump should be off unless conditions are met
    
  }
   
  
}



 void toggle(){
  if (upButtonPressed == true){
    hours++;
  }
  if (downButtonPressed == true){
    if(hours <= 0){
      return;
    }
    else{
    hours--;
  }
  }
  lcd.clear();
  
  interval = hours * 1000;
   
  


   
}
