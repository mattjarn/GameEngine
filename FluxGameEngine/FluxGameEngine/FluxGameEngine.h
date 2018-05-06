#pragma once

#ifndef FLUX_GAME_ENGINE_H
#define FLUX_GAME_ENGINE_H

#include "gameTester.h"
#include "Renderer.h"
#include "StackAllocator.h"


class FluxGameEngine
{
public:
	Renderer R; //initialize the renderer

	FluxGameEngine();
	~FluxGameEngine();

	int StartUp();
	int ShutDown();

	void Render();

	//Memory Manager (pool)
	//File System
	//Rendering
	//Physics 

};

#endif // !FLUX_GAME_ENGINE_H