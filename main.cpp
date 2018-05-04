/*

Joseph Bailey Moore
Final Project
main.cpp
Cosc 2030
Started: 5/1/18

Menu and testing interface for final proj

*/

#include"Algorithms.h"
#include"RandomUtilities.h"
#include"GeneralHashFunctions.h"
#include <string>
#include <iostream>
#include <vector>

using std::vector;

using namespace std;

vector<int> manual();
void vecPrint(vector<int> vec);
vector<int> getNums();
int stringToInt(string s);
vector<int> makeUnique(vector<int> vec);

int main()
{

	cout << "Please select an option\n1: Quicksort\n2: Mergesort\n3: Binary Search\n4: Hash Function\n5: Bloom Filter\n";

	short choice = 0;
	cin >> choice;

	vector<int> vec,test;
	int choice2 = 0;	//aparently cant define vars in cases so i recyled this var many times
	int target = 0;
	string c="";

	switch (choice) {
	case 1:

		cout << "Press 1 for manual vecotor creation or 2 for random automatic creation\n";
		
		cin >> choice2;
		if (choice2 == 1)
		{
			vec = manual();
		}
		else {
			vec = getNums();
		}
		vec=QuickSort(vec);
		cout << "Printing Vector after QuickSort\n";
		vecPrint(vec);

		test = vec;
		sort(test.begin(), test.end());
		if (vec == test)
		{
			cout << "The vector is sorted succesfully\n";
		}
		else {
			cout << "There was a sorting error\n";
		}

		break;
	case 2:
		
		cout << "Press 1 for manual vecotor creation or 2 for random automatic creation\n";

		cin >> choice2;
		if (choice2 == 1)
		{
			vec = manual();
		}
		else {
			vec = getNums();
		}
		vec = mergeSort(vec);
		cout << "Printing Vector after mergeSort\n";
		vecPrint(vec);

		test = vec;
		sort(test.begin(), test.end());
		if (vec == test)
		{
			cout << "The vector is sorted succesfully\n";
		}
		else {
			cout << "There was a sorting error\n";
		}

		break;
	case 3:

		cout << "Press 1 for manual vecotor creation or 2 for random automatic creation\n";

		cin >> choice2;
		if (choice2 == 1)
		{
			vec = manual();
		}
		else {
			vec = getNums();
		}
		vec=QuickSort(vec);		//my quicksort has proven itself many times already
		vec = makeUnique(vec);
		cout << "Here is the vector (may be a bit smaller to ensure vector is unique)\n";
		vecPrint(vec);

		cout << "Please enter the target for the search\n";
		cin >> target;
		choice2 = binarySearch(vec,target,-1,-1);
		if (choice2 == -1)
		{
			cout << "The Target was not found" << endl;
		}
			else 
			{
				cout << "The Target was found at index value " << choice2 << endl;

				if (vec.at(choice2) == target)
				{
					cout << "Binary Search Successful\n";
				}
				else
				{
				cout << "Binary Search Failed\n";
				}
		
		}
		
		//cout << "Printing Vector for debugging\n";
		//vecPrint(vec);	

		break;

	case 4:

	cout << "Type 1 for int hashing, 2 for string hashing or 3 for unit testing\n";
	cin >> choice2;
	if (choice2 == 1)
	{
	cout << "Please insert an int to be hashed or -999 to quit\n";
	do
	{
		cin >> choice2;
		if (choice2 != -999)
		{
			choice2 = myHash(choice2);
			cout << "The outputed hash was: " << choice2 << endl << endl;
		}
	} while (choice2 != -999);
	}
	if (choice2 == 2)
	{

		cout << "Please insert a string to be hashed or -999 to quit\n";
		do
		{
			cin >> c;
			if (c != "-999")
			{

				choice2 = stringToInt(c);			// I am adding al the ascII values of the string together to get an int then gonna hash it
				//cout << choice2 << endl;
				choice2 = myHash(choice2);
				cout << "The outputed hash was: " << choice2 << endl << endl;
		}
	} while (c != "-999");

	}
	if (choice2 == 3)
	{
		vector<int> in;
		int table[8192];
		for (int i = 0; i < 8192; i++)//cleaning the array
		{
			table[i] = 0;
		}
		in = getNums();
		in = QuickSort(in);
		in = makeUnique(in);	//for my make unique function to work it must be sorted
		int collissions = 0;

		for (int i = 0; i < in.size(); i++)	//going through the vector and hashing the value and adding to the array
		{
			int temp = in.at(i);
			temp = myHash(temp);
			table[temp]++;
		}

		for (int i = 0; i < 8192; i++)
		{
			if (table[i] > 1)			//finding collisions in the array
			{
				collissions += (table[i] - 1);
			}
		}
		/*for (int i = 0; i < 8192; i++)
		{
			cout << i << ":\t" << table[i] << endl;		//debugging the function
		}*/
		cout << "There were " << collissions << " collissions found with " << in.size() << " unique numbers\n";

	}

	break;

	case 5:
		
		bool table[8192];

		for (int i = 0; i < 8192; i++)
		{
			table[i] = false;
		}
		
		cout << "Please enter 1 for manual tests or 2 for automatic test\n";

		cin >> choice2;

		if (choice2 == 1)
		{
			cout << "Please enter strings to add or -999 to move on\n";
			do
			{
				cin >> c;
				if (c != "-999")
				{
					table[myHash(stringToInt(c))] = true;
					int temp = (RSHash(c)) % 8192;
					table[temp] = true;
					temp= (JSHash(c)) % 8192;
					table[temp] = true;
				}

			}while(c != "-999");
			cout << "Please enter strings to test for presence or -999 to quit\n";
			do
			{
				cin >> c;
				if (c != "-999")
				{
					int test[3];	//the three hash values

					test[0] = myHash(stringToInt(c));
					test[1] = (RSHash(c)) % 8192;
					test[2] = (JSHash(c)) % 8192;
					
					if (table[test[0]] && table[test[1]] && table[test[2]])	//if they all link to true values it must exist in here
					{
						cout << "The string is in the bloom filter\n";
					}
					else {
						cout << "The string is not in the bloom filter\n";
					}
				}

			} while (c!= "-999");
		}
		if (choice2 == 2)
		{
			vector<int> testInts;//im gonna convert these to strings for the other 
			testInts = getNums();
			testInts = QuickSort(testInts);	
			testInts = makeUnique(testInts);
			int fails = 0;
			for (int i = 0; i < testInts.size(); i++)	//since myHash takes ints I decided to hash the values with this hash first before I convert it to strings
			{
				table[myHash(testInts.at(i))] = true;
				table[(RSHash(to_string(testInts.at(i))) % 8192)] = true;
				table[(JSHash(to_string(testInts.at(i))) %  8192)] = true;
			}
			
			cout << "Please enter how many tests to be done\n";
			cin >> choice2;

			for (int i = 0; i < choice2; i++)
			{

				int temp = randInt(0, 8192);
				bool filtered;	//will be true if the value is in the testInts
				if (binarySearch(testInts,temp,-1,-1) == -1)
				{
					filtered = false;
				}
				else
				{
					filtered = true;
				}
				int test[3];

				test[0] = myHash(temp);
				test[1] = (RSHash(to_string(temp))) % 8192;
				test[2] = (JSHash(to_string(temp))) % 8192;

				if (table[test[0]] && table[test[1]] && table[test[2]])
				{
					if (!filtered)
					{
						fails++;
					}
				}
				else
				{
					if (filtered) 
					{
						fails++;
					}
				}
			}
			cout << "With " << testInts.size() << " numbers inside the filter and " << choice2 << " random numbers tested the bloom filter had " << fails << " error(s)\n";

		}
		break;
	}
	system("pause");
	return 0;
}

