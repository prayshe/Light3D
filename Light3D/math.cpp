#include <stdio.h>
#include <math.h>
#include "math.hpp"

MATRIX44 Zero(MATRIX44 &m)
{
	m.m11 = m.m12 = m.m13 = m.m14 = 0.0;
	m.m21 = m.m22 = m.m23 = m.m24 = 0.0;
	m.m31 = m.m32 = m.m33 = m.m34 = 0.0;
	m.m41 = m.m42 = m.m43 = m.m44 = 0.0;

	return m;
}

MATRIX44 Identity(MATRIX44 &m)
{
	m.m11 = m.m22 = m.m33 = m.m44 = 1.0;

	m.m12 = m.m13 = m.m14 = 0.0;
	m.m21 = m.m23 = m.m24 = 0.0;
	m.m31 = m.m32 = m.m34 = 0.0;
	m.m41 = m.m42 = m.m43 = 0.0;

	return m;
}

double Dot(const VECTOR3 &one, const VECTOR3 &two)
{
	return one.x * two.x + one.y * two.y + one.z * two.z;
}

VECTOR3 Subtract(const VECTOR3 &one, const VECTOR3 &two)
{
	return VECTOR3{ one.x - two.x, one.y - two.y, one.z - two.z };
}

VECTOR3 Cross(const VECTOR3 &one, const VECTOR3 &two)
{
	return VECTOR3{
		one.y * two.z - one.z * two.y,
		one.z * two.x - one.x * two.z,
		one.x * two.y - one.y * two.x,
	};
}

VECTOR3 Normalize(const VECTOR3 &vector)
{
	double factor = 1.0 / sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	return VECTOR3 { vector.x * factor, vector.y * factor, vector.z * factor };
}

VECTOR3 LinearTransform(const VECTOR3 &v, const MATRIX44 &m)
{
	return VECTOR3{
		v.x * m.m11 + v.y * m.m21 + v.z * m.m31,
		v.x * m.m12 + v.y * m.m22 + v.z * m.m32,
		v.x * m.m13 + v.y * m.m23 + v.z * m.m33,
	};
}

VECTOR3 HomogeneousTransform(const VECTOR3 &v, const MATRIX44 &m)
{
	double w = 1.0 / (v.x * m.m14 + v.y * m.m24 + v.z * m.m34 + m.m44);
	return VECTOR3{
		(v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + m.m41) * w,
		(v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + m.m42) * w,
		(v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + m.m43) * w,
	};
}

MATRIX44 Multiply(const MATRIX44 &one, const MATRIX44 &two)
{
	return MATRIX44{
		one.m11 * two.m11 + one.m12 * two.m21 + one.m13 * two.m31 + one.m14 * two.m41,
		one.m11 * two.m12 + one.m12 * two.m22 + one.m13 * two.m32 + one.m14 * two.m42,
		one.m11 * two.m13 + one.m12 * two.m23 + one.m13 * two.m33 + one.m14 * two.m43,
		one.m11 * two.m14 + one.m12 * two.m24 + one.m13 * two.m34 + one.m14 * two.m44,
		one.m21 * two.m11 + one.m22 * two.m21 + one.m23 * two.m31 + one.m24 * two.m41,
		one.m21 * two.m12 + one.m22 * two.m22 + one.m23 * two.m32 + one.m24 * two.m42,
		one.m21 * two.m13 + one.m22 * two.m23 + one.m23 * two.m33 + one.m24 * two.m43,
		one.m21 * two.m14 + one.m22 * two.m24 + one.m23 * two.m34 + one.m24 * two.m44,
		one.m31 * two.m11 + one.m32 * two.m21 + one.m33 * two.m31 + one.m34 * two.m41,
		one.m31 * two.m12 + one.m32 * two.m22 + one.m33 * two.m32 + one.m34 * two.m42,
		one.m31 * two.m13 + one.m32 * two.m23 + one.m33 * two.m33 + one.m34 * two.m43,
		one.m31 * two.m14 + one.m32 * two.m24 + one.m33 * two.m34 + one.m34 * two.m44,
		one.m41 * two.m11 + one.m42 * two.m21 + one.m43 * two.m31 + one.m44 * two.m41,
		one.m41 * two.m12 + one.m42 * two.m22 + one.m43 * two.m32 + one.m44 * two.m42,
		one.m41 * two.m13 + one.m42 * two.m23 + one.m43 * two.m33 + one.m44 * two.m43,
		one.m41 * two.m14 + one.m42 * two.m24 + one.m43 * two.m34 + one.m44 * two.m44,
	};
}

MATRIX44 Zero()
{
	return MATRIX44{
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
	};
}

MATRIX44 Indentity()
{
	return MATRIX44{
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0,
	};
}

