/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "ground.h"

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) : posUpperRight(posUpperRight), ground(posUpperRight) {}

   Ground& getGround() { return ground; }
   const Ground& getGround() const { return ground; }

private:
   Position posUpperRight;
   Ground ground;
};