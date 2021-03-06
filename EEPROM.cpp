#include <avr/eeprom.h>
#include "Arduino.h"
#include "EEPROM.h"
#include "types.h"
#include "KV_Team_OSD.h"


uint8_t EEPROMClass::read(int address)
{
	return eeprom_read_byte((unsigned char *) address);
}

void EEPROMClass::write(int address, uint8_t value)
{
	eeprom_write_byte((unsigned char *) address, value);
}

EEPROMClass EEPROM;

// For Settings Defaults
static const uint8_t EEPROM_DEFAULT[EEPROM_SETTINGS] = {
1,   // used for check              0

0,   // S_RSSIMIN                   1
255, // S_RSSIMAX                   2
60,  // S_RSSI_ALARM                3
1,   // S_MWRSSI                    4
0,   // S_PWMRSSI                   5
8,   // S_PWMRSSIDIVIDER            6    // PWM Freq 500Hz=8, 1KHz=4 (Divider to avoid value >255)
105, // S_VOLTAGEMIN                7
3,   // S_BATCELLS                  8
100, // S_DIVIDERRATIO              9
1,   // S_MAINVOLTAGE_VBAT          10
100, // S_VIDDIVIDERRATIO           11
0,   // S_VIDVOLTAGE_VBAT           12
//90,  // S_TEMPERATUREMAX            13   // Do not remove yet
1,   // S_BOARDTYPE                 14
1,   // S_DISPLAYGPS                15
1,   // S_COORDINATES               16
0,   // S_HEADING360                17
0,   // S_UNITSYSTEM                18
1,   // S_VIDEOSIGNALTYPE           19
0,   // S_RESETSTATISTICS           20
1,   // S_ENABLEADC                 21
5,   // S_BLINKINGHZ                22   // 10=1Hz, 9=1.1Hz, 8=1,25Hz, 7=1.4Hz, 6=1.6Hz, 5=2Hz, 4=2,5Hz, 3=3,3Hz, 2=5Hz, 1=10Hz
0,   // S_MWAMPERAGE                23
40,  // S_CURRSENSSENSITIVITY       24   // May vary from 17 to 40mV/A (Sensor type)
2,   // S_CURRSENSOFFSET_H          25   // offset(H/L) =0 for unidir sensors or =512 for bidirectional sensors, may be changed only of few units.
0,   // S_CURRSENSOFFSET_L          26   // 2H+0L=512
2,   // S_CLIMB_RATE_ALARM          27
5,   // S_VOLUME_DIST_MAX           28   // Flying Volume Warning (Distance value in meters x100) by default is 500m
25,  // S_VOLUME_ALT_MAX            29   //   "     "       "   (Altitude Max "    "    "   x2  )  "     "   "   50m
0,   // S_VOLUE_ALT_MIN             30   //   "     "       "   (Altitude Min "    "    "   ___    "     "   "    0m
105, // S_VIDVOLTAGEMIN             31
30,  // S_PITCH_WARNING             32   // Warning message at given angle in degrees positive and negative (default 30�)

0,   //S_CALLSIGN                   32   // TEXT CONFIGURATION ONLY (On by default using L_CALLSIGNPOSITIONDSPL)


0,   // S_CS0,                    33    // 10 callsign char locations
0,   // S_CS1,
0,   // S_CS2,
0,   // S_CS3,
0,   // S_CS4,
0,   // S_CS5,
0,   // S_CS6,
0,   // S_CS7,
0,   // S_CS8,
0,   // S_CS9,                    42
};


