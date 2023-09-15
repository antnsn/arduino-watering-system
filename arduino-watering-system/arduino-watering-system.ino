// Define constants for the number of plants
const int numPlants = 8;

// Define a struct to represent each plant
struct Plant {
  String name;
  int relayPin;
  int sensorPin;
};

// Create an array of Plant structs for each plant
Plant plants[numPlants] = {
  {"plant nr:1", 2, A0},
  {"plant nr:2", 3, A1},
  {"plant nr:3", 4, A2},
  {"plant nr:4", 5, A3},
  {"plant nr:5", 6, A4},
  {"plant nr:6", 7, A5},
  {"plant nr:7", 8, A6},
  {"plant nr:8", 9, A7}
};

// Initialize variables for sensor values and watering thresholds
int sensorValues[numPlants] = {0};
int wateringThreshold = 35;  // Adjust as needed

// Function to convert sensor values to percentage
int convertToPercent(int value) {
  return map(value, 845, 220, 0, 100);
}

// Function to control watering
void waterPlant(int relayPin, int sensorPin, String plantName) {
  Serial.println(plantName + " - Moisture: " + convertToPercent(sensorValues[relayPin - 2]) + "%");
  digitalWrite(relayPin, LOW);   // Turn on the pump
  delay(3000);                    // Water for 3 seconds
  digitalWrite(relayPin, HIGH);  // Turn off the pump
  delay(1000);                    // Wait for 1 second
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication

  // Initialize pins and relay states for each plant
  for (int i = 0; i < numPlants; i++) {
    pinMode(plants[i].relayPin, OUTPUT);
    digitalWrite(plants[i].relayPin, HIGH); // Turn off pumps initially
    pinMode(plants[i].sensorPin, INPUT);
  }
}

void loop() {
  // Read sensor values for each plant
  for (int i = 0; i < numPlants; i++) {
    sensorValues[i] = analogRead(plants[i].sensorPin);
  }

  // Water plants based on moisture levels
  for (int i = 0; i < numPlants; i++) {
    if (convertToPercent(sensorValues[i]) <= wateringThreshold) {
      waterPlant(plants[i].relayPin, plants[i].sensorPin, plants[i].name);
    } else {
      digitalWrite(plants[i].relayPin, HIGH); // Turn off the pump
    }
  }

  delay(3600000); // Delay for 1 hour (adjust as needed)
}
