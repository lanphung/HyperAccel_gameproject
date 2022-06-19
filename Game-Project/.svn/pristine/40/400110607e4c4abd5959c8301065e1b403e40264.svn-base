#pragma once
#include "../Utilities/utilities.h" 
#include <cmath>
#define M_PI 3.14159265359  //Pi


class Camera
{
public:
	Camera();
	~Camera();
	Vector3 Position;
	Vector3 Rotation;
	Matrix getrTransMat()  { return rTransMat; }
	Matrix getRotMat()  { return RotMat; }
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetTransMat();
	void SetRotationMat();
	void MoveForward(); 
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void RotUpward();
	void RotDownward();
	void RotLeft();
	void RotRight();
	float Near;
	float Far;
	float FOV;
	float SPEED;
private:
	Matrix rTransMat, RotMat;
};