// PAL item position Defaults
static const uint8_t EEPROM_PAL_DEFAULT[EEPROM_ITEM_LOCATION-EEPROM_SETTINGS] = {
	// ROW= Row position on screen (255= no action)
	// COL= Column position on screen (255= no action)
	// DSPL= Display item on screen

	2,   // L_GPS_NUMSATPOSITIONROW LINE02+6
	18,  // L_GPS_NUMSATPOSITIONCOL
	1,   // L_GPS_NUMSATPOSITIONDSPL

	6,   // L_GPS_DIRECTIONTOHOMEPOSROW LINE03+14
	2,   // L_GPS_DIRECTIONTOHOMEPOSCOL
	1,   // L_GPS_DIRECTIONTOHOMEPOSDSPL

	10,   // L_GPS_DISTANCETOHOMEPOSROW LINE02+24
	2,   // L_GPS_DISTANCETOHOMEPOSCOL
	1,   // L_GPS_DISTANCETOHOMEPOSDSPL

	10,  // L_SPEEDPOSITIONROW LINE03+24
	23,   // L_SPEEDPOSITIONCOL
	1,   // L_SPEEDPOSITIONDSPL

	9,   // L_GPS_ANGLETOHOMEPOSROW LINE04+12
	2,   // L_GPS_ANGLETOHOMEPOSCOL
	0,   // L_GPS_ANGLETOHOMEPOSDSPL

	/*13,  // L_MW_GPS_ALTPOSITIONROW LINE04+24   Do not remove yet
	2,   // L_MW_GPS_ALTPOSITIONCOL
	0,   // L_MW_GPS_ALTPOSITIONDSPL*/

	2,   // L_SENSORPOSITIONROW LINE03+2
	24,  // L_SENSORPOSITIONCOL
	1,   // L_SENSORPOSITIONDSPL

	2,   // L_MODEPOSITIONROW   LINE05+2
	8,   // L_MODEPOSITIONCOL
	1,   // L_MODEPOSITIONDSPL

	3,   // L_MW_HEADINGPOSITIONROW LINE02+19
	2,   // L_MW_HEADINGPOSITIONCOL
	1,   // L_MW_HEADINGPOSITIONDSPL

	2,   // L_MW_HEADINGGRAPHPOSROW LINE02+10
	2,   // L_MW_HEADINGGRAPHPOSCOL
	1,   // L_MW_HEADINGGRAPHPOSDSPL

	/*12,  // L_TEMPERATUREPOSROW LINE11+2  // Do not remove yet
	2,   // L_TEMPERATUREPOSCOL
	0,   // L_TEMPERATUREPOSDSPL*/

	6,  // L_MW_ALTITUDEPOSITIONROW LINE08+2
	23,  // L_MW_ALTITUDEPOSITIONCOL
	1,   // L_MW_ALTITUDEPOSITIONDSPL

	8,   // L_CLIMBRATEPOSITIONROW LINE08+24
	5,  // L_CLIMBRATEPOSITIONCOL
	1,   // L_CLIMBRATEPOSITIONDSPL

	6,   // L_HORIZONPOSITIONROW LINE06+8
	8,   // L_HORIZONPOSITIONCOL
	1,   // L_HORIZONPOSITIONDSPL

	255, // L_HORIZONSIDEREFROW
	255, // L_HORIZONSIDEREFCOL
	1,   // L_HORIZONSIDEREFDSPL

	255, // L_HORIZONCENTERREFROW
	255, // L_HORIZONCENTERREFCOL
	1,   // L_HORIZONCENTERREFDSPL

	7,   // L_CURRENTTHROTTLEPOSITIONROW LINE14+22
	20,  // L_CURRENTTHROTTLEPOSITIONCOL
	1,   // L_CURRENTTHROTTLEPOSITIONDSPL

	15,   // L_FLYTIMEPOSITIONROW LINE15+22
	14,   // L_FLYTIMEPOSITIONCOL
	1,    // L_FLYTIMEPOSITIONDSPL

	15,   // L_ONTIMEPOSITIONROW LINE15+22
	14,   // L_ONTIMEPOSITIONCOL
	1,    // L_ONTIMEPOSITIONDSPL

	3,   // L_MOTORARMEDPOSITIONROW LINE14+11
	24,  // L_MOTORARMEDPOSITIONCOL
	1,   // L_MOTORARMEDPOSITIONDSPL

	14,   // L_MW_GPS_LATPOSITIONROW  LINE12+2
	2,    // L_MW_GPS_LATPOSITIONCOL
	1,    // L_MW_GPS_LATPOSITIONDSPL

	15,   // L_MW_GPS_LONPOSITIONROW  LINE12+15
	2,    // L_MW_GPS_LONPOSITIONCOL
	1,    // L_MW_GPS_LONPOSITIONDSPL

	2,    // L_RSSIPOSITIONROW LINE14+2
	12,   // L_RSSIPOSITIONCOL
	1,    // L_RSSIPOSITIONDSPL

	15,   // L_VOLTAGEPOSITIONROW LINE15+3
	23,   // L_VOLTAGEPOSITIONCOL
	1,    // L_VOLTAGEPOSITIONDSPL

	255,  // L_MAINBATLEVEVOLUTIONROW,
	255,  // L_MAINBATLEVEVOLUTIONCOL,
	1,    // L_MAINBATLEVEVOLUTIONDSPL,

	13,   // L_VIDVOLTAGEPOSITIONROW LINE13+3
	23,   // L_VIDVOLTAGEPOSITIONCOL
	0,    // L_VIDVOLTAGEPOSITIONDSPL

	14,   // L_AMPERAGEPOSITIONROW LINE15+10
	23,   // L_AMPERAGEPOSITIONCOL
	1,    // L_AMPERAGEPOSITIONDSPL

	14,   // L_PMETERSUMPOSITIONROW LINE15+16
	14,   // L_PMETERSUMPOSITIONCOL
	1,    // L_PMETERSUMPOSITIONDSPL

	13,   // L_CALLSIGNPOSITIONROW LINE14+10
	10,   // L_CALLSIGNPOSITIONCOL
	1,    // L_CALLSIGNPOSITIONDSPL
};


