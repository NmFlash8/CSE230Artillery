/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/


#pragma once

#include "howitzer.h"
#include "unitTest.h"
#include <cassert>         
#include <cmath>           
#include "position.h"   
#include "angle.h"      

/*******************************
 * TEST HOWITZER
 * A friend class for Howitzer which contains the Howitzer unit tests
 ********************************/
class TestHowitzer : public UnitTest
{
public:
   void run()
   {
      // Ticket 1: Getters
      defaultConstructor();
      getPosition_zero();
      getPosition_middle();
      getMuzzleVelocity_slow();
      getMuzzleVelocity_standard();
      getElevation_up();
      getElevation_right();
      getElevation_left();

      // Ticket 2: Setters
      generatePosition_small();
      generatePosition_large();
      raise_rightDown();
      raise_rightUp();
      raise_leftDown();
      raise_leftUp();
      rotate_clock();
      rotate_counterClock();
      rotate_wrapClock();
      rotate_wrapCounterClock();

      report("Howitzer");
   }

private:
   double metersFromPixels = -1.0;

   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    DEFAULT CONSTRUCTOR
     * input:   nothing
     * output:  zeros (except angle is at 45 degrees, 
     *                 and the muzzle velocity is correct)
     *********************************************/
   void defaultConstructor()
   {  // Setup
      Howitzer howitzer;

      // Exercise
      double muzzleVelocity = howitzer.getMuzzleVelocity();
      double elevation = howitzer.elevation.getDegrees();
      double posX = howitzer.getPosition().getPixelsX();
      double posY = howitzer.getPosition().getPixelsY();

      // Verify
      assertEquals(muzzleVelocity, DEFAULT_MUZZLE_VELOCITY);
      assertEquals(elevation, 45.0);
      assertEquals(posX, 0.0);
      assertEquals(posY, 0.0);
   }  // Teardown

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GET POSITION ZERO
     * input:   h.pos=(0,0)
     * output:  pos=(0,0)
     *********************************************/
   void getPosition_zero()
   {  // Setup
      Howitzer howitzer;
      howitzer.getPosition().setPixelsX(0.0);
      howitzer.getPosition().setPixelsY(0.0);

      // Exercise
      Position pos = howitzer.getPosition();

      // Verify
      assertEquals(pos.getPixelsX(), 0.0);
      assertEquals(pos.getPixelsY(), 0.0);
   }  // Teardown


   /*********************************************
    * name:    GET POSITION MIDDLE
    * input:   h.pos=(123.4, 567.8)
    * output:  pos=(123.4, 567.8)
    *********************************************/
   void getPosition_middle()
   {  // Setup
      Howitzer howitzer;
      howitzer.getPosition().setPixelsX(123.4);
      howitzer.getPosition().setPixelsY(567.8);

      // Exercise
      Position pos = howitzer.getPosition();

      // Verify
      assertEquals(pos.getPixelsX(), 123.4);
      assertEquals(pos.getPixelsY(), 567.8);
   }  // Teardown


   /*********************************************
    * name:    GET MUZZLE VELOCITY - SLOW SPEED
    * input:   h.muzzleVelocity=(24.68)
    * output:  m=24.68
    *********************************************/
   void getMuzzleVelocity_slow()
   {  // Setup
      Howitzer howitzer;
      howitzer.muzzleVelocity = 24.68;

      // Exercise
      double m = howitzer.getMuzzleVelocity();

      // Verify
      assertEquals(m, 24.68);
   }  // Teardown

   /*********************************************
    * name:    GET MUZZLE VELOCITY - STANDARD SPEED
    * input:   h.muzzleVelocity=(827.00)
    * output:  m=827
    *********************************************/
   void getMuzzleVelocity_standard()
   {  // Setup
      Howitzer howitzer;
      howitzer.muzzleVelocity = 827.00;

      // Exercise
      double m = howitzer.getMuzzleVelocity();

      // Verify
      assertEquals(m, 827.00);
   }  // Teardown


