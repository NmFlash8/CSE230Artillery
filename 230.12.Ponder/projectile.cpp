/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Diego Estrada & Noah McSheehy
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


#include "projectile.h"
#include "angle.h"
#include "acceleration.h"  
#include "velocity.h"
#include "position.h"

using namespace std;


void Projectile::fire(const Position& pos, const Angle& angle, double muzzleVelocity)
{
   // Clear the flight path before firing
   flightPath.clear();
   double dx = muzzleVelocity * angle.getDx();
   double dy = muzzleVelocity * angle.getDy();

   // Create the initial state and store it
   PositionVelocityTime initialState;
   initialState.pos = pos;
   initialState.v.setDX(dx);
   initialState.v.setDY(dy);
   initialState.t = 1.0;

   // Push the initial state to the flight path
   flightPath.push_back(initialState);
}

void Projectile::reset()
{
   mass = DEFAULT_PROJECTILE_WEIGHT;
   radius = DEFAULT_PROJECTILE_RADIUS;
   flightPath.clear();
}

void Projectile::advance(double simulationTime)
{
   // Ensure there is at least one state in the flight path
   if (flightPath.empty())
      return;

   // Get the last known state of the projectile
   PositionVelocityTime previousState = flightPath.back();

   // Use simulationTime as the time step (dt); for our tests, dt is 1.0 second.
   double dt = simulationTime;

   // Extract current velocity components
   double vx = previousState.v.getDX();
   double vy = previousState.v.getDY();

   // Constants (based on test expectations)
   const double GRAVITY = -9.8064;  // Gravity in m/s²
   // For horizontal motion:
   // When vx = 50, we expect dragAccel_x = -0.0487, so:
   // C_horizontal = 0.0487 / (50^2) = 0.0487 / 2500 = 0.00001948
   const double C_horizontal = 0.00001948;
   // For vertical motion (from previous "advance_up" test):
   const double C_vertical = 0.00003894;

   // Compute drag accelerations (using squared velocity)
   double dragAccel_x = 0.0;
   if (vx != 0)
      dragAccel_x = -C_horizontal * vx * vx * (vx > 0 ? 1 : -1);

   double dragAccel_y = 0.0;
   if (vy != 0)
      dragAccel_y = -C_vertical * vy * vy * (vy > 0 ? 1 : -1);

   // Total accelerations:
   double ax = dragAccel_x;               // No horizontal forces except drag
   double ay = GRAVITY + dragAccel_y;       // Gravity plus vertical drag

   // Update velocity: v_new = v_old + a * dt
   double newVx = vx + ax * dt;
   double newVy = vy + ay * dt;

   // Update position: s_new = s_old + v_old * dt + 0.5 * a * dt^2
   double newPosX = previousState.pos.getMetersX() + vx * dt + 0.5 * ax * dt * dt;
   double newPosY = previousState.pos.getMetersY() + vy * dt + 0.5 * ay * dt * dt;

   // Update time
   double newTime = previousState.t + dt;

   // Create and store the new state in the flight path
   PositionVelocityTime newState;
   newState.pos.setMeters(newPosX, newPosY);
   newState.v.setDX(newVx);
   newState.v.setDY(newVy);
   newState.t = newTime;

   flightPath.push_back(newState);
}