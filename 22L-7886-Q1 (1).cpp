//AZFAR NAYYAN 22L-7886.
//ASSIGNMENT NUMBER 05 DATA STRUCTURES.
//BSE-3C


#include<iostream>
#include<Windows.h>
using namespace std;


class IntervalHeap
{

private:
	int currSize;
	int maxsize;
	int** intervalHeap;
	bool createNewNode;

	void heapUpMinHeap(int ele[], int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (ele[parent] > ele[bottom])
			{
				swap(ele[parent], ele[bottom]);
				heapUpMinHeap(ele, root, parent);
			}
		}
	}
	void heapUpMaxHeap(int ele[], int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (ele[parent] < ele[bottom])
			{
				swap(ele[parent], ele[bottom]);
				heapUpMaxHeap(ele, root, parent);
			}
		}
	}
	void heapDownMinHeap(int elements[], int root, int bottom)
	{
		int minChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom) 
		{ 
			if (leftChild == bottom) 
				minChild = leftChild;
			else 
			{
				if (elements[leftChild] >= elements[rightChild])
					minChild = rightChild;
				else
					minChild = leftChild;
			}
			if (elements[root] > elements[minChild]) 
			{
				swap(elements[root], elements[minChild]);
				heapDownMinHeap(elements, minChild, bottom);
			}
		}
	}
	void heapDownMaxHeap(int elements[], int root, int bottom)
	{
		int maxChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom)
		{
			if (leftChild == bottom)
				maxChild = leftChild;
			else
			{
				if (elements[leftChild] <= elements[rightChild])
					maxChild = rightChild;
				else
					maxChild = leftChild;
			}
			if (elements[root] < elements[maxChild])
			{
				swap(elements[root], elements[maxChild]);
				heapDownMaxHeap(elements, maxChild, bottom);
			}
		}
	}
	void printHeapTree(int heap[], int size)
	{
		int height = static_cast<int>(log2(size));
		int currentIndex = 0;

		for (int level = 0; level <= height; ++level)
		{
			int elementsInLevel = min(static_cast<int>(pow(2, level)), size - currentIndex);

			for (int i = 0; i < pow(2, height - level) - 1; ++i)
			{
				cout << " ";
			}

			for (int i = 0; i < elementsInLevel; ++i) 
			{
				cout << heap[currentIndex++];
				if (i < elementsInLevel - 1)
				{
					
					for (int j = 0; j < pow(2, height - level + 1) - 1; ++j) 
					{
						cout << " ";
					}
				}
			}

			cout << endl;
		}
	}



