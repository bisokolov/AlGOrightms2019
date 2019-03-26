#include <iostream>


struct TreeNode {
	int data;
	TreeNode * left;
	TreeNode * right;
};

TreeNode * recurisiveSplit(int * arr,int size, int left, int right) {
	if (size == 1 && left != right) {
		
		return nullptr;
		
	}

	if (size == 1) {
		TreeNode * leaf = new TreeNode{ arr[left],nullptr,nullptr };
		
		return leaf;
		

	}
	
	/*
	if (size == 2) {
		TreeNode *
	}
	*/
	
	int median = size / 2;

	
	TreeNode * leftChild = recurisiveSplit(arr, median, left, left + median-1);
	TreeNode * rightChild = recurisiveSplit(arr, size - median, median, right + median);
	TreeNode * middle = new TreeNode{ arr[median],leftChild,rightChild };
	
	return middle;
}


TreeNode * Transform(int * arr, int size) {
	int med = size / 2;

	

	TreeNode * tPtr = recurisiveSplit(arr, med, 0, size - 1);
	

	return tPtr;
}


int main() {
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	TreeNode * ptr = Transform(arr, 10);
	std::cout << ptr->data;

	system("pause");
	return 0;
}