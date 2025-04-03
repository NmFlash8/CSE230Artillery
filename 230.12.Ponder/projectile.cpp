/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 using namespace std;


 void Projectile::fire(const Position& pos, const Angle& angle, double muzzleVelocity)
 {
    // Clear the flight path before firing
    flightPath.clear();

    // Use the Angle's getDx() and getDy() for proper directional components:
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


