#pragma once

#ifndef SIMULTION_MANAGER_H
#define SIMULTION_MANAGER_H

#include <glad/glad.h>
#include <iostream>
#include <GLFW\glfw3.h>



class SimulationManager
{
public:
	SimulationManager();
	~SimulationManager();

	int StartUp();
	//int ShutDown();

	void run();

};





#endif // !SIMULTION_MANAGER_H