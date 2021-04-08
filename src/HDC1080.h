#pragma once
#include <Arduino.h>
#include <Wire.h>

#define HDC1080_TEMPERATURE 0x00
#define HDC1080_HUMIDITY 0x01
#define HDC1080_CONFIGURATION 0x02
#define HDC1080_MANUFACTURER_ID 0xFE
#define HDC1080_DEVICE_ID 0xFF
#define HDC1080_SERIAL_ID_FIRST 0xFB
#define HDC1080_SERIAL_ID_MID 0xFC
#define HDC1080_SERIAL_ID_LAST 0xFD
#define HDC1080_VALUE_DEVICE_ID 0x1050
#define HDC1080_VALUE_TEXAS_ID 0x5449

class HDC1080
{
public:
	typedef enum
	{
		HDC1080_RESOLUTION_8BIT,
		HDC1080_RESOLUTION_11BIT,
		HDC1080_RESOLUTION_14BIT,
	} HDC1080_MeasurementResolution;

	typedef union
	{
		uint8_t rawData[6];
		struct
		{
			uint16_t serialFirst;
			uint16_t serialMid;
			uint16_t serialLast;
		};
	} HDC1080_SerialNumber;

	typedef union
	{
		uint8_t rawData;
		struct
		{
			uint8_t HumidityMeasurementResolution : 2;
			uint8_t TemperatureMeasurementResolution : 1;
			uint8_t BatteryStatus : 1;
			uint8_t ModeOfAcquisition : 1;
			uint8_t Heater : 1;
			uint8_t ReservedAgain : 1;
			uint8_t SoftwareReset : 1;
		};
	} HDC1080_Registers;
	bool Initialize(TwoWire *theWire);

	HDC1080_SerialNumber readSerialNumber();

	void HeatUp(uint8_t seconds);

	void Setup(HDC1080_MeasurementResolution humidity, HDC1080_MeasurementResolution temperature);

	double ReadTemperature();
	double ReadHumidity();

private:
	uint8_t _address = 0x40;
	TwoWire *_wire;

	uint16_t readManufacturerId(); // 0x5449 ID of Texas Instruments
	uint16_t readDeviceId();	   // 0x1050 ID of the device
	uint16_t readData(uint8_t pointer);
	HDC1080_Registers readRegister();
	void writeRegister(HDC1080_Registers reg);
};