// NTSC item position Defaults
uint8_t EEPROM_NTSC_DEFAULT[EEPROM_ITEM_LOCATION-EEPROM_SETTINGS] = {
	// ROW= Row position on screen (255= no action)
	// COL= Column position on screen (255= no action)
	// DSPL= Display item on screen

	2,   // L_GPS_NUMSATPOSITIONROW LINE02+6
	18,  // L_GPS_NUMSATPOSITIONCOL
	1,   // L_GPS_NUMSATPOSITIONDSPL

	6,   // L_GPS_DIRECTIONTOHOMEPOSROW LINE03+14
	2,   // L_GPS_DIRECTIONTOHOMEPOSCOL
	1,   // L_GPS_DIRECTIONTOHOMEPOSDSPL

	10,   // L_GPS_DISTANCETOHOMEPOSROW LINE02+24
	2,   // L_GPS_DISTANCETOHOMEPOSCOL
	1,   // L_GPS_DISTANCETOHOMEPOSDSPL

	10,  // L_SPEEDPOSITIONROW LINE03+24
	23,   // L_SPEEDPOSITIONCOL
	1,   // L_SPEEDPOSITIONDSPL

	9,   // L_GPS_ANGLETOHOMEPOSROW LINE04+12
	2,   // L_GPS_ANGLETOHOMEPOSCOL
	0,   // L_GPS_ANGLETOHOMEPOSDSPL

	/*11,  // L_MW_GPS_ALTPOSITIONROW LINE04+24   Do not remove yet
	2,   // L_MW_GPS_ALTPOSITIONCOL
	0,   // L_MW_GPS_ALTPOSITIONDSPL*/

	2,   // L_SENSORPOSITIONROW LINE03+2
	24,  // L_SENSORPOSITIONCOL
	1,   // L_SENSORPOSITIONDSPL

	2,   // L_MODEPOSITIONROW   LINE05+2
	8,  // L_MODEPOSITIONCOL
	1,   // L_MODEPOSITIONDSPL

	3,   // L_MW_HEADINGPOSITIONROW LINE02+19
	2,   // L_MW_HEADINGPOSITIONCOL
	1,   // L_MW_HEADINGPOSITIONDSPL

	2,   // L_MW_HEADINGGRAPHPOSROW LINE02+10
	2,   // L_MW_HEADINGGRAPHPOSCOL
	1,   // L_MW_HEADINGGRAPHPOSDSPL

	/*12,  // L_TEMPERATUREPOSROW LINE11+2       // Do not remove yet
	2,   // L_TEMPERATUREPOSCOL
	0,   // L_TEMPERATUREPOSDSPL*/

	6,  // L_MW_ALTITUDEPOSITIONROW LINE08+2
	23,  // L_MW_ALTITUDEPOSITIONCOL
	1,   // L_MW_ALTITUDEPOSITIONDSPL

	8,   // L_CLIMBRATEPOSITIONROW LINE08+24
	5,  // L_CLIMBRATEPOSITIONCOL
	1,   // L_CLIMBRATEPOSITIONDSPL

	6,   // L_HORIZONPOSITIONROW LINE06+8
	8,   // L_HORIZONPOSITIONCOL
	1,   // L_HORIZONPOSITIONDSPL

	255, // L_HORIZONSIDEREFROW
	255, // L_HORIZONSIDEREFCOL
	1,   // L_HORIZONSIDEREFDSPL

	255, // L_HORIZONCENTERREFROW
	255, // L_HORIZONCENTERREFCOL
	1,   // L_HORIZONCENTERREFDSPL

	7,   // L_CURRENTTHROTTLEPOSITIONROW LINE14+22
	20,  // L_CURRENTTHROTTLEPOSITIONCOL
	1,   // L_CURRENTTHROTTLEPOSITIONDSPL

	13,   // L_FLYTIMEPOSITIONROW LINE15+22
	14,   // L_FLYTIMEPOSITIONCOL
	1,    // L_FLYTIMEPOSITIONDSPL

	13,   // L_ONTIMEPOSITIONROW LINE15+22
	14,   // L_ONTIMEPOSITIONCOL
	1,    // L_ONTIMEPOSITIONDSPL

	3,    // L_MOTORARMEDPOSITIONROW LINE14+11
	24,   // L_MOTORARMEDPOSITIONCOL
	1,    // L_MOTORARMEDPOSITIONDSPL

	12,   // L_MW_GPS_LATPOSITIONROW  LINE12+2
	2,    // L_MW_GPS_LATPOSITIONCOL
	1,    // L_MW_GPS_LATPOSITIONDSPL

	13,   // L_MW_GPS_LONPOSITIONROW  LINE12+15
	2,    // L_MW_GPS_LONPOSITIONCOL
	1,    // L_MW_GPS_LONPOSITIONDSPL

	2,    // L_RSSIPOSITIONROW LINE14+2
	12,   // L_RSSIPOSITIONCOL
	1,    // L_RSSIPOSITIONDSPL

	13,   // L_VOLTAGEPOSITIONROW LINE15+3
	23,   // L_VOLTAGEPOSITIONCOL
	1,    // L_VOLTAGEPOSITIONDSPL

	255,  // L_MAINBATLEVEVOLUTIONROW
	255,  // L_MAINBATLEVEVOLUTIONCOL
	1,    // L_MAINBATLEVEVOLUTIONDSPL

	11,   // L_VIDVOLTAGEPOSITIONROW LINE13+3
	23,   // L_VIDVOLTAGEPOSITIONCOL
	0,    // L_VIDVOLTAGEPOSITIONDSPL

	12,   // L_AMPERAGEPOSITIONROW LINE15+10
	23,   // L_AMPERAGEPOSITIONCOL
	1,    // L_AMPERAGEPOSITIONDSPL

	12,   // L_PMETERSUMPOSITIONROW LINE15+16
	14,   // L_PMETERSUMPOSITIONCOL
	1,    // L_PMETERSUMPOSITIONDSPL

	11,   // L_CALLSIGNPOSITIONROW LINE14+10
	10,   // L_CALLSIGNPOSITIONCOL
	1,    // L_CALLSIGNPOSITIONDSPL
};

