#define ml 4
#define mr 7
#define sl 5
#define sr 6
const int IRpin = A0;
int trigPin = 10; 
int echoPin = 11;
int speed = 150;
int fdur = 30;
int ldur = 60;
int newLeft;
int newForward;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ml, OUTPUT);
  pinMode(mr, OUTPUT);
  pinMode(sl, OUTPUT);
  pinMode(sr, OUTPUT);
}

void loop() {
  stopMove();  
  stopMind();      
}
int fdist(){
  int duration;
  float distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  distance = duration / 58;
  return distance;
}
int ldist(){ 
  float volts = analogRead(IRpin) * 0.0048828125;
  float distance = 32 * pow(volts, -1.10); 
  return distance;                  
  } 

void stopMind(){
  
  while(fdist() > fdur and ldist() < ldur){
    forwardMove();
  }
  while(fdist() <= fdur and ldist() <= ldur){
    rightMove();
        
  }
  while(fdist() > fdur and ldist() > ldur){
    forwardMove();
    leftMove();
    delay(50);
  }
  
}

void stopMove(){

  digitalWrite(ml, LOW);
  analogWrite(sl, 0);

  digitalWrite(mr, LOW);
  analogWrite(sr, 0);
  delay(20);

}

void forwardMove(){

  digitalWrite(ml, HIGH);
  analogWrite(sl, speed);

  digitalWrite(mr, HIGH);
  analogWrite(sr, speed);
  
}

void leftMove(){

  digitalWrite(ml, LOW);
  analogWrite(sl, 0);

  digitalWrite(mr, HIGH);
  analogWrite(sr, speed);
}

void rightMove(){

  digitalWrite(ml, HIGH);
  analogWrite(sl, speed);

  digitalWrite(mr, LOW);
  analogWrite(sr, 0);
}
