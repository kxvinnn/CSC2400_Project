#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include "ticket.hpp"
#include "topdown_dp.hpp"
#include <vector>
using namespace std;

struct Ticket {
    int start;   // minute timestamp
    int end;     // minute timestamp
    float value; // scientific value
    int idx;     // original index
};

// Convert month/day + hour/min into an absolute comparable minute count
int toMinuteStamp(/*int month, int day, */int hour, int minute) {
    // Days in months (no leap-year logic needed for scheduling)
    /*static int mdays[13] = {0,
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };*/

    //int daysBefore = 0;
    //for(int m = 1; m < month; m++)
    //    daysBefore += mdays[m];

    //int totalDays = daysBefore + (day - 1);
    //return totalDays * 24 * 60 + hour * 60 + minute;

    return hour * 60 + minute;
}


// Memoization table and p[] array
vector<float> memo;
vector<int> pIndex;         // p[i] = last non-conflicting ticket before i
vector<Ticket> tickets;

// this is the actual topdown DP function
// Return max scientific value achievable using tickets[0..i]
float solveDP(int i) {
    if (i < 0) return 0;
    if (memo[i] != -1) return memo[i];

    // Option A: skip ticket i
    float skip = solveDP(i - 1);

    // Option B: take ticket i
    float take = tickets[i].value + solveDP(pIndex[i]);

    return memo[i] = max(skip, take);
}

// main function to set up before dynamic programming can be called
float telescopeScheduleTopDown(Scope_Ticket arr[], int n) {
    tickets.clear();
    pIndex.clear();
    memo.clear();
    vector<Scope_Ticket> temp_request(arr, arr + n);

    // turning all time variables into minutes and storing it in another vector
    for (int i = 0; i < (int)temp_request.size(); i++) {
        int startTS = toMinuteStamp(
            //temp_request[i].month,
            //temp_request[i].date,
            temp_request[i].S_hour,
            temp_request[i].S_min
        );

        int endTS = toMinuteStamp(
            //temp_request[i].month,
            //temp_request[i].date,
            temp_request[i].E_hour,
            temp_request[i].E_min
        );

        tickets.push_back({
            startTS,
            endTS,
            temp_request[i].Val,   // scientific value
            i                      // original index
        });
    }

    // sorting by the end time before pushing it through the dp
    sort(tickets.begin(), tickets.end(), [](const Ticket &a, const Ticket &b) {
        return a.end < b.end;
    });

    int s = tickets.size();
    pIndex.assign(s, -1);

    // precompute p[i] using binary search
    for (int i = 0; i < s; i++) {
        int lo = 0, hi = i - 1, ans = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (tickets[mid].end <= tickets[i].start) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        pIndex[i] = ans;
    }

    memo.assign(tickets.size(), -1.0f);

    return solveDP(tickets.size() - 1);
}