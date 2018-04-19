#include "gameTester.h"

GameTester::GameTester() {}
GameTester::~GameTester() {}


void GameTester::testMemory(StackAllocator stack) {
	//float some[4] = {1.5f, 0.3f, 4.2f, 8.0f};
	//std::cout << "the size of test is " << sizeof(some) << std::endl;
	int allocations = 5000;
	std::cout << "testing memory speed for " << allocations << " allocations" << std::endl;
	auto begin = Clock::now();
	for (int i = 0; i < allocations; i++)
	{
		stack.allocate(sizeof(vec4));
	
	}
	auto end = Clock::now();
	std::cout << "Time taken to create " << allocations << " allocations " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to create " << allocations << " allocations " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl << std::endl;

	
	//void* p = stack.allocateAligned(64, 2);

	//*(int*)p = 5;
	//std::cout << "void p has a value of " << *(int*)p << " is located at " << p << " and is " << sizeof(p) << " bytes" << std::endl;
	//
	//p = some;
	//std::cout << "void p has a value of " << *(float*)p << " is located at " << p << " and is " << sizeof(p) << " bytes" << std::endl;

	//void* m = stack.allocateAligned(64, 2);
	//p = some;
	//std::cout << "void m has a value of " << *(float*)m << " is located at " << m << " and is " << sizeof(m) << " bytes" << std::endl;

	//for (int i = 0; i<5; i++)
	//{
	//	/* ptr[i] and *(ptr+i) can be used interchangeably */
	//	std::cout << *((float*)p + i) << std::endl;
	//}

	//stack.deallocateAligned(p);
	//std::cout << "void p has a value of " << *(float*)p << " is located at " << p << " and is " << sizeof(p) << " bytes" << std::endl;

	//stack.clear();

	//stack.deallocateAligned(m);
	//std::cout << "void m has a value of " << *(float*)m << " is located at " << m << " and is " << sizeof(m) << " bytes" << std::endl;

}


void GameTester::test5000() {

	std::cout << "Begin vertex tests" << std::endl;
	const int vecTestSize = 5000;
	vec4 vectors[vecTestSize];

	std::cout << "Creating vertices" << std::endl;
	auto begin = Clock::now();
	for (int i = 0; i < vecTestSize; i++)
	{
		vectors[i] = vec4(rand() % 200 - 100, rand() % 200 - 100, rand() % 200 - 100, 0);

	}
	auto end = Clock::now();
	std::cout << "Time taken to create " << vecTestSize << " vectors " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to create " << vecTestSize << " vectors " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

	std::cout << "multiplying Vectors by a rotation, scale, transformation matrix" << std::endl;

	mat4 scale = mat4(5);
	mat4 translation = mat4::createTranslationMat(5, 5, 5);
	mat4 mult = scale * translation;
	mat4 rot = mat4::createRotationMat(0, 90, 0);
	mult = mult * rot;
	begin = Clock::now();
	for (int i = 0; i < vecTestSize; i++)
	{
		vectors[i] = mat4::mulVectorMatrix(vectors[i], mult);
	}
	end = Clock::now();

	std::cout << "Time taken to compute " << vecTestSize << " vector matrix multiplications is " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to compute " << vecTestSize << " vector matrix multiplications is " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

	std::cout << "Multiplying vectors by a quaternion" << std::endl;
	vec4 y = vec4(0, 1, 0, 0);
	quaternion q = quaternion(y, 90);
	begin = Clock::now();
	for (int i = 0; i < vecTestSize; i++)
	{
		vectors[i] = q * vectors[i];
	}
	end = Clock::now();

	std::cout << "Time taken to compute " << vecTestSize << " vector quaternion multiplications is " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds" << std::endl;
	std::cout << "Time taken to compute " << vecTestSize << " vector quaternion multiplications is " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl << std::endl;


}

void GameTester::testQuaternions() {

	std::cout << "Begin Quaternion tests" << std::endl;

	std::cout << "Multiplying a vector by one quaternion" << std::endl;

	vec4 x = vec4(1, 0, 0, 0);
	vec4 y = vec4(0, 1, 0, 0);
	std::cout << "The start vector" << std::endl;
	vec4::print(x);

	quaternion w = quaternion(y, 90);
	quaternion::print(w);

	vec4 d = w * x;
	std::cout << "The vector after rotating 90 degrees about the y axis" << std::endl;
	vec4::print(d);

	quaternion h = quaternion::conjugate(w);
	quaternion::print(h);

	d = h * d;
	std::cout << "The vector after rotating it back" << std::endl;
	vec4::print(d);
	// --------------------------------------------------------------------------------------------------
	std::cout << "Multiplying a vector by two separate quaternions" << std::endl;

	quaternion x90 = quaternion(x, 90);
	quaternion::print(x90);
	w = quaternion(y, 90);
	quaternion::print(w);

	d = w * x;
	std::cout << "The vector after rotating 90 degrees about the y axis" << std::endl;
	vec4::print(d);

	d = x90 * d;
	std::cout << "The vector after rotating 90 degrees about the x axis" << std::endl;
	vec4::print(d);

	h = quaternion::conjugate(x90);
	quaternion::print(h);

	d = h * d;
	std::cout << "The vector after undoing the x rotation of 90" << std::endl;
	vec4::print(d);

	h = quaternion::conjugate(w);
	quaternion::print(h);

	d = h * d;
	std::cout << "The vector after undoing the y rotation of 90" << std::endl;
	vec4::print(d);


}