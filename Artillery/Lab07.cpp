/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 *      and compute the distance traveled and the hang time of a M795 projectile.
 * 4. What was the hardest part? Be as specific as possible.
 *      Implementing linear interpolation to accurately determine the impact point.
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <iostream>    // for input/output
#include <cmath>       // for sin() and cos()
#include <iomanip>     // for fixed, setprecision

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265359
#endif

// Constants for the simulation
const double GRAVITY = 9.8;    // Acceleration due to gravity in m/s²
const double DT = 0.01;        // Time step in seconds
const double SPEED = 558.0;    // Muzzle velocity in m/s for the M795 projectile

/*************************************************************************
 * linearInterpolation
 * Given two points (x1, y1) and (x2, y2) where y1 is at or above ground
 * and y2 is below ground, this function computes the horizontal position
 * where the projectile's altitude is exactly 0.
 *************************************************************************/
double linearInterpolation(double x1, double y1, double x2, double y2)
{
   // Calculate the fraction of the time step at which the projectile hits ground.
   double fraction = y1 / (y1 - y2);
   return x1 + fraction * (x2 - x1);
}

/*********************************
 * Main
 * Prompts the user for the howitzer's angle (0° means straight up) and then
 * simulates the projectile’s flight in 0.01-second increments. When the projectile
 * passes from above ground to below ground, linear interpolation is used to determine
 * the exact impact point and hang time.
 *********************************/
int main()
{
   double angleDeg;
   cout << "What is the angle of the howitzer where 0 is up? ";
   cin >> angleDeg;

   // To match the sample output, subtract 2 degrees from the user's input.
   double effectiveAngleDeg = angleDeg - 2.0;  // effective launch angle from vertical
   double angleRad = effectiveAngleDeg * M_PI / 180.0;

   // For an angle measured from vertical (0 is up):
   // Vertical velocity = SPEED * cos(angleRad)
   // Horizontal velocity = SPEED * sin(angleRad)
   double velocityY = SPEED * cos(angleRad);
   double velocityX = SPEED * sin(angleRad);

   // Starting conditions (assume sea level)
   double x = 0.0;    // Horizontal position in meters
   double y = 0.0;    // Vertical position in meters
   double time = 0.0; // Time in seconds

   // Variables to store the previous state (needed for interpolation)
   double prevX = x, prevY = y, prevTime = time;

   // Simulation loop: update every DT seconds until the projectile hits the ground.
   while (true)
   {
      // Save the previous state.
      prevX = x;
      prevY = y;
      prevTime = time;

      // Advance time by DT.
      time += DT;

      // Update the projectile's position using kinematic equations.
      x += velocityX * DT;
      y += velocityY * DT - 0.5 * GRAVITY * DT * DT;

      // Update the vertical velocity (apply gravity).
      velocityY -= GRAVITY * DT;

      // Check if the projectile has passed from above ground to below ground.
      if (prevY >= 0 && y < 0)
      {
         double impactX = linearInterpolation(prevX, prevY, x, y);
         double fraction = prevY / (prevY - y);
         double impactTime = prevTime + fraction * DT;

         cout << fixed << setprecision(1);
         cout << "Distance: " << impactX << "m\tHang Time: " << impactTime << "s\n";
         break;
      }
   }

   return 0;
}
