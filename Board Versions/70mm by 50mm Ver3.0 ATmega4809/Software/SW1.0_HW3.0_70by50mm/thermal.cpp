#include <Arduino.h>
#include "thermal.h"
#include "device_config.h"

#ifdef THERMAL_NTC_BETA
#define THERMAL_NTC
#endif

#ifdef THERMAL_NTC_2_POINT
#define THERMAL_NTC
#endif

#ifdef THERMAL_NTC
float beta;
float r_inf;
#endif

#ifdef THERMAL_LINEAR_2_POINT
float gradient;
float intercept;
#endif

/**
 * Thermal sensor parameter setup.
 * 
 * Different thermal sensor algorithms can be supported based on thermal sensor setup.
 * Configuration header supports specifying thermal sensor specifications based on the
 * datasheet or published specs. This function calculates various conversion factors
 * that may be used at runtime to convert the ADC readings to a temperature value in
 * celsius.
 */
void initializeTemperatureSensor() {
  pinMode(THERMAL_PIN,INPUT);

#ifdef THERMAL_LINEAR_2_POINT
  // Code below assumes 10-bit ADC resolution, but would be better to determine read
  // resolution somehow either in the code or pre-processor and act accordingly
  float adc0 = ADC_MAX * THERMAL_V0 / VDD;
  float adc1 = ADC_MAX * THERMAL_V1 / VDD;
  
  gradient = (THERMAL_T0 - THERMAL_T1) / (adc0 - adc1);
  intercept = THERMAL_T0 - gradient * adc0;
#endif

#ifdef THERMAL_NTC_BETA
  beta = THERMAL_BETA;
  float kelvin0 = THERMAL_T0 + 273.15;
#endif

#ifdef THERMAL_NTC_2_POINT
  float kelvin0 = THERMAL_T0 + 273.15;
  float kelvin1 = THERMAL_T1 + 273.15;

  beta = kelvin1 * kelvin0 / (kelvin1 - kelvin0) * log(THERMAL_R0 / THERMAL_R1);
#endif

#ifdef THERMAL_NTC
  r_inf = THERMAL_R0 * exp(-beta / kelvin0);
#endif
}

/**
 * Read the temperature sensor and return hotplate temperature in celsius.
 */
float getHotplateTemperature() {
  float t = 0;

  // Fetch raw ADC values as per oversampling configuration
  for (byte i = 0; i < THERMAL_OVERSAMPLE; i++) {
    t += analogRead(THERMAL_PIN);
  }
  t = t / THERMAL_OVERSAMPLE;

#ifdef THERMAL_LINEAR_2_POINT
  t = t * gradient + intercept;
#endif

#ifdef THERMAL_NTC
#ifdef THERMAL_RLO
  float r = THERMAL_RLO * (ADC_MAX - t) / t;
#endif
#ifdef THERMAL_RHI
  float r = THERMAL_RHI * t / (ADC_MAX - t);
#endif
  t = beta / log(r / r_inf);
#endif

  return THERMAL_AMBIENT + (t - THERMAL_AMBIENT) * THERMAL_FUDGE_FACTOR;
}
