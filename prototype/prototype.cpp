/*********************************************
* Lab 07 : Artillery Prototype
* Created by Noah McSheehy, and Diego Estrada
**********************************************/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

// Constants
const double INITIAL_SPEED = 827.0;       // m/s
const double TIME_INCREMENT = 0.01;       // seconds
const double GRAVITY = -9.8;              // at sea level
const double PI = 3.14159265358979323846; 
const double MASS = 46.7;                 // kg

// Drag constants
const double DIAMETER = 0.15489;          // m
const double RADIUS = DIAMETER / 2.0;     // m
const double AREA = PI * RADIUS * RADIUS; // m^2

// Helper function to convert degrees to radians
double degreesToRadians(double degrees) 
{
   return degrees * (PI / 180.0);
}

// Linear interpolation function
double linearInterpolation(double value, double d0, double d1, double r0, double r1) 
{
   return r0 + (r1 - r0) * ((value - d0) / (d1 - d0));
}

// Table-based function for calculating gravity, speed of sound, density, and drag
double calculateFromTable(double altitude, const vector<pair<double, double>>& table) 
{
   for (size_t i = 0; i < table.size() - 1; ++i) 
   {
      if (altitude >= table[i].first && altitude <= table[i + 1].first) 
      {
         return linearInterpolation(altitude, table[i].first, table[i + 1].first,
            table[i].second, table[i + 1].second);
      }
   }
   return -1;  // Return -1 if no valid range is found
}

// Function to calculate gravity based on altitude
double calculateGravity(double altitude) 
{
   const vector<pair<double, double>> gravityTable = 
   {
       {0, 9.807},      {1000, 9.804},    {2000, 9.801},    {3000, 9.797},    {4000, 9.794},
       {5000, 9.791},   {6000, 9.788},    {7000, 9.785},    {8000, 9.782},    {9000, 9.779},
       {10000, 9.776},  {15000, 9.761},   {20000, 9.745},   {25000, 9.730},   {30000, 9.715},
       {40000, 9.684},  {50000, 9.654},   {60000, 9.624},   {70000, 9.594},   {80000, 9.564}
   };
   return -calculateFromTable(altitude, gravityTable);  // Return a negative gravity value for downward direction
}

// Function to calculate speed of sound based on altitude
double calculateSpeedOfSound(double altitude) 
{
   const vector<pair<double, double>> speedOfSoundTable = 
   {
       {0, 340},     {1000, 336},   {2000, 332},   {3000, 328},   {4000, 324},   {5000, 320},
       {6000, 316},  {7000, 312},   {8000, 308},   {9000, 303},   {10000, 299},  {15000, 295},
       {20000, 295}, {25000, 295},  {30000, 305},  {40000, 324},  {50000, 337},  {60000, 319},
       {70000, 289}, {80000, 269}
   };
   return calculateFromTable(altitude, speedOfSoundTable);
}

// Function to calculate air density based on altitude
double calculateDensity(double altitude) 
{
   const vector<pair<double, double>> densityTable = 
   {
       {0, 1.225},         {1000, 1.112},       {2000, 1.007},       {3000, 0.9093},      {4000, 0.8194},
       {5000, 0.7364},     {6000, 0.6601},      {7000, 0.59},        {8000, 0.5258},      {9000, 0.4671},
       {10000, 0.4135},    {15000, 0.1948},     {20000, 0.08891},    {25000, 0.04008},    {30000, 0.01841},
       {40000, 0.003996},  {50000, 0.001027},   {60000, 0.0003097},  {70000, 0.0000828},  {80000, 0.0000185}
   };
   return calculateFromTable(altitude, densityTable);
}

// Function to calculate drag coefficient based on Mach number
double calculateDrag(double mach) 
{
   const vector<pair<double, double>> dragTable = 
   {
       {0.300, 0.1629}, {0.500, 0.1659}, {0.700, 0.2031}, {0.890, 0.2597}, {0.920, 0.3010},
       {0.960, 0.3287}, {0.980, 0.4002}, {1.000, 0.4258}, {1.020, 0.4335}, {1.060, 0.4483},
       {1.240, 0.4064}, {1.530, 0.3663}, {1.990, 0.2897}, {2.870, 0.2297}, {2.890, 0.2306},
       {5.000, 0.2656}
   };
   return calculateFromTable(mach, dragTable);
}

/***************************** 
* Main Simulator Prototype 
* houses the main logic 
******************************/

int main() 
{
   double angle_degrees;
   double angle_radians;
   double time_units = 0;

   double x = 0, dx = 0, ddx = 0;
   double y = 0, dy = 0, ddy = 0;

   double gravity = 0;
   double last_y  = 0, last_time = 0;

   // Prompt for user angle
   cout << "What is the angle of the howitzer where 0 is up? ";
   cin >> angle_degrees;

   // Adjust angle so 0 is up and flip the angle
   angle_degrees = 90 - angle_degrees;
   angle_radians = degreesToRadians(angle_degrees);

   // Initial velocity components
   dy = INITIAL_SPEED * sin(angle_radians);  // Vertical
   dx = INITIAL_SPEED * cos(angle_radians);  // Horizontal

   // Simulate projectile motion
   while (y >= 0) 
   {
      // Calculate drag_force
      double velocity        = sqrt(dx * dx + dy * dy);  // Calculate velocity
      double speedOfSound    = calculateSpeedOfSound(y);
      double mach            = velocity / speedOfSound;
      double dragCoefficient = calculateDrag(mach);
      double airDensity      = calculateDensity(y);
      double drag_force      = 0.5 * dragCoefficient * airDensity * velocity * velocity * AREA;

      // Calculate drag acceleration and direction
      double drag_acceleration = drag_force / MASS;
      double drag_angle        = atan2(dy, dx);
      ddx = -drag_acceleration * cos(drag_angle);
      ddy = -drag_acceleration * sin(drag_angle);

      // Find and update positions and velocities
      gravity   = calculateGravity(y);
      x        += dx * TIME_INCREMENT;
      y        += dy * TIME_INCREMENT;
      dy       += (gravity + ddy) * TIME_INCREMENT;
      dx       += ddx * TIME_INCREMENT;

      // Store last positive y value and time
      if (y >= 0) 
      {
         last_y = y;
         last_time = time_units;
      }

      // Increment time
      time_units += TIME_INCREMENT;
   }

   // Linear interpolation to find impact time and distance
   double impact_time     = last_time + (0 - last_y) / (y - last_y) * (time_units - last_time);
   double impact_distance = x + (impact_time - time_units) * dx;

   // Output results
   cout << fixed         << setprecision(1);
   cout << "Distance: "  << impact_distance << "m  ";
   cout << "Hang Time: " << impact_time     << "s  ";
   cout << endl << endl;

   return 0;
}
