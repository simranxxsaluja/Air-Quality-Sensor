#include <Wire.h> //including the I2C library for communication

#include <LiquidCrystal_I2C.h> //Library for I2C LCD
LiquidCrystal_I2C lcd(0x27,16,2); //Creating I2C LCD object

#include <dht.h> //dht sensor library
#define datapin 7 // output pin specification for dht sensor
dht DHT;

//defining the buzzer, mq sensor, and rgb led
int buzz = 8;
int mq135 = A0;
int r = 9;
int g = 10;
int b = 11;

void setup() {
  Serial.begin(9600);//baud rate
  pinMode(mq135, INPUT); //mq sensor
  pinMode(r, OUTPUT); //rgb led 
  pinMode(g, OUTPUT); //rgb led
  pinMode(b, OUTPUT); //rgb led
  pinMode(buzz, OUTPUT); //buzzer
  
  lcd.init();  // initiating LCD                  
  lcd.backlight(); // turning on backlight for LCD
}

void loop() {
  int MQsensor = analogRead(A0); // read the MQ sensor
  
  int readdata = DHT.read11(datapin) ; //dht sensor 
  double tc = DHT.temperature ; //dht temp input
  double h = DHT.humidity; //dht humidity input
  double tf = (tc * 9.0) / 5.0 + 32.0; //conversion for temp to farenheight

  if(MQsensor<500) // Air Quality is Safe
 { 
    lcd.setCursor(0,0);
    lcd.print("Air Quality Safe.");
    delay(2000);
    lcd.clear(); //printing on LCD that AQI is safe
    
    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    lcd.print(tf);
    lcd.print("°F");
    delay(5000);
    lcd.clear(); //printing temperature on LCD
    
    lcd.setCursor(0,0);
    lcd.print("Humidity = ");
    lcd.print(h);
    lcd.print("%");
    delay(5000);
    lcd.clear(); //printing humidity on LCD
  
    Serial.print(" Temperature= ");
    Serial.print(tc);
    Serial.print("  ");
    Serial.print("°C   | ");
    Serial.print(tf); // conversion from degree to Fahrenheit
    Serial.print(" ");
    Serial.println("°F");
    Serial.print(" Humidity= ");
    Serial.print(h);
    Serial.println(" % ");
    Serial.println("");
    delay(2000); //printing temperature and humidity on serial monitor

    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    noTone(8); //RGB LED and buzzer application
  }

    if(MQsensor>=500 and MQsensor<= 600) // Air Quality is Average
 { 
    lcd.setCursor(0,0);
    lcd.print("Air Quality Avg.");
    delay(2000);
    lcd.clear(); //printing AQI is Avg on LCD
    
    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    lcd.print(tf);
    lcd.print("°F");
    delay(5000);
    lcd.clear(); //Printing temp on LCD
    
    lcd.setCursor(0,0);
    lcd.print("Humidity = ");
    lcd.print(h);
    lcd.print("%");
    delay(5000);
    lcd.clear(); //printing humidity on LCD
  
    Serial.print(" Temperature= ");
    Serial.print(tc);
    Serial.print("  ");
    Serial.print("°C   | ");
    Serial.print(tf); // conversion from degree to Fahrenheit
    Serial.print(" ");
    Serial.println("°F");
    Serial.print(" Humidity= ");
    Serial.print(h);
    Serial.println(" % ");
    Serial.println("");
    delay(2000); // printing temp and humidity on serial monitor

    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    noTone(8); //setting up thergb led and buzzer
  }
  
  if(MQsensor>600) // Air Quality is Unsafe
 {
    tone(buzz, 500, 200);
    delay(100);
    tone(buzz, 1000, 200);
    delay(100);
    tone(buzz, 2000, 200);
    delay(100);
    tone(buzz, 3000, 200);
    delay(100);
    tone(buzz, 4000, 200);
    delay(100);
    tone(buzz, 3000, 200);
    delay(100);
    tone(buzz, 2000, 200);
    delay(100);
    tone(buzz, 1000, 200);
    delay(100); //buzzer tone sequence for unsafe air quality detection
    
    digitalWrite(r, HIGH);
    delay(100);
    digitalWrite(r, LOW);
    delay(100);
    digitalWrite(g, LOW);
    digitalWrite(b, LOW); //flashing light sequence for unsafe air quality
    
    lcd.setCursor(0,0);
    lcd.print("Unsafe AQI!");
    delay(2000);
    lcd.clear(); //printing unsafe air quality on the LCD
    
    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    lcd.print(tf);
    lcd.print("°F");
    delay(2000);
    lcd.clear(); //printing temp on LCD
    
    lcd.setCursor(0,0);
    lcd.print("Humidity = ");
    lcd.print(h);
    lcd.print("%");
    delay(5000);
    lcd.clear(); //printing humidity on the LCD

    Serial.print(" Temperature= ");
    Serial.print(tc);
    Serial.print("  ");
    Serial.print("°C   | ");
    Serial.print(tf); // conversion from degree to Fahrenheit
    Serial.print(" ");
    Serial.println("°F");
    Serial.print(" Humidity= ");
    Serial.print(h);
    Serial.println(" % ");
    Serial.println("");
    delay(2000); //printing the temp and humidity on serial monitor
  }

  Serial.println(MQsensor); //printing air quality level on serial monitor
}
