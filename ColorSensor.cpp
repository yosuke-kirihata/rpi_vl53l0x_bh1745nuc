#include "ColorSensor.h"

#include <unistd.h>
#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <fcntl.h>

#include <stdio.h>

ColorSensor::ColorSensor()
{

}


ColorSensor::~ColorSensor()
{

}


ColorSensor* ColorSensor::_instance = 0;

ColorSensor* ColorSensor::getInstance()
{
    if (_instance == 0)
    {
        _instance = new ColorSensor();
    }

    return _instance;
}


static int fd;

void ColorSensor::Initialize()
{
    char *bus = "/dev/i2c-1";
    if ((fd = open(bus, O_RDWR)) < 0)
    {
        printf("Faild to open i2c port\n");
//        return 1;
    }

    if (ioctl(fd, I2C_SLAVE, 0x39) < 0)
    {
        printf("Unable to get bus access to talk to slave\n");
//        return 1;
    }

    uint8_t config[2] = {0};

    //BH1745NUC_MODE_CONTROL1
    config[0] = 0x41;
    config[1] = 0x00;
    write(fd, config, 2);

    //BH1745NUC_MODE_CONTROL2
    config[0] = 0x42;
    config[1] = 0x90;
    write(fd, config, 2);

    //BH1745NUC_MODE_CONTROL3
    config[0] = 0x44;
    config[1] = 0x02;
    write(fd, config, 2);
}

void ColorSensor::getColor(int * r, int * g, int * b, int * c)
{

    //BH1745NUC_RED_DATA_LSB

    uint8_t reg[1] = {0x50};
    write(fd, reg, 1);
    uint8_t data[8] = {0};
    if(read(fd, data, 8) != 8)
    {
        printf("Erorr : Input/output Erorr \n");
    }
    else
    {
        // Convert the data
        *r = (data[1] * 256 + data[0]);
        *g = (data[3] * 256 + data[2]);
        *b = (data[5] * 256 + data[4]);
        *c = (data[7] * 256 + data[6]);
    }
}
