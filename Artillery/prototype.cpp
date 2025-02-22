#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double INITIAL_SPEED = 827.0; // m/s
const double TIME_INCREMENT = 1.0; // seconds
const double ANGLE_DEGREES = 75.0;
const double PI = 3.14159265358979323846;

int main() {
   // Convert angle to radians
   double angle_radians = ANGLE_DEGREES * (PI / 180.0);

   // Compute initial velocity components
   double dx = INITIAL_SPEED * cos(angle_radians);
   double dy = INITIAL_SPEED * sin(angle_radians);

   // Initial position
   double x = 0.0;
   double y = 0.0;

   // Simulate 20 seconds of flight without acceleration, drag, or gravity
   for (int i = 0; i < 20; i++) {
      x += dx * TIME_INCREMENT;
      y += dy * TIME_INCREMENT;
   }

   // Output final results
   std::cout << "Distance: " << std::fixed << std::setprecision(2) << x << "m";
   std::cout << "   Altitude: " << y << "m" << std::endl;

   return 0;
}
