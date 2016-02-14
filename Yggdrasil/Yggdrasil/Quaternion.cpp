#include "Quaternion.hpp"

using namespace YG;
using namespace Math;

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(const Vector3& axis, float angle)
{
	fromAxisAngle(axis, angle);
}

Quaternion::Quaternion(const Quaternion& q)
{
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
	this->w = q.w;
}

Quaternion::~Quaternion()
{
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
	this->w = q.w;
	return *this;
}

float Quaternion::length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}
float Quaternion::distance(const Quaternion& q) const
{
	return q.length() - length();
}

Quaternion& Quaternion::normalize()
{
	float l = length();
	x = x / l;
	y = y / l;
	z = z / l;
	w = w / l;
	return *this;
}
Quaternion Quaternion::normalized() const
{
	Quaternion q(*this);
	float l = q.length();
	q.x = q.x / l;
	q.y = q.y / l;
	q.z = q.z / l;
	q.w = q.w / l;
	return q;
}

Quaternion& Quaternion::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
	return *this;
}

std::ostream& ::operator<<(std::ostream& out, const Quaternion& q)
{
	out << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
	return out;
}

Quaternion Quaternion::operator+(const Quaternion& q)
{
	Quaternion r(*this);
	r.operator+=(q);
	return r;
}
Quaternion& Quaternion::operator+=(const Quaternion& q)
{
	x = x + q.x;
	y = y + q.y;
	z = z + q.z;
	w = w + q.w;
	return *this;
}

Quaternion Quaternion::operator-(const Quaternion& q)
{
	Quaternion r(*this);
	r.operator-=(q);
	return r;
}
Quaternion& Quaternion::operator-=(const Quaternion& q)
{
	x = x - q.x;
	y = y - q.y;
	z = z - q.z;
	w = w - q.w;
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q)
{
	Quaternion r(*this);
	r.operator*=(q);
	return r;
}
Quaternion& Quaternion::operator*=(const Quaternion& q)
{
	x = x * q.w + y * q.z - z * q.y + w * q.x;
	y = -x * q.z + y * q.w + z * q.x + w * q.y;
	z = x * q.y - y * q.x + z * q.w + w * q.z;
	w = -x * q.x - y * q.y - z * q.z + w * q.w;
	return *this;
}

Quaternion Quaternion::operator*(const Vector3& v)
{
	Quaternion r(*this);
	r.operator*=(v);
	return r;
}
Quaternion& Quaternion::operator*=(const Vector3& v)
{
	Quaternion q(v.x, v.y, v.z, 0.0f);
	return q.operator*=(*this);
}

Quaternion Quaternion::operator-()
{
	Quaternion q(*this);
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	q.w = -q.w;
	return q;
}

bool Quaternion::operator==(const Quaternion& q)
{
	return ((x == q.x) && (y == q.y) && (z == q.z) && (w == q.w));
}
bool Quaternion::operator<(const Quaternion& q)
{
	return (length() < q.length());
}
bool Quaternion::operator!=(const Quaternion& q)
{
	return !operator==(q);
}
bool Quaternion::operator>(const Quaternion& q)
{
	return (!operator==(q) && !operator<(q));
}
bool Quaternion::operator<=(const Quaternion& q)
{
	return (operator<(q) || operator==(q));
}
bool Quaternion::operator>=(const Quaternion& q)
{
	return (operator>(q) || operator==(q));
}

Quaternion& Quaternion::fromAxisAngle(const Vector3& axis, float angle)
{
	this->w = cos(angle / 2.0f);
	this->x = sin(angle / 2.0f) * axis.x;
	this->y = sin(angle / 2.0f) * axis.y;
	this->z = sin(angle / 2.0f) * axis.z;
	return *this;
}

void Quaternion::setRotationMatrix(float *R)
{
	R[0] = 1.0f - 2.0f * (y * y) - 2.0f * (z * z);		R[4] = 2.0f * x * y - 2.0f * z * w;					R[8] = 2.0f * x * z + 2.0f * y * w;					R[12] = 0.0f;
	R[1] = 2.0f * x * y + 2.0f * z * w;					R[5] = 1.0f - 2.0f * (x * x) - 2.0f * (z * z);		R[9] = 2.0f * y * z - 2.0f * x * w;					R[13] = 0.0f;
	R[2] = 2.0f * x * z - 2.0f * y * w;					R[6] = 2.0f * y * z + 2.0f * x * w;					R[10] = 1.0f - 2.0f * (x * x) - 2.0f * (y * y);		R[14] = 0.0f;
	R[3] = 0.0f;										R[7] = 0.0f;										R[11] = 0.0f;										R[15] = 1.0f;
}