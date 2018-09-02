#include <Servo.h>  //add '<' and '>' before and after servo.h
Servo servo;

#include <Encoder.h>
Encoder myEnc(6, 7);

#include <IRremote.h>

//#define encoder0PinA 3
//#define encoder0PinB 4
//#define encoder0Btn 5
//int encoder0Pos = 0;
//int valRotary,lastValRotary;

int servoPin = 10;  
int servoAngle = 10;   // servo position in degrees
int control_signal;

int Fan_INA = 9; 
int Fan_INB = 8;
int delay_time = 200;

long oldPosition  = -999;

int button = 0;

const int IR_RECV_PIN = 7;
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

//Quick accelerometer test
//X is on A0; Y is on A1; Z is on A2
 
//Analog input pins 0, 1, and 2
//are what I send the x,y, and z
//accelerometer outputs to, respectively
int xAxisPin = A3;
int yAxisPin = A4;
int zAxisPin = A5;
 
//Variables to hold the returned
//ADC data from the analog input
//pins
int xAxisValADC = 0;
int yAxisValADC = 0;
int zAxisValADC = 0;
 
//Variables to hold the voltage
//values after converting from ADC
//units to mV
float xAxisValmV = 0;
float yAxisValmV = 0;
float zAxisValmV = 0;
 
//My Arduino Uno has a 10-bit
//AD converter, with a max value
//of 1023
int ADCMaxVal = 1023;
 
//The AD converter voltage
//is powered by 5V
float mVMaxVal = 5000;
 
//I measured the power going to the
//accelerometer as actually being 
//3230 mV, so I use this value to 
//define the mid-point
float supplyMidPointmV = 3230 / 2;
 
//Since the supply is actually 3230
//mV, I know the output will be 323mV
//per 1g detected
int mVperg = 323;
 
//Multiply any acquired ADC value
//by mVPerADC to convert to mV
float mVPerADC = mVMaxVal / ADCMaxVal;

int default_value_x;
float xVal;

int ct = 0;
int ct2 = 0;
int ct3 = 0;
 
void setup(){
  Serial.begin(9600);  
  servo.attach(servoPin);

  default_value_x = analogRead(xAxisPin);
  
  pinMode(Fan_INA,OUTPUT); 
  pinMode(Fan_INB,OUTPUT);

  irrecv.enableIRIn();
  irrecv.blink13(true);

  Serial.println(delay_time);
}
 
 
void loop(){

  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    button = Serial.read(); // Reads the data from the serial port
  }


// Read Remote IR data
  if (irrecv.decode(&results)){
      if (results.value == 0xFF30CF){
        button = '1';
      } else if (results.value == 0xFF18E7){
        button = '2';
      }
      else if (results.value == 0XFF7A85){
        button = '3';
      }
      irrecv.resume();
  }


// Read Encoder
  long newPosition = myEnc.read();

  accelerometer();

  if(button == '1'){ 
    ct = ct + 1;
    servo.write(servoAngle);
    delay(350);
    if(ct == 1){
      digitalWrite(Fan_INA, HIGH);
      digitalWrite(Fan_INB, LOW);
      delay(delay_time);
      digitalWrite(Fan_INA, LOW);
      digitalWrite(Fan_INB, LOW);
    }
  }
  else if (button == '2'){
    servo.write(servoAngle); 
    ct = 0;
  }
  else if (button == '3'){
//    Serial.println("Released");
     servo.write(180);
     digitalWrite(Fan_INA,LOW);
     digitalWrite(Fan_INB,LOW); 
     ct = 0;
     ct2 = 0;
     ct3 = 0;
   }
   else if(button == '-'){
      ct2 = ct2 + 1;
      if(ct2 == 1){
        delay_time  = delay_time - 50;
        Serial.println(delay_time);
        button = '3';
      }
   }
    else if(button == '+'){
        ct3 = ct3 + 1;
        if(ct3 == 1){
          delay_time  = delay_time + 50;
          Serial.println(delay_time);
          button = '3';
        }
   }
   

// ------------------------------------------

}


void accelerometer_fan(){
  //Read the x, y, and z values from
  //the analog input pins
  xAxisValADC = analogRead(xAxisPin);
  yAxisValADC = analogRead(yAxisPin);
  zAxisValADC = analogRead(zAxisPin);
   
  //Convert the ADC values to millivolts
  xAxisValmV = xAxisValADC * mVPerADC;
  yAxisValmV = yAxisValADC * mVPerADC;
  zAxisValmV = zAxisValADC * mVPerADC;

  xVal = (xAxisValmV - supplyMidPointmV) / mVperg;

//  Serial.println(xVal);
}

void accelerometer(){
  //Read the x, y, and z values from
  //the analog input pins
  xAxisValADC = analogRead(xAxisPin);
  yAxisValADC = analogRead(yAxisPin);
  zAxisValADC = analogRead(zAxisPin);
   
  //Convert the ADC values to millivolts
  xAxisValmV = xAxisValADC * mVPerADC;
  yAxisValmV = yAxisValADC * mVPerADC;
  zAxisValmV = zAxisValADC * mVPerADC;

  xVal = (xAxisValmV - supplyMidPointmV) / mVperg;
//  Serial.println(xVal);

}

void activeFan(){
  if(xVal < -0.2){
    digitalWrite(Fan_INA, HIGH);
    digitalWrite(Fan_INB, LOW);
    delay(250);
  }
  else if(xVal > 0.9){
    digitalWrite(Fan_INA, LOW);
    digitalWrite(Fan_INB, HIGH);
    delay(250);
  }else{
    digitalWrite(Fan_INA, LOW);
    digitalWrite(Fan_INB, LOW);
  }
}

