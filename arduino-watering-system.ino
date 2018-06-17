

String plant1 = "plant nr:1";
int relay1 = 2;
int sensor1 = A0;  
int sensorval1 = 0;

String plant2 = "plant nr:2";
int relay2 = 3;
int sensor2 = A1;  
int sensorval2 = 0;

String plant3 = "plant nr:3";
int relay3 = 4;
int sensor3 = A2; 
int sensorval3 = 0;

String plant4 = "plant nr:4";
int relay4 = 5;
int sensor4 = A3; 
int sensorval4 = 0;

String plant5 = "plant nr:5";
int relay5 = 6;
int sensor5 = A4; 
int sensorval5 = 0;

String plant6 = "plant nr:6";
int relay6 = 7;
int sensor6 = A5; 
int sensorval6 = 0;

String plant7 = "plant nr:7";
int relay7 = 8;
int sensor7 = A6; 
int sensorval7 = 0;

String plant8 = "plant nr:8";
int relay8 = 9;
int sensor8 = A7; 
int sensorval8 = 0;


int percent = 0;


void setup() {
Serial.begin(9600);      // open the serial port at 9600 bps:    

  //plant 1
  pinMode(relay1, OUTPUT); digitalWrite (relay1, HIGH); pinMode(sensor1, INPUT);

  //plant 2
  pinMode(relay2, OUTPUT); digitalWrite (relay2, HIGH); pinMode(sensor2, INPUT);

  //plant 3
  pinMode(relay3, OUTPUT); digitalWrite (relay3, HIGH); pinMode(sensor3, INPUT);

  //plant 4
  pinMode(relay4, OUTPUT); digitalWrite (relay4, HIGH); pinMode(sensor4, INPUT);

  //plant 5
  pinMode(relay5, OUTPUT); digitalWrite (relay5, HIGH); pinMode(sensor5, INPUT);

  //plant 6
  pinMode(relay6, OUTPUT); digitalWrite (relay6, HIGH); pinMode(sensor6, INPUT);

  //plant 7
  pinMode(relay7, OUTPUT); digitalWrite (relay7, HIGH); pinMode(sensor7, INPUT);

  //plant 8
  pinMode(relay8, OUTPUT); digitalWrite (relay8, HIGH); pinMode(sensor8, INPUT);
  

  

}

void loop() {

sensorval1 = analogRead(sensor1);
sensorval2 = analogRead(sensor2);
sensorval3 = analogRead(sensor3);
sensorval4 = analogRead(sensor4);
sensorval5 = analogRead(sensor5);
sensorval6 = analogRead(sensor6);
sensorval7 = analogRead(sensor7);
sensorval8 = analogRead(sensor8);


    percent = convertToPercent(sensorval1);
    if (percent > 35) {digitalWrite(relay1, HIGH);} else { watering(relay1,sensor1, plant1 );}
    percent = convertToPercent(sensorval2);
    if (percent > 35) {digitalWrite(relay2, HIGH);} else { watering(relay2,sensor2, plant2 );}
    percent = convertToPercent(sensorval3);
    if (percent > 35) {digitalWrite(relay3, HIGH);} else { watering(relay3,sensor3, plant3 );}
    percent = convertToPercent(sensorval4);
    if (percent > 35) {digitalWrite(relay4, HIGH);} else { watering(relay4,sensor4, plant4 );}
    percent = convertToPercent(sensorval5);
    if (percent > 35) {digitalWrite(relay5, HIGH);} else { watering(relay5,sensor5, plant5 );}
    percent = convertToPercent(sensorval6);
    if (percent > 35) {digitalWrite(relay6, HIGH);} else { watering(relay6,sensor6, plant6 );}
    percent = convertToPercent(sensorval7);
    if (percent > 35) {digitalWrite(relay7, HIGH);} else { watering(relay7,sensor7, plant7 );}
    percent = convertToPercent(sensorval8);
    if (percent > 35) {digitalWrite(relay8, HIGH);} else { watering(relay8,sensor8, plant8 );}

    delay(36000); 
}

 int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 845, 220, 0, 100);
  return percentValue;
} 

int watering(int value, int value2, String value3)
{


  Serial.println(value3 +" - Moisture: "+ percent +"%" );
  
  digitalWrite(value, LOW);
    delay(3000);
  digitalWrite(value, HIGH);
    delay(1000);
    
}


