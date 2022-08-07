#include <IRremote.h>

IRrecv irrecv(11);
decode_results results;

#define motor1A 5
#define motor1B 6
#define motor2A 9
#define motor2B 10

int spd = 150;
int btnPress = 0;

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode()) {
    String command = String(irrecv.decodedIRData.command, HEX);

    if(command == "45") {   // Speed 1
      spd = 100;
    }else if(command == "46") {   // Speed 2
      spd = 150;
    }else if(command == "47") {   // Speed 3
      spd = 200;
    }else if(command == "44") {   // Speed 4
      spd = 250;
    }

    if(command == "18") {   // Front
      analogWrite(motor1A, spd);
      digitalWrite(motor1B, LOW);

      analogWrite(motor2A, spd);
      digitalWrite(motor2B, LOW);
      btnPress++;
    }else if(command == "52") {   // Back
      digitalWrite(motor1A, LOW);
      analogWrite(motor1B, spd);

      digitalWrite(motor2A, LOW);
      analogWrite(motor2B, spd);
      btnPress++;
    }else if(command == "8") {   // Left
      analogWrite(motor1A, LOW);
      digitalWrite(motor1B, LOW);

      analogWrite(motor2A, 125);
      digitalWrite(motor2B, LOW);
      
      btnPress++;
    }else if(command == "5a") {   // Right
      analogWrite(motor1A, 125);
      digitalWrite(motor1B, LOW);

      analogWrite(motor2A, LOW);
      digitalWrite(motor2B, LOW);
      
      btnPress++;
    }
    
    irrecv.resume();
  }
  if(btnPress == 0) {
    Serial.println("if");
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, LOW);

    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, LOW);
  }else {
   btnPress--;
  }
  delay(200);
}
