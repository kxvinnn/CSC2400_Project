#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <random>

using namespace std;

string getName(int length)
{
	string name;
	int n_size = 0;
	int v_start;
	
	char consonents[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
	char vowels[] = {'a','e','i','o','u','y'};
	
	
	v_start = rand();
	if( v_start % 2 == 1 )
	{
		name = name + vowels[rand() % 6];
		n_size = n_size + 1;
	}
	else
	{
		name = name + consonents[rand() % 20];
		n_size = n_size + 1;
		name = name + vowels[rand() % 6];
		n_size = n_size + 1;
	}
		
	
	while(n_size < length)
	{
		if( (length - n_size) > 3)
		{
			for (int i = rand() % 2; i < 3; i++)
			{
				name = name + consonents[rand() % 20];
				n_size = n_size + 1;
			}
		}
		else if (n_size < length)
		{
			name = name + consonents[rand() % 20];
			n_size = n_size + 1;
		}
		if( n_size < length)
		{
			name = name + vowels[rand() % 6];
			n_size = n_size + 1;
		}
	}
	
	return name;
}

string getID()
{
	char ID[20];
	char myChar [36] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z','a','e','i','o','u','y','0','1','2','3','4','5','6','7','8','9'};
	for (int i = 0; i < 20; i++)
	{
		ID[i] = myChar[rand() % 36];
	}
	
	string newID = ID;
	return newID;
}

float getVal()
{
	float val;
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	int i = rand() % 11;
	
	val = r + i;
	
	return val;
}

int getS_Hour()
{
	int hour = rand() % 24;
	return hour;
}

int getMin()
{
	int min;
	min = rand() % 60;
	
	return min;
}

int getE_Hour(int S_Hour)
{
	int E_Hour;
	int range = 24 - S_Hour + 1;
	
	E_Hour = rand() % range + S_Hour;
	
	if(E_Hour == S_Hour)
	{
		E_Hour = E_Hour + 1;
	}
	
	return E_Hour;
}

int getMonth(int maxMonth, int minMonth)
{
	int month;
	int range;
	range = maxMonth - minMonth + 1;
	month = rand() % range + minMonth;
	return month;
}

int getDay()
{
	int day;
	day = rand() % 30;
	day = day + 1;
	return day;
}

int main()
{
	srand(time(NULL));
	string name;
	string ID;
	float val;
	int S_Hour;
	int S_Min;
	int E_Hour;
	int E_Min;
	int month;
	int date;
	
	int size;
	int sMonth;
	int eMonth;
	
	string file_name;
	
	cout << "What will you name the file?" << "\n" << "File name:";
	cin >> file_name;
	cout << "\n\n";
	
	ofstream MyFile(file_name);
	
	cout << "How many items do you wish to generate?" << "\n";
	cout << "Num elements: ";
	cin >> size;
	cout << "\n\n";
	
	MyFile << size << "\n";
	
	cout << "What is the first month we will generate for?" << "\n" << "First month (1-12):";
	cin >> sMonth;
	cout << "\n" << "What is the last month we will generate for?" << "\n" << "Last monght (1-12):";
	cin >> eMonth;
	cout << "\n\n";
	
	for(int i = 0; i < size; i++)
	{
		name = getName(1 + rand() % 20);
		MyFile << name << "\n";
		ID = getID();
		MyFile << ID << "\n";
		val = getVal();
		MyFile << val << "\n";
		S_Hour = getS_Hour();
		S_Min = getMin();
		MyFile << S_Hour << "\n"; 
		MyFile << S_Min << "\n";
		E_Hour = getE_Hour(S_Hour);
		if(E_Hour == 24)
		{
			E_Min = 0;
		}
		else
		{
			E_Min = getMin();
		}
		MyFile << E_Hour << "\n";
		MyFile << E_Min << "\n";
		month = getMonth(eMonth, sMonth);
		MyFile << month << "\n";
		date = getDay();
		MyFile << date << "\n";
	}
	
	cout << "File Generated. Have a nice day!";
	
	MyFile.close();
	
	return 1;
}