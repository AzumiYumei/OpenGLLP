#pragma once
#include<string>
#include<vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

class ObjLoad
{
public:
	ObjLoad(string objName);
	string obj;
	int triangleSize;
	int vSize;
	vector<float> vertexArr;
	vector<float> Load();
};

