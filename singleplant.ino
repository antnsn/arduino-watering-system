//this is created for a 3d printer planter with integrated peristaltic pump running on 5v

int timer = 24;
int utsett = ((timer*3600) * 1000);

class plant
{
  int pumpPin;
  int vann;

  public:
  plant(int pPin, int amount)
  {
    pumpPin = pPin;
    pinMode(pumpPin, OUTPUT);

    vann = amount * 1000;
  }

  void vanning()
  {
    digitalWrite(pumpPin, HIGH);
    delay(vann);
    digitalWrite(pumpPin, LOW);
  }
};

//define pumpnumber and how log to water in seconds
//plant plant1(pin number, x seconds to keep pump running);
plant plant1(2,45);


void setup(){}


void loop() {

  plant1.vanning();
  delay(utsett);

}