public:
	IntervalHeap()
	{
		maxsize = 100;
		currSize = 0;
		intervalHeap = new int* [2];
		intervalHeap[0] = new int[maxsize];
		intervalHeap[1] = new int[maxsize];
		for (int i = 0; i < maxsize; i++)
		{
			intervalHeap[0][i] = 0;
			intervalHeap[1][i] = 0;
		}
		createNewNode = true;
	}
	IntervalHeap(int m)
	{
		maxsize = m;
		currSize = 0;
		intervalHeap = new int* [2];
		intervalHeap[0] = new int[maxsize];
		intervalHeap[1] = new int[maxsize];
		for (int i = 0; i < maxsize; i++)
		{
			intervalHeap[0][i] = 0;
			intervalHeap[1][i] = 0;
		}
		createNewNode = true;
	}
	void insert(int d)
	{
		if (currSize == maxsize)
		{
			cout << "HEAP IS FULL NO INSERTION!!" << endl;
			return;
		}

		if (createNewNode == true)
		{
			currSize++;
			intervalHeap[0][currSize - 1] = d;
			intervalHeap[1][currSize - 1] = d;
			createNewNode = false;

			if (d <= intervalHeap[1][0])
				heapUpMinHeap(intervalHeap[0], 0, currSize - 1);
			else if (d > intervalHeap[1][0])
				heapUpMaxHeap(intervalHeap[1], 0, currSize - 1);
		}
		else
		{
			if (d <= intervalHeap[1][0])
			{
				intervalHeap[0][currSize - 1] = d;
				heapUpMinHeap(intervalHeap[0], 0, currSize - 1);
				createNewNode = true;
			}
			else if (d > intervalHeap[1][0])
			{
				intervalHeap[1][currSize - 1] = d;
				heapUpMaxHeap(intervalHeap[1], 0, currSize - 1);
				createNewNode = true;
			}
			else
			{
				cout << "NAHI HO SAKTI INSERTION" << endl;
			}
		}
	}
	void display()
	{
		cout << "Interval Heap:" << endl;

		for (int i = 0; i < currSize; i++)
		{
			cout << "[" << intervalHeap[0][i] << ", " << intervalHeap[1][i] << "] ";
		}
		cout << endl << endl;

		cout << "INTERVAL HEAP FOR MIN HEAP: " << endl;
		printHeapTree(intervalHeap[0], currSize);
		cout << endl;
		cout << "INTERVAL HEAP FOR MAX HEAP: " << endl;
		printHeapTree(intervalHeap[1], currSize);
		cout << endl;
	}
	void update(int left, int right)
	{
		if (currSize == 0)
		{
			cout << "NO ELEMENT TO UPDATE!" << endl;
			return;
		}

		intervalHeap[0][0] = left;
		intervalHeap[1][0] = right;

		heapDownMinHeap(intervalHeap[0], 0, currSize - 1);
		heapDownMaxHeap(intervalHeap[1], 0, currSize - 1);
	}
	void Delete()
	{
		if (currSize == 0)
		{
			cout << "NO ELEMENT TO DELETE!" << endl;
			return;
		}

		int temp1 = intervalHeap[0][currSize - 1];
		int temp2 = intervalHeap[1][currSize - 1];

		intervalHeap[0][0] = temp1;
		intervalHeap[1][0] = temp2;

		currSize--;

		heapDownMinHeap(intervalHeap[0], 0, currSize - 1);
		heapDownMaxHeap(intervalHeap[1], 0, currSize - 1);
	}
	~IntervalHeap()
	{
		delete[] intervalHeap[0];
		delete[] intervalHeap[1];
		delete[] intervalHeap;
	}
};

int main()
{
	//IntervalHeap myIH;
	//myIH.insert(40);
	//myIH.insert(1);
	//myIH.insert(30);
	//myIH.insert(2);
	//myIH.insert(20);
	//myIH.insert(3);
	//myIH.insert(0);
	//myIH.insert(50);
	//myIH.display();
	//myIH.update(7, 100);
	//myIH.display();
	//myIH.Delete();
	//myIH.display();

	int sleepTime = 1500;
	int s;
	cout << "Enter the maximum size of the Interval Heap: ";
	cin >> s;
	IntervalHeap intervalHeap(s);
	system("cls");

	int choice = 0;
	while (choice != 5) 
	{
		cout << "Interval Heap Operations" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Display" << endl;
		cout << "3. Update" << endl;
		cout << "4. Delete" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) 
		{
			int data;
			cout << "Enter data to insert: ";
			cin >> data;
			intervalHeap.insert(data);
			
			Sleep(sleepTime);
			system("cls");
		}
		else if (choice == 2) 
		{
			intervalHeap.display();
			Sleep(3000);
			system("cls");
		}
		else if (choice == 3) 
		{
			int left, right;
			cout << "Enter new left and right values to update the root: ";
			cin >> left;
			cin >> right;
			intervalHeap.update(left, right);
			Sleep(sleepTime);
			system("cls");
		}
		else if (choice == 4) 
		{
			intervalHeap.Delete();
			cout << "Root interval deleted from heap" << endl;
			Sleep(sleepTime);
			system("cls");
		}
		else if (choice == 5) 
		{
			cout << "ja raha hoon bye" << endl;
		}
		else 
		{
			cout << "sahi option choose kro !." << endl;
			Sleep(sleepTime);
			system("cls");
		}
	}
	

	system("pause>0");
	return 0;

	//assignment 05 q1
}