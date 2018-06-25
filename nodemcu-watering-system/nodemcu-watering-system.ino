 
#include <ESP8266WiFi.h>
#include <DHTesp.h>
#include <PubSubClient.h>

const char* ssid = "plecto";
const char* password = "marius87";
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* topict = "temp";
const char* topicm = "moisture";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


class dht{
   DHTesp dhtsensor;
   int AsensRead;
   int BsensRead;
   int CsensRead;
   int DsensRead;
   int sensorPin;
   
   public:
   dht(int AsensR, int BsensR, int CsensR, int DsensR, int sensPin)
   {
    sensorPin = sensPin;
    pinMode(sensorPin, INPUT);
    AsensRead = AsensR;
    pinMode(AsensRead, OUTPUT);
    BsensRead = BsensR;
    pinMode(BsensRead, OUTPUT);
    CsensRead = CsensR;
    pinMode(CsensRead, OUTPUT);
    DsensRead = DsensR;
    pinMode(DsensRead, OUTPUT);
    dhtsensor.setup(sensorPin, DHTesp::DHT11); 
   }
   
  void dhtread()
  {
      delay(dhtsensor.getMinimumSamplingPeriod());

      float humidity = dhtsensor.getHumidity();
      float temperature = dhtsensor.getTemperature();
    
      Serial.print(dhtsensor.getStatusString());
      snprintf (msg, 75, "Temp:", temperature);
      client.publish("temp", msg);
      Serial.print(temperature, 1);
      Serial.print("\t\t");

      Serial.print(dhtsensor.getStatusString());
      snprintf (msg, 75, "Humidity:", humidity);
      client.publish("temp", msg);
      Serial.print(humidity, 1);
      Serial.print("\t\t");

      Serial.print(dhtsensor.computeHeatIndex(temperature, humidity, false), 1);
  }
};

class plant
{
    int AsensRead;
    int BsensRead;
    int CsensRead;
    int DsensRead;
    int sensorPin;

    int ApumpWrite;
    int BpumpWrite;
    int CpumpWrite;
    int DpumpWrite;
    int pumpPin;
    
    int moisture;
    int lagg;

  public:
  plant(int AsensR, int BsensR, int CsensR, int DsensR, int sensPin, int pPin, int ApumpW, int BpumpW, int CpumpW, int DpumpW, int humid, int lag)
  {
    sensorPin = sensPin;
    pinMode(sensorPin, INPUT);
    AsensRead = AsensR;
    pinMode(AsensRead, OUTPUT);
    BsensRead = BsensR;
    pinMode(BsensRead, OUTPUT);
    CsensRead = CsensR;
    pinMode(CsensRead, OUTPUT);
    DsensRead = DsensR;
    pinMode(DsensRead, OUTPUT);
  
    pumpPin = pPin;
    pinMode(pumpPin, OUTPUT);
    ApumpWrite = ApumpW;
    pinMode(ApumpWrite, OUTPUT);    
    BpumpWrite = BpumpW;
    pinMode(BpumpWrite, OUTPUT);
    CpumpWrite = CpumpW;
    pinMode(CpumpWrite, OUTPUT);
    DpumpWrite = DpumpW;
    pinMode(DpumpWrite, OUTPUT);    
    
    moisture = humid;
    lagg = lag;
 
  }

  void status()
  {
    if(AsensRead == 1) {digitalWrite(AsensRead, HIGH);} else {digitalWrite(AsensRead, LOW);}
    if(BsensRead == 2) {digitalWrite(BsensRead, HIGH);} else {digitalWrite(BsensRead, LOW);}
    if(CsensRead == 3) {digitalWrite(CsensRead, HIGH);} else {digitalWrite(CsensRead, LOW);}
    if(DsensRead == 4) {digitalWrite(DsensRead, HIGH);} else {digitalWrite(DsensRead, LOW);}      
    if(analogRead(sensorPin) > moisture)
    {
      if(ApumpWrite == 5) {digitalWrite(ApumpWrite, HIGH);} else {digitalWrite(ApumpWrite, LOW);}
      if(BpumpWrite == 6) {digitalWrite(BpumpWrite, HIGH);} else {digitalWrite(BpumpWrite, LOW);}
      if(CpumpWrite == 7) {digitalWrite(CpumpWrite, HIGH);} else {digitalWrite(CpumpWrite, LOW);}
      if(DpumpWrite == 8) {digitalWrite(DpumpWrite, HIGH);} else {digitalWrite(DpumpWrite, LOW);}
      
        digitalWrite(pumpPin, LOW);
        delay(lagg);
        digitalWrite(pumpPin, HIGH);
        if (!client.connected()) {reconnect();}
        client.loop();
        snprintf (msg, 75, "Watered plant", pumpPin);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("moisture", msg);
    }
    else
    {
        if(ApumpWrite == 5) {digitalWrite(ApumpWrite, HIGH);} else {digitalWrite(ApumpWrite, LOW);}
        if(BpumpWrite == 6) {digitalWrite(BpumpWrite, HIGH);} else {digitalWrite(BpumpWrite, LOW);}
        if(CpumpWrite == 7) {digitalWrite(CpumpWrite, HIGH);} else {digitalWrite(CpumpWrite, LOW);}
        if(DpumpWrite == 8) {digitalWrite(DpumpWrite, HIGH);} else {digitalWrite(DpumpWrite, LOW);}            
        digitalWrite(pumpPin, HIGH);
    }
  }
};

plant plant1(1, 0, 0, 0, A0, 0, 5, 0, 0, 0, 60, 3500);

dht dht1(1, 2, 3, 4, A0);



void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  
}

void loop() {
  dht1.dhtread();
  plant1.status();
}
