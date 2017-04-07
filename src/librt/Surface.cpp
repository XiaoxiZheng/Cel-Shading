//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Surface.cpp
// Base class for all Surfaces
//-------------------------------------------------------------------------------


#include "Surface.h"
#include <assert.h>
#include <stdio.h>
#include <string>


Surface::Surface() :m_name("surface"), m_a(0),m_b(0),m_c(0),m_center(0){

}

Surface::Surface(std::string name)
{
	m_name = name;
	m_a = 0;
	m_b = 0;
	m_c = 0;
	m_center = 0;
}


Surface::~Surface()
{

}

std::string Surface::getSurfaceNmae(){
	return m_name;
}

void Surface::setSurfaceNmae(std::string name){
	m_name = name;
}

// Returns the closest intersection point
int Surface::FindClosestIntersection(Intersection *pIntersection)
{

    return(0);
}

STVector3 Surface::GetPosition(){
	return m_center;
}

void Surface::draw(){

}