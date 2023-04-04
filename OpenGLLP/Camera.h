#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	SHIFT,
	NONE
};

class Camera
{
public:
	//摄像机向量
	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 spaceUp;

	//鼠标角度
	float Yaw;
	float Pitch;
	float LimitLow;
	float LimitHigh;

	//摄像机鼠标属性
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	float ShiftSpeed;
	
	Camera(glm::vec3 C_POS,glm::vec3 S_UP,float yaw,float pitch,float moveSpeed,float sensitive,float shiftSpeed,float limitLow,float limitHigh,float zoom);

	glm::mat4 GetViewMatrix();
	
	void ProcessKeyboard(Camera_Movement MovemDirection, float deltaTime);

	void ProcessMouseMovement(float xoffset, float yoffset);

	void ProcessMouseScroll(float yoffset);

private:
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw))* cos(glm::radians(Pitch));
		cameraDirection = glm::normalize(front);
		
		cameraRight = glm::normalize(glm::cross(cameraDirection, spaceUp));  
		cameraUp = glm::normalize(glm::cross(cameraRight, spaceUp));
	}

};
