/********************/
/**    関根 明良   **/
/** ベクトルクラス **/
/********************/

#include "MuscleBreakMath.hpp"

const Vector2 Vector2::zero(0.0, 0.0);

Vector2::Vector2()
{
	x = 0.0;
	y = 0.0;

	magnitude = 0.0;
}

Vector2::Vector2(double _x, double _y)
{
	x = _x;
	y = _y;

	Recalc();
}

const char * Vector2::ToString(void)
{
	char str[256];

	sprintfDx(str, "x : %lf\ty : %lf", x, y);

	return str;
}

double Vector2::Distance(Vector2 _pos)
{
	double ret;

	Vector2 tmp(_pos.x - x, _pos.y - y);

	ret = sqrt(pow(tmp.x, 2.0) + pow(tmp.y, 2.0));

	return ret;
}

double Vector2::Distance(int _x, int _y)
{
	double ret;

	Vector2 tmp(_x - x, _y - y);

	ret = sqrt(pow(tmp.x, 2.0) + pow(tmp.y, 2.0));

	return ret;
}

double Vector2::Distance(Vector2 _pos1, Vector2 _pos2)
{
	double ret;

	Vector2 tmp = _pos2 - _pos1;

	ret = sqrt(pow(tmp.x, 2.0) + pow(tmp.y, 2.0));

	return ret;
}

double Vector2::Distance(int _x, int _y, Vector2 _pos)
{
	double ret;

	Vector2 _pos1(_x, _y);
	Vector2 tmp = _pos - _pos1;

	ret = sqrt(pow(tmp.x, 2.0) + pow(tmp.y, 2.0));

	return ret;
}

double Vector2::Distance(int _x1, int _y1, int _x2, int _y2)
{
	double ret;

	Vector2 tmp(_x2 - _x1, _y2 - _y1);

	ret = sqrt(pow(tmp.x, 2.0) + pow(tmp.y, 2.0));

	return ret;
}

double Vector2::Angle(Vector2 _pos)
{
	double angle;

	angle = atan2(_pos.y - y, _pos.x - x);

	return angle;
}

double Vector2::Angle(int _x, int _y)
{
	double angle;

	angle = atan2(_y - y, _x - x);

	return angle;
}

double Vector2::Angle(Vector2 _pos1, Vector2 _pos2)
{
	double angle;

	angle = atan2(_pos2.y - _pos1.y, _pos2.x - _pos1.x);

	return angle;
}

double Vector2::Angle(int _x, int _y, Vector2 _pos)
{
	double angle;

	angle = atan2(_pos.y - _y, _pos.x - _x);

	return angle;
}

double Vector2::Angle(int _x1, int _y1, int _x2, int _y2)
{
	double angle;

	angle = atan2(_y2 - _y1, _x2 - _x1);

	return angle;
}

Vector2 Vector2::Normalize(void)
{
	Vector2 normalize(x, y);
	double mag = 1 / magnitude;

	normalize *= Vector2(mag, mag);

	return normalize;
}

Vector2 Vector2::Normalize(Vector2 _value)
{
	double mag;

	mag = 1 / Distance(_value, zero);

	_value *= Vector2(mag, mag);

	return _value;
}

Vector2 Vector2::Normalize(int _x, int _y)
{
	Vector2 normalize(_x, _y);
	double mag = 1 / Distance(normalize, zero);

	normalize *= Vector2(mag, mag);

	return normalize;
}

const Vector2 Vector2::operator-() const
{
	Vector2 tmp;

	tmp.x = -x;
	tmp.y = -y;

	return tmp;
}

const Vector2 Vector2::operator + (const Vector2 & vec) const
{
	Vector2 tmp;

	tmp.x = x + vec.x;
	tmp.y = y + vec.y;

	return tmp;
}

const Vector2 Vector2::operator - (const Vector2 & vec) const
{
	Vector2 tmp;

	tmp.x = x - vec.x;
	tmp.y = y - vec.y;

	return tmp;
}

const Vector2 Vector2::operator * (const Vector2 & vec) const
{
	Vector2 tmp;

	tmp.x = x * vec.x;
	tmp.y = y * vec.y;

	return tmp;
}

const Vector2 Vector2::operator / (const Vector2 & vec) const
{
	Vector2 tmp;

	tmp.x = x / vec.x;
	tmp.y = y / vec.y;

	return tmp;
}

const Vector2 Vector2::operator + (const int & vec) const
{
	Vector2 tmp;

	tmp.x = x + vec;
	tmp.y = y + vec;

	return tmp;
}

const Vector2 Vector2::operator + (const double & vec) const
{
	Vector2 tmp;

	tmp.x = x + vec;
	tmp.y = y + vec;

	return tmp;
}

const Vector2 Vector2::operator - (const int & vec) const
{
	Vector2 tmp;

	tmp.x = x - vec;
	tmp.y = y - vec;

	return tmp;
}

const Vector2 Vector2::operator - (const double & vec) const
{
	Vector2 tmp;

	tmp.x = x - vec;
	tmp.y = y - vec;

	return tmp;
}

const Vector2 Vector2::operator * (const int & vec) const
{
	Vector2 tmp;

	tmp.x = x * vec;
	tmp.y = y * vec;

	return tmp;
}

const Vector2 Vector2::operator * (const double & vec) const
{
	Vector2 tmp;

	tmp.x = x * vec;
	tmp.y = y * vec;

	return tmp;
}

const Vector2 Vector2::operator / (const int & vec) const
{
	Vector2 tmp;

	tmp.x = x / vec;
	tmp.y = y / vec;

	return tmp;
}

const Vector2 Vector2::operator / (const double & vec) const
{
	Vector2 tmp;

	tmp.x = x / vec;
	tmp.y = y / vec;

	return tmp;
}

bool Vector2::operator == (const Vector2 & vec) const
{
	bool ret = false;

	if (x == vec.x && y == vec.y)
		ret = true;

	return ret;
}

bool Vector2::operator != (const Vector2 & vec) const
{
	bool ret = false;

	if (x != vec.x || y != vec.y)
		ret = true;

	return ret;
}