#define IN_PIN1 36
#define IN_PIN2 39
#define IN_PIN3 34
#define WINDOW_SIZE 3

int INDEX1 = 0;
int INDEX2 = 0;
int INDEX3 = 0;
int VALUE1 = 0;
int VALUE2 = 0;
int VALUE3 = 0;
int SUM1 = 0;
int SUM2 = 0;
int SUM3 = 0;
int READINGS1[WINDOW_SIZE];
int READINGS2[WINDOW_SIZE];
int READINGS3[WINDOW_SIZE];
int AVERAGED1 = 0;
int AVERAGED2 = 0;
int AVERAGED3 = 0;

int PulseSensorPurplePin1 = 0; // Pulse Sensor 1
int PulseSensorPurplePin2 = 1; // Pulse Sensor 2
int PulseSensorPurplePin3 = 2; // Pulse Sensor 3
int LED13 = 2;               // The on-board Arduino LED

int Signal1;
int Signal2;
int Signal3;
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore.
char ssid[] = "Reading Room";
char pass[] = "Password@4321";

String GOOGLE_SCRIPT_ID = "AKfycbyhFcnPSqI3O6bMQ0diF4Wdk4UDqO2mMZFx1nWm_3_3fw0MrGgUlEBMzEr_m2ECRLKx";
void setup() {
  pinMode(IN_PIN1, INPUT);
  pinMode(IN_PIN2, INPUT);
  pinMode(IN_PIN3, INPUT);
  pinMode(LED13, OUTPUT); // Pin that will blink to your heartbeat
  Serial.begin(9600);    // Set up Serial Communication at a certain speed
}

void loop() {
  Signal1 = analogRead(PulseSensorPurplePin1);
  Signal2 = analogRead(PulseSensorPurplePin2);
  Signal3 = analogRead(PulseSensorPurplePin3);

  if (Signal1 > Threshold) {
    digitalWrite(LED13, HIGH);
  } else {
    digitalWrite(LED13, LOW);
  }
    if (Signal2 > Threshold) {
    digitalWrite(LED13, HIGH);
  } else {
    digitalWrite(LED13, LOW);
  }
    if (Signal3 > Threshold) {
    digitalWrite(LED13, HIGH);
  } else {
    digitalWrite(LED13, LOW);
  }

  // Implement noise reduction for Pulse Sensor 1
  SUM1 = SUM1 - READINGS1[INDEX1];
  VALUE1 = analogRead(IN_PIN1);
  READINGS1[INDEX1] = VALUE1;
  SUM1 = SUM1 + VALUE1;
  INDEX1 = (INDEX1 + 1) % WINDOW_SIZE;
  AVERAGED1 = SUM1 / WINDOW_SIZE;

  // Implement noise reduction for Pulse Sensor 2
  SUM2 = SUM2 - READINGS2[INDEX2];
  VALUE2 = analogRead(IN_PIN2);
  READINGS2[INDEX2] = VALUE2;
  SUM2 = SUM2 + VALUE2;
  INDEX2 = (INDEX2 + 1) % WINDOW_SIZE;
  AVERAGED2 = SUM2 / WINDOW_SIZE;

  // Implement noise reduction for Pulse Sensor 3
  SUM3 = SUM3 - READINGS3[INDEX3];
  VALUE3 = analogRead(IN_PIN3);
  READINGS3[INDEX3] = VALUE3;
  SUM3 = SUM3 + VALUE3;
  INDEX3 = (INDEX3 + 1) % WINDOW_SIZE;
  AVERAGED3 = SUM3 / WINDOW_SIZE;

  // Print the averaged values for the Pulse Sensors
  // Serial.print("Averaged1: ");
  Serial.print(AVERAGED1);
  Serial.print(",");
  Serial.print(AVERAGED2);
  Serial.print(",");
  Serial.println(AVERAGED3);

  
 String urlFinal ="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+"data1="+ int(bpm1)+"&data2="+ int(bpm2)+"&data3="+ int(bpm3);




HTTPClient http;

http.begin(urlFinal.c_str());

http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

int httpCode = http.GET();


http.end();

delay(100);
}
