#include"Camera.h"



Camera::Camera(glm::vec3 C_POS , glm::vec3 S_UP,float yaw,float pitch,
    float moveSpeed,float sensitive,float shiftSpeed,float limitLow,float limitHigh,float zoom)
{
	cameraPosition = C_POS;
	spaceUp = S_UP;
	Yaw = yaw;
	Pitch = pitch;
	MovementSpeed = moveSpeed;
	MouseSensitivity = sensitive;
    ShiftSpeed = shiftSpeed;
    LimitHigh = limitHigh;
    LimitLow = limitLow;
    Zoom = zoom;
    
	updateCameraVectors();
}


glm::mat4 Camera::GetViewMatrix()
{
    //注意，这里的spaceUp向量，如果填入的是摄象cameraUp的向量，那么会出现异常的画面翻转
	return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, spaceUp);
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::ProcessKeyboard(Camera_Movement MovemDirection, float deltaTime)
{
    float velocity;
    if (MovemDirection == SHIFT)
        velocity = MovementSpeed * deltaTime * ShiftSpeed;
    else
        velocity = MovementSpeed * deltaTime;
    if (MovemDirection == FORWARD)
        cameraPosition += cameraDirection * velocity ;
    if (MovemDirection == BACKWARD)
        cameraPosition -= cameraDirection * velocity;
    if (MovemDirection == LEFT)
        cameraPosition -= cameraRight * velocity ;
    if (MovemDirection == RIGHT)
        cameraPosition += cameraRight * velocity ;

    if (MovemDirection == NULL);
    //cout << velocity << endl;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > LimitHigh)
        Pitch = LimitHigh;
    if (Pitch < LimitLow)
        Pitch = LimitLow;

    updateCameraVectors();
}

