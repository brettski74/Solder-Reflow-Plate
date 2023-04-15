/**
 * Configuration Header
 * Author: Brett Gersekowski
 * 
 * Copyright (C) 2023 by Brett Gersekowski and others
 * See LICENCE file in the root of thir repository for licence terms.
 * 
 */

// Prevent reloading
#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

/**
 * Set the analog read resolution for the current device. Typically 10 bits.
 */
#define ANALOG_READ_RES 10
#define ADC_MAX ((1 << ANALOG_READ_RES) - 1)

/**
 * Positive MCU power rail voltage. Typically 5.0 volts.
 */
#define VDD 5.0

// ifndef DEVICE_CONFIG_H
#endif
