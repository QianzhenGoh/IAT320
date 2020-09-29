#include <Adafruit_CircuitPlayground.h>

int capIndex[8] = {3,2,0,1,6,9,10,12};
float pitches[8] = {261.626, 293.665, 329.228, 391.995, 440.0, 493,883, 523.251};
//boolean speakerOn = false;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

}

void loop() {
  // setting speaker.enable to false then true works for me
  CircuitPlayground.speaker.enable(false);

  for (int i=0; i<8; i++) {
    Serial.print(CircuitPlayground.readCap(capIndex[i]));
    Serial.print(" ");
  }

  Serial.println(" ");

  for (int i=0; i<8; i++) {
    if(CircuitPlayground.readCap(capIndex[i])>600){
      CircuitPlayground.speaker.enable(true);
      CircuitPlayground.playTone(pitches[i],300,false);
    }
  }
  
  delay(100);

}
