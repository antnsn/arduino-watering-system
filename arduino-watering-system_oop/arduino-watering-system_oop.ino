class Plant {
  int sensorPin;
  int pumpPin;

public:
  Plant(int sensPin, int pPin) {
    sensorPin = sensPin;
    pinMode(sensorPin, INPUT);
    pumpPin = pPin;
    pinMode(pumpPin, OUTPUT);
  }

  void waterPlant() {
    if (digitalRead(sensorPin) == LOW) {
      digitalWrite(pumpPin, HIGH);
    } else {
      digitalWrite(pumpPin, LOW);
    }
  }
};

const int numPlants = 8;
Plant plants[numPlants] = {
  Plant(A0, 2),
  Plant(A1, 3),
  Plant(A2, 4),
  Plant(A3, 5),
  Plant(A4, 6),
  Plant(A5, 7),
  Plant(A6, 8),
  Plant(A7, 9)
};

void setup() {
  // Add any setup code if needed
}

void loop() {
  for (int i = 0; i < numPlants; i++) {
    plants[i].waterPlant();
  }
}
