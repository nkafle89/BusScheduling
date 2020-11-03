#pragma once
#include "Basic.h"
#include "ortools/linear_solver/linear_solver.h"

using namespace std;

namespace operations_research{
void BuildandSolveMIP() {
  // Create the linear solver with the SCIP backend.
  MPSolver solver("Problem", MPSolver::SCIP_MIXED_INTEGER_PROGRAMMING);

  // Create the variables

  MPVariable* const x = solver.MakeNumVar(0.0, 1, "x");
  MPVariable* const y = solver.MakeNumVar(0.0, 2, "y");

  cout << "Number of variables = " << solver.NumVariables();

  // Create a linear constraint, 0 <= x + y <= 2.
  MPConstraint* const ct = solver.MakeRowConstraint(0.0, 2.0, "ct");
  ct->SetCoefficient(x, 1);
  ct->SetCoefficient(y, 1);

  cout << "Number of constraints = " << solver.NumConstraints();

  // Create the objective function, 3 * x + y.
  MPObjective* const objective = solver.MutableObjective();
  objective->SetCoefficient(x, 3);
  objective->SetCoefficient(y, 1);
  objective->SetMaximization();

  solver.Solve();

  cout << "Solution:" << std::endl;
  cout << "Objective value = " << objective->Value();
  cout << "x = " << x->solution_value();
  cout << "y = " << y->solution_value();
}
}
