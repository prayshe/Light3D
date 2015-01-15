#pragma once

struct VECTOR3 {
	double x;
	double y;
	double z;
};

struct MATRIX44 {
	double m11, m12, m13, m14;
	double m21, m22, m23, m24;
	double m31, m32, m33, m34;
	double m41, m42, m43, m44;
};

double Dot(const VECTOR3 &, const VECTOR3 &);
VECTOR3 Subtract(const VECTOR3 &, const VECTOR3 &);
VECTOR3 Cross(const VECTOR3 &, const VECTOR3 &);
VECTOR3 Normalize(const VECTOR3 &);
VECTOR3 LinearTransform(const VECTOR3 &, const MATRIX44 &);
VECTOR3 HomogeneousTransform(const VECTOR3 &, const MATRIX44 &);

MATRIX44 Multiply(const MATRIX44 &, const MATRIX44 &);
MATRIX44 Zero(MATRIX44 &);
MATRIX44 Identity(MATRIX44 &);
MATRIX44 Transpose(const MATRIX44 &);
MATRIX44 TransposeR(const MATRIX44 &);
MATRIX44 Inverse(const MATRIX44 &);
MATRIX44 RotationX(double);
MATRIX44 RotationY(double);
MATRIX44 RotationZ(double);
MATRIX44 Rotation(double, double, double);
MATRIX44 Rotation(const VECTOR3 &);
MATRIX44 RotationAxis(const VECTOR3 &, double);
MATRIX44 Scaling(double, double, double);
MATRIX44 Scaling(const VECTOR3 &);
MATRIX44 Translation(double, double, double);
MATRIX44 Translation(const VECTOR3 &);
MATRIX44 LookAt(const VECTOR3 &, const VECTOR3 &, const VECTOR3 &);
MATRIX44 Frustum(double, double, double, double);
MATRIX44 Perspective(double, double, double, double);