void checkEEPROM(void)
{
	// For H/W Settings
	uint8_t EEPROM_Loaded = EEPROM.read(0);
	if (!EEPROM_Loaded){
		for(uint8_t en=0;en<EEPROM_SETTINGS;en++){
			if (EEPROM.read(en) != EEPROM_DEFAULT[en])  EEPROM.write(en,EEPROM_DEFAULT[en]);
		}
		// For items on screen.
		// First run, the default will be NTSC (show all data lines with NTSC systems that has only 13 lines)
		// In OSD menu' it's possible a quick default setup for PAL or NTSC
		for(uint16_t en=0;en<EEPROM_ITEM_LOCATION-EEPROM_SETTINGS;en++) {
			if (EEPROM.read(en+EEPROM_SETTINGS+1) != EEPROM_NTSC_DEFAULT[en]) EEPROM.write(en+EEPROM_SETTINGS+1,EEPROM_NTSC_DEFAULT[en]);
		}
	}
}

void writeEEPROM(void)
{
	// For Settings
	for(uint16_t en=0;en<EEPROM_SETTINGS;en++){
		if (EEPROM.read(en) != Settings[en]) EEPROM.write(en,Settings[en]);
	}
	// For Position of items on screen
	for(uint16_t en=0;en<EEPROM_ITEM_LOCATION-EEPROM_SETTINGS;en++){
		if (EEPROM.read(en+EEPROM_SETTINGS+1) != Settings[en+EEPROM_SETTINGS+1]) EEPROM.write(en+EEPROM_SETTINGS+1,Settings[en+EEPROM_SETTINGS+1]);
	}
}

void readEEPROM(void)
{
	// For Settings
	for(uint16_t en=0;en<EEPROM_SETTINGS;en++){
		Settings[en] = EEPROM.read(en);
	}
	// For Position of items on screen
	for(uint16_t en=0;en<EEPROM_ITEM_LOCATION-EEPROM_SETTINGS;en++){
		Settings[en+EEPROM_SETTINGS+1] = EEPROM.read(en+EEPROM_SETTINGS+1);
	}
}

// back to default setting & position for PAL/NTSC
void WriteScreenLayoutDefault(void)
{
	if (Settings[S_VIDEOSIGNALTYPE]){  // PAL
		for(uint16_t en=0;en<EEPROM_ITEM_LOCATION-EEPROM_SETTINGS;en++) {
			if (EEPROM.read(en+EEPROM_SETTINGS+1) != EEPROM_PAL_DEFAULT[en]) EEPROM.write(en+EEPROM_SETTINGS+1,EEPROM_PAL_DEFAULT[en]);
		}
	}
	else {
		for(uint16_t en=0;en<EEPROM_ITEM_LOCATION-EEPROM_SETTINGS;en++) {
			if (EEPROM.read(en+EEPROM_SETTINGS+1) != EEPROM_NTSC_DEFAULT[en]) EEPROM.write(en+EEPROM_SETTINGS+1,EEPROM_NTSC_DEFAULT[en]);
		}
	}
	readEEPROM();  // Refresh with default data
}