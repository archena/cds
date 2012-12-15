/**
 * A one-dimensional lattice of dynamical systems linked by a coupling function.
 */

#include "lattice.hh"

#include <vector>
#include <algorithm>
#include <functional>
#include <ostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <limits.h>

/**
 * Constructor
 */
Lattice::Lattice(unsigned size, state_function state_fn, coupling_function couple_fn)
  : fn(state_fn),
    phi(couple_fn)
{
  state.assign(size, 0);
}

/**
 * Fill the lattice states with random values
 */
void Lattice::randomize(cell_t min, cell_t max)
{
  srand(time(NULL));
  for(cell_t& x : state)
  {
    x = min + (static_cast<cell_t>(random()) / INT_MAX) * (max - min);
  }
}

/**
 * Assign a fixed value to the internal state vector
 */
void Lattice::assign(size_t n, const cell_t& value)
{
  state.assign(n, value);
}

/**
 * Assign a vector of values to the internal state vector
 */
void Lattice::assign(cell_v_iterator start, cell_v_iterator end)
{
  state.assign(start, end);
}

/**
 * Update the lattice state.
 *
 * This first applies the state transition function to all cells in the lattice
 * And then applies the coupling function to every pair (overlapping),
 * working from left to right.
 *
 * Returns the result of the coupling function at the last (rightmost) cell.
 */
cell_t Lattice::update()
{
  // Dynamical update
  for(cell_t& x : state)
  {
    x = fn(x);
  }

  // Coupling function
  cell_t sink = 0;
  for(unsigned a = 0; a < state.size(); ++a)
  {
    // Call the coupling function with this pair of cells
    // If there is no suitable cell to the right of 'a',
    // the special 'sink' cell is provided instead.
    phi(state[a], a + 1 < state.size() ? state[a+1] : sink);
  }

  return sink;
}

/**
 * Output the lattice state to a stream.
 * This may be used in conjunction with cout.
 */
std::ostream& operator<< (std::ostream& os, const Lattice& l)
{
  auto iter = l.state.begin();
  auto end  = l.state.end();

  os << std::setprecision(3);

  while(iter != end)
  {
    os << *iter << "\t" << " ";
    ++iter;
  }

  return os;
}
