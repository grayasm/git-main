
#include "Rhino.hpp"
#include "strconv.hpp"



//////////////////////////////////////////////////////////////////////////
Pt3d::Pt3d()
{
	m_x=0.f;
	m_y=0.f;
	m_z=0.f;
};

Pt3d::Pt3d(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
};

Pt3d::Pt3d(const Pt3d& pt3d)
{
	*this = pt3d;	
};

Pt3d::~Pt3d()
{
};

Pt3d& Pt3d::operator=(const Pt3d& pt3d)
{
	if(this!=&pt3d)
	{
		m_x = pt3d.m_x;
		m_y = pt3d.m_y;
		m_z = pt3d.m_z;
	}
	return *this;
};


float& Pt3d::operator[](size_t pos)
{
	if(pos > 2)
		throw misc::exception("pt3d position is out of range");

	switch(pos)
	{
	case 0: return m_x;
	case 1: return m_y;
	case 2: return m_z;
	}

	throw misc::exception("pt3d position is out of range");
};


const float& Pt3d::operator[](size_t pos) const
{
	if(pos > 2)
		throw misc::exception("pt3d position is out of range");

	switch(pos)
	{
	case 0: return m_x;
	case 1: return m_y;
	case 2: return m_z;
	}	

	throw misc::exception("pt3d position is out of range");
};

//////////////////////////////////////////////////////////////////////////

Circle::Circle()
{
	m_p1 = Pt3d();
	m_p2 = Pt3d();
	m_p3 = Pt3d();
};

Circle::Circle(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3)
{
	m_p1 = p1;
	m_p2 = p2;
	m_p3 = p3;
};

Circle::Circle(const Circle& c)
{
	*this = c;
};

Circle::~Circle()
{
};

Circle& Circle::operator=(const Circle& c)
{
	if(this != &c)
	{
		m_p1 = c.m_p1;
		m_p2 = c.m_p2;
		m_p3 = c.m_p3;
	}
	return *this;
};



//////////////////////////////////////////////////////////////////////////

Rhino::Rhino()
{
};

Rhino::~Rhino()
{
};

void Rhino::Log(misc::ofstream& out, const misc::string& layer, const int clr[3], const std::vector<Pt3d>& array)
{

	//write layer info
	out << U(";") << layer << std::endl;
	out << U("-Layer n ") << layer << U(" Current ") << layer << U(" r ") << layer << U(" ") <<
		misc::from_value(clr[0]) << U(",") <<
		misc::from_value(clr[1]) << U(",") <<
		misc::from_value(clr[2]) << std::endl;
	out << U("_enter") << std::endl;

	//write points
	out << U("_Polyline") << std::endl;

	for(size_t i=0; i<array.size(); ++i)
	{
		LogPt3d(out, array[i]);
	}//for

	out << U("_enter") << std::endl;
	//done
};


void Rhino::Log(misc::ofstream& out, const misc::string& layer, const int clr[3], const std::vector<Circle>& array)
{
	//write layer info
	out << U(";") << layer << std::endl;
	out << U("-Layer n ") << layer << U(" Current ") << layer << U(" r ") << layer << U(" ") <<
		misc::from_value(clr[0]) << U(",") <<
		misc::from_value(clr[1]) << U(",") <<
		misc::from_value(clr[2]) << std::endl;
	out << U("_enter") << std::endl;

	//write _Circle(s)

	for(size_t i=0; i<array.size(); ++i)
	{
		LogCircle(out, array[i]);
	}//for
	
	//done
};


void Rhino::LogPt3d(misc::ofstream& out, const Pt3d& pt3d)
{
	out << 
		misc::from_value(pt3d[0], 3) <<
		U(",") <<
		misc::from_value(pt3d[1], 3) <<
		U(",") <<
		misc::from_value(pt3d[2], 3) <<
		std::endl;
};


void Rhino::LogCircle(misc::ofstream& out, const Circle& c)
{
	out << U("_Circle") << std::endl;
	out << U("_3Point") << std::endl;
	
	LogPt3d(out, c.m_p1);
	LogPt3d(out, c.m_p2);
	LogPt3d(out, c.m_p3);

	out << U("_enter") << std::endl;
	out << U("_enter") << std::endl;
};

//////////////////////////////////////////////////////////////////////////
