#include "SerialCommunication.h"

SerialCommunication::SerialCommunication()
{
    int i;
    for(i = 0; i< W_ADDRESS; i++)
    {
        address[i] = 0;
    }
    for(i = 0; i< W_DATA; i++)
    {
        data[i] = 0;
    }
    for(i = 0; i<W_DATA+W_ADDRESS+1; i++)
    {
        received_data[i] = 0;
    }
}

int SerialCommunication::receiveRS232()
{
    int i, siz;

    siz = Serial1.readBytes(received_data, W_DATA+W_ADDRESS+1);
    Serial1.flush();

    //* Teste de comunicação direto pelo arduino MEGA (Não rodar o Vard!)
    char string_velX[4];
    char string_velY[4];
    char string_velAng[4];

    *((float*)&string_velX) = 10;
    *((float*)&string_velY) = 0;
    *((float*)&string_velAng) = 0;

    //siz = Serial1.readBytes(received_data, W_DATA+W_ADDRESS+1);
    siz = W_DATA+W_ADDRESS+1;
    received_data[0] = BEGIN;
    received_data[1] = 'A';
    received_data[2] = 'L';
    received_data[3] = 'E';
    received_data[4] = 'F';
    received_data[5] = 'E';
    received_data[6] = 0;
    received_data[7] = KEY;
    for(i=0; i<4; i++)
    {
        received_data[8+i]=string_velX[i];
        received_data[12+i]=string_velY[i];
        received_data[16+i]=string_velAng[i];
    }
    //Serial1.flush();
    //*/

    if(siz==W_DATA+W_ADDRESS+1 && received_data[0] == BEGIN)
    {
        return 1;
        
    }
    else
    {
        // Gambiarra para tentar sincronizar o buffer circular do arduino
        siz = Serial1.readBytes(received_data, 1);
        Serial1.flush();
        return 0;
    }
}

void SerialCommunication::getAddress(uint8_t *_address)
{
    int i;
    for(i=0; i<W_ADDRESS; i++)
    {
        address[i] = received_data[i+1];
    }
    for(i=0; i<W_ADDRESS; i++)
    {
        _address[i] = address[i];
    }
}

void SerialCommunication::getData(unsigned char *_data)
{
    int i;
    for(i=1; i<W_DATA; i++)
    {
        data[i] = received_data[i+1+W_ADDRESS];
    }
    for(i=0; i<W_DATA; i++)
    {
        _data[i] = data[i];
    }
}

char SerialCommunication::getName()
{
    data[0] = received_data[1+W_ADDRESS];
    return data[0];
}
