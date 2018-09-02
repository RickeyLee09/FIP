int Fan_INA = 9; 
int Fan_INB = 8;


//Quick accelerometer test
//X is on A0; Y is on A1; Z is on A2
 
//Analog input pins 0, 1, and 2
//are what I send the x,y, and z
//accelerometer outputs to, respectively
int xAxisPin = A5;
int yAxisPin = A2;
int zAxisPin = A1;
 
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
 
void setup()
{
  Serial.begin(9600);

  default_value_x = analogRead(xAxisPin);
   
  //I don't know if setting them to
  //input is necessary, but I do it
  //anyways.
  
//  pinMode(A0, INPUT);
//  pinMode(A1, INPUT);
//  pinMode(A2, INPUT);

  pinMode(Fan_INA,OUTPUT); 
  pinMode(Fan_INB,OUTPUT);
   
}
 
void loop()
{
  //Read the x, y, and z values from
  //the analog input pins
  xAxisValADC = analogRead(xAxisPin);
  yAxisValADC = analogRead(yAxisPin);
  zAxisValADC = analogRead(zAxisPin);
   
  //Convert the ADC values to millivolts
  xAxisValmV = xAxisValADC * mVPerADC;
  yAxisValmV = yAxisValADC * mVPerADC;
  zAxisValmV = zAxisValADC * mVPerADC;
   
  //This could be prettier. What's happening is the mid-point
  //voltage value is subtracted from the voltage recorded
  //from the analog input, and then that value is divided
  //by how many millivolts per g the accelerometer is
  //ouputing. This results in the value being printed
  //in units of g.
  
  Serial.println((xAxisValmV - supplyMidPointmV) / mVperg);
//  Serial.print("\t");
//  Serial.print((yAxisValmV - supplyMidPointmV) / mVperg);
//  Serial.print("\t");
//  Serial.print((zAxisValmV - supplyMidPointmV) / mVperg);
//  Serial.print("\t");   

//  Serial.print(xAxisValADC);
//  Serial.print("\t");
//  Serial.print(yAxisValADC);
//  Serial.print("\t");
//  Serial.print(zAxisValADC);
//  Serial.print("\t");

//  Serial.println();

//  if(xAxisValADC > (default_value_x + 30)){
//    digitalWrite(Fan_INA,LOW);
//    digitalWrite(Fan_INB,HIGH); 
////    delay(1000); 
//  }else{
//    digitalWrite(Fan_INA,LOW);
//    digitalWrite(Fan_INB,LOW); 
////    delay(1000); 
//  }
//   
//  delay(100);
}
