/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    Diego Estrada & Noah McSheehy
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"

 /*********************************************
  * Constructor
  *********************************************/
Simulator::Simulator(const Position& posUpperRight)
   : posUpperRight(posUpperRight),
     ground(posUpperRight),
     howitzer(),
     projectile(),
     initialized(false),
     firing(false),
     flightTime(0.0),
     hit(false)
{
   // Generate howitzer's random X position
   howitzer.generatePosition(posUpperRight);

   // Get howitzer's current position (with random X)
   Position pos = howitzer.getPosition();

   // Use this X value to get the elevation at that X on the ground
   Position xOnly;
   xOnly.setMetersX(pos.getMetersX());

   // Get the Y elevation in meters at that X
   double yMeters = ground.getElevationMeters(xOnly);

   // Convert Y elevation to pixels
   Position elevationPos;
   elevationPos.setMetersY(yMeters);
   int yPixels = elevationPos.getPixelsY();

   // Set howitzer's Y position to the correct ground elevation
   howitzer.setPixelY(yPixels);

   // Reset ground with the updated howitzer position
   ground.reset(howitzer.getPosition());
}


/*********************************************
 * Draw: render the simulation elements
 *********************************************/
void Simulator::draw(ogstream& gout)
{
   if (!initialized)
      initializeSimulation();

   updateProjectileFlight();
   projectile.draw(gout, flightTime);
   ground.draw(gout);
   howitzer.draw(gout, flightTime);

   displayText(gout);
}

/*********************************************
 * Input: handle user input
 *********************************************/
void Simulator::input(const Interface* pUI)
{
   handleHowitzerInput(pUI);

   if (pUI->isSpace())
      startFiring();
}

/*********************************************
 * initializeSimulation: setup ground for new sim
 *********************************************/
void Simulator::initializeSimulation()
{
   Position pos = howitzer.getPosition();
   ground.reset(pos);
   initialized = true;
}

/*********************************************
 * updateProjectileFlight
 *********************************************/
void Simulator::updateProjectileFlight()
{
   if (firing)
   {
      flightTime += FLIGHT_SPEED;
      projectile.advance(FLIGHT_SPEED);

      if (checkForHit())
      {
         hit = true;      
         firing = false; 
      }
   }
   else
   {
      flightTime = 0.0;
   }
}

/*********************************************
 * displayText: status info like angle & time
 *********************************************/
void Simulator::displayText(ogstream& gout)
{
   Position textPos;
   textPos.setPixelsX(600);
   textPos.setPixelsY(485);

   std::string status = "Ready";

   if (hit)
      status = "Target Hit";
   else if (firing)
      status = "Firing";

   gout = textPos;
   gout << "Status: " << status << "\n"
      << "Angle: " << howitzer.getElevation().getDegrees() << "\n"
      << "Flight time: " << flightTime << "\n\n";
}


/*********************************************
 * handleHowitzerInput: rotate & aim
 *********************************************/
void Simulator::handleHowitzerInput(const Interface* pUI)
{
   if (pUI->isUp())     howitzer.raise( SMALL_ANGLE_DELTA);
   if (pUI->isDown())   howitzer.raise(-SMALL_ANGLE_DELTA);
   if (pUI->isRight())  howitzer.rotate( ANGLE_DELTA);
   if (pUI->isLeft())   howitzer.rotate(-ANGLE_DELTA);
}

/*********************************************
 * checkForHit: collision detection
 *********************************************/
bool Simulator::checkForHit() const
{
   Position projectilePos = projectile.getPosition();
   Position targetPos = ground.getTarget();

   double distance = std::sqrt(
      std::pow(projectilePos.getPixelsX() - targetPos.getPixelsX(), 2) +
      std::pow(projectilePos.getPixelsY() - targetPos.getPixelsY(), 2)
   );

   return distance <= HIT_THRESHOLD;
}

/*********************************************
 * startFiring: fire the projectile
 *********************************************/
void Simulator::startFiring()
{
   firing = true;
   hit = false;
   flightTime = 0.0;

   Position howitzerPos = howitzer.getPosition();
   Angle    howitzerAngle = howitzer.getElevation();
   projectile.fire(howitzerPos, howitzerAngle, MUZZLE_VELOCITY);
}
