#include "static1.hpp"

void get_random_color (int& r, int& g, int& b)
{
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}
