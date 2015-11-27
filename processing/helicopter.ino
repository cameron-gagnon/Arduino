const unsigned int button = 10;
const unsigned int led_out = 9;
void setup(){
 Serial.begin(9600);
 pinMode(button, INPUT);
 pinMode(led_out, OUTPUT);
}

void loop(){
  
  if (digitalRead(button) == LOW){
    digitalWrite(led_out, HIGH);
    Serial.println(1);
    delay(20);
  } else {
    Serial.println(0);
    delay(20);
  }
  
}
