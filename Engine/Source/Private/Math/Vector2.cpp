#include"Math/Vector2.h"
#include"Debug.h"
#include <iostream>
using namespace std;
Vector2 Vector2::operator/(const Vector2& Other)
{

	Vector2 NewVector(NaN());

	if (Other.x == 0.0f) {
		EE_LOG("Vector2", "Cannot divide by zero, returning with NaN x.");
	}
	else {
		NewVector.x = x / Other.x;
	}
	if (Other.y == 0.0f) {
		EE_LOG("Vector2", "Cannot divide by zero, returning with NaN y.");
	}
	else {
		NewVector.y = y / Other.y;
	}


	return NewVector;
}
Vector2& Vector2::operator/=(const Vector2& Other)
{
	return *this = *this / Other;
}
Vector2 Vector2::operator/(const float& Scalar)
{
	if (Scalar == 0.0f) {
		EE_LOG("Vector2", "Cannot divide by zero, returnnig a NaN vector2.");

			return Vector2::NaN();
	}
	return Vector2(x / Scalar, y / Scalar);
}
Vector2& Vector2::operator/=(const float& Other)
{
	return *this = *this / Other;
}
Vector2 Vector2::NaN()
{


	return Vector2(std:: numeric_limits<float>::quiet_NaN());
	// TODO: insert return statement here
}

float Vector2::Length()
{
	return std::sqrtf(LengthSqd());
}

float Vector2::Distance(Vector2& V1, Vector2& V2)
{
	return sqrtf(DistSqd(V1, V2));
}

void Vector2::Log()
{
	EE_LOG("Vector2", x<<", "<<y);

}

void Vector2::LogLength()
{
	EE_LOG("Vector2", Length());

}
