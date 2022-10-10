#include <Servo.h>

Servo servo;
int velAjuste;
void setup() {
  Serial.begin(57600);
  servo.attach(9);
}

void loop() {
    if(Serial.available() > 0) {
        while(1){
            if(Serial.available() > 0){
                velAjuste = Serial.parseInt();

                if(velAjuste == -1){ break; }
                
                servo.write(velAjuste);
                
                Serial.print("Velocidade igual ");
                Serial.println(velAjuste);
                delay(200);
                
            }
        }
    }
}
