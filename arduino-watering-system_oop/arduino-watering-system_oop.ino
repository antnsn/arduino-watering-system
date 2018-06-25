
class plant
{
   int sensorPin;
   int pumpPin;

  public:
  plant(int sensPin, int pPin)
  {
    sensorPin = sensPin;
    pinMode(sensorPin, INPUT);
  
    pumpPin = pPin;
    pinMode(pumpPin, OUTPUT);
 
  }

  void status()
  {
    if(sensorPin == LOW)
    {
      digitalWrite(pumpPin, HIGH);
    }
    else
    {
      digitalWrite(pumpPin, LOW);
    }
  }
};

plant plant1(A0, 2);
plant plant2(A1, 3);
plant plant3(A2, 4);
plant plant4(A3, 5);
plant plant5(A4, 6);
plant plant6(A5, 7);
plant plant7(A6, 8);
plant plant8(A7, 9);


void setup() {}

void loop() {

  plant1.status();
  plant2.status();
  plant3.status();
  plant4.status();
  plant5.status();
  plant6.status();
  plant7.status();
  plant8.status();
  
}
