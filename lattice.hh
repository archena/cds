/**
 * A one-dimensional lattice of dynamical systems linked by a coupling function.
 */

#pragma once

#include <functional>
#include <ostream>
#include <vector>

// Type definition for a lattice cell
typedef float cell_t;

// Type definition for an update / state-transition function
typedef std::function<cell_t(cell_t x)> state_function;

// Type definition for a coupling function
typedef std::function<void(cell_t& x1, cell_t& x2)> coupling_function;

// Type definition for a cell_t vector iterator
typedef std::vector<cell_t>::iterator cell_v_iterator;

class Lattice
{
public:
  Lattice(unsigned size, state_function state_fn, coupling_function couple_fn);
  cell_v_iterator begin();
  cell_v_iterator end();
  void assign(size_t n, const cell_t& value);
  void assign(cell_v_iterator start, cell_v_iterator end);
  void randomize(cell_t min, cell_t max);
  cell_t update(unsigned n);
  cell_t update();
  void setMaxPrintedCells(unsigned n);
  friend std::ostream& operator<< (std::ostream& os, const Lattice& l);

private:
  std::vector<cell_t> state;
  state_function fn;
  coupling_function phi;
  unsigned max_printed_cells;
};
