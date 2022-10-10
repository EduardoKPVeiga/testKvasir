//biblioteca feita para coordenacao das componentes de Vard

#ifndef _VARD_HPP_
#define _VARD_HPP_
#include <iostream>
#include <fstream>
#include <string>
#include <smmclib.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include "Robot.hpp"
#include "SerialCommunication.hpp"
#include <QtCore>
#include <QCoreApplication>

class Vard{
    std::ifstream robot_settings;
    SerialCommunication *serial_comm;
    std::vector<Robot>robot;

public:
    Vard();
    ~Vard();
    void start();

};
#endif
