#define BLUE_LED 2
#define RED_LED 16
#define ON_LINE true
#define OFF_LINE false

int adcVal = 0;
int MAX_LDR = 1024;
float LOW_LIGHT_THRESHOLD = 93;
bool currState;


void setup() {
  Serial.begin(9600);
  
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);     

  pinMode(D4, OUTPUT);
  currState = ON_LINE;
}
double calculateLightIntensity(int adcVal){
  double lI = (double)adcVal / MAX_LDR * 100;
  return lI;
}
void goOnLine(){
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(D4, LOW);
}
void goOutLine(){
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(D4, HIGH);
}
void checkLine(bool *currState, double lightIntensity){
  Serial.println("In checkLine");
  Serial.println(*currState);
  Serial.println(lightIntensity);
  Serial.println("=========================");
  
  if(lightIntensity <= LOW_LIGHT_THRESHOLD){
     //On Line 
     if(*currState == ON_LINE){}
     else{
        goOnLine();
        *currState = ON_LINE;
        Serial.println(":)))))))))))))))))))");
     }
  }else{
     //Not On Line
     if(*currState == ON_LINE){
        goOutLine();
        *currState = OFF_LINE;
        Serial.println("**********************");
     }
     else{}
  }
}
void loop() {
  adcVal = analogRead(A0);
  double lightIntensity = calculateLightIntensity(adcVal);

  
  checkLine(&currState, lightIntensity);
  delay(50);
} 
