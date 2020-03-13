#pragma once


#include "../include/core/vec3.h"
#include <cmath>

terr::Vec3::Vec3() : x(0), y(0), z(0)
{
}

terr::Vec3::Vec3(float x, float y, float z) 
{
	this->x = x;
	this->y = y;
	this->z = z;
}

terr::Vec3::Vec3(const Vec3& vec) 
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

terr::Vec3 terr::Vec3::Normal()
{
	float norm_val = Magnitude();
	
	return Vec3(this->x/norm_val, this->y / norm_val, this->z / norm_val);
}

float terr::Vec3::Dot(Vec3 other)
{
	float prod = this->x * other.x + this->y * other.y + this->z * other.z;

	return prod;
}

float terr::Vec3::GetAngle(Vec3 other)
{
	float norm_val_1 = this->Magnitude();
	float norm_val_2 = other.Magnitude();
	float dot_val = Dot(other);

	return acos(dot_val/(norm_val_1*norm_val_2));
}

float terr::Vec3::Magnitude()
{
	return std::sqrt(std::powf(this->x, 2) + std::powf(this->x, 2) + std::powf(this->x, 2));;
}