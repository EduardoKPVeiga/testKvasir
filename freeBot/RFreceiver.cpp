#include "RFreceiver.hpp"

RFreceiver::RFreceiver()
{
    bool debug = true;
    vel_x = 0;
    vel_y = 0;
    vel_ang = 0;
    queue = NULL;
#ifndef XBEE
    radio = new Radio();
    uint8_t address[] = {ADDRESS};
    radio->openReadingPipe(1, address);
    radio->startListening();
#endif
}

void RFreceiver::receiveData()
{
    int i;
    unsigned char data[W_DATA];
#ifndef XBEE
    if(debug) {
        Serial.print("Radio Available: ");
        Serial.println(radio->available());
    }
    
    if(radio->available())
    {
        radio->read(&data,W_DATA);
        if(debug)
            Serial.print("Recebendo... ");
        if(data[0]==NAME && data[1]!=0) // se for 0 eh pq deu erro no envio
        {
            if(debug)
                Serial.print("Data recebida: ");
            for(i=0; i<W_DATA; i++)
            {
                queue = queue->addByte(data[i], queue);
                if(debug) {
                    Serial.print(data[i], HEX);
                    Serial.print("  ");
                }
            }
        }
        else
            queue = NULL;
        Serial.println();
        
    }
    if(!radio->isChipConnected())
    {
        Serial.println("nao tem pacote");
    }

#else
    int siz = Serial.available();
    if(z>0)
    {
        for(i=0; i<siz; i++)
        {
            queue = queue->addByte(Serial.read(), queue);
        }
    }
#endif
}

int RFreceiver::updateBuffer()
{
    boolean debug = true;
    unsigned char input_byte[DATA_SIZE];
    int i;
    if(queue == NULL) {
        return 0;
    }

    if(debug){
        if(queue != NULL) {
            Serial.print("Update queue->getSize(): ");
            Serial.println(queue->getSize());
        }
    }

    if(queue->getSize()<W_DATA) { // nao tem um pacote completo
        return 0;
    }

    Serial.print("");

    while(queue->getByte()!=KEY) { // Remove o 'nome' e a 'KEY' da queue, restando somente as velocidades
        if(debug) {
            Serial.print(queue->getByte());
            Serial.print(" - ");
        }
        queue = queue->removeByte(queue);
    }

    Serial.print(queue->getByte());

    if(queue->getByte()==KEY && queue->getSize()>DATA_SIZE) { // mudar isso, passar para constantes
        Serial.println("Vetor Input Byte:");
        for(i=0; i<DATA_SIZE; i++) {
            queue = queue->removeByte(queue);
            input_byte[i] = queue->getByte();

            if(debug) {
                Serial.print(input_byte[i]);
                Serial.print(" - ");
            }
        }
	//estas operacoes convertem 4 char em 1 float
        vel_x = *(float*)&input_byte[0];
        vel_y = *(float*)&input_byte[4];
        vel_ang = *(float*)&input_byte[8];
        
        Serial.print("x ");
        Serial.print(vel_x);
        Serial.print(" y ");
        Serial.println(vel_y);
    }
    //if(queue!=NULL&&queue->getSize()>(DATA_SIZE+1))//significa que ainda tem um pacote inteiro a ser lido, nesse caso nao se verifica o Buffer do arduino ate que o Buffer local seja totalmente usado
    //{
    //    return 1;
    //}
    return 1;
}

void RFreceiver::debug()
{
#ifndef XBEE
    radio->printDetails();
#endif
}

float RFreceiver::getVelY()
{
    return vel_y;
}

float RFreceiver::getVelX()
{
    return vel_x;
}
float RFreceiver::getVelAng()
{
    return vel_ang;
}
