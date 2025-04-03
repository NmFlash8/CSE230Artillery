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
   // Constructor initializes the ground with the upper-right position
   Simulator(const Position& posUpperRight) : ground(posUpperRight) {}

   // Accessor for ground
   Ground& getGround() { return ground; }
   const Ground& getGround() const { return ground; }

private:
   Ground ground; // The ground object to be drawn
};