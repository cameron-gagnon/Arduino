const unsigned int button = 10;
const unsigned int led_out = 9;

void setup(){
 Serial.begin(9600);
 pinMode(button, INPUT);
 pinMode(led_out, OUTPUT); // to see when the button is pushed
}

void loop(){
  
  if (digitalRead(button) == LOW){
    digitalWrite(led_out, HIGH);
    Serial.println(1);
    // delay of 20 to prevent over
    // saturating the serial
    // communication line to processing?
    delay(20);
  } else {
    // send a 0 to not hang the processing sketch
    Serial.println(0);
    delay(20);
  }
  
}
