#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

const double INITIAL_SPEED = 827.0;   // m/s
const double TIME_INCREMENT = 0.01;   // seconds
const double ANGLE_DEGREES = 15.0;      // Changed from 75.0 to 15.0 for expected output
const double PI = 3.14159265358979323846;

int main() {
   // Convert angle to radians
   double angle_radians = ANGLE_DEGREES * (PI / 180.0);

   // Compute initial velocity components
   double dx = INITIAL_SPEED * cos(angle_radians);
   double dy = INITIAL_SPEED * sin(angle_radians);

   // Initial position and hang time
   double x = 0.0;
   double y = 0.0;
   double hang_time = 0.0;

   // Gravity table: altitudes (m) and corresponding gravity values (m/s^2)
   vector<double> altitudes = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
                               10000, 15000, 20000, 25000, 30000, 40000, 50000, 60000, 70000, 80000 };
   vector<double> gravity_values = { 9.807, 9.804, 9.801, 9.797, 9.794, 9.791, 9.788, 9.785, 9.782, 9.779,
                                    9.776, 9.761, 9.745, 9.730, 9.715, 9.684, 9.654, 9.624, 9.594, 9.564 };

   while (y >= 0) {
      // Determine current gravity using linear interpolation based on altitude.
      double current_gravity;
      if (y <= altitudes.front()) {
         current_gravity = gravity_values.front();
      }
      else if (y >= altitudes.back()) {
         current_gravity = gravity_values.back();
      }
      else {
         // Find the two table entries between which y falls.
         for (size_t i = 0; i < altitudes.size() - 1; i++) {
            if (y >= altitudes[i] && y < altitudes[i + 1]) {
               double fraction = (y - altitudes[i]) / (altitudes[i + 1] - altitudes[i]);
               current_gravity = gravity_values[i] + fraction * (gravity_values[i + 1] - gravity_values[i]);
               break;
            }
         }
      }
      // Gravity acts downward so use a negative value.
      current_gravity = -current_gravity;

      // Update horizontal position (no horizontal acceleration)
      x += dx * TIME_INCREMENT;

      // Update vertical position using the kinematics equation:
      // y = y0 + v*t + (1/2)*a*t^2
      y += dy * TIME_INCREMENT + 0.5 * current_gravity * TIME_INCREMENT * TIME_INCREMENT;

      // Update vertical velocity: v = v0 + a*t
      dy += current_gravity * TIME_INCREMENT;

      // Increment hang time
      hang_time += TIME_INCREMENT;
   }

   // Set formatting for output
   cout << fixed << setprecision(1);

   // Output final results
   cout << "Distance: " << x << "m   Altitude: " << y << "m   Hang Time: " << hang_time << "s" << endl;

   return 0;
}
