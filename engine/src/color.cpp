#include"../include/core/color.h"

terr::Color::Color() : r(0), g(0), b(0), a(0)
{
}

terr::Color::Color(float red, float green, float blue) : r(red), g(green), b(blue), a(1)
{
}

terr::Color::Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha)
{
}

terr::Color terr::Color::Red()
{
	return Color(1, 0, 0, 1);
}

terr::Color terr::Color::Green()
{
	return Color(0, 1, 0, 1);
}

terr::Color terr::Color::Blue()
{
	return Color(0, 0, 1, 1);
}

terr::Color terr::Color::GetRandomColor()
{
	return Color(((float)rand()) / (float)RAND_MAX, ((float)rand()) / (float)RAND_MAX, ((float)rand()) / (float)RAND_MAX);
}

terr::Color terr::Color::Mix(Color c, float bias)
{
	float newR, newG, newB, newA;
	
	newR = bias * this->r + (1 - bias) * c.r;
	newG = bias * this->g + (1 - bias) * c.g;
	newB = bias * this->b + (1 - bias) * c.b;
	newA = bias * this->a + (1 - bias) * c.a;

	return Color(newR, newG, newB, newA);
}

