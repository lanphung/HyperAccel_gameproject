#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	Position.x = x;
	Position.y = y;
	Position.z = z;
}

void Camera::SetRotation(float x, float y, float z)
{
	Rotation.x = x;
	Rotation.y = y;
	Rotation.z = z;
}

void Camera::SetTransMat()
{
	rTransMat.SetTranslation(-Position.x, -Position.y, -Position.z);
}

void Camera::SetRotationMat()
{
	Matrix RotX, RotY, RotZ;
	RotX.SetRotationX(Rotation.x);
	RotY.SetRotationY(Rotation.y);
	RotZ.SetRotationZ(Rotation.z);
	RotMat = RotZ * RotX * RotY;
}

void Camera::MoveForward()
{
	Vector3 target;
	target.x = Position.x - SPEED*sin(Rotation.y)*cos(Rotation.z)*cos(Rotation.x);
	target.z = Position.z - SPEED*cos(Rotation.x)*cos(Rotation.y)*cos(Rotation.z);
	target.y = Position.y + SPEED*sin(Rotation.x)*cos(Rotation.z)*abs(cos(Rotation.y));
	SetPosition(target.x, target.y, target.z);
}

void Camera::MoveBackward()
{
	Vector3 target;
	target.x = Position.x + SPEED*sin(Rotation.y)*cos(Rotation.z)*cos(Rotation.x);
	target.z = Position.z + SPEED*cos(Rotation.x)*cos(Rotation.y)*cos(Rotation.z);
	target.y = Position.y - SPEED*sin(Rotation.x)*cos(Rotation.z)*abs(cos(Rotation.y));
	SetPosition(target.x, target.y, target.z);
}

void Camera::MoveLeft()
{
	Vector3 target;
	target.x = Position.x - SPEED*cos(Rotation.y)*cos(Rotation.z)*cos(Rotation.x);
	target.z = Position.z + SPEED*cos(Rotation.x)*sin(Rotation.y)*cos(Rotation.z);
	target.y = Position.y - SPEED*cos(Rotation.x)*sin(Rotation.z)*cos(Rotation.y);
	SetPosition(target.x, target.y, target.z);
}

void Camera::MoveRight()
{
	Vector3 target;
	target.x = Position.x + SPEED*cos(Rotation.y)*cos(Rotation.z)*cos(Rotation.x);
	target.z = Position.z - SPEED*cos(Rotation.x)*sin(Rotation.y)*cos(Rotation.z);
	target.y = Position.y + SPEED*cos(Rotation.x)*sin(Rotation.z)*cos(Rotation.y);
	SetPosition(target.x, target.y, target.z);
}

void Camera::RotUpward()
{
	Rotation.x += SPEED;
	Rotation.x = Rotation.x >= M_PI / 2 ? M_PI / 2 : Rotation.x;
	SetRotation(Rotation.x, Rotation.y, Rotation.z);
}

void Camera::RotDownward()
{
	Rotation.x -= SPEED;
	Rotation.x = Rotation.x <= -M_PI / 2 ? -M_PI / 2 : Rotation.x;
	SetRotation(Rotation.x, Rotation.y, Rotation.z);
}

void Camera::RotLeft()
{
	SetRotation(Rotation.x, Rotation.y - SPEED, Rotation.z);
}

void Camera::RotRight()
{
	SetRotation(Rotation.x, Rotation.y + SPEED, Rotation.z);
}