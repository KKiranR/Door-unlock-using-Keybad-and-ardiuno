#include <Keypad.h>

#include<LiquidCrystal.h>

#include<EEPROM.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


LiquidCrystal liquid_crystal_display(12,11,5,4,3,2);

char password[4];

char initial_password[4],new_password[4];

int i=0;



char key_pressed=0;

const byte rows = 4; 

const byte columns = 3; 

char hexaKeys[rows][columns] = {

{'1','2','3'},

{'4','5','6'},

{'7','8','9'},

{'*','0','#'}

};

byte row_pins[rows] = {0,1,6,7};

byte column_pins[columns] = {8,10,13};
   

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);




void setup()

{
   myservo.attach(9);
 

  liquid_crystal_display.begin(16,2);



  liquid_crystal_display.print("keypad doorLock ");

  delay(2000);

  liquid_crystal_display.clear();

  liquid_crystal_display.print("Enter Password");

  liquid_crystal_display.setCursor(0,1);

  initialpassword();
}




void loop()

{



  key_pressed = keypad_key.getKey();

  if(key_pressed=='*')

    change();

  if (key_pressed)

  {

    password[i++]=key_pressed;

    liquid_crystal_display.print(key_pressed);

      }

  if(i==4)

  {

    delay(200);

    for(int j=0;j<4;j++)

      initial_password[j]=EEPROM.read(j);

    if(!(strncmp(password, initial_password,4)))

    {

      liquid_crystal_display.clear();

      liquid_crystal_display.print("Pass Accepted");

      open_t();
     

      delay(2000);

      liquid_crystal_display.setCursor(0,1);

      liquid_crystal_display.print("Pres * to change");

      delay(2000);

      liquid_crystal_display.clear();

      liquid_crystal_display.print("Enter Password:");

      liquid_crystal_display.setCursor(0,1);

      i=0;




    }

    else

    {




      liquid_crystal_display.clear();

      liquid_crystal_display.print("Wrong Password");

      liquid_crystal_display.setCursor(0,1);

      liquid_crystal_display.print("Pres * to Change");

      delay(2000);

      liquid_crystal_display.clear();

      liquid_crystal_display.print("Enter Password");

      liquid_crystal_display.setCursor(0,1);

      i=0;




    }

  }

}

void change()

{

  int j=0;

  liquid_crystal_display.clear();

  liquid_crystal_display.print("Current Password");

  liquid_crystal_display.setCursor(0,1);

  while(j<4)

  {

    char key=keypad_key.getKey();

    if(key)

    {

      new_password[j++]=key;

      liquid_crystal_display.print(key);

       

    }

    key=0;

  }

  delay(500);




  if((strncmp(new_password, initial_password, 4)))

  {

    liquid_crystal_display.clear();

    liquid_crystal_display.print("Wrong Password");

    liquid_crystal_display.setCursor(0,1);

    liquid_crystal_display.print("Try Again");

    delay(1000);

  }

  else

  {

    j=0;

    liquid_crystal_display.clear();

    liquid_crystal_display.print("New Password:");

    liquid_crystal_display.setCursor(0,1);

    while(j<4)

    {

      char key=keypad_key.getKey();

      if(key)

      {

        initial_password[j]=key;

        liquid_crystal_display.print(key);

        EEPROM.write(j,key);

        j++;

     

      }

    }

    liquid_crystal_display.print("Pass Changed");

    delay(1000);

  }

  liquid_crystal_display.clear();

  liquid_crystal_display.print("Enter Password");

  liquid_crystal_display.setCursor(0,1);

  key_pressed=0;

}




void initialpassword(){

  for(int j=0;j<4;j++)

    EEPROM.write(j, j+49);

  for(int j=0;j<4;j++)

    initial_password[j]=EEPROM.read(j);

}
void open_t() {
  int pos=0;
  

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
   liquid_crystal_display.setCursor(0,1);
      liquid_crystal_display.print("closing..");
      delay(1000);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
