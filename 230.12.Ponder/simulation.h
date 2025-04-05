/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    Diego Estrada & Noah McSheehy
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "ground.h"
#include "howitzer.h" 
#include "uiInteract.h"  
#include <iostream>

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight)
      : posUpperRight(posUpperRight),
      ground(posUpperRight),
      howitzer() // Default constructor
   {
      // Reset the ground before generating the howitzer's position
      Position pos = howitzer.getPosition();
      ground.reset(pos);

      std::cout << ground.getTarget() << std::endl;

      // Now, generate the howitzer's position after the ground has been reset
      howitzer.generatePosition(posUpperRight);

      initialized = false;
      firing = false;
      flightTime = 0.0;
   }


   void draw(ogstream& gout)
   {
      if (!initialized)
      {
         Position pos = howitzer.getPosition();
         ground.reset(pos);
         initialized = true;
      }

      if (firing)
         flightTime += 0.1;
      else
         flightTime = 0.0;

      ground.draw(gout);
      howitzer.draw(gout, flightTime); // Use updated time
   }


   void input(const Interface* pUI)
   {
      const double angleDelta = 0.03; // radians (~1.7 degrees)

      if (pUI->isUp())
         howitzer.raise(angleDelta);
      if (pUI->isDown())
         howitzer.raise(-angleDelta);

      if (pUI->isSpace())
      {
         firing = true;
         flightTime = 0.0;  // Reset timer when firing starts
      }
   }

private:
   Position posUpperRight;
   Ground   ground;
   Howitzer howitzer;
   bool     initialized;
   bool     firing;              
   double   flightTime;   

};