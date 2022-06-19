#ifndef __CMATRIX_H__
#define __CMATRIX_H__

#include <math.h>
#include <stdio.h>
#include <define.h>

class Matrix
{
public:
	float m_content[4][4];
	float m_array[16];

	Matrix();
	virtual ~Matrix();

	void operator=(const Matrix &matrix);
	Matrix operator+(const Matrix &matrix);
	Matrix operator-(const Matrix &matrix);
	Matrix operator*(const Matrix &matrix);

	void SetValue(int m, int n, float value);
	void SetArrayValue(float *aValue);
	void MakeIdentity();
	void MakeTranspose();
	void MakeTranslate(float tx, float ty, float tz, bool useLeftHanded = false);
	void MakeScale(float sx, float sy, float sz);
	void MakeRotate(float angle, bool x, bool y, bool z, bool useLeftHanded = false);
	void MakeRotate(float angleX, float angleY, float angleZ, bool useLeftHanded = false);
	void MakeRotateX(float angle, bool useLeftHanded = false);
	void MakeRotateY(float angle, bool useLeftHanded = false);
	void MakeRotateZ(float angle, bool useLeftHanded = false);
	void SetPerspective(float near, float far, float left, float right, float top, float bottom);
	void SetPerspectiveFov(float fovi, float aspect, float near, float far);
	void SetOrthor(float near = 1.0f, float far = 10000.0f, float left = -1.0f, float right = 1.0f, float top = 1.0f, float bottom = -1.0f);
	float* ToArray();
};
#endif