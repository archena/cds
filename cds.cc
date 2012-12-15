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

#include "lattice.hh"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 4)
  {
    cout << "Usage: cds <size> <iterations> <threshold>" << endl;
    exit(1);
  }

  unsigned size       = atoi(argv[1]);
  unsigned iterations = atoi(argv[2]);
  cell_t t            = atof(argv[3]);
  cell_t a            = 4;

  Lattice lattice(size,
                  [a](cell_t x) { return a * x * (1 - x); },
                  [t](cell_t& x1, cell_t& x2)
                  {
                    cell_t excess = x1 > t ? x1 - t : 0;
                    x1 -= excess;
                    x2 += excess;
                  });

  lattice.randomize(0, 1);
  //std::vector<cell_t> v = {0.1, 0.2, 0.3, 0.4, 0.5};
  //lattice.assign(v.begin(), v.end());

  cout << lattice
       << endl
       << endl;

  for(int i = 0; i < iterations; ++i)
  {
    cell_t excess = lattice.update();
    cout << lattice << " | " << excess << endl;
  }
}
