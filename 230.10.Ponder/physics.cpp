/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/
  
 #include "physics.h"  // for the prototypes
 

 /*********************************************************
 * calculateFromTable
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
 // Table-based function for calculating gravity, speed of sound, density, and drag
/*double calculateFromTable(double altitude, const vector<pair<double, double>>& table)
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


 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   // Edge cases: If the domain is outside the range of the provided mappings, return the boundary values.
   if (domain <= mapping[0].domain)
   {
      return mapping[0].range;
   }
   if (domain >= mapping[numMapping - 1].domain)
   {
      return mapping[numMapping - 1].range;
   }

   // Find the two mappings to interpolate between
   for (int i = 0; i < numMapping - 1; ++i)
   {
      if (domain >= mapping[i].domain && domain <= mapping[i + 1].domain)
      {
         double d0 = mapping[i].domain;
         double r0 = mapping[i].range;
         double d1 = mapping[i + 1].domain;
         double r1 = mapping[i + 1].range;

         // Perform linear interpolation
         return linearInterpolation(d0, r0, d1, r1, domain);
      }
   }

   // If no match is found (shouldn't happen if data is valid), return a default value
   return -999.999;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   return -99.9;
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   return -99.9;
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   return -99.9;
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   return -99.9;
}

