// lab1-16313.cpp : This file contains the 'main' function. Program execution begins and ends there.
//HEAP and Counting sort

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <chrono> 
#include "windows.h"
#include <ctime>
#include <exception>



using namespace std::chrono;
using namespace std;

void CountingSort(int *arrayF, int *res, int maxBr, int brElem);
void ComparationSort(int numEl);
void GenerateNumber(int numOfEl, int *arrayEl);
void HeapSort(int *arrayUnorder, int numOfEl);

int main()
{
	
	
	ComparationSort(100);
	cout << "\n\n";
	
	ComparationSort(1000);
	cout << "\n\n";
	ComparationSort(10000);
	cout << "\n\n";
	ComparationSort(100000);
	cout << "\n\n";
	ComparationSort(1000000);
	cout << "\n\n";
	ComparationSort(10000000);
	cout << "\n\n";
	ComparationSort(100000000);




}



void ComparationSort(int numEl)
{
	int *arrayUnorder = new int[numEl];
	int *arrayOrder = new int[numEl];
	GenerateNumber(numEl, arrayUnorder);
	CountingSort(arrayUnorder, arrayOrder, 999, numEl);
	HeapSort(arrayUnorder, numEl); //odkomentarisi

	
}

 void GenerateNumber(int numOfEl, int *arrayEl)
{
	 for (int i = 0; i < numOfEl; i++)
	 {
		 arrayEl[i] = rand() % 1000;
	 }
}
 const char* Number(int numEl)
 {
	 const char* str = new char[10];
	 switch (numEl)
	 {
	 case 1000000: return str="1M";
		 break;
	 case 10000000:return str = "10M";
		 break;
	 case 100000000: return str = "100M";
		 break;
	 case 1000: return str = "1k";
		 break;
	 case 10000: return str = "10k";
		 break;
	 case 100000: return str = "100k";
		 break;
	 default:
		 return str = "nije ukljuceno to --- proveriii ";

	 }

 }
	void CountingSort(int *arrayF, int *res, int maxBr, int brElem)
	{
		
		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);	
		DWORDLONG totalPhysMem = memInfo.ullTotalPhys;

		cout << "Counting sort for ";
		if (brElem < 1000)
			cout << brElem;
		else
			cout << Number(brElem);
		cout << " elements -> ";

		auto start = high_resolution_clock::now();
		

		//int brElemenata = brElem;
		int *pomArray = new int[maxBr];
		for (int i = 0; i <= maxBr; i++) //int i = 0; i < maxBr; i++
		{
			pomArray[i] = int( 0);
		}
		for (int j = 0; j < brElem; j++)
		{
			pomArray[arrayF[j] ]++;
		}
		for (int i = 1; i <= maxBr; i++) //int i = 0; i < maxBr; i++
		{
			pomArray[i] = pomArray[i] + pomArray[i - 1] - 1; //-1 jer se array od 0 racuna
		}
		for (int j = brElem - 1; j >= 0; j--)
		{
			
			res[pomArray[arrayF[j]] ]= arrayF[j];
			pomArray[arrayF[j]]--;
		}

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count() << " microseconds" << endl;

		DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
		cout << "memory: " << physMemUsed;
	}



 int Parent(int i) //i je indeks 
 {
	 return i / 2 - 1;
 }

 int Left(int i)
 {
	 return (2 * i + 1);
 }

 int Right(int i)
 {
	 return 2 * i + 2;
 }





	void Heapify(int *arrayF, int i, int heapSize)
	{
		int largest;
		int l = Left(i);
		int r = Right(i);
		if (l < heapSize && arrayF[l] > arrayF[i])
			largest = l;
		else
			largest = i;
		if (r < heapSize && arrayF[r] > arrayF[largest])
			largest = r;
		if (largest != i)
		{
			int pom = arrayF[i];
			arrayF[i] = arrayF[largest];
			arrayF[largest] = pom;

			Heapify(arrayF, largest, heapSize);
		}

	}

	void BuildHeap(int *arrayUnorder, int numOfEl)
	{
		int heapSize = numOfEl;
		for (int i = numOfEl / 2 - 1; i >= 0; i--)
			Heapify(arrayUnorder, i, numOfEl);

	}
	
	
	void HeapSort(int *arrayUnorder, int numOfEl)
	{

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);
		DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
		
			cout << " \n";
			cout << "Heap sort for ";
			if (numOfEl < 1000)
				cout << numOfEl;
			else
				cout << Number(numOfEl);
			cout << " elements -> ";
			int heapSize = numOfEl;
	
		auto start = high_resolution_clock::now();

		BuildHeap(arrayUnorder,numOfEl);
		for (int i = heapSize - 1; i >= 1; i--)
		{
			int pom = arrayUnorder[0];
			arrayUnorder[0] = arrayUnorder[i];
			arrayUnorder[i] = pom;
			heapSize--;
			Heapify(arrayUnorder, 0, heapSize);

		}

		auto stop = high_resolution_clock::now();		
		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count() << " microseconds" << endl;


		DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
		cout << "memory: " << physMemUsed;

	}

	

	
