#include "Principal.h"

Principal::Principal()
{
    serial = new SerialCommunication(); //comunicacao Serial1
    rWriter = new RadioWriter(); //envio de dados
}

void Principal::start()
{
    uint8_t address[W_ADDRESS];
    unsigned char data[W_DATA];
    char name;
    long time = millis();
    int qt = 0;
	  while(1)
	  {
        Serial.println(".");
        if(serial->receiveRS232())
        {
            digitalWrite(13, HIGH);
            serial->getAddress(address);
            name = serial->getName();
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
        delay(1000);
    }
}
