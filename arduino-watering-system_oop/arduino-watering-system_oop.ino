// Define a class for a plant
class Plant {
  int sensorPin;  // Pin connected to the plant's sensor
  int pumpPin;    // Pin connected to the plant's pump

public:
  // Constructor to initialize pins
  Plant(int sensPin, int pPin) {
    sensorPin = sensPin;
    pinMode(sensorPin, INPUT);
    pumpPin = pPin;
    pinMode(pumpPin, OUTPUT);
  }

  // Method to water the plant based on sensor status
  void waterPlant() {
    if (digitalRead(sensorPin) == LOW) {
      digitalWrite(pumpPin, HIGH);  // Activate pump if sensor is LOW
    } else {
      digitalWrite(pumpPin, LOW);   // Deactivate pump if sensor is not LOW
    }
  }
};

const int numPlants = 8;  // Number of plants
Plant plants[numPlants] = {
  Plant(A0, 2),  // Create instances for each plant with sensor and pump pins
  Plant(A1, 3),
  Plant(A2, 4),
  Plant(A3, 5),
  Plant(A4, 6),
  Plant(A5, 7),
  Plant(A6, 8),
  Plant(A7, 9)
};

void setup() {
  // Setup code (if needed)
}

void loop() {
  // Loop through all the plants and water them based on sensor status
  for (int i = 0; i < numPlants; i++) {
    plants[i].waterPlant();
  }
}
