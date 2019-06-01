#ifndef __COLOER_SENSOR__
#define __COLOER_SENSOR__

#include <cstdint>


class ColorSensor
{
public:
    ColorSensor();
    ~ColorSensor();

    static ColorSensor* _instance;

    static ColorSensor* getInstance();
    void Initialize();
    void getColor(int * r, int * g, int * b, int * c);

private:

};


#endif //__COLOR_SENSOR__