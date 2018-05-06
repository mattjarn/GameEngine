#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <memory>
#include <cstdint>

class StackAllocator
{
public:

	//typedef std::uint32_t Marker; // Stack marker: Represents the current top of the stack.

	StackAllocator(size_t stackSize_bytes); //Constructs a stack allocator with the given total size

	void* allocate(size_t size_bytes); // allocates a new block of the given size from stack top

	void* allocateAligned(size_t size_bytes, size_t alignment); //allocates a new aligned block of given size

	void deallocate(void* pRawMem); //deallocate raw memory

	void deallocateAligned(void* pMem); //deallocate the top aligned block

	void clear(); //clears the entire stack(rolls the stack back to zero)

};

#endif // STACK_ALLOCATOR_H