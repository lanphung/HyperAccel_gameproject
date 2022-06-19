#include <matrix.h>
Matrix::Matrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_content[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{

}


void Matrix::operator=(const Matrix &matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_content[i][j] = matrix.m_content[i][j];
		}
	}
}

Matrix Matrix::operator+(const Matrix &matrix)
{
	Matrix result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m_content[i][j] = m_content[i][j] + matrix.m_content[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator-(const Matrix &matrix)
{
	Matrix result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m_content[i][j] = m_content[i][j] - matrix.m_content[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator*(const Matrix &matrix)
{
	Matrix result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m_content[i][j] += m_content[i][k] * matrix.m_content[k][j];
			}
		}
	}

	return result;
}

void Matrix::MakeIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_content[i][j] = ((i == j) ? 1.0f : 0);
		}
	}
}

void Matrix::MakeTranspose()
{
	Matrix result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m_content[j][i] = m_content[i][j];
		}
	}

	*this = result;
}

void Matrix::MakeTranslate(float tx, float ty, float tz, bool useLeftHanded)
{
	MakeIdentity();

	if (useLeftHanded)
	{
		m_content[3][0] = tx;
		m_content[3][1] = ty;
		m_content[3][2] = tz;		
	}
	else
	{
		m_content[0][3] = tx;
		m_content[1][3] = ty;
		m_content[2][3] = tz;
	}
}


void Matrix::MakeScale(float sx, float sy, float sz)
{
	MakeIdentity();
	m_content[0][0] = sx;
	m_content[1][1] = sy;
	m_content[2][2] = sz;
}

void Matrix::MakeRotate(float angle, bool x, bool y, bool z, bool useLeftHanded)
{
	MakeIdentity();

	float rad = (float)(angle * PI) / 180.0f;

	if (x)
	{
		m_content[1][1] = cos(rad);
		m_content[1][2] = -sin(rad);
		m_content[2][1] = sin(rad);
		m_content[2][2] = cos(rad);
	}
	else if (y)
	{
		m_content[0][0] = cos(rad);
		m_content[0][2] = sin(rad);
		m_content[2][0] = -sin(rad);
		m_content[2][2] = cos(rad);
	}
	else if (z)
	{
		m_content[0][0] = cos(rad);
		m_content[0][1] = -sin(rad);
		m_content[1][0] = sin(rad);
		m_content[1][1] = cos(rad);
	}

	if (useLeftHanded)
	{
		MakeTranspose();
	}
}

void Matrix::MakeRotateX(float angle, bool useLeftHanded)
{
	MakeRotate(angle, true, false, false, useLeftHanded);
}

void Matrix::MakeRotateY(float angle, bool useLeftHanded)
{
	MakeRotate(angle, false, true, false, useLeftHanded);
}

void Matrix::MakeRotateZ(float angle, bool useLeftHanded)
{
	MakeRotate(angle, false, false, true, useLeftHanded);
}

void Matrix::MakeRotate(float angleX, float angleY, float angleZ, bool useLeftHanded)
{
	Matrix rotateX;
	Matrix rotateY;
	Matrix rotateZ;

	rotateX.MakeRotateX(angleX, useLeftHanded);
	rotateY.MakeRotateY(angleY, useLeftHanded);
	rotateZ.MakeRotateZ(angleZ, useLeftHanded);

	*this = rotateX * rotateY * rotateZ;
}
float* Matrix::ToArray()
{
	// Since GLSL use matrix[col][row]
	for (int i = 0 ; i < 16; i++)
	{
		m_array[i] = m_content[i / 4][i % 4];
	}

	return m_array;
}

void Matrix::SetValue(int m, int n, float value)
{
	m_content[m][n] = value;
}

void Matrix::SetArrayValue(float *aValue)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_content[i][j] = aValue[i * 4 + j];
}

void Matrix::SetPerspective(float near, float far, float left, float right, float top, float bottom)
{
	MakeIdentity();

	m_content[0][0] = (float)2.0f * near / (right - left);
	m_content[0][2] = (float)(right + left) / (right - left);
	m_content[1][1] = (float)2.0f * near / (top - bottom);	
	m_content[1][2] = (float)(top + bottom) / (top - bottom);
	m_content[2][2] = (float)-(far + near) / (far - near);
	m_content[2][3] = (float)-(2.0f * far * near) / (far - near);
	m_content[3][2] = -1.0f;

}

void Matrix::SetPerspectiveFov(float fovi, float aspect, float near, float far)
{
	MakeIdentity();

	const float PI_OVER_360 = (float)PI / 360.0f; 
	const float h = 1.0f / tan(fovi * PI_OVER_360);
	float depth = near - far;

	m_content[0][0] = h / aspect;
	m_content[1][1] = h;
	m_content[2][2] = (far + near) / depth;;
	m_content[2][3] = -1;
	m_content[3][2] = 2.0f * (near * far) / depth;;
	m_content[3][3] = 0;
}

void Matrix::SetOrthor(float near, float far, float left, float right, float top, float bottom)
{
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_content[i][j] = 0;
	m_content[0][0] = (float)2.0f / (right - left);
	m_content[0][3] = (float)-(right + left) / (right - left);
	m_content[1][1] = (float)2.0f / (top - bottom);	
	m_content[1][3] = (float)-(top + bottom) / (top - bottom);
	m_content[2][2] = (float)-(2.0f) / (far - near);
	m_content[2][3] = (float)-(far + near) / (far - near);
	m_content[3][3] = 1.0f;

}
