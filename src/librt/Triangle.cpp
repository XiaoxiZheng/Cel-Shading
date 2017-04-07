//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
// 
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"


// contructo
Triangle::Triangle():Surface(){

}
Triangle::Triangle(std::string name) : Surface(name){

}

Triangle::Triangle(std::string name,STVector3 a, STVector3 b, STVector3 c){
	m_name = name;
	m_a = a;
	m_b = b;
	m_c = c;
}

// clean up
Triangle::~Triangle()
{

}



//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    LinearSolver L;
    bool bFoundSolution = false;


    return(bFoundSolution);
}



//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;



    return(bFound);
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
	STVector3 p1 = m_b - m_a;

	STVector3 p2 = m_c - m_a;

	STVector3 normal = STVector3::Cross(p1, p2);

	normal.Normalize();

	return(normal);
}

void Triangle::draw(){
	
	STVector3 normal = ComputeNormalVector();
	glBegin(GL_TRIANGLES);
	glColor4f(0.5f, 0.5f, 0.5f, 1.f);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(m_a.x, m_a.y, m_a.z);
	glVertex3f(m_b.x, m_b.y, m_b.z);
	glVertex3f(m_c.x, m_c.y, m_c.z);
	glEnd();
}
