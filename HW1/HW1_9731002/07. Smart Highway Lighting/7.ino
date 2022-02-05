#define echoPin D7 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin D8 //attach pin D3 Arduino to pin Trig of HC-SR04

int ledPins[5] = {D4, D3, D2, D1, D6};

// defines variables
double duration; // variable for the duration of sound wave travel
double distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  for(int i=0; i<5; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
double calculateDistance(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}
void checkDistance(double distance){
  if(distance <= 23 && distance >= 3){
    int index = (distance - 3.1)/4;
    for(int i=0; i<5;i++)
      digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[index], HIGH);
    
  }
}
void loop() {
  double distance = calculateDistance();
  checkDistance((int)distance);
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

}
