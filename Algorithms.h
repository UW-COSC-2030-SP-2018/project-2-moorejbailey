/*

Joseph Bailey Moore
Final Project
Algorithms.h
Cosc 2030
Started: 5/1/18

A place to store all of my written algorithms

*/

#pragma once
#include<iostream>
#include<vector>

using std::vector;
using namespace std;

int binarySearch(vector<int> vec, int target, int upper, int lower);

vector<int> QuickSort(vector<int> vec1);
vector<int> mergeSort(vector<int> vec);
vector<int> mergeVecotrs(vector<int> vec1, int mid, vector<int> vec2);
int myHash(int);

vector<int> QuickSort(vector<int> vec1) {   //I stole this from the lab


	if (vec1.size() <= 1)
	{

		return vec1;

	}

	vector<int> low;
	vector<int> high;
	double pivot = vec1.at(0);

	for (int i = 1; i < vec1.size(); i++)
	{

		if (vec1.at(i) <= pivot)
		{
			low.push_back(vec1.at(i));
		}
		else
		{
			high.push_back(vec1.at(i));
		}

	}

	low = QuickSort(low);
	high = QuickSort(high);

	vector<int> merge;

	if (low.size() == 0)
	{
		merge.push_back(pivot);
		merge.insert(merge.end(), high.begin(), high.end());
	}
	if (high.size() == 0)
	{
		merge.insert(merge.end(), low.begin(), low.end());
		merge.push_back(pivot);
	}
	else {
		merge = mergeVecotrs(low, pivot, high);
	}

	return merge;
}

vector<int> mergeVecotrs(vector<int> vec1, int mid, vector<int> vec2)
{

	vector<int> merge;
	/*
	merge.reserve(vec1.size() +1+ vec2.size());
	merge.insert(merge.end(), vec1.begin(), vec1.end());					//based off of this https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors
	merge.push_back(mid);
	merge.insert(merge.end(), vec2.begin(), vec2.end());
	*/

	for (int i = 0; i < vec1.size(); i++)
	{
		merge.push_back(vec1.at(i));
	}
	merge.push_back(mid);
	for (int i = 0; i < vec2.size(); i++)
	{
		merge.push_back(vec2.at(i));
	}

	return merge;
}

vector<int> mergeSort(vector<int> vec)
{
	
	if (vec.size() <= 1)
	{
		return vec;
	}
	else
	{
		vector<int> low;
		vector<int> high;

		for (int i = 0; i < vec.size(); i++)
		{
			if (i < vec.size() / 2)
			{
				low.push_back(vec.at(i));
			}
			else
			{
				high.push_back(vec.at(i));
			}
		}

		low = mergeSort(low);
		high = mergeSort(high);

		vector<int> merge;
		int l = 0, h = 0;	//iterators for low and high vectors
		cout << low.size() << " " << high.size() << endl;
		if (low.size() == 0)
		{
			return high;
		}
		else if (high.size() == 0)
		{
			return low;
		}
		else{
			do
			{
				cout << l << " " << h << endl;
				if (l == low.size())
				{
					while (h != high.size())
					{
						merge.push_back(high.at(h));
						h++;
					}
				}
				else if (h == high.size())
				{
					while (l != low.size())
					{
						merge.push_back(low.at(l));
						l++;
					}
				}
				else {
					if (low.at(l) < high.at(h))
					{
						merge.push_back(low.at(l));
						l++;
					}
					else
					{
						merge.push_back(high.at(h));
						h++;
					}
				}

			} while (merge.size()<vec.size());

			return merge;
		}
		

	}
}

int binarySearch(vector<int> vec, int target, int upper, int lower)	//gonna return the index of the value or -1
{

	if (vec.size() == 0)
	{
		return -1;
	}

	//I am going to set upper and lower to -1 whenever I call this function and have it find them automatically on the first time
	
	if (upper == -1)
	{
		lower = 0;
		upper = vec.size()-1;
	}

	if (vec.size()-2 == lower&&vec.at(upper)!=target)
	{
		return -1;
	}
	else if (upper == 1 && vec.at(0) != target)
	{

		return -1; 
	}
	else if ((upper)-1 == lower&&vec.at(upper)!=target&&vec.at(lower)!=target)
	{
		return-1;
	}
	else
	{

		
		int midpoint = (upper+lower) / 2;
		//cout << midpoint << endl;
		if (target > vec.at(midpoint))
		{
			return binarySearch(vec, target, upper, midpoint);
		}
		else if (target < vec.at(midpoint))
		{
			return binarySearch(vec, target, midpoint, lower);
		}
		else
		{
			return midpoint;
		}
	}
}

int myHash(int in)
{

	in *= 71;
	in += 63;
	in *= in;
	in /= 17;
	in--;
	in *= 888;
	in /= 13;

	if (in < -1)
		in *= -1;

	return (in % 8191);

}