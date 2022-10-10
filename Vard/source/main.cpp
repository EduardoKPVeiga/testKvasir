//Este programa tem por objetivo captar as informacoes ditadas pela inteligencia artificial ou por um dispositivo de entrada e transmiti-las para os robos em campo

#include <smmclib.hpp>
#include <iostream>
#include <string>

#include "Vard.hpp"
#include <QApplication>

int main()
{
    Vard* vard = new Vard();
    vard->start();
}
