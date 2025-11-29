#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "ticket.hpp"

using namespace std;
float greedy_value_time(Scope_Ticket* arr, int size);

//takes the values passed to it and inserts them into a new ticket object
Scope_Ticket NewTicket(string T_name, string ID, float val, int S_hour, int S_min, int E_hour, int E_min, int month, int date) 
{
	Scope_Ticket new_T;
	new_T.T_name = T_name;
	new_T.ID = ID;
	new_T.Val = val;
	new_T.S_hour = S_hour;
	new_T.S_min = S_min;
	new_T.E_hour = E_hour;
	new_T.E_min = E_min;
	new_T.month = month;
	new_T.date = date;
	return new_T;
}

//prints an individual ticket to the standard output.
void printTicket(Scope_Ticket* myTicket)
{
	cout << "My tickets value: " << myTicket->Val << "\n";
	cout << "My tickets start time: " << myTicket->S_hour << "\n";
	cout << "My tickets end time: " << myTicket->E_hour << "\n";
}
//prints every ticket in an array to the standard output.
void printArray(Scope_Ticket* myTicket, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "My tickets value: " << myTicket[i].Val << "\n";
		cout << "My tickets start time: " << myTicket[i].S_hour << "\n";
		cout << "My tickets end time: " << myTicket[i].E_hour << "\n";
	}
}

