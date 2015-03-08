#include "gpio.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using std::endl;
using std::fstream;
using std::ios;
using std::logic_error;
using std::runtime_error;
using std::string;
using std::stringstream;

const string GPIO::PATH_EXPORT        = "/sys/class/gpio/export";
const string GPIO::PATH_UNEXPORT      = "/sys/class/gpio/unexport";
const string GPIO::PREFIX             = "/sys/class/gpio/pio";
const string GPIO::POSTFIX_VALUE      = "/value";
const string GPIO::POSTFIX_DIRECTION  = "/direction";
const string GPIO::POSTFIX_ACTIVE_LOW = "/active_low";

GPIO::GPIO(int id) {
    id_ = id;

    Export();

    std::string IO = "-";

    switch(id){
        case 64: IO = KERNEL_ID_64; break;
        case 65: IO = KERNEL_ID_65; break;
        case 66: IO = KERNEL_ID_66; break;
        case 67: IO = KERNEL_ID_67; break;
        case 68: IO = KERNEL_ID_68; break;
        case 92: IO = KERNEL_ID_92; break;
        case 6: IO = KERNEL_ID_6; break;
        case 8: IO = KERNEL_ID_8; break;
        case 0: IO = KERNEL_ID_0; break;
        case 29: IO = KERNEL_ID_29; break;
        case 28: IO = KERNEL_ID_28; break;
        case 27: IO = KERNEL_ID_27; break;
        case 26: IO = KERNEL_ID_26; break;
        case 25: IO = KERNEL_ID_25; break;
        case 24: IO = KERNEL_ID_24; break;
        case 23: IO = KERNEL_ID_23; break;
        case 22: IO = KERNEL_ID_22; break;
        case 21: IO = KERNEL_ID_21; break;
        case 31: IO = KERNEL_ID_31; break;
        case 30: IO = KERNEL_ID_30; break;
        case 1: IO = KERNEL_ID_1; break;
        case 7: IO = KERNEL_ID_7; break;
        case 5: IO = KERNEL_ID_5; break;
        case 91: IO = KERNEL_ID_91; break;
        case 95: IO = KERNEL_ID_95; break;
        case 43: IO = KERNEL_ID_43; break;
        case 44: IO = KERNEL_ID_44; break;
        case 45: IO = KERNEL_ID_45; break;
        case 46: IO = KERNEL_ID_46; break;
        case 81: IO = KERNEL_ID_81; break;
    }

    stringstream value_path;
    stringstream active_low_path;
    stringstream direction_path;
    
    value_path << PREFIX;
    value_path << IO;
    value_path << POSTFIX_VALUE;
    
    value_stream_.open(value_path.str().c_str());

    direction_path << PREFIX;
    direction_path << IO;
    direction_path << POSTFIX_DIRECTION;
    
    direction_stream_.open(direction_path.str().c_str());
 
    active_low_path << PREFIX;
    active_low_path << IO;
    active_low_path << POSTFIX_ACTIVE_LOW;

    active_low_stream_.open(active_low_path.str().c_str());
}

GPIO::~GPIO() {
    value_stream_.close();
    direction_stream_.close();
    active_low_stream_.close();

    Unexport();
}

bool
GPIO::Exists() {
    stringstream path;

    path << PREFIX;
    path << id_;

    fstream gpio;

    gpio.open(path.str().c_str());
    
    bool result = gpio.good();

    gpio.close();

    return result;
}

void
GPIO::Export() {
    if (Exists()) return;

    fstream gpio_export;
    stringstream string_stream;

    string_stream << id_;

    gpio_export.open(PATH_EXPORT.c_str(), ios::out);
    gpio_export << string_stream.str();
    gpio_export.close();
}

void
GPIO::Unexport() {
    if (!Exists()) return;

    fstream gpio_unexport;
    stringstream string_stream;

    string_stream << id_;

    gpio_unexport.open(PATH_UNEXPORT.c_str(), ios::out);
    gpio_unexport << string_stream.str();
    gpio_unexport.close();
}

int
GPIO::GetValue() {
    string value;
    
    value_stream_.seekg(0);
    value_stream_ >> value;

    if (value == "0") return GPIO_LOW;
    if (value == "1") return GPIO_HIGH;

    throw logic_error("Invalid GPIO value.");
}

void
GPIO::SetValue(int value) {
    value_stream_.seekp(0);

    if (GetDirection() == GPIO_IN)
        throw logic_error("Cannot set value when direction is IN.");

    switch (value) {
        case GPIO_LOW:
            value_stream_ << "0" << endl; 
        
            if (!value_stream_.good())
                throw runtime_error("Error writting to value file stream.");

            break;
        case GPIO_HIGH:
            value_stream_ << "1" << endl; 
        
            if (!value_stream_.good())
                throw runtime_error("Error writting to value file stream.");

            break;
        default:
            throw logic_error("Error cannot set invalid GPIO value.");
    }
}

int
GPIO::GetActiveLow() {
    string active_low;
    
    active_low_stream_.seekg(0);
    active_low_stream_ >> active_low;

    if (active_low == "0") return GPIO_LOW;
    if (active_low == "1") return GPIO_HIGH;

    throw logic_error("Invalid GPIO active_low.");
}

void
GPIO::SetActiveLow(int value) {
    active_low_stream_.seekp(0);

    switch (value) {
        case GPIO_LOW:
            active_low_stream_ << "0" << endl; 
        
            if (!active_low_stream_.good())
                throw runtime_error("Error writting to active_low file stream.");

            break;
        case GPIO_HIGH:
            active_low_stream_ << "1" << endl; 
        
            if (!active_low_stream_.good())
                throw runtime_error("Error writting to active_low file stream.");

            break;
        default:
            throw logic_error("Error cannot set invalid GPIO active_low.");
    }
}

int
GPIO::GetDirection() {
    string direction;

    direction_stream_.seekg(0);
    direction_stream_ >> direction;

    if (direction == "in") return GPIO_IN;
    if (direction == "out") return GPIO_OUT;

    throw logic_error("Invalid GPIO direction.");
}

void
GPIO::SetDirection(int value) {
    direction_stream_.seekp(0);

    switch (value) {
        case GPIO_IN:
            direction_stream_ << "in" << endl;
            
            if (!direction_stream_.good())
                throw runtime_error("Error writting to direction file stream.");
            
            break;
        case GPIO_OUT:
            direction_stream_ << "out" << endl;
            
            if (!direction_stream_.good())
                throw runtime_error("Error writting to direction file stream.");
            
            break;
        default:
            throw logic_error("Error cannot set invalid GPIO direction.");
    }
}
