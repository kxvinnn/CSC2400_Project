#include <iostream>
#include <fstream>
#include "ticket.hpp"

using namespace std;

/*class Scope_Ticket {
  public:
    string T_name;
    string ID;
    float Val;
    int S_hour;
    int S_min;
    int E_hour;
    int E_min;
    int month;
    int date;

    int startMinutes; //disregard
    int endMinutes;   //disregard
};*/

int convertToMinutes(int month, int date, int hour, int min){ //function used to convert day/month to minutes to existing time
  int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //array doesn not account for leap years
  int totalDays = 0;
  for (int i = 0; i < month - 1; i++){ //subtract 1 from month to not account the days in of the current month and only days before current month
    totalDays += daysInMonth[i];
  }
  totalDays += date - 1;//subtract 1 because current date is not yet "done"  
  return totalDays * 1440 + hour * 60 + min;
};

bool compareByEndTime(Scope_Ticket &a, Scope_Ticket &b){//compares which two tickets is less than
  int aEnd = convertToMinutes(a.month, a.date, a.E_hour, a.E_min);
  int bEnd = convertToMinutes(b.month, b.date, b.E_hour, b.E_min);
  return aEnd < bEnd;
};

void sortTicketsByEndTime(Scope_Ticket *ticket, int size){//used brute force bubble sort: big O(n^2)
  for (int i = 0; i < size - 1; i++){
    for (int j = i + 1; j < size; j++){
      if(!compareByEndTime(ticket[i], ticket[j])){// if ticket j time < i time swap
        Scope_Ticket temp = ticket[i];
        ticket[i] = ticket[j];
        ticket[j] = temp;
      }
    }
  }
};

void buildPredecessor(Scope_Ticket *tickets, int size, int *Predecessor){
  for (int i = 0; i < size; i++){
    Predecessor[i] = -1;//initializes first element with no predecessor
    int iStart = convertToMinutes(tickets[i].month, tickets[i].date, tickets[i].S_hour, tickets[i].S_min);
    for (int j = i - 1; j >= 0; j--){//loop used to scan backwards 
      int jEnd = convertToMinutes(tickets[j].month, tickets[j].date, tickets[j].E_hour, tickets[j].E_min);
      if (jEnd <= iStart){
        Predecessor[i]=j; //initialize P[] at index i with the predecessor j
        break;
      }
    }

  }

};

void buildMaxVal(Scope_Ticket *tickets, int size, int *Predecessor, float *Max, int *choice){
  Max[0] = tickets[0].Val;//first ticket will always be included in optimal schedule since no overlap before
  choice[0] = 1;

  for(int i = 1; i < size; i++){//checks for all other tickets 
    float includeValue = tickets[i].Val;
    if (Predecessor[i] != -1){// if there is a predecessor 
      includeValue += Max[Predecessor[i]]; 
    }

    float excludeValue = Max[i-1];

    if (includeValue > excludeValue){
      Max[i] = includeValue;
      choice[i] = 1;
    } else{
      Max[i] = excludeValue;
      choice[i] = 0;
    }

  }
}

int reconstructSchedule(int size, int *Predecessor, int *choice, int *selected){
  int count = 0; 
  int i = size - 1;

  while (i >= 0){
    if (choice[i] == 1){
      selected[count++] = i;
      i = Predecessor[i];
    } else{
      i--;
    }
  }
  return count;
}

float runBottomUpDP(Scope_Ticket *tickets, int size){
  sortTicketsByEndTime(tickets,size);
  int *P = new int[size];
  float *Max = new float[size];
  int *choice = new int[size];
  int *selected = new int[size];

  buildPredecessor(tickets,size,P);
  buildMaxVal(tickets, size, P, Max, choice);
  int count = reconstructSchedule(size, P, choice, selected);
  cout << "\nOptimal Schedule" << endl;
  cout << "-----------------------" << endl;

  for (int i = count - 1; i >= 0; i--){
  int j = selected[i];
  cout << "Ticket Name: " << tickets[j].T_name << endl;
  cout <<"Month: " << tickets[j].month << "/" << tickets[j].date << endl;
  cout << "Start: " << tickets[j].S_hour << ":" << tickets[j].S_min << endl;
  cout << "End: " << tickets[j].E_hour << ":" << tickets[j].E_min << endl;
  cout << "Value: " << tickets[j].Val << endl;
  cout << "----------------------------" << endl;
  }

  cout << "Total schedules produced from initial " << size << " down to" << count << endl;

  float maxScheduleValue = Max[size-1];
  cout << "Maximum Total DP Schedule Value: " << maxScheduleValue << endl;

  delete[] P; 
  delete[] Max; 
  delete[] choice; 
  delete[] selected; 
  return maxScheduleValue;
}
