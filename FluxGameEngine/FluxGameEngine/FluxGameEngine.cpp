#include "FluxGameEngine.h"


FluxGameEngine::FluxGameEngine() {
	StartUp();
}

FluxGameEngine::~FluxGameEngine() {}

int FluxGameEngine::StartUp() {
	//float aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;
	//mat4 pMat = mat4::perspective(60.0f, aspect, 0.1f, 1000.0f);
	StackAllocator stack(5000 * sizeof(vec4)); //initialize the stack allocator

	GameTester tester; 

	//initialize the tester
	//tester.testMemory(stack);
	//tester.testQuaternions();
	//tester.test5000();

	Render();

	return 0;
}

int FluxGameEngine::ShutDown() {
	return 0;
}

void FluxGameEngine::Render() {
	//R.MultipleLights();
	R.BulletPhysics();
	//R.shadows();
	//R.setupVertices();
	//R.Draw();
}


