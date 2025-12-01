#include <bits/stdc++.h>
#include "ticket.hpp"
#include "brute_force.hpp"

using namespace std;

int toMinute(int hour, int minute) {
    return hour * 60 + minute;
}

// brute-force solver: try all subsets
long long bruteForceSchedule(Scope_Ticket* arr, int n)
{
    vector<int> start(n), end(n);
    for (int i = 0; i < n; i++) {
        int startTS = toMinute(arr[i].S_hour, arr[i].S_min);
        int endTS = toMinute(arr[i].E_hour, arr[i].E_min);
        start[i] = startTS;
        end[i]   = endTS;
    }

    long long totalSubsets = 1LL << n;
    long long bestValue = 0;

    // try all subsets
    for (long long mask = 0; mask < totalSubsets; mask++) {

        long long currentValue = 0;
        bool valid = true;

        // check for overlap among chosen tasks
        for (int i = 0; i < n && valid; i++) {
            if (!(mask & (1LL << i))) continue;

            for (int j = i + 1; j < n; j++) {
                if (!(mask & (1LL << j))) continue;

                // overlap check
                if (!(end[i] <= start[j] || end[j] <= start[i])) {
                    valid = false;
                    break;
                }
            }
        }

        if (!valid) continue;

        // compute value
        for (int i = 0; i < n; i++) {
            if (mask & (1LL << i))
                currentValue += arr[i].Val;
        }

        bestValue = max(bestValue, currentValue);
    }

    return bestValue;
}