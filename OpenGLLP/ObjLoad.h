#pragma once
#include<string>
#include<vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class ObjLoad
{
public:
	ObjLoad(string objName);
	string obj;
	vector<float> vertexArr;
	vector<float> Load();
};