bool lessThanTicket(Scope_Ticket* first, Scope_Ticket* second)
{
	if(first->month < second->month)
	{
		return true;
	}
	else if(first->month == second->month)
	{
		if(first->date < second->date)
		{
			return true;
		}
		else if(first->date == second->date)
		{
			if(first->S_hour < second->S_hour)
			{
				return true;
			}
			else if(first->S_hour == second->S_hour)
			{
				if(first->S_min <= second->S_min)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
}

void mergeArrayTime(Scope_Ticket* myArray, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	
	Scope_Ticket L[n1];
	Scope_Ticket R[n2];
	
	for(int i = 0; i < n1; i++)
	{
		L[i] = myArray[left + i];
	}
	for(int j = 0; j < n2; j++)
	{
		R[j] = myArray[mid + 1 + j];
	}
	
	int i = 0, j = 0;
	int k = left;
	while( i < n1 && j < n2)
	{
		if(lessThanTicket(&L[i], &R[j]))
		{
			myArray[k] = L[i];
			i++;
		}
		else
		{
			myArray[k] = R[j];
			j++;
		}
		k++;
	}
	
	while(i < n1)
	{
		myArray[k] = L[i];
		i++;
		k++;
	}
	
	while(j < n2)
	{
		myArray[k] = R[j];
		j++;
		k++;
	}
}

void mergeSortTime(Scope_Ticket* myArray, int left, int right)
{
	if(left > right)
	{
		return;
	}
	int mid = left + (right - left) / 2;
	mergeSortTime(myArray, left, mid);
	mergeSortTime(myArray, mid + 1, right);
	mergeArrayTime(myArray, left, mid, right);
}

void sortArrayTime(Scope_Ticket* myArray, int size)
{
	mergeSortTime(myArray, 0, size-1);
}

int menu(Scope_Ticket* myArray, int size)
{
	int u_choice;
	bool done = false; 
	clock_t start;
	clock_t duration;
	float result_greedy;
	
	int c1, c2;
	
	while (!done)
	{
		cout << "\n\n----------\n";
		cout << "Enter: \n1. output all current tickets. \n2: Run greedy algorithm. \n3: Run dynamic programing \n4: load another file." << "\n";
		cout << "5: display the ticket for a specific \n6: Exit the program. \n7:Compare tow tickets. \n8:sort array.\n";
		cout << "---------- \n";
		cin >> u_choice;
		cout << "\n";
		switch(u_choice) {
			
			case 0:
				cout << "Enter 1: output all current tickets. 2: Run greedy algorithm. 3: Run dynamic programing 4: load another file. 5:Exit the program. \n";
				break;
			
			case 1:
				//sends the 
				cout << "---------- \n";
				printArray(myArray, size);
				cout << "---------- \n\n";
				break;
			
			break;
			
			case 2:
				start = clock();
				cout << "This is the start time: " << start << "\n";
				result_greedy = greedy_value_time(myArray, size);
				cout << "The total value from the greedy algorithm is: " << result_greedy << "\n";
				duration = clock() - start;
				cout << "This is how long it took to run: " << (float)duration / CLOCKS_PER_SEC;
				break;
			
			case 3:
				cout << "waiting to be implimented... \n\n";
				break;
			case 4:
				return -1;
				break;
			case 5:
				cout << "The ticket you wish to view? 1-" << size << ":";
				cin >> u_choice;
				cout << "\n\n";
				printTicket(&myArray[u_choice - 1]);
				cout << "----------\n";
				u_choice = 0;
				break;
			case 6:
				cout << "Good Bye;";
				done = true;
				break;
			case 7:
				cout << "Select the first element you wish to compare (1-" << size << "): ";
				cin >> c1;
				cout << "\nSelect the second element you wish to compare (1-" << size << "): ";
				cin >> c2;
				cout << "\n----------\n";
				cout << "This was comparing: \n";
				printTicket(&myArray[c1-1]);
				printTicket(&myArray[c2-1]);
				cout << "This element 1 starts before element 2: " << lessThanTicket(&myArray[c1], &myArray[c2]) << "\n";
				break;
			case 8:
				sortArrayTime(myArray, size);
				cout << "----------\nArray sorted. \n\n";
			default:
			{
				cout << "There was an error. Please enter 1-5. or 0 to see the options again. Or contact administration \n";
				u_choice = -1;
				break;
			}
		}
	}
	return 0;	
}

int main()
{
	//simple bool to keep the program running until we don't want to. And to check if a file was loaded.
	int fine = -1;
	//variable for user to select menu options
	//file name will be placed in to try and load.
	
	//variables for oppening the file and a temp object to be inserted into an array.
	//As well as a pointer that will point to the array we will make by taking the file input.
	string file_name;
	Scope_Ticket temp; 
	Scope_Ticket* myArray;
	
	//The attributes of the class. These variables will be set from the file
	//to then be made into a new object that will be saved into the array.
	string T_name;
	string ID;
	float val;
	int S_hour;
	int S_min; 
	int E_hour;
	int E_min;
	int month;
	int date;
	int size;
	
	cout << "This program is designed to test and run algorithms to solve \"Telescope Scheduling\" problems. \n\n";
	
while(fine < 0)
{
	
	//Get the name of the file we'll use.
	cout << "Enter file name: ";
	cin >> file_name;
	cout << "\n\n";
	fstream Myfile(file_name);
				
				
	//check to see if a file is open. loop until a proper name is given.
	while(!Myfile.is_open())
	{
		Myfile.close();
		cout << "Please enter a valid file name: \n";
		cin >> file_name;
		Myfile.open(file_name);
	}
	//once a proper file is given. Program starts to read from file.
				
	//the first line in any file should be how many items we will get in the array
	Myfile >> size;
	
	//Making the array of the size given. Then reading the file with fstream.
	//it will make a new ticket with each itteration. Then assign the ticket to the slot in the array.
	Scope_Ticket insArray[size];
	for (int i = 0; i < size; i++)
	{
		Myfile >> T_name;
		Myfile >> ID;
		Myfile >> val;
		Myfile >> S_hour;
		Myfile >> S_min;
		Myfile >> E_hour;
		Myfile >> E_min;
		Myfile >> month;
		Myfile >> date;
		temp = NewTicket(T_name, ID, val, S_hour, S_min, E_hour, E_min, month, date);
		insArray[i] = temp;
	}	
	myArray = insArray;
	
	Myfile.close();
	
	fine = menu(myArray, size);
	
}
	
	return 1;
}