MATRIX44 Transpose(const MATRIX44 &matrix)
{
	return MATRIX44{
		matrix.m11, matrix.m21, matrix.m31, matrix.m41,
		matrix.m12, matrix.m22, matrix.m32, matrix.m42,
		matrix.m13, matrix.m23, matrix.m33, matrix.m43,
		matrix.m14, matrix.m24, matrix.m34, matrix.m44,
	};
}

MATRIX44 TransposeR(const MATRIX44 &matrix)
{
	return MATRIX44{
		matrix.m41, matrix.m31, matrix.m21, matrix.m11,
		matrix.m42, matrix.m32, matrix.m22, matrix.m12,
		matrix.m43, matrix.m33, matrix.m23, matrix.m13,
		matrix.m44, matrix.m34, matrix.m24, matrix.m14,
	};
}

MATRIX44 Inverse(const MATRIX44 &matrix)
{
	double d2132 = matrix.m21 * matrix.m32 - matrix.m22 * matrix.m31;
	double d2133 = matrix.m21 * matrix.m33 - matrix.m23 * matrix.m31;
	double d2134 = matrix.m21 * matrix.m34 - matrix.m24 * matrix.m31;
	double d2233 = matrix.m22 * matrix.m33 - matrix.m23 * matrix.m32;
	double d2234 = matrix.m22 * matrix.m34 - matrix.m24 * matrix.m32;
	double d2334 = matrix.m23 * matrix.m34 - matrix.m24 * matrix.m33;
	double d2142 = matrix.m21 * matrix.m42 - matrix.m22 * matrix.m41;
	double d2143 = matrix.m21 * matrix.m43 - matrix.m23 * matrix.m41;
	double d2144 = matrix.m21 * matrix.m44 - matrix.m24 * matrix.m41;
	double d2243 = matrix.m22 * matrix.m43 - matrix.m23 * matrix.m42;
	double d2244 = matrix.m22 * matrix.m44 - matrix.m24 * matrix.m42;
	double d2344 = matrix.m23 * matrix.m44 - matrix.m24 * matrix.m43;
	double d3142 = matrix.m31 * matrix.m42 - matrix.m32 * matrix.m41;
	double d3143 = matrix.m31 * matrix.m43 - matrix.m33 * matrix.m41;
	double d3144 = matrix.m31 * matrix.m44 - matrix.m34 * matrix.m41;
	double d3243 = matrix.m32 * matrix.m43 - matrix.m33 * matrix.m42;
	double d3244 = matrix.m32 * matrix.m44 - matrix.m34 * matrix.m42;
	double d3344 = matrix.m33 * matrix.m44 - matrix.m34 * matrix.m43;

	double a11 = matrix.m22 * d3344 - matrix.m23 * d3244 + matrix.m24 * d3243;
	double a12 = matrix.m21 * d3344 - matrix.m23 * d3144 + matrix.m24 * d3143;
	double a13 = matrix.m21 * d3244 - matrix.m22 * d3144 + matrix.m24 * d3142;
	double a14 = matrix.m21 * d3243 - matrix.m22 * d3143 + matrix.m23 * d3142;
	double a21 = matrix.m12 * d3344 - matrix.m13 * d3244 + matrix.m14 * d3243;
	double a22 = matrix.m11 * d3344 - matrix.m13 * d3144 + matrix.m14 * d3143;
	double a23 = matrix.m11 * d3244 - matrix.m12 * d3144 + matrix.m14 * d3142;
	double a24 = matrix.m11 * d3243 - matrix.m12 * d3143 + matrix.m13 * d3142;
	double a31 = matrix.m12 * d2344 - matrix.m13 * d2244 + matrix.m14 * d2243;
	double a32 = matrix.m11 * d2344 - matrix.m13 * d2144 + matrix.m14 * d2143;
	double a33 = matrix.m11 * d2244 - matrix.m12 * d2144 + matrix.m14 * d2142;
	double a34 = matrix.m11 * d2243 - matrix.m12 * d2143 + matrix.m13 * d2142;
	double a41 = matrix.m12 * d2334 - matrix.m13 * d2234 + matrix.m14 * d2233;
	double a42 = matrix.m11 * d2334 - matrix.m13 * d2134 + matrix.m14 * d2133;
	double a43 = matrix.m11 * d2234 - matrix.m12 * d2134 + matrix.m14 * d2132;
	double a44 = matrix.m11 * d2233 - matrix.m12 * d2133 + matrix.m13 * d2132;

	double det = 1.0 / (matrix.m11 * a11 - matrix.m12 * a12 + matrix.m13 * a13 - matrix.m14 * a14);

	return MATRIX44{
		 a11 * det, -a21 * det,  a31 * det, -a41 * det,
		-a12 * det,  a22 * det, -a32 * det,  a42 * det,
		 a13 * det, -a23 * det,  a33 * det, -a43 * det,
		-a14 * det,  a24 * det, -a34 * det,  a44 * det,
	};
}

