#include "Camera.hpp"

NS_BEGIN

Camera::Camera()
{}

void Camera::Initialize()
{
	right = Vector3::Right;
	up = Vector3::Up;
	forward = Vector3::Forward;
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	SetLens(0.25f * PI, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
	UpdateViewMatrix();
}

void Camera::SetLens(float fovY, float aspect, float zNear, float zFar)
{
	this->fovY = fovY;
	aspectRatio = aspect;
	nearZ = zNear;
	farZ = zFar;

	nearHeight = 2.0f * nearZ * tanf(0.5f * fovY);
	farHeight = 2.0f * farZ * tanf(0.5f * fovY);

	projection = Matrix::CreatePerspectiveFov(fovY, aspect, zNear,zFar);
}

void Camera::UpdateViewMatrix()
{
	forward = Vector3::Normalize(forward);
	up = Vector3::Normalize(Vector3::Cross(forward, right));
	right = Vector3::Cross(up, forward);

	float x = -Vector3::Dot(position, right);
	float y = -Vector3::Dot(position, up);
	float z = -Vector3::Dot(position, forward);


	view = Matrix(
		right.x, up.x, forward.x, 0.0f,
		right.y, up.y, forward.y, 0.0f,
		right.z, up.z, forward.z, 0.0f,
		x, y, z, 1.0f);

	// Cache the viewProjection matrix
	viewProjection = projection * view;
	dirty = false;
}

void Camera::Move(Vector3 move)
{
	position = position + move;
	dirty = true;
}

void Camera::MoveForward(float speed)
{
	position = position + forward * speed;
	dirty = true;
}

void Camera::MoveRight(float speed)
{
	position = position + right * speed;
	dirty = true;
}

void Camera::SetPosition(Vector3 position)
{
	this->position = position;
	dirty = true;
}

void Camera::LookAt(Vector3 target, Vector3 up)
{
	view = Matrix::CreateLookAt(position, target, up);
	right = view.Right();
	this->up = view.Up();
	forward = view.Forward();

	viewProjection = projection * view;
}

void Camera::Pitch(float angle)
{
	Matrix m = Matrix::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(right, angle));

	forward = (forward * m).Normalized();
	right = (right * m).Normalized();
	up = Vector3::Cross(forward, right);

	dirty = true;
}

void Camera::Yaw(float angle)
{
	Matrix m = Matrix::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(up, angle));

	forward = (forward * m).Normalized();
	right = (right * m).Normalized();
	up = Vector3::Cross(forward, right);

	dirty = true;
}

void Camera::Roll(float angle)
{
	Matrix m = Matrix::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(forward, angle));

	forward = (forward * m).Normalized();
	right = (right * m).Normalized();
	up = Vector3::Cross(forward, right);

	dirty = true;
}

void Camera::RotateY(float angle)
{
	Matrix m = Matrix::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(Vector3::Up, angle));

	forward = (forward * m).Normalized();
	right = (right * m).Normalized();
	up = Vector3::Cross(forward, right);

	dirty = true;
}

Matrix Camera::GetView()const
{
	return view;
}

Matrix Camera::GetProjection()const
{	
	return projection;
}
Matrix Camera::GetViewProjection()const
{
	return viewProjection;
}

Vector3 Camera::GetPosition()const
{
	return position;
}

bool Camera::IsDirty()const
{
	return dirty;
}

NS_END