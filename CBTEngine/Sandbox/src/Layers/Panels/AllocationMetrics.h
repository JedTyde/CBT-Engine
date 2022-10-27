#pragma once
#include <cstdlib>

namespace CBT {
	// Allocation metrics
	struct AllocationMetrics {
		static size_t allocation_count;
		static size_t bytes_allocated;
	};

	size_t AllocationMetrics::allocation_count = 0;
	size_t AllocationMetrics::bytes_allocated = 0;
}

// Allocation overloads
void* operator new(size_t size) {
	//size > 0 ? return 0 : 1;

	CBT::AllocationMetrics::allocation_count++;
	CBT::AllocationMetrics::bytes_allocated += size;

	return malloc(size);
}

void operator delete(void* memory, size_t size) {
	CBT::AllocationMetrics::allocation_count--;
	CBT::AllocationMetrics::bytes_allocated -= size;

	free(memory);
}