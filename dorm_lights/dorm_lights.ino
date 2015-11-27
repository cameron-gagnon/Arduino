const unsigned int strand1 = 13;
const unsigned int strand2 = 12;
const unsigned int strand3 = 11;
const unsigned int strand4 = 10;
const unsigned int strand5 = 9;
const unsigned int buttonTrig = 2;
const unsigned int buttonBeat = 3;
const unsigned int steadyPin = 4;
unsigned int time = random(50, 1000);
boolean steady = true;



void setup(){

  pinMode(strand1, OUTPUT);
  pinMode(strand2, OUTPUT);
  pinMode(strand3, OUTPUT);
  pinMode(strand4, OUTPUT);
  pinMode(strand5, OUTPUT);
  
  pinMode(buttonTrig, INPUT);
  pinMode(buttonBeat, INPUT);
  pinMode(steadyPin, INPUT);

  Serial.begin(9600);
}


void loop(){
  steady = getSteady();
  
  if (!steady){
    time = getDelay();
    randomRelay(time);
  } else {
    digitalWrite(strand1, HIGH);
    digitalWrite(strand2, HIGH);
    digitalWrite(strand3, HIGH);
    digitalWrite(strand4, HIGH);
    digitalWrite(strand5, HIGH);
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
      digitalWrite(strand1, HIGH);
      digitalWrite(strand2, HIGH);
      digitalWrite(strand3, HIGH);
      digitalWrite(strand4, HIGH);
      digitalWrite(strand5, HIGH);
      
      unsigned long currentTime = millis();
      unsigned long timeDiff = 0;

      
      if (digitalRead(buttonBeat) == LOW){
        Serial.println(i);
        if (i != 0){
          timeDiff = currentTime - lastTime;
          Serial.print(i - 1);
          Serial.print(" ");
          Serial.println(timeDiff);
          arr[i - 1] = timeDiff;
        }
          lastTime = currentTime;
          i++;
          delay(100);
      }
  }
 
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
    digitalWrite(strand1, random(0, 2));
    digitalWrite(strand2, random(0, 2));
    digitalWrite(strand3, random(0, 2));
    digitalWrite(strand4, random(0, 2));
    digitalWrite(strand5, random(0, 2));
    delay(time);
}
