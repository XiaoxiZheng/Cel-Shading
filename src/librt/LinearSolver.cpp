//------------------------------------------------------------------------------------------------
// Solves for u, v, and w in a set of linear equations
//       Du + Ev + Fw + G = 0
//       Hu + Iv + Jw + K = 0
//       Lu + Mv + Nw + P = 0
//
// Linear Solver.cpp
//------------------------------------------------------------------------------------------------

#include "LinearSolver.h"


const double Tol = 1.0e-8;



LinearSolver::LinearSolver(void)
{

}


LinearSolver::~LinearSolver()
{

}


//----------------------------------------------------------------------
// Returns true if finds the solution, u, v, and w for a set of linear 
// equations:
//----------------------------------------------------------------------
bool LinearSolver::Run( double D, double E, double F, double G,
                        double H, double I, double J, double K,
                        double L, double M, double N, double P,
                        double &u, double &v, double &w)
{
    if (fabs(F) >= Tol){

        double b = E*J - F*I;
        if (fabs(b) >= Tol) {

            double a = D*J - F*H;
            double d = H*N - J*L;
            double e = I*N - J*M;

            double normVal = a*e - b*d;

            if (fabs(normVal) >= Tol) {
                const double c = G*J - F*K;
                const double f = K*N - J*P;

                u = (b*f - e*c) / normVal;
                v = -(a*u + c) / b;
                w = -(D*u + E*v + G) / F;

                // found solution
                return true;      
            }
        }
    }

    return (false); 
}