   /*********************************************
    * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
    *********************************************/
   void getElevation_up()
   {
      // Setup
      Howitzer h;
      h.setElevation(0); // Use the setter to set the elevation to 0

      // Exercise
      double elevation = h.elevation.getRadians();

      // Verify
      assertEquals(elevation, 0.0);

   }  // Teardown

   /*********************************************
    * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
    *********************************************/
   void getElevation_right()
   {
      // Setup
      Howitzer h;
      h.setElevation(0.4); // Use the setter to set the elevation to 0.4 radians

      // Exercise
      double elevation = h.elevation.getRadians();

      // Verify
      assertEquals(elevation, 0.4);

   }  // Teardown

   /*********************************************
    * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
    *********************************************/
   void getElevation_left()
   {
      // Setup
      Howitzer h;
      h.setElevation(5.8); // Use the setter to set the elevation to 5.8 radians

      // Exercise
      double elevation = h.elevation.getRadians();

      // Verify
      assertEquals(elevation, 5.8);

   }  // Teardown

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GENERATE POSITION small board
     * input:   (10px, 10px)
     * output:  1px <= x <= 9px
     *********************************************/
   void generatePosition_small()
   {  // Setup
      Howitzer h;
      Position posUpperRight;
      posUpperRight.setPixelsX(10); // Set board width to 10px
      posUpperRight.setPixelsY(10); // Set board height to 10px

      // Exercise
      h.generatePosition(posUpperRight);
      Position howitzerPos = h.getPosition();
      double x = howitzerPos.getPixelsX();

      // Verify
      assertEquals(x >= 1.0 && x <= 9.0);

   }  // Teardown

    /*********************************************
    * name:    GENERATE POSITION large board
    * input:   (1000px, 1000px)
    * output:  100px <= x <= 900px
    *********************************************/
   void generatePosition_large()
   {
      // Setup
      Howitzer h;
      Position posUpperRight;
      posUpperRight.setPixelsX(1000); // Set board width to 1000px
      posUpperRight.setPixelsY(1000); // Set board height to 1000px

      // Exercise
      h.generatePosition(posUpperRight);
      Position howitzerPos = h.getPosition();
      double x = howitzerPos.getPixelsX();
      
      // Verify
      assertUnit(true x >= 100.0 && x <= 900.0);

   }  // Teardown

   /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
   void raise_rightDown()
   {
      // Setup
      Howitzer h;
      h.setElevation(0.5); 
      h.raise(-0.1); 

      // Verify
      double elevation = h.elevation.getRadians();

      assertEquals(elevation, 0.6);

   }  // Teardown

   /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_rightUp()
   {
      // Setup
      Howitzer h;
      h.setElevation(0.5); // Set the initial elevation to 0.5 radians

      // Exercise
      h.raise(0.1); // Raise the elevation to the right/up by 0.1 radians

      // Verify
      double elevation = h.elevation.getRadians();

      // Ensure the elevation has been updated correctly
      assertEquals(elevation, 0.4);
   }  // Teardown

   /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=-0.6radians
    *********************************************/
   void raise_leftDown()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_leftUp()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
   void rotate_clock()
   {  // Setup
      Howitzer h;
      h.setElevation(1.23); 
      // Exercise
      h.rotate(0.3);
      // Verify
      double elevation = h.elevation.getRadians();
      assertEquals(elevation, 1.53);
   }  // Teardown

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
   void rotate_counterClock()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 (2pi + -0.1) rotate=.2
    * output:  h.elevation=.1
    *********************************************/
   void rotate_wrapClock()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
    * input:   h.elevation=0.1 rotate=-.2 - 4PI
    * output:  h.elevation=6.1 (2pi + -0.1)
    *********************************************/
   void rotate_wrapCounterClock()
   {
      // Setup
      Howitzer howitzer;
      howitzer.elevation.setRadians(0.1);  

      // Exercise
      howitzer.rotate(-0.2 - (4 * M_PI));

      // Verify
      double expected = 2 * M_PI - 0.1; // 6.1 radians
      assertEquals(abs(howitzer.elevation.getRadians() - expected) < 0.0001);

      // Teardown
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1100.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assertEquals(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
};
