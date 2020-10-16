#ifndef _RADSENS1V2_H_
#define _RADSENS1V2_H_


#include <Arduino.h>
#include <Wire.h>
#include <defines.h>


class ClimateGuard_RadSens1v2 {
    private:
        uint8_t _sensor_address;
        uint8_t _data[19] = { 0 };
        uint8_t  _chip_id;
        uint8_t _firmware_ver;
        uint32_t _pulse_cnt;
        bool updateData();
    public:
        ClimateGuard_RadSens1v2(uint8_t sensorAddress);
        ~ClimateGuard_RadSens1v2();
        bool radSens_init();
        uint8_t getChipId();
        uint8_t getFirmwareVersion();
        float getRadIntensyDyanmic();
        float getRadIntensyStatic();
        uint32_t getNumberOfPulses();
        uint8_t getSensorAddress();
        bool getHVGeneratorState();
        uint8_t getSensitivity();
        bool setHVGeneratorState(bool state);
        bool setSensitivity(uint8_t sens);

};

#endif // _RADSENS1V2_H_