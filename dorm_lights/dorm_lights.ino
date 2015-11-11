const unsigned int led1 = 13;
const unsigned int led2 = 12;
const unsigned int led3 = 11;
const unsigned int led4 = 10;
const unsigned int indicatorLed = 9;
const unsigned int buttonTrig = 2;
const unsigned int buttonBeat = 3;
const unsigned int steadyPin = 4;
unsigned int time = random(50, 1000);
boolean steady = true;



void setup(){

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buttonTrig, INPUT);
  pinMode(buttonBeat, INPUT);
  pinMode(steadyPin, INPUT);
  pinMode(indicatorLed, OUTPUT);

  Serial.begin(9600);
}


void loop(){
  steady = getSteady();
  
  if (!steady){
    time = getDelay();
    randomRelay(time);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
  
}

// checks if the steady button is pressed to change the state of the lights
boolean getSteady(){
  if ((digitalRead(steadyPin) == LOW) && !steady){
    steady = true;
    Serial.println("SETTING STEADY TO TRUE");
    delay(1000);
  } else if ((digitalRead(steadyPin) == LOW) && steady){
    steady = false; 
    Serial.println("SETTING STEADY TO FALSE");
    delay(1000);
  }
  
  return steady; 
}


unsigned int getDelay(){
  unsigned long lastTime;
  unsigned long arr[100];
  int i = 0;

  while (digitalRead(buttonTrig) == LOW){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      
      digitalWrite(indicatorLed, LOW);
      unsigned long currentTime = millis();
      unsigned long timeDiff = 0;

      
      if (digitalRead(buttonBeat) == LOW){
        Serial.println(i);
        if (i != 0){
          timeDiff = currentTime - lastTime;
          Serial.println(i - 1 + " " + timeDiff);
          arr[i - 1] = timeDiff;
        }
          lastTime = currentTime;
          i++;
          delay(50);
      }
  }
  
  digitalWrite(indicatorLed, HIGH);
  
  if (i != 0){
    unsigned long totalTimeDiff = 0;
  
    for (int j = 0; j < i - 1; j++){
      totalTimeDiff += arr[j];  
    }
  
    // should average our time differences and return
    // them to then control the relay's.
    time = (totalTimeDiff / (i - 1));
    Serial.print("Setting time: ");
    Serial.println((double)time/1000);
  }

  return time;
 
}

void randomRelay(int time){  
    digitalWrite(led1, random(0, 2));
    digitalWrite(led2, random(0, 2));
    digitalWrite(led3, random(0, 2));
    digitalWrite(led4, random(0, 2));
    delay(time);
}
