/**********************************************************************
 * Header File:
 *    SIMULATOR
 * Author:
 *    Diego Estrada & Noah McSheehy
 * Summary:
 *    Executes one simulation of a projectile being fired.
 ************************************************************************/

#pragma once

#include "position.h"
#include "ground.h"
#include "howitzer.h"
#include "projectile.h"
#include "uiInteract.h"
#include <iostream>
#include <cmath>

 // Constants
constexpr double MUZZLE_VELOCITY = 827.0;
constexpr double FLIGHT_SPEED = 1.0;
constexpr double ANGLE_DELTA = 0.03;
constexpr double SMALL_ANGLE_DELTA = 0.005;
constexpr double HIT_THRESHOLD = 8.0;

/*********************************************
 * SIMULATOR
 * Execute one simulation of a projectile being fired.
 *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight);
   void draw(ogstream& gout);
   void input(const Interface* pUI);

private:
   void initializeSimulation();
   void updateProjectileFlight();
   void displayText(ogstream& gout);
   void handleHowitzerInput(const Interface* pUI);
   bool checkForHit() const;
   void startFiring();

   Projectile projectile;
   Position   posUpperRight;
   Howitzer   howitzer;
   Ground     ground;
   bool       initialized;
   bool       firing;
   bool       hit;
   double     flightTime;
};
