#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>


LiquidCrystal_I2C lcd(0x27,16,2);

// ultrasonic sensor
#define echoPin 2 
#define trigPin 3 

//buzz
int buzz = 4;

//irsensor
int irsensor = 5;
int valueirsensor = 0;

long duration; 
int distance;

int count = 0;

bool state1 = false;
bool state2 = false;

int state3 = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(irsensor, INPUT);
  Timer1.initialize(100);
  Timer1.attachInterrupt(runirsensor);
  Serial.begin(9600); 
  lcd.setCursor(4,0);
  lcd.print("welcome");
  lcd.setCursor(0,1);
  lcd.print("count =");
}
void loop() {
  //irsensor
  if (state3 == 1 && state2 == false ){  //pnp
    count = count - 1;
    lcd.setCursor(8,1);
    lcd.print("  ");
    lcd.setCursor(8,1);
    lcd.print(count);
    state2 = true;
    }

  if (valueirsensor == HIGH){
    state2 = false;
    state3 = 0;
    }
  
  //ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 

  if (count < 0){
    count = 0;
    }



  if (distance <= 40 && distance > 0 && state1 == false){
    count++;
    lcd.setCursor(8,1);
    lcd.print("  ");
    lcd.setCursor(8,1);
    lcd.print(count);
    state1 = true;
    }

  if (distance >= 41){
    state1 = false;
    }
  

  if (count >= 11){
    digitalWrite(buzz, HIGH);
    Serial.println("buzz on");
    delay(3000);
    count = 10;
    }

  else{
    digitalWrite(buzz, LOW);
    //Serial.println("buzz off");
    }

 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm ");
  Serial.print("count: ");
  Serial.println(count);
  
}


void runirsensor(){
  //irsensor
  valueirsensor = digitalRead(irsensor);

  if(valueirsensor == LOW){
    state3 = 1;
    }

  }
