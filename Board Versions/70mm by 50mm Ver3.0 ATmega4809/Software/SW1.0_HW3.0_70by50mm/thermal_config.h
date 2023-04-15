/**
 * Configuration Header
 * Author: Brett Gersekowski
 * 
 * Copyright (C) 2023 by Brett Gersekowski and others
 * See LICENCE file in the root of thir repository for licence terms.
 * 
 */

// Prevent reloading
#ifndef THERMAL_CONFIG_H
#define THERMAL_CONFIG_H

/**
 * Temperature analog input pin
 */
#define THERMAL_PIN PIN_PF5

/**
 * Temperature oversampling - how many times to read the temperature sensor and average to reduce noise
 */
#define THERMAL_OVERSAMPLE 64

/**
 * Fudge factor parameters for sub-optimal thermal sensor placement.
 * 
 * The original hardware design placed the thermal sensor off to the side of the hotplate. This led to
 * large differences between the measured temperature and temperatures on the actual heating element.
 * Temperatures at the edge could be as much as 30 celsius higher than measured, while temperatures in
 * the centre may be as much as 70-80 celsius higher than measured.
 */

/**
 * Typical ambient temperature. 25 celsius should be close enough for most practical purposes.
 */
#define THERMAL_AMBIENT 25.0

/**
 * Fudge factor to be applied to the measured temperature prior to returning to the control
 * code. The way this value is used is that the returned temperature is calculated as:
 *
 *     ambient + (temperature - ambient) * fudge_factor
 *
 * A fudge factor of 1.194 and ambient temperature of 1.194 means that when the sensor measures
 * 180 celsius, the controller will assume a temperature of about 210 on the hotplate.
 */
#define THERMAL_FUDGE_FACTOR 1.0
 
/**
 * Select thermal sensor algorithm.
 * Uncomment one and only one of the following thermal sensor algorithms
 * 
 *  - THERMAL_LINEAR_2_POINT
 *  - THERMAL_NTC_BETA
 *  - THERMAL_NTC_2_POINT
 */
 
/**
 * #define THERMAL_LINEAR_2_POINT
 * 
 * Use two-point linear approximation for sensors like the LMT85 or LMT86.
 * 
 * Algorithm requires definition of:
 *   THERMAL_T0 - lower reference temperature for the temperature sensor
 *   THERMAL_V0 - sensor output voltage at temperature THERMAL_T0
 *   THERMAL_T1 - upper reference temperature for the temperature sensor
 *   THERMAL_V1 - sensor output voltage at temperature THERMAL_T1
 */

/**
 * #define THERMAL_NTC_BETA
 * 
 * Use an NTC thermistor with the Steinhart-Hart equation with T0/R0 and published beta value.
 * 
 * Algorithm requires definition of:
 *   THERMAL_T0   - temperature in celsius at which nominal resistance is observed (typically 25)
 *   THERMAL_R0   - resistance in ohms at temperature THERMAL_T0
 *   THERMAL_BETA - beta value for the thermistor in Kelvin (typically something like 3950)
 *   THERMAL_RHI  - resistance in ohms of the fixed resistor if connected between the thermistor and Vdd
 *   THERMAL_RLO  - resistance in ohms of the fixed resistor if connected between the thermistor and ground
 */

/**
 * #define THERMAL_NTC_2_POINT
 * 
 * Use an NTC thermistor with the Steinhart-Hart equation with two reference points from the thermistor datasheet.
 * This will generally be more accurate than simply using a published beta value provided that the reference points
 * are separated by a suitably wide margin. For best results, suggested reference points should be based on
 * 25 celsius and 200 celsius, or if the datasheet doesn't go as high as 200 celsius, then the highest temperature
 * for which data is available.
 * 
 * Suggested value for the series resistor is 1k, to be connected between the thermistor and ground. This gives
 * ADC outputs which are higher for higher temperatures. It can also work with the series resistor connected
 * between the thermistor and ground, but the ADC outputs now go in the opposite direction to temperature. ie.
 * lower ADC output for higher temperatures.
 *
 * Algorithm requires definition of:
 *   THERMAL_T0   - temperature in celsius at which nominal resistance is observed (typically 25)
 *   THERMAL_R0   - resistance in ohms at temperature THERMAL_T0
 *   THERMAL_BETA - beta value for the thermistor in Kelvin (typically something like 3950)
 *   THERMAL_RHI  - resistance in ohms of the fixed resistor if connected between the thermistor and Vdd (recommended)
 *   THERMAL_RLO  - resistance in ohms of the fixed resistor if connected between the thermistor and ground
 *   
 * Technically, resistances don't necessarily need to be in ohms. So long as all resistances are specified in the same
 * unit, it should work ok, although the code has only been tested with resistances specified in ohms, so...
 */

/**
 * Uncomment below if using an LMT85 temperature sensor.
 * 
 *
#define THERMAL_LINEAR_2_POINT
#define THERMAL_T0 25.0
#define THERMAL_V0 1.365
#define THERMAL_T1 150.0
#define THERMAL_V1 0.301
/**/

/**
 * Uncomment below if using an LMT86 temperature sensor.
 * 
 *
#define THERMAL_LINEAR_2_POINT
#define THERMAL_T0 25.0
#define THERMAL_V0 1.831
#define THERMAL_T1 150.0
#define THERMAL_V1 0.420
/**/

/**
 * Uncomment below if using an NTC thermistor using 2 reference points from the datasheet.
 * 
 * Example data below is for an Eaton NRBG504?3950B1* thermistor with a 1k resistor connected
 * between Vdd and one of the thermistor leads.
 * 
 */
#define THERMAL_NTC_2_POINT
#define THERMAL_T0  25.0
#define THERMAL_R0  50000.0
#define THERMAL_T1  200.0
#define THERMAL_R1  252.4
#define THERMAL_RHI 1000.0
/**/

/**
 * Uncomment below if using an NTC thermistor using a single reference point and a published beta
 * value from the datasheet. This method can be used is the datasheet does not publish detailed
 * temperature/resistance data or if the specific datasheet for the thermistor used cannot be
 * found. Note that thermistors usually specify beta values based on fairly narrow temperature
 * range, such as 25-50 celsius (or sometimes 25-85 or 25-100 celsius) Temperature can be estimated
 * using the Steinhart-Hart equation, but accuracy gets worse the further outside this range you
 * go. If you have the data available, using a 2-point Steinhart-Hart approximation using more
 * widely spaced data points is likely to give more accurate results - especially at higher
 * temperatures.
 *
 * Values below for a typical 10k NTC thermistor (B=3950K) with 1k fixed resistor between the
 * thermistor and ground.
 * 
#define THERMAL_NTC_BETA
#define THERMAL_T0   25.0
#define THERMAL_R0   10000.0
#define THERMAL_BETA 3950.0
#define THERMAL_RLO  1000.0
/**/

// ifndef THERMAL_CONFIG_H
#endif
