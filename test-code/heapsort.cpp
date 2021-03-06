#include <iostream>

void build_heap(int array[], unsigned int size);
void heapsort(int array[], unsigned int size);
void max_heapify(int array[], unsigned int start, unsigned int size);
void min_heapify(int array[], unsigned int start, unsigned int size);

void (*heapify) (int [], unsigned int, unsigned int) = &min_heapify;

void print_array(int array[], unsigned int size)
{
	std::cout << "\t";
	for (unsigned int i = 0; i < size; i++) {
		std::cout << array[i];
		if (i != size-1) std::cout << ", ";
	}
	std::cout << "\n";
}

inline void swap(int* val1, int* val2)
{
	(*val1) = (*val1) ^ (*val2);
	(*val2) = (*val1) ^ (*val2);
	(*val1) = (*val1) ^ (*val2);
}

void build_heap(int array[], unsigned int size)
{
	for (int i = size/2; i >= 0; i--) {
		heapify(array, i, size);
	}
}

void min_heapify(int array[], unsigned int parent, unsigned int size)
{
	if (parent >= size) {
		return;		// leaf
	}

	const unsigned int left_child = 2*parent + 1;
	const unsigned int right_child = 2*parent + 2;

	unsigned int smallest = parent;

	if (left_child < size && array[left_child] < array[smallest]) {
		smallest = left_child;
	}

	if (right_child < size && array[smallest] > array[right_child]) {
		smallest = right_child;
	}

	// parent was swapped
	if (parent != smallest) {
		swap(&array[smallest], &array[parent]);
		min_heapify(array, smallest, size); // does subtree we swapped with follows heap property?
	}
}

void max_heapify(int array[], unsigned int parent, unsigned int size)
{
	if (parent >= size) {
		return;		// leaf
	}

	const unsigned int left_child = 2*parent + 1;
	const unsigned int right_child = 2*parent + 2;

	unsigned int largest = parent;

	if (left_child < size && array[left_child] > array[largest]) {
		largest = left_child;
	}

	if (right_child < size && array[largest] < array[right_child]) {
		largest = right_child;
	}

	// parent was swapped
	if (parent != largest) {
		swap(&array[largest], &array[parent]);
		max_heapify(array, largest, size); // does subtree we swapped  with follows heap property?
	}
}

void heapsort(int array[], unsigned int size)
{
	// build the heap for first time; O(n) complexity
	build_heap(array, size);

	// top element is max, shrink the array size and work on the remaining
	for (int end = size-1; end > 0; --end) {
		std::cout << end << "|";
		print_array(array, size);

		swap(&array[0], &array[end]);
		heapify(array, 0, end);
	}
}

int main()
{
	int array[] = {2, 1, 0, 5, 4, 10, 6, -1};
	unsigned int size = sizeof(array)/sizeof(array[0]);

	std::cout << "before:";
	print_array(array, size);

	// heapify = &max_heapify;
	heapsort(array, size);

	std::cout << "final:";
	print_array(array, size);

	return 0;
}
