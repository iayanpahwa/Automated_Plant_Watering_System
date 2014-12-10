#include<Servo.h>      // For Servo Motors

#define threshold 600 // Defining Thresholds

#define wateringTime 5000 //5 seconds
#define wateringTime2 8000 //8 seconds

#define plantpos2 70    // plant 1 position 
#define plantpos1 145 // plant 2 position
// change position according to your pots
    
    // servo objects
Servo plantServo;



int plantSensor1 = A0;    // sensor pins  
int plantSensor2 = A1;

int value1 = 0;  //initializing sensor value & variables 
int value2 = 0;

int pump = 3; // water pump control pin

void watering1();
void watering2();
void setup()
{
  Serial.begin(9600);
  
 
  plantServo.attach(9);
  plantServo.write(20); //set servo at 20*
  
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW); //pump off at initial
}

void loop()
{
  value1= analogRead(plantSensor1);
  value2= analogRead(plantSensor2);  //Reading values from sensot
  
  Serial.println(value1);  //Displaying values on serial monitor for debugging
  Serial.println(value2);
   delay(2000); 
  
     if(value1 >= threshold)
     {
       watering1();  //control watering operations
     }
     
     else if(value2 >= threshold)
     {
       watering2();
      
    }
}



void watering1()
{
    
      
    plantServo.write(20);

    Serial.println("Watering Plant 1");
    
    for(int ppos=20; ppos<=plantpos1; ppos++)
    plantServo.write(ppos); // Take pipe to plant 1
    
    delay(3000); // wait for three seconds
   
    digitalWrite(pump, HIGH); //Pump onn
    delay(wateringTime); //Watering Time
    digitalWrite(pump, LOW); //Pump off
    delay(5000); //Wait till extra water flows out
    
    
      plantServo.write(20); //servo back to initial position
    
    delay(15000); //wait for 15 seconds before reading again, this will let water sets in soil
    
    
  }
  
  
  void watering2() //Suppose pot 2 is bigger and requires more water
  
  {
    Serial.println("Watering pot 2");
    
    int ppos = 20;    //initial servo positions

    for(ppos=20; ppos<=plantpos2; ppos++)
    {
      plantServo.write(ppos); //take pipe to pot 2
    }
    delay(2000); //wait for it to reach pot 2
    
    digitalWrite(pump, HIGH); //Pump onn
    delay(wateringTime2); //Watering Time
    
    digitalWrite(pump, LOW); //Pump off
    delay(3000);//for(ppos=plantpos1; ppos=0; ppos--)
   
    plantServo.write(20);
    delay(15000);
    
    
  }
