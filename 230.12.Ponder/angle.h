/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;


   // Constructors
   Angle();                                        // Default constructor
   Angle(const Angle& rhs);                        // Copy constructor
   Angle(double degrees);                          // Constructor with degrees

   // Getters
   double getDegrees() const;                      // Get the angle in degrees
   double getRadians() const;                      // Get the angle in radians
   double getDx()      const;                      // Get horizontal component
   double getDy()      const;                      // Get vertical component
   bool   isRight()    const;                      // Check if angle is right side
   bool   isLeft()     const;                      // Check if angle is left side

   // Setters
   void   setDegrees(double degrees);              // Set using degrees
   void   setRadians(double radians);              // Set using radians
   void   setUp();                                 // Set to 0 radians (up)
   void   setDown();                               // Set to Pi radians (down)
   void   setRight();                              // Set to Pi/2 radians (right)
   void   setLeft();                               // Set to 3Pi/2 radians (left)
   void   reverse();                               // Reverse the direction by Pi radians
   Angle& add(double delta);                       // Add a delta in radians
   void   setDxDy(double dx, double dy);           // Set angle based on components

private:
   double normalize(double radians) const;         // Normalize radians between (0, 2Pi)
   double convertToDegrees() const;                // Convert radians to degrees
   double convertToRadians(double degrees) const;  // Convert degrees to radians
   double radians;                                 // 360 degrees equals 2 PI radians
};
