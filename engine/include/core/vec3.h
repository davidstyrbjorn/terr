#pragma once

#include<iostream>
#include<fstream>

namespace terr {

	class Vec3 {
	
	public:
		Vec3();
		Vec3(float x, float y, float z);
		Vec3(const Vec3& vec);

		float x, y, z;

		Vec3 Normal();

		float Dot(Vec3 other);
		float GetAngle(Vec3 other);

		float Magnitude();

		/*
		Vec3& operator+(const Vec3& other) {
			Vec3 pam(this->x + other.x, this->y + other.y, this->z + other.z);
			return pam;
		}
		*/

		/*
		friend Vec3 operator-(const Vec3 other) {
			return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);

		}

		friend Vec3 operator*(const float val) {
			return Vec3(this->x * val, this->y * val, this->z * val);

		}

		Vec3 operator/(const float val) {
			return Vec3(this->x / val, this->y / val, this->z / val);

		}
		*/

	};

	


}
