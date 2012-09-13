#include "Utility.h"
//#include "Quaternion.h"

float DotProduct(const Vector3& v1, const Vector3& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
Vector3 CrossProduct(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}
float Length(const Vector3& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
float Length(const Vector2& v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}
float LengthSquared(const Vector3& v)
{
	return v.x*v.x + v.y*v.y + v.z*v.z;
}
float LengthSquared(const Vector2& v)
{
	return v.x*v.x + v.y*v.y;
}
void Normalize(Vector3& v)
{
	v = v / Length(v);
}
/*void Rotate(Vector3& v, float Angle, Vector3 Axis)
{
	Quaternion quat(v, 0);
	quat.Rotate(Angle, Axis);
	v = quat.GetUVector();
}*/
float RandomFloat()
{
	int limit = RAND_MAX;
	float number = (float)(rand() % limit+0)/RAND_MAX;
	return number;
}
float RandomFloat(float minValue, float maxValue)
{
	return RandomFloat()*(maxValue-minValue)+minValue;
}
Vector3 RandomUnitVector3()
{
	Vector3 vec = Vector3(RandomFloat(-1, 1), RandomFloat(-1, 1), RandomFloat(-1, 1));
	Normalize(vec);
	return vec;
}
Vector4 Vec4MatrixMult(Vector4& vec, Matrix mat)
{
	vec = Vector4(mat._11 *vec.x + mat._21 *vec.y + mat._31 *vec.z + mat._41 *vec.w,
						mat._12 *vec.x + mat._22 *vec.y + mat._32 *vec.z + mat._42 *vec.w,
							mat._13 *vec.x + mat._23 *vec.y + mat._33 *vec.z + mat._43 *vec.w,
								mat._14 *vec.x + mat._24 *vec.y + mat._34 *vec.z + mat._44 *vec.w);
	return vec;
}
Vector3 Vec3Transform(Vector3& vec, Matrix mat)
{
	Vector4 v4(vec.x, vec.y, vec.z, 1);
	Vec4MatrixMult(v4, mat);
	vec = Vector3(v4.x, v4.y, v4.z);
	return vec;
}
Vector3 Vec3TransformNormal(Vector3& vec, Matrix mat)
{
	Vector4 v4(vec.x, vec.y, vec.z, 0);
	Vec4MatrixMult(v4, mat);
	vec = Vector3(v4.x, v4.y, v4.z);
	return vec;
}

D3DXMATRIX ToDxMatrix(Matrix pMatrix)
{
	Matrix m = pMatrix;
	return D3DXMATRIX(m._11, m._12, m._13, m._14, m._21, m._22, m._23, m._24, m._31, m._32, m._33, m._34, m._41, m._42, m._43, m._44);
}
Matrix ToMatrix(D3DXMATRIX pMatrix)
{
	D3DXMATRIX m = pMatrix;
	return Matrix(m._11, m._12, m._13, m._14, m._21, m._22, m._23, m._24, m._31, m._32, m._33, m._34, m._41, m._42, m._43, m._44);
}