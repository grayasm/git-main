#ifndef __Rhino_hpp__
#define __Rhino_hpp__


#include <vector>
#include "exception.hpp"
#include "stream.hpp"



//////////////////////////////////////////////////////////////////////////
class Pt3d
{
public:
	Pt3d();
	Pt3d(float x, float y, float z);
	Pt3d(const Pt3d& pt3d);
	~Pt3d();
	Pt3d& operator=(const Pt3d& pt3d);

	float& operator[](size_t pos);
	const float& operator[](size_t pos) const;
	
	float m_x;
	float m_y;
	float m_z;
};
//////////////////////////////////////////////////////////////////////////
class Circle
{
public:
	Circle();
	Circle(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3);
	Circle(const Circle& c);
	~Circle();
	Circle& operator=(const Circle& c);

	
	Pt3d m_p1;
	Pt3d m_p2;
	Pt3d m_p3;
};

//////////////////////////////////////////////////////////////////////////
class Rhino
{
public:
	Rhino();
	~Rhino();
	void Log(misc::ofstream& out, const misc::string& layer, const int clr[3], const std::vector<Pt3d>& array);
	void Log(misc::ofstream& out, const misc::string& layer, const int clr[3], const std::vector<Circle>& array);
	
private:
	void LogPt3d(misc::ofstream& out, const Pt3d& pt3d);
	void LogCircle(misc::ofstream& out, const Circle& c);

private:
	Rhino(const Rhino&);
	Rhino& operator=(const Rhino&);
};
//////////////////////////////////////////////////////////////////////////


#endif//__Rhino_hpp__


