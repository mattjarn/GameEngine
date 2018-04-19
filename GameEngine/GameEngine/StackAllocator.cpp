#include "StackAllocator.h"
#include <assert.h>
#include <iostream>

void* top;
void* start;

StackAllocator::StackAllocator(size_t stackSize_bytes) {
	top = (void*)malloc(stackSize_bytes);
	assert(top != NULL);
	start = top;
	//	top = (int*)calloc(stackSize_bytes, 1); //allocates and then clears stuff
	//std::cout << "void top has value of " << *(float*)top << " is located at " << top << " and is " << sizeof(top) << " bytes" << std::endl;

	//std::cout << "void start has value of " << *(float*)start << " is located at " << start << " and is " << sizeof(start) << " bytes" << std::endl;


}

void* StackAllocator::allocate(size_t size_bytes) {
	void* newItem = top;
	top = static_cast<char*>(top) + size_bytes;
	//std::cout << "void newItem has value of " << *(float*)newItem << " is located at " << newItem << " and is " << sizeof(newItem) << " bytes" << std::endl;
	
	//std::cout << "void top has value of " << *(float*)top << " is located at " << top << " and is " << sizeof(top) << " bytes" << std::endl;

	return newItem;

}

void* StackAllocator::allocateAligned(size_t size_bytes, size_t alignment) {
	assert(alignment >= 1);
	assert(alignment <= 128);
	assert((alignment & (alignment - 1)) == 0); // pwr of 2
	//std::cout << "Allocating memory" << std::endl;


	size_t expandedSize_bytes = size_bytes + alignment;

	uintptr_t rawAddress = reinterpret_cast<uintptr_t>(StackAllocator::allocate(expandedSize_bytes));

	size_t mask = (alignment - 1);
	uintptr_t misalignment = (rawAddress & mask);
	ptrdiff_t adjustment = alignment - misalignment;

	uintptr_t alignedAddress = rawAddress + adjustment;
	assert(adjustment < 256);
	std::uint8_t* pAlignedMem = reinterpret_cast<uint8_t*>(alignedAddress);
	pAlignedMem[-1] = static_cast<uint8_t>(adjustment);

	return static_cast<void*>(pAlignedMem);
}

void StackAllocator::deallocate(void* pRawMem) {
	//std::cout << "Deallocating memory" << std::endl;

	//std::cout << "void pRawMem has value of " << *(float*)pRawMem << " is located at " << pRawMem << " and is " << sizeof(pRawMem) << " bytes" << std::endl;

	top = pRawMem;

	//std::cout << "void top has value of " << *(float*)top << " is located at " << top << " and is " << sizeof(top) << " bytes" << std::endl;

}


void StackAllocator::deallocateAligned(void* pMem) {
	const std::uint8_t* pAlignedMem = reinterpret_cast<const std::uint8_t*>(pMem);

	uintptr_t alignedAddress = reinterpret_cast<uintptr_t>(pMem);
	ptrdiff_t adjustment = static_cast<ptrdiff_t>(pAlignedMem[-1]);

	uintptr_t rawAddress = alignedAddress - adjustment;
	void* pRawMem = reinterpret_cast<void*>(rawAddress);

	StackAllocator::deallocate(pRawMem);
}


void StackAllocator::clear() {
	//std::cout << "Clearing memory" << std::endl;

	top = start;

	//std::cout << "void top has value of " << *(float*)top << " is located at " << top << " and is " << sizeof(top) << " bytes" << std::endl;

}