MATRIX44 RotationX(double theta)
{
	double sint = sin(theta);
	double cost = cos(theta);
	return MATRIX44{
		1.0,   0.0,  0.0, 0.0,
		0.0,  cost, sint, 0.0,
		0.0, -sint, cost, 0.0,
		0.0,   0.0,  0.0, 1.0,
	};
}

MATRIX44 RotationY(double theta)
{
	double sint = sin(theta);
	double cost = cos(theta);
	return MATRIX44{
		cost, 0.0, -sint, 0.0,
		 0.0, 1.0,   0.0, 0.0,
		sint, 0.0,  cost, 0.0,
		 0.0, 0.0,   0.0, 1.0,
	};
}

MATRIX44 RotationZ(double theta)
{
	double sint = sin(theta);
	double cost = cos(theta);
	return MATRIX44{
		 cost, sint, 0.0, 0.0,
		-sint, cost, 0.0, 0.0,
		  0.0,  0.0, 1.0, 0.0,
		  0.0,  0.0, 0.0, 1.0,
	};
}

MATRIX44 Rotation(double yaw, double pitch, double roll)
{
	return Multiply(RotationZ(roll), Multiply(RotationX(pitch), RotationY(yaw)));
}

MATRIX44 Rotation(const VECTOR3 &v)
{
	return Multiply(RotationZ(v.z), Multiply(RotationX(v.x), RotationY(v.y)));
}

MATRIX44 RotationAxis(const VECTOR3 &axis, double theta)
{
	VECTOR3 Axis = Normalize(axis);
	double sint = -sin(theta);
	double cost = cos(theta);
	double tem = 1 - cost;
	return MATRIX44{
		Axis.x * Axis.x * tem + cost,
		Axis.x * Axis.y * tem - Axis.z * sint,
		Axis.x * Axis.z * tem + Axis.y * sint,
		0.0,
		Axis.y * Axis.x * tem + Axis.z * sint,
		Axis.y * Axis.y * tem + cost,
		Axis.y * Axis.z * tem - Axis.x * sint,
		0.0,
		Axis.z * Axis.x * tem - Axis.y * sint,
		Axis.z * Axis.y * tem + Axis.x * sint,
		Axis.z * Axis.z * tem + cost,
		0.0,
		0.0, 0.0, 0.0, 1.0,
	};
}

MATRIX44 Scaling(double sx, double sy, double sz)
{
	return MATRIX44{
		 sx, 0.0, 0.0, 0.0,
		0.0,  sy, 0.0, 0.0,
		0.0, 0.0,  sz, 0.0,
		0.0, 0.0, 0.0, 1.0,
	};
}

MATRIX44 Scaling(const VECTOR3 &v)
{
	return MATRIX44{
		v.x, 0.0, 0.0, 0.0,
		0.0, v.y, 0.0, 0.0,
		0.0, 0.0, v.z, 0.0,
		0.0, 0.0, 0.0, 1.0,
	};
}

MATRIX44 Translation(double tx, double ty, double tz)
{
	return MATRIX44{
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		 tx,  ty,  tz, 1.0,
	};
}

MATRIX44 Translation(const VECTOR3 &v)
{
	return MATRIX44{
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		v.x, v.y, v.z, 1.0,
	};
}

MATRIX44 LookAt(const VECTOR3 &eye, const VECTOR3 &target, const VECTOR3 &up)
{
	VECTOR3 AxisZ = Normalize(Subtract(target, eye));
	VECTOR3 AxisX = Normalize(Cross(up, AxisZ));
	VECTOR3 AxisY = Normalize(Cross(AxisZ, AxisX));
	
	return MATRIX44{
		 AxisX.x, AxisY.x, AxisZ.x, 0.0,
		 AxisX.y, AxisY.y, AxisZ.y, 0.0,
		 AxisX.z, AxisY.z, AxisZ.z, 0.0,
		-Dot(AxisX, eye),
		-Dot(AxisY, eye),
		-Dot(AxisZ, eye),
		 1.0
	};
}

MATRIX44 Frustum(double width, double height, double znear, double zfar)
{
	double znear2 = 2.0 * znear;
	double deepth = znear - zfar;
	return MATRIX44{
		znear2 / width, 0.0, 0.0, 0.0,
		0.0, znear2 / height, 0.0, 0.0,
		0.0, 0.0, -zfar / deepth, -1.0,
		0.0, 0.0, znear * zfar / deepth, 0.0,
	};
}

MATRIX44 Perspective(double fov, double aspect, double znear, double zfar)
{
	double tant = 1.0 / tan(fov * 0.5);
	double deepth = znear - zfar;
	return MATRIX44{
		tant / aspect, 0.0, 0.0, 0.0,
		0.0, tant, 0.0, 0.0,
		0.0, 0.0, -zfar / deepth, -1.0,
		0.0, 0.0, znear * zfar / deepth, 0.0,
	};
}