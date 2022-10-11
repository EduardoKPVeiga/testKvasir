#include "Principal.h"

Principal::Principal()
{
    serial = new SerialCommunication(); //comunicacao Serial1
    rWriter = new RadioWriter(); //envio de dados
}

void Principal::start()
{
    bool debug = true;
    bool receiveRS232_bool;
    uint8_t address[W_ADDRESS];
    unsigned char data[W_DATA];
    char name;
    long time = millis();
    int qt = 0;
	  while(1)
	  {
        receiveRS232_bool = serial->receiveRS232();
        Serial.println(".");
        if(debug) {
            Serial.print("receiveRS232: ");
            Serial.println(receiveRS232_bool);
        }

        if(receiveRS232_bool)
        {
            digitalWrite(13, HIGH);
            serial->getAddress(address);
            if(debug) {
                Serial.print("Address: ");
                for(int i = 0; i < W_ADDRESS; i++) {
                    Serial.print((char) address[i]);
                    Serial.print(" - ");
                }
                Serial.println("");
            }

            name = serial->getName();
            if(debug) {
                Serial.print("Name: ");
                Serial.println((int) name);
            }

            if(name == 0)
            {
              qt++;
            }
	          rWriter->setAddress(address);
              serial->getData(data);
	          rWriter->sendData(data);
              qt++;
        }
        else
        {
            digitalWrite(13, LOW);
        }
        if(millis()-time >=1000)
        {
            time = millis();
        }

        if(debug) {
            Serial.print("Dados: ");
            for(int i = 0; i < W_DATA; i++) {
                Serial.print(data[i]);
                Serial.print(" - ");
            }
            Serial.println("");
        }

        delay(10);
    }
}
