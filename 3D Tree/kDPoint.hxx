#include "kDPoint.h"
#include <cmath>

PUJ::kDPoint::kDPoint()
{

}

PUJ::kDPoint::kDPoint(double x, double y, double z)
{
	this->m_X = x;
	this->m_Y = y;
	this->m_Z = z;
}

const double PUJ::kDPoint::
getX() const
{
	return (this->m_X);
}

const double PUJ::kDPoint::
getY() const
{
	return (this->m_Y);
}

const double PUJ::kDPoint::
getZ()const
{
	return (this->m_Z);
}

bool PUJ::
orderbyX(kDPoint const& p1, kDPoint const& p2)
{
	return (p1.getX() < p2.getX());
}

bool PUJ::
orderbyY(kDPoint const& p1, kDPoint const& p2)
{
	return (p1.getY() < p2.getY());
}

bool PUJ::
orderbyZ(kDPoint const& p1, kDPoint const& p2)
{
	return (p1.getZ() < p2.getZ());
}

double PUJ::Distance(const PUJ::kDPoint& p1, const PUJ::kDPoint& p2)
{
	double distance = 0;
	distance = sqrt(pow((p2.getX()-p1.getX()),2)+pow((p2.getY()-p1.getY()),2)+pow((p2.getZ()-p1.getZ()),2));
	return distance;
}

const double PUJ::kDPoint::
getValue(unsigned int crit) const
{
	if(crit==0) return this->m_X;
	else if(crit==1) return this->m_Y;
	else if(crit==2) return this->m_Z;
}

