#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 8, 9, 10, 11); //Creates a lcd object and defines the pins used on the Arduino

 const int buttonUp = 5; //Up button is digital pin 5
 const int buttonDown = 6; //Down button is digital pin 6
 const int buttonConf = 7; //Confirmation button is digital pin 7

 int buttonStateUp = 0;
 int buttonStateDown = 0;
 int buttonStateConf = 0;

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

  lcd.setCursor(0, 0);
  lcd.print("Enter Hours");
  
 
}

void loop() {

  cur_time = millis();

  //Button states are checked every loop
  buttonStateUp = digitalRead(buttonUp);
  buttonStateDown = digitalRead(buttonDown);
  buttonStateConf = digitalRead(buttonConf);
  

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


    if ((cur_time - prev_time >= interval) && confirmation == true){

    prev_time = cur_time;

    lcd.setCursor(0, 1);
    lcd.print("Time elapsed");
    delay(2000);
    lcd.clear();

  }


   
  
}



 void toggle(){
  if (upButtonPressed == true){
    hours++;
  }
  if (downButtonPressed == true){
    hours--;
  }
  lcd.clear();
  
  interval = hours * 1000;
   
  


   
}
