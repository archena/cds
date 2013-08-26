/**
 * A simple command-line tool for coupled dynamical systems simulation
 * This program simulates a threshold-coupled lattice of chaotic logistic maps
 * As described by Sudeshna Sinha et al.
 *
 * See:
 *  Sinha and Biswas "Adaptive Dynamics on a Chaotic Lattice" Physical Review Letters vol 71 no 13 September 1993
 *  Sinha and Ditto "Computing with Distributed Chaos" Physical Review E vol 60 no 1, July 1999
 *
 * Author: Matt Squire
 * Date: Fri Dec 14, 2012  2:30 PM
 *
 * http://github.com/archena/CDS
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string.h>

#include "lattice.hh"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 4)
  {
    cout << "Usage: cds <size> <iterations> <threshold> [(csv|png)] [filename]. The final two arguments optionally and used to specify a file export format." << endl;
    exit(1);
  }

  unsigned size       = atoi(argv[1]);
  unsigned iterations = atoi(argv[2]);
  cell_t t            = atof(argv[3]);
  cell_t a            = 4;

  // Set up the lattice with update and coupling functions
  Lattice lattice(size,
                  [a](cell_t x) { return a * x * (1 - x); },
                  [t](cell_t& x1, cell_t& x2)
                  {
                    cell_t excess = x1 > t ? x1 - t : 0;
                    x1 -= excess;
                    x2 += excess;
                  });

  lattice.randomize(0, 1);

  if(argc == 5)
  {
    if(strncmp(argv[4], "csv", 3) == 0)
    {
      // const unsigned max_filename = 100;
      // char filename[max_filename + 1] = {0};
      // strncpy(filename, argv[5], max_filename);
      
      // Output as csv
      cell_t excess = 0;

      // Initial state followed by a number of updates
      for(int i = 0; i <= iterations; ++i)
      {
        for_each(lattice.begin(), lattice.end(),
                 [](cell_t x) { cout << x << ","; });

        cout << excess << endl;
        
        excess = lattice.update();
      }
    }
    else if(strncmp(argv[4], "png", 3) == 0)
    {
      // Write output as an image (time-space diagram)
      cout << "Image export not supported" << endl;
    }
  }
  else
  {
    // Print a textual summary to standard out
    cout << lattice
         << endl
         << endl;

    for(int i = 0; i < iterations; ++i)
    {
      cell_t excess = lattice.update();
      cout << lattice << " | " << excess << endl;
    }

    cout << endl
         << size       << " cells with "
         << iterations << " iterations and threshold " << t << endl;
  }
}
