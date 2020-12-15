#include <Adafruit_CircuitPlayground.h>


int capIndex[5] = {3,2,0,1,6};
int capNo[5] = {4,5,6,7,0};
//float pitches[20] = {65, 131, 262, 523, 1047,    
//                     82, 165, 330, 659, 1318,    
//                     87, 175, 349, 698, 1397,    
//                     98, 196, 392, 784, 1568,    
//                     };
float pitches[20] = {165, 196, 261, 329, 391,    //C Chord
                     220, 261, 349, 440, 523,    //F Chord
                     207, 246, 329, 415, 493,    //E Chord
                     247, 293, 392, 494, 587,    //G Chord
                     };
int key = 0;
int duration = 100;
int randList[5] = {0,1,2,3,4};
boolean randomNotes = false;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  CircuitPlayground.speaker.enable(false);
  // left button plays note at a random order right button resets and plays note from low to high if more than 1 is triggered
  //checked within note playing loop so it can break anytime
  if (CircuitPlayground.leftButton()) {
    randomNotes = true;
    for (int i=0; i<5; i++){
      int r = int(random(i,4));
      int temp = randList[i];
      randList[i] = randList[r];
      randList[r] = temp;
    }
  }

  if (CircuitPlayground.rightButton()) {
    randomNotes = false;  
  }
  
  // note playing code
  if (randomNotes == false){
    for (int i=0; i<5; i++) {
      if(CircuitPlayground.readCap(capIndex[i])>600){
        CircuitPlayground.speaker.enable(true);
        CircuitPlayground.playTone(pitches[i+key],duration,false);
      }
      if (CircuitPlayground.leftButton()) {
        randomNotes = true;
        for (int i=0; i<5; i++){
          int r = int(random(i,4));
          int temp = randList[i];
          randList[i] = randList[r];
          randList[r] = temp;
        }
      }
      if (CircuitPlayground.rightButton()) {
        randomNotes = false;  
      } 
    }
  }
  
// test for note duration as long as finger held
//  for (int i=0; i<5; i++) {
//      while true (CircuitPlayground.readCap(capIndex[i])>600){
//        CircuitPlayground.speaker.enable(true);
//        tone(CPLAY_BUZZER, pitches[i+key]);
//      }
//  }

  if (randomNotes == true){
    for (int i=0; i<5; i++) {
      if(CircuitPlayground.readCap(capIndex[randList[i]])>600){
        CircuitPlayground.speaker.enable(true);
        CircuitPlayground.playTone(pitches[randList[i]+key],duration,false);
      }
      if (CircuitPlayground.leftButton()) {
        randomNotes = true;
        for (int i=0; i<5; i++){
          int r = int(random(i,4));
          int temp = randList[i];
          randList[i] = randList[r];
          randList[r] = temp;
        }
      }
      if (CircuitPlayground.rightButton()) {
        randomNotes = false;  
      }
    }
  }
//  Serial.print("X: "); Serial.print(CircuitPlayground.motionX());
//  Serial.print(" \tY: "); Serial.print(CircuitPlayground.motionY());
//  Serial.print(" \tZ: "); Serial.print(CircuitPlayground.motionZ());
//  Serial.println(" ");

//  for (int i=0; i<5; i++) {
//    Serial.print("CapNo");
//    Serial.print(capNo[i]);
//    Serial.print(": ");
//    Serial.print(CircuitPlayground.readCap(capIndex[i]));
//    Serial.println(" ");
//    //uncomment for slower scroll to test out readings
//    //delay(100);
//  }

  // Motion code
  if (CircuitPlayground.motionY()>=7){
    key = 15;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,100,255,170);
    }
      
  } else if (CircuitPlayground.motionY()>=0 && CircuitPlayground.motionY()<7 ){
    key = 10;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,0,100,200);
    }
  } else if (CircuitPlayground.motionY()<0 && CircuitPlayground.motionY()>-7 ){
    key = 5;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,170,150,255);
    }
  } else if (CircuitPlayground.motionY()<= -7 ){
    key = 0;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,255,100,170);
    }
  }
  
  //light sensor data affecting note duration
  duration = int(map( CircuitPlayground.lightSensor(), 0, 1023, 350, 90));
    
}
