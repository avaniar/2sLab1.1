#include "Header.h"
#include "Header.cpp"
int main()
{
	RBTree<int,int> tree;
	tree.insert(6, 2);
	tree.insert(9, 2);
	tree.insert(4, 2);
	tree.insert(11, 9);
	tree.insert(10, 8);
	tree.insert(12, 9);
	tree.insert(13, 9);
	tree.insert(3, 8);
	tree.insert(5, 8);
	tree.insert(2, 8);
	tree.insert(1, 8);
	tree.remove(10);
	tree.remove(6);
	tree.find(52);
	tree.get_keys();
	tree.get_values();
	tree.print();
}
