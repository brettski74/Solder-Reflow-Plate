/**
 * Configuration Header
 * Author: Brett Gersekowski
 * 
 * Copyright (C) 2023 by Brett Gersekowski and others
 * See LICENCE file in the root of thir repository for licence terms.
 * 
 */
#ifndef THERMAL_H
#define THERMAL_H

#include "thermal_config.h"

/**
 * Function primitive for thermal sensor parameter setup. Called once on device startup to calculate
 * required coefficients to convert ADC output into a temperature value.
 */
void initializeTemperatureSensor();

/**
 * Function primitive for obtaining the current hotplate temperature from the temperature sensor.
 * 
 * Returns temperature in celsius.
 */
float getHotplateTemperature();

// ifndef THERMAL_H
#endif
