#ifndef GAME_TESTER_H
#define GAME_TESTER_H

#include <vector>
#include <iostream>
#include <chrono>
#include "vec4.h"
#include "mat4.h"
#include "quaternion.h"
#include "StackAllocator.h"

class GameTester
{
public:

	typedef std::chrono::high_resolution_clock Clock; //timer

	GameTester();
	~GameTester();

	static void test5000();

	static void testQuaternions();

	static void testMemory(StackAllocator stack);


};

#endif // GAME_TESTER_H