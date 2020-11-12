#pragma once
#include "Basic.h"
#include "ortools/linear_solver/linear_solver.h"

using namespace std;


void ColumnGeneration();

/*
namespace operations_research{

void BuildandSolveMIP() {
  // Create the linear solver with the SCIP backend.
  MPSolver solver("Problem", MPSolver::CLP_LINEAR_PROGRAMMING);

  MPSolverParameters params;
  MPSolverParameters::IntegerParam parms = MPSolverParameters::IntegerParam::LP_ALGORITHM;
  params.SetIntegerParam(parms, MPSolverParameters::LpAlgorithmValues::PRIMAL);
	  //SetIntegerParam(MPSolverParameters::IntegerParam param, int value)
  // Create the variables

  MPVariable* const x1 = solver.MakeNumVar(0.0, 1, "x1");
  MPVariable* const x2 = solver.MakeNumVar(0.0, 1, "x2");
  MPVariable* const x3 = solver.MakeNumVar(0.0, 1, "x3");
  //MPVariable* const x4 = solver.MakeNumVar(0.0, 1, "x4");

  cout << "Number of variables = " << solver.NumVariables()<< std::endl;

  // Create a linear constraint, 0 <= x + y <= 2.
  LinearExpr exp = x1;
  MPConstraint* const rt1 = solver.MakeRowConstraint(exp<=1.0, "Rt1");
  LinearExpr exp2=x2;
  MPConstraint* const rt2 = solver.MakeRowConstraint(exp2<=1.0, "Rt2");
  LinearExpr exp3 =x3;
  MPConstraint* const rt3 = solver.MakeRowConstraint(exp3<=1.0, "Rt3");
  LinearExpr cap;
  cap += x1;
  cap += x2;
  cap += x3;
  MPConstraint* const rt4 = solver.MakeRowConstraint(cap<= 1.0, "Rt4");


  rt1->SetCoefficient(x1, 1);
  //rt1->SetCoefficient(x4, 1);
  rt2->SetCoefficient(x2, 1);
  //rt2->SetCoefficient(x4, 1);
  rt3->SetCoefficient(x3, 1);

  rt4->SetCoefficient(x1, 1);
  rt4->SetCoefficient(x2, 1);
  rt4->SetCoefficient(x3, 1);
  //rt4->SetCoefficient(x4, 1);



  cout << "Number of constraints = " << solver.NumConstraints()<< std::endl;

  // Create the objective function, 3 * x + y.
  MPObjective* const objective = solver.MutableObjective();
  objective->SetCoefficient(x1, 2);
  objective->SetCoefficient(x2, 2.8);
  objective->SetCoefficient(x3, 2);
  //objective->SetCoefficient(x4, 3.4);
  objective->SetMaximization();

  //MPSolverParameters
  solver.Solve(params);

  cout << "Solution:" << std::endl;
  cout << "Objective value = " << objective->Value()<< std::endl;
  cout << "x1 = " << x1->solution_value()<< std::endl;
  cout << "x2 = " << x2->solution_value()<< std::endl;
  cout << "x3 = " << x3->solution_value()<< std::endl;
  //cout << "x4 = " << x4->solution_value()<< std::endl;

  cout << "Dual rt1 = " << rt1->dual_value()<< std::endl;
  cout << "Dual rt2 = " << rt2->dual_value()<< std::endl;;
  cout << "Dual rt3 = " << rt3->dual_value()<< std::endl;;
  cout << "Dual cap = " << rt4->dual_value()<< std::endl;;

  cout << "RV x1 = " << x1->reduced_cost()<< std::endl;
  cout << "RV x2 = " << x2->reduced_cost()<< std::endl;
  cout << "RV x3 = " << x3->reduced_cost()<< std::endl;
  //cout << "RV x4 = " << x4->reduced_cost()<< std::endl;

  string lpfile;
  solver.ExportModelAsLpFormat(false, &lpfile);

  cout<< lpfile <<endl;
}
}
*/
