#include "Vard.hpp"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>

using namespace boost::interprocess;

Vard::Vard(){
    serial_comm = new SerialCommunication();   
    robot.push_back(Robot(0, "ALEFE"));
}

Vard::~Vard()
{
    delete serial_comm;
}

void Vard::start()
{
    while(1){
        char* adress = "ALEFE";
        float vel_x = 11;
        float vel_y = 12;
        float vel_ang = 0;

/*
        serial_comm->mountPacket(robot[0].getName(), robot[0].getRFAddress(), robot[0].getVelX(), robot[0].getVelY(), robot[0].getVelAng());
        serial_comm->sendData();

        usleep(COMMUNICATION_DELAY);
*/

        serial_comm->mountPacket(robot[0].getName(), adress, vel_x, vel_y, vel_ang);
        serial_comm->sendData();

        usleep(COMMUNICATION_DELAY);

    } 
}
