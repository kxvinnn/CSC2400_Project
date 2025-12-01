#include <string>
using namespace std;

class Scope_Ticket {
	public:
	
	//A name and id. Just incase it needs to be used for output. 
	//name will be the group requesting the time
	//id could be used to be implimented in a database
	string T_name;
	string ID;
	
	//the overall scientific value of the request.
	float Val;
	
	// S_hour and minute: The hour and minute the task needs to start.
	// E_hour and min: The hour and minute the task ends. 
	// this seperation is to make math easier when dealing with time.
	// since there is 60 min in an hour.
	int S_hour;
	int S_min; 
	
	int E_hour;
	int E_min;
	
	int month;
	int date;
	
	int score;
};