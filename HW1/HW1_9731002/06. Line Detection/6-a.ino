int adc_val = 0;
int MAX_LDR = 1024;
void setup() {
  Serial.begin(9600);
 
}

void loop() {
  adc_val = analogRead(A0);
  Serial.println((double)adc_val/MAX_LDR*100);
  delay(500);
} 