//manual vector creation for debugging
vector<int> manual()
{
	vector<int> vec;

	cout << "Type doubles to add to the vector or -999 to quit\n";
	double temp = 0;
	do
	{
		cin >> temp;
		if (temp != -999)
			vec.push_back(temp);
	} while (temp != -999);
	return vec;
}

void vecPrint(vector<int> vec)	//I dont like the default vector print function so I always make my own
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << i << ":\t" << vec.at(i) << endl;
	}
}

vector<int> getNums()		//stolen from lab7 and modded to read in inputs within and use ints
{
	int minNum, maxNum;
	int listSize;
	cout << "Please input the size of the vector, max and min values\n";

	cin >> listSize >> maxNum >> minNum;

	vector<int> theList;
	for (int i = 0; i < listSize; i++)
	{
		theList.push_back(randInt(minNum, maxNum));
	}
	return theList;
}

int stringToInt(string s)	//adding all the ascii values together to get a int that myHash will take
{
	int ret = 0;
	for (char c : s)
	{
		ret += c;
	}
	return ret;
}

vector<int> makeUnique(vector<int> vec)		//vector must be sorted before entering
{

	vector<int> temp;
	temp.push_back(vec.at(0));
	for (int i = 1; i < vec.size(); i++)
	{
		if (vec.at(i) > temp.at(temp.size() - 1))
		{
			temp.push_back(vec.at(i));
		}
	}
	return temp;

}