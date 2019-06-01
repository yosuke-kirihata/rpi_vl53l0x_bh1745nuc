#include <iostream>
#include <sys/time.h>
#include <time.h>
#include "wiringPi.h"

#include "RangingSensor.h"

#include "ColorSensor.h"

static RangingSensor * mp_rangingSensor;
static ColorSensor * mp_colorSensor;

int main(void)
{
    struct timeval now;
    struct timeval prev;

    mp_rangingSensor = RangingSensor::getInstance();
    mp_rangingSensor->Initialize();

    mp_colorSensor = ColorSensor::getInstance();
    mp_colorSensor->Initialize();

    float ranging;

    if( wiringPiSetupGpio() < 0)
    {
        //initialize failed
        return 1;
    }

    gettimeofday(&now, NULL);
    gettimeofday(&prev, NULL);

    while(1)
    {
        //100ms
        while((now.tv_sec - prev.tv_sec) + (now.tv_usec - prev.tv_usec)*1.0E-6 < 0.05F)
        {
            gettimeofday(&now, NULL);
        }
        prev = now;

        ranging = mp_rangingSensor->getRanging();
        printf("RANGING:%f\n",ranging);

        int red, blue, green, clear;
        mp_colorSensor->getColor(&red, &blue, &green, &clear);
        printf("COLOR:%d,%d,%d,%d\n",red, blue, green, clear);

    }

}