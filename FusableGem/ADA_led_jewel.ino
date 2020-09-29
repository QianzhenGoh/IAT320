#include <Adafruit_CircuitPlayground.h>

uint8_t pixeln = 0;
boolean shaken = false;
boolean leftTilt = false;
boolean rightTilt = false;
int shakeTime = 0;
int presets[3][2][3] = {
  {{0,255,0},{255,0,0}},
  
  {{0,0,255},{128,128,0}},
  
  {{255,0,0},{128,128,128}}
};
int preset = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();

}

void loop() {
//  Serial.print("X: "); Serial.print(CircuitPlayground.motionX());
//  Serial.print(" \tY: "); Serial.print(CircuitPlayground.motionY());
//  Serial.print(" \tZ: "); Serial.print(CircuitPlayground.motionZ());
//  Serial.println(" ");
  float x = CircuitPlayground.motionX();
  float y = CircuitPlayground.motionY();
  float z = CircuitPlayground.motionZ();
  //can't evaluate functions inside abs() as per documentation, doing so might result in negative values
  float total = abs(x)+abs(y)+abs(z);
  //Serial.print(" total "); Serial.print(total); Serial.println(" ");

  // set shake to true after total > 18 for 4 ticks
  if (total > 18){
    shakeTime++;
    if(shakeTime >= 4){
      shaken = true;
      shakeTime = 0;
    }
  }

 // if total < 18 reset shakeTime to 0 
  if (total < 18){
    shakeTime = 0;
  }

  // left tilt condition
  if (x < -5 && z < 4) {
    shaken = false;
    leftTilt = true;
  }

  if (leftTilt == true){
    rightTilt = false;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,120+i*3,15,200);
    }
  }

// right tilt condition
  if (x > 5 && z < 4) {
    shaken = false;
    rightTilt = true;
  }

  if (rightTilt == true){
    leftTilt = false;
    for (int i=0; i<10; i++) {
      CircuitPlayground.setPixelColor(i,25,150,20+3*i);
    }
  }

  // mix both leds when shake = true
  if (shaken == true){
    leftTilt = false;
    rightTilt = false;
    for (int i=0; i<10; i++) {
      if (i<5){
        CircuitPlayground.setPixelColor(i,25,150,20+3*i);
      } if(i >= 5){
        CircuitPlayground.setPixelColor(i,120+i*3,15,200);
      }
    }
  }


  delay(100);

}
