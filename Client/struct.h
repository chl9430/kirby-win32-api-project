#pragma once

struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y); // iostream을 포함 시키니 float값용 sqrt함수가 불러졌다.
	}

	void operator+=(Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2& operator=(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;

		return *this;
	}

	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x{ _x }
		, y{ _y }
	{}

	Vec2(int _x, int _y)
		: x{ (float)_x }
		, y{ (float)_y }
	{}

	Vec2(const POINT& _pt)
		: x{ (float)_pt.x }
		, y{ (float)_pt.y }
	{}
};