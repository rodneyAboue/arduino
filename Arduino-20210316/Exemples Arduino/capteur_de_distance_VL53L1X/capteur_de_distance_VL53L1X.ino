﻿

// Utilise la librairie sparkfun
// https://github.com/sparkfun/SparkFun_VL53L1X_Arduino_Library

// télécharger SparkFun_VL53L1X_Arduino_Library-master.zip
// Installer l'archive dans l'application Arduino
// Lancer le programme Arduino sur PC
// Clic sur Croquis / Importer bibliothèque / Add Library 
// puis importer l'archive .zip
// Note : 
// l'installation diffère suivant la version de l'application Arduino

// ce programme affiche la distance mesurée et la fiabilité de la mesure
// la mesure est fiable si la valeur de signalRate est de l'ordre de 15000



#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>

/*
  Reading distance from the laser based VL53L1X
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SparkFun labored with love to create this code. Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/14667

  This example prints the distance to an object.

  Are you getting weird readings? Be sure the vacuum tape has been removed from the sensor.
*/

#include <Wire.h>
#include "SparkFun_VL53L1X.h" //Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X

//Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3

SFEVL53L1X distanceSensor;
//Uncomment the following line to use the optional shutdown and interrupt pins.
//SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

void setup(void)
{
  Wire.begin();

  Serial.begin(9600);
  Serial.println("VL53L1X Qwiic Test");

  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }

  //distanceSensor.setDistanceModeShort();
  distanceSensor.setDistanceModeLong();

  Serial.println("Sensor online!");
}

void loop(void)
{
  distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
  }
  int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();

  Serial.print("Distance(mm): ");
  Serial.print(distance);

  float distanceInches = distance * 0.0393701;
  float distanceFeet = distanceInches / 12.0;

  Serial.print("\tDistance(ft): ");
  Serial.print(distanceFeet, 2);

  Serial.print(" ");

  int signalRate = distanceSensor.getSignalRate();
  Serial.print("\tSignal rate: ");
  Serial.print(signalRate);

  byte rangeStatus = distanceSensor.getRangeStatus();
  Serial.print("\tRange Status: ");

  //Make it human readable
  switch (rangeStatus)
  {
  case 0:
    Serial.print("Good");
    break;
  case 1:
    Serial.print("Sigma fail");
    break;
  case 2:
    Serial.print("Signal fail");
    break;
  case 7:
    Serial.print("Wrapped target fail");
    break;
  default:
    Serial.print("Unknown: ");
    Serial.print(rangeStatus);
    break;
  }

  Serial.println();

}

