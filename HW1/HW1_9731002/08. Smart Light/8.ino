#define LED D1
void setup() {
  Serial.begin(9600);
  analogWriteRange(75);
}

void loop() {
  int ldr = analogRead(A0);
  double scaled = (double)ldr/1024*100;
  analogWrite(LED, scaled-30);
  Serial.println(scaled-10);
  delay(50);

}
