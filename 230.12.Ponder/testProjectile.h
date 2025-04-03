/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/


#pragma once

#include "projectile.h"
#include "unitTest.h"


using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
   void run()
   {
      // Ticket 3: Setup
      defaultConstructor();
      reset_empty();
      reset_full();
      fire_right();
      fire_left();
      fire_up();

      // Ticket 4: Advance
      advance_nothing();
      advance_fall();
      advance_horizontal();
      advance_up();
      advance_diagonalUp();
      advance_diagonalDown();

      report("Projectile");
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
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void defaultConstructor()
   {
      // Setup
      Projectile p;

      // Exercise & Verify
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertEquals(p.flightPath.size(), (size_t)0); // Ensure flight path is empty

      // Teardown
   }

   /*********************************************
    * name:    RESET from empty
    * input:   mass=-99, radius=-99, flightPath={}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_empty()
   {
      // Create a projectile with invalid values
      Projectile p;
      p.mass = -99;
      p.radius = -99;
      // flightPath is already empty

      // Exercise: call reset to restore defaults
      p.reset();

      // Verify: mass, radius, and flightPath
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertEquals(p.flightPath.size(), (size_t)0);
   }

   /*********************************************
    * name:    RESET with a non-zero flight path
    * input:   mass=-99, radius=-99, flightPath={0,1,2}
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void reset_full()
   {
      // Setup: Create a projectile with invalid values and a non-empty flight path.
      Projectile p;
      p.mass = -99;
      p.radius = -99;

      // Add three entries to the flightPath list.
      Projectile::PositionVelocityTime entry;

      entry.pos = Position(0, 0);
      entry.v = Velocity(10, 10);
      entry.t = 0;
      p.flightPath.push_back(entry);

      entry.pos = Position(1, 1);
      entry.v = Velocity(20, 20);
      entry.t = 1;
      p.flightPath.push_back(entry);

      entry.pos = Position(2, 2);
      entry.v = Velocity(30, 30);
      entry.t = 2;
      p.flightPath.push_back(entry);

      // Exercise: Call reset to restore default values.
      p.reset();

      // Verify: Check that mass and radius have been reset, and that the flight path is cleared.
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertEquals(p.flightPath.size(), (size_t)0);
   }


   /*****************************************************************
    *****************************************************************
    * FIRE
    *****************************************************************
    *****************************************************************/  

   /*********************************************
    * name:    FIRE horizontally right
    * input:   angle=90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=100,0 t=1}
    *********************************************/
   void fire_right()
   {
      // Setup: Create a projectile
      Projectile p;

      // Input: position (111,222), angle 90 degrees, and muzzleVelocity 100
      Position pos(111, 222);
      Angle angle(90.0);    // Assuming 90 degrees is horizontal right
      double muzzleVelocity = 100.0;

      // Exercise: Fire the projectile
      p.fire(pos, angle, muzzleVelocity);

      // Verify: The flightPath should have exactly one entry with expected values
      assertEquals(p.flightPath.size(), (size_t)1);
      auto state = p.flightPath.front();

      // The position should match the input position
      assertEquals(state.pos.getMetersX(), 111.0);
      assertEquals(state.pos.getMetersY(), 222.0);

      // The velocity should be horizontal only: 100 in x direction, 0 in y direction
      assertEquals(state.v.getDX(), 100.0);
      assertEquals(state.v.getDY(), 0.0);

      // The time should be set to 1
      assertEquals(state.t, 1.0);
   }

   /*********************************************
    * name:    FIRE horizontally left
    * input:   angle=-90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=-100,0 t=1}
    *********************************************/
   void fire_left()
   {
      // Setup: Create a projectile
      Projectile p;

      // Input: position (111,222), angle -90 degrees, and muzzleVelocity 100
      Position pos(111, 222);
      Angle angle(-90.0);    // Assuming -90 degrees is horizontally left
      double muzzleVelocity = 100.0;

      // Exercise: Fire the projectile
      p.fire(pos, angle, muzzleVelocity);

      // Verify: The flightPath should have exactly one entry with expected values
      assertEquals(p.flightPath.size(), (size_t)1);
      auto state = p.flightPath.front();

      // The position should match the input position
      assertEquals(state.pos.getMetersX(), 111.0);
      assertEquals(state.pos.getMetersY(), 222.0);

      // The velocity should be horizontal only: -100 in x direction, 0 in y direction
      assertEquals(state.v.getDX(), -100.0);
      assertEquals(state.v.getDY(), 0.0);

      // The time should be set to 1
      assertEquals(state.t, 1.0);
   }

   /*********************************************
    * name:    FIRE straight up
    * input:   angle=0  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=0,100 t=1}
    *********************************************/
   void fire_up()
   {
      // Setup: Create a projectile
      Projectile p;

      // Input: position (111,222), angle 0 degrees, and muzzleVelocity 100
      Position pos(111, 222);
      Angle angle(0.0);  // 0 degrees means straight up
      double muzzleVelocity = 100.0;

      // Exercise: Fire the projectile
      p.fire(pos, angle, muzzleVelocity);

      // Verify: The flightPath should have exactly one entry with expected values
      assertEquals(p.flightPath.size(), (size_t)1);
      auto state = p.flightPath.front();

      // The position should match the input position
      assertEquals(state.pos.getMetersX(), 111.0);
      assertEquals(state.pos.getMetersY(), 222.0);

      // The velocity should be vertical only: 0 in x direction, 100 in y direction
      assertEquals(state.v.getDX(), 0.0);
      assertEquals(state.v.getDY(), 100.0);

      // The time should be set to 1
      assertEquals(state.t, 1.0);
   }

   /*****************************************************************
    *****************************************************************
    * ADVANCE
    *****************************************************************
    *****************************************************************/ 

   /*********************************************
    * name:    ADVANCE : the projectile is not fired. Nothing will happen
    * input:   flightPath={}
    * output:  flightPath={}
    *********************************************/
   void advance_nothing()
   {
      // Setup: Create a projectile that has not been fired
      Projectile p;

      // Ensure the flightPath is empty before advancing
      assertEquals(p.flightPath.empty(), true);

      // Exercise: Try advancing time (should do nothing)
      p.advance(1.0);

      // Verify: Flight path should remain empty
      assertEquals(p.flightPath.empty(), true);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is stationary and falls down
    * input:   flightPath={pos=100,200 v=0,0 t=100}
    * output:  flightPath={}{pos.x=100      = 100 + 0*1
    *                        pos.y=195.0968 = 200 + 0*1 + .5(-9.806)*1*1
    *                        v.dx =0        = 0 + 0*1
    *                        v.dy =-9.8     = 0 + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_fall()
   {
      // Setup: Create a projectile with an initial stationary state
      Projectile p;
      Projectile::PositionVelocityTime state;
      state.pos.setMeters(100, 200);  // Initial position (100,200)
      state.v.setDX(0);               // Initial velocity (0,0)
      state.v.setDY(0);
      state.t = 100;                  // Initial time
      p.flightPath.push_back(state);  // Add this state to flightPath

      // Exercise: Advance the projectile by 1 second
      p.advance(1.0);

      // Verify: Check updated position, velocity, and time
      const Projectile::PositionVelocityTime& updated = p.flightPath.back();

      assertEquals(updated.pos.getMetersX(), 100.0);       // X remains the same
      assertEquals(updated.pos.getMetersY(), 195.0968, 0.0001);  // Y falls due to gravity
      assertEquals(updated.v.getDX(), 0.0);                // No horizontal movement
      assertEquals(updated.v.getDY(), -9.806, 0.0001);     // Velocity affected by gravity
      assertEquals(updated.t, 101);                        // Time increments

   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling horizontally
    * input:   flightPath={pos=100,200 v=50,0 t=100}
    * output:  flightPath={}{pos.x=149.9756 = 100 + 50*1 + .5(-0.0487)*1*1
    *                        pos.y=195.0968 = 200 + 0*1  + .5(-9.8064)*1*1
    *                        v.dx =49.9513  = 50 + (-0.0487)*1
    *                        v.dy =-9.8064  = 0  + (-9.8064)*1
    *                        t=101}
    *********************************************/
   void advance_horizontal()
   {
      // Setup: Create a projectile with initial horizontal motion
      Projectile p;
      Projectile::PositionVelocityTime state;
      state.pos.setMeters(100, 200);  // Initial position (100,200)
      state.v.setDX(50);              // Initial velocity (50,0)
      state.v.setDY(0);
      state.t = 100;                  // Initial time
      p.flightPath.push_back(state);  // Add this state to flightPath

      // Exercise: Advance the projectile by 1 second
      p.advance(1.0);

      // Verify: Check updated position, velocity, and time
      const Projectile::PositionVelocityTime& updated = p.flightPath.back();

      assertEquals(updated.pos.getMetersX(), 149.9756, 0.0001);  // X moves due to velocity + drag
      assertEquals(updated.pos.getMetersY(), 195.0968, 0.0001);  // Y falls due to gravity
      assertEquals(updated.v.getDX(), 49.9513, 0.0001);          // Horizontal velocity affected by drag
      assertEquals(updated.v.getDY(), -9.8064, 0.0001);          // Vertical velocity affected by gravity
      assertEquals(updated.t, 101);                              // Time increments
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up, no horizontal position change
    * input:   flightPath={pos=100,200 v=0,100 t=100}
    * output:  flightPath={}{pos.x=100      = 0   + 0*1   + .5(0)*1*1
    *                        pos.y=294.9021 = 200 + 100*1 + .5(-9.8064-.3893)*1*1
    *                        v.dx =0        = 0   + 0*1
    *                        v.dy =89.8042  = 100 + (-9.8064-.3893)
    *                        t=101}
    *********************************************/
   void advance_up()
   {
      // Setup: Create a projectile with initial vertical motion
      Projectile p;
      Projectile::PositionVelocityTime state;
      state.pos.setMeters(100, 200);  // Initial position (100,200)
      state.v.setDX(0);               // No horizontal velocity
      state.v.setDY(100);             // Initial vertical velocity (100)
      state.t = 100;                  // Initial time
      p.flightPath.push_back(state);  // Add this state to flightPath

      // Exercise: Advance the projectile by 1 second
      p.advance(1.0);

      // Verify: Check updated position, velocity, and time
      const Projectile::PositionVelocityTime& updated = p.flightPath.back();

      assertEquals(updated.pos.getMetersX(), 100, 0.0001);      // X position remains unchanged
      assertEquals(updated.pos.getMetersY(), 294.9021, 0.0001); // Y moves up, slowed by gravity + drag
      assertEquals(updated.v.getDX(), 0, 0.0001);               // No horizontal velocity
      assertEquals(updated.v.getDY(), 89.8042, 0.0001);         // Vertical velocity decreases due to gravity & drag
      assertEquals(updated.t, 101);                             // Time increments
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up and across
    * input:   flightPath={pos=100,200 v=50,40 t=100}
    * output:  flightPath={}{pos.x=149.9600 = 100 + 50*1 + .5(-0.0799)*1*1
    *                        pos.y=235.0648 = 200 + 40*1 + .5(-9.8064-0.0638)*1*1
    *                        v.dx =49.9201  = 50 + (-.0799)*1
    *                        v.dy =30.1297  = 40 + (-9.8064-0.0638)*1
    *                        t=101}
    *********************************************/
   void advance_diagonalUp()
   {
      // Setup: Create a projectile with initial diagonal motion
      Projectile p;
      Projectile::PositionVelocityTime state;
      state.pos.setMeters(100, 200);  // Initial position (100,200)
      state.v.setDX(50);              // Initial horizontal velocity (50)
      state.v.setDY(40);              // Initial vertical velocity (40)
      state.t = 100;                  // Initial time
      p.flightPath.push_back(state);  // Add this state to flightPath

      // Exercise: Advance the projectile by 1 second
      p.advance(1.0);

      // Verify: Check updated position, velocity, and time
      const Projectile::PositionVelocityTime& updated = p.flightPath.back();

      assertEquals(updated.pos.getMetersX(), 149.9600, 0.0001);  // X position updates with velocity & drag
      assertEquals(updated.pos.getMetersY(), 235.0648, 0.0001);  // Y position updates with velocity, gravity & drag
      assertEquals(updated.v.getDX(), 49.9201, 0.0001);          // Horizontal velocity decreases slightly due to drag
      assertEquals(updated.v.getDY(), 30.1297, 0.0001);          // Vertical velocity decreases due to gravity & drag
      assertEquals(updated.t, 101);                              // Time increments
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling down and across
    * input:   flightPath={}{}{pos=100,200 v=50,-40 t=100}
    * output:  flightPath={}{}{}{pos.x=149.9201 = 100 + 50*1 + .5(-0.0799)*1*1
    *                            pos.y=155.1287 = 200 +-40*1 + .5(-9.8064+0.0638)*1*1
    *                            v.dx = 49.9201 =  50 + (-0.0799)*1
    *                            v.dy =-49.7425 = -40 + (-9.8064+0.0638)*1*1
    *                            t=101}
    *********************************************/
   void advance_diagonalDown()
   {
      // setup
      setupStandardFixture();
      Projectile p;
      Projectile::PositionVelocityTime pvt;

      // Add two dummy states
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);

      // Set initial state: position (100,200), velocity (50,-40), time 100
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = -40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);

      // exercise: advance the projectile (time now 101)
      p.advance(101.0);

      // verify: flightPath should now have 4 entries and the last entry is updated correctly
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());

      // Directly verify the last (updated) state without using an if statement
      assertEquals(p.flightPath.back().pos.x, 149.9601, 0.0001);   // 100 + 50*1 + 0.5*(-0.0799)*1*1
      assertEquals(p.flightPath.back().pos.y, 155.1287, 0.0001);   // 200 + (-40)*1 + 0.5*(-9.8064+0.0638)*1*1
      assertEquals(p.flightPath.back().v.dx, 49.9201, 0.0001);     // 50 + (-0.0799)*1
      assertEquals(p.flightPath.back().v.dy, -49.7425, 0.0001);    // -40 + (-9.8064+0.0638)*1
      assertEquals(p.flightPath.back().t, 101.0);                  // time is updated to 101

      // teardown
      teardownStandardFixture();
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
      p.metersFromPixels = 1.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }

};

