#ifndef __PUJ__kDPoint__h__
#define __PUJ__kDPoint__h__

namespace PUJ
{
	class kDPoint
	{
	public:
		typedef kDPoint Self;
	protected:
		double m_X;
		double m_Y;
		double m_Z;
	public:
		kDPoint();
		kDPoint(double x, double y, double z);
		const double getX() const;
		const double getY() const;
		const double getZ() const;
		const double getValue(unsigned int crit) const;

		
	};

	bool orderbyX(kDPoint const& p1, kDPoint const& p2);
	bool orderbyY(kDPoint const& p1, kDPoint const& p2);
	bool orderbyZ(kDPoint const& p1, kDPoint const& p2);

	double Distance(const kDPoint& p1, const kDPoint& p2);
}

#include "kDPoint.hxx"

#endif

