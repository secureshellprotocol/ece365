#include <vector>
#include <stdio>

class Heap{
	public:
		Heap* allocHeap(int size);
		int removeIndex(int index);

	private:
		void percolateUp();	

		int size;

}
