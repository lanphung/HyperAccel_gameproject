#include "stdafx.h"
#include "WVP.h"

WVP * WVP::ms_pInstance = NULL;
void WVP::createViewMat()
{
	Matrix Rotation, Translation;
	Rotation.SetIdentity();
	Translation.SetIdentity();

	Vector3 zaxis, xaxis, yaxis;
	zaxis = (Vector3(0, 0, 1) - Vector3(0, 0, 0)).Normalize();
	xaxis = (Vector3(0, 1, 0).Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	Rotation.m[0][0] = xaxis.x;	Rotation.m[0][1] = xaxis.y;	Rotation.m[0][2] = xaxis.z;
	Rotation.m[1][0] = yaxis.x;	Rotation.m[1][1] = yaxis.y;	Rotation.m[1][2] = yaxis.z;
	Rotation.m[2][0] = zaxis.x;	Rotation.m[2][1] = zaxis.y;	Rotation.m[2][2] = zaxis.z;
	Rotation = Rotation.Transpose();

	Translation.m[3][0] = 0; Translation.m[3][1] = 0; Translation.m[3][2] = -1;
	ViewMat =  Translation * Rotation;
}