/*

	Copyright 2014 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

float RandomFloat() {
	float Max = RAND_MAX;
	return ((float) random() / Max);
}

struct Vector2i {
	int x;
	int y;
};

struct Vector2f {
	float x;
	float y;

	Vector2f() {
	}

	Vector2f(float _x, float _y) {
		x = _x;
		y = _y;
	}
};

struct Vector3f {
	float x;
	float y;
	float z;

	Vector3f() {
	}

	Vector3f(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f(float f) {
		x = y = z = f;
	}

	Vector3f& operator+=(const Vector3f& r) {
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3f& operator*=(float f) {
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	operator const float*() const {
		return &(x);
	}

	Vector3f Cross(const Vector3f& v) const {
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	Vector3f & Normalize() {
		const float Length = sqrtf(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	float dist(const Vector3f& other){
		float diffX = x - other.x;
		float diffY = y - other.y;
		float diffZ = z - other.z;
		float Length = sqrtf(diffX * diffX + diffY * diffY + diffZ * diffZ);
		return Length;	
	}

	float length(){
		float Length = sqrtf(x * x + y * y + z * z);
		return Length;	
	}

	void Print() const {
		printf("(%.02f, %.02f, %.02f)", x, y, z);
	}
};

struct Vector4f {
	float x;
	float y;
	float z;
	float w;

	Vector4f() {
	}

	Vector4f(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Print() const {
		printf("(%.02f, %.02f, %.02f, %.02f)", x, y, z, w);
	}
};

inline Vector3f operator+(const Vector3f& l, const Vector3f& r) {
	Vector3f Ret(l.x + r.x,
		l.y + r.y,
		l.z + r.z);

	return Ret;
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r) {
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f) {
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}

struct PersProjInfo {
	float FOV;
	float Width;
	float Height;
	float zNear;
	float zFar;

	PersProjInfo() {
	}

	PersProjInfo(float _FOV, float _Width, float _Height, float _zNear, float _zFar) {
		FOV = _FOV;
		Width = _Width;
		Height = _Height;
		zNear = _zNear;
		zFar = _zFar;
	}
};

class Matrix4f {
public:
	float m[4][4];

	Matrix4f() {
	}

	Matrix4f(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33) {
		m[0][0] = a00;
		m[0][1] = a01;
		m[0][2] = a02;
		m[0][3] = a03;
		m[1][0] = a10;
		m[1][1] = a11;
		m[1][2] = a12;
		m[1][3] = a13;
		m[2][0] = a20;
		m[2][1] = a21;
		m[2][2] = a22;
		m[2][3] = a23;
		m[3][0] = a30;
		m[3][1] = a31;
		m[3][2] = a32;
		m[3][3] = a33;
	}

	void SetZero() {
		memset(m, 0, sizeof(m));
	}

	Matrix4f Transpose() const {
		Matrix4f n;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				n.m[i][j] = m[j][i];
			}
		}

		return n;
	}

	inline void InitIdentity() {
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	inline Matrix4f operator*(const Matrix4f& Right) const {
		Matrix4f Ret;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				Ret.m[i][j] = m[i][0] * Right.m[0][j] +
					m[i][1] * Right.m[1][j] +
					m[i][2] * Right.m[2][j] +
					m[i][3] * Right.m[3][j];
			}
		}

		return Ret;
	}

	Vector4f operator*(const Vector4f& v) const {
		Vector4f r;

		r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
		r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
		r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
		r.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

		return r;
	}

	operator const float*() const {
		return &(m[0][0]);
	}

	void Print() const {
		for (int i = 0; i < 4; i++) {
			printf("%6.2f %6.2f %6.2f %6.2f\n", m[i][0], m[i][1], m[i][2], m[i][3]);
		}
	}

	float Determinant() const {
		return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3]
			+ m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3]
			- m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2]
			+ m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1]
			+ m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1]
			- m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
	}

	Matrix4f& Inverse() {
		// Compute the reciprocal determinant
		float det = Determinant();
		if (det == 0.0f) {
			// Matrix not invertible. Setting all elements to nan is not really
			// correct in a mathematical sense but it is easy to debug for the
			// programmer.
			/*const float nan = std::numeric_limits<float>::quiet_NaN();
			 *this = Matrix4f(
				nan,nan,nan,nan,
				nan,nan,nan,nan,
				nan,nan,nan,nan,
				nan,nan,nan,nan);*/
			//assert(0);
			return *this;
		}

		float invdet = 1.0f / det;

		Matrix4f res;
		res.m[0][0] = invdet * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
		res.m[0][2] = invdet * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
		res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
		res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][1] = invdet * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
		res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
		res.m[1][3] = invdet * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
		res.m[2][0] = invdet * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[2][2] = invdet * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][1] = invdet * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
		res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
		res.m[3][3] = invdet * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
		*this = res;

		return *this;
	}

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ) {
		m[0][0] = ScaleX;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][0] = 0.0f;
		m[1][1] = ScaleY;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = ScaleZ;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitRotateTransform(float RotateX, float RotateY, float RotateZ) {
		Matrix4f rx, ry, rz;

		const float x = ToRadian(RotateX);
		const float y = ToRadian(RotateY);
		const float z = ToRadian(RotateZ);

		rx.m[0][0] = 1.0f;
		rx.m[0][1] = 0.0f;
		rx.m[0][2] = 0.0f;
		rx.m[0][3] = 0.0f;
		rx.m[1][0] = 0.0f;
		rx.m[1][1] = cosf(x);
		rx.m[1][2] = -sinf(x);
		rx.m[1][3] = 0.0f;
		rx.m[2][0] = 0.0f;
		rx.m[2][1] = sinf(x);
		rx.m[2][2] = cosf(x);
		rx.m[2][3] = 0.0f;
		rx.m[3][0] = 0.0f;
		rx.m[3][1] = 0.0f;
		rx.m[3][2] = 0.0f;
		rx.m[3][3] = 1.0f;

		ry.m[0][0] = cosf(y);
		ry.m[0][1] = 0.0f;
		ry.m[0][2] = -sinf(y);
		ry.m[0][3] = 0.0f;
		ry.m[1][0] = 0.0f;
		ry.m[1][1] = 1.0f;
		ry.m[1][2] = 0.0f;
		ry.m[1][3] = 0.0f;
		ry.m[2][0] = sinf(y);
		ry.m[2][1] = 0.0f;
		ry.m[2][2] = cosf(y);
		ry.m[2][3] = 0.0f;
		ry.m[3][0] = 0.0f;
		ry.m[3][1] = 0.0f;
		ry.m[3][2] = 0.0f;
		ry.m[3][3] = 1.0f;

		rz.m[0][0] = cosf(z);
		rz.m[0][1] = -sinf(z);
		rz.m[0][2] = 0.0f;
		rz.m[0][3] = 0.0f;
		rz.m[1][0] = sinf(z);
		rz.m[1][1] = cosf(z);
		rz.m[1][2] = 0.0f;
		rz.m[1][3] = 0.0f;
		rz.m[2][0] = 0.0f;
		rz.m[2][1] = 0.0f;
		rz.m[2][2] = 1.0f;
		rz.m[2][3] = 0.0f;
		rz.m[3][0] = 0.0f;
		rz.m[3][1] = 0.0f;
		rz.m[3][2] = 0.0f;
		rz.m[3][3] = 1.0f;

		*this = rz * ry * rx;
	}

        /* axis is a unit vector about which rotation is done. angle should be in radians*/ 
	void InitAxisRotateTransform(const Vector3f& axis, float angle) {
		const float c = cosf(angle);
		const float s = sinf(angle);
		const float t = 1 - c;

		m[0][0] = t * axis.x * axis.x + c;
		m[0][1] = t * axis.x * axis.y - axis.z * s;
		m[0][2] = t * axis.x * axis.z + axis.y * s;
		m[0][3] = 0.0f;
		m[1][0] = t * axis.x * axis.y + axis.z * s;
		m[1][1] = t * axis.y * axis.y + c;
		m[1][2] = t * axis.y * axis.z - axis.x * s;
		m[1][3] = 0.0f;
		m[2][0] = t * axis.x * axis.z - axis.y * s;
		m[2][1] = t * axis.y * axis.z + axis.x * s;
		m[2][2] = t * axis.z * axis.z + c;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitTranslationTransform(float x, float y, float z) {
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = x;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = y;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = z;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitCameraTransform(const Vector3f& Target, const Vector3f& Up) {
		Vector3f N = Target;
		N.Normalize();
		Vector3f U = Up;
		U.Normalize();
		U = U.Cross(N);
		Vector3f V = N.Cross(U);

		m[0][0] = U.x;
		m[0][1] = U.y;
		m[0][2] = U.z;
		m[0][3] = 0.0f;
		m[1][0] = V.x;
		m[1][1] = V.y;
		m[1][2] = V.z;
		m[1][3] = 0.0f;
		m[2][0] = N.x;
		m[2][1] = N.y;
		m[2][2] = N.z;
		m[2][3] = 0.0f;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void InitPersProjTransform(const PersProjInfo& p) {
		const float ar = p.Width / p.Height;
		const float zRange = p.zNear - p.zFar;
		const float tanHalfFOV = tanf(ToRadian(p.FOV / 2.0f));

		m[0][0] = 1.0f / (tanHalfFOV * ar);
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0;
		m[1][0] = 0.0f;
		m[1][1] = 1.0f / tanHalfFOV;
		m[1][2] = 0.0f;
		m[1][3] = 0.0;
		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = (-p.zNear - p.zFar) / zRange;
		m[2][3] = 2.0f * p.zFar * p.zNear / zRange;
		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 1.0f;
		m[3][3] = 0.0;
	}
};
