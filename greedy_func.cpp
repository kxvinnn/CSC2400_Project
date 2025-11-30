#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "ticket.hpp"

using namespace std;
int to_minutes(int hour, int minute);

// definition matches the prototype in ticket.hpp
float greedy_value_time(Scope_Ticket* arr, int size)
{
    // allocate helper arrays
    int   *start_minutes = new int[size];
    int   *end_minutes   = new int[size];
    int   *duration      = new int[size];
    float *score         = new float[size];
    bool  *used          = new bool[size];

    // precompute times, durations, and scores
    for (int i = 0; i < size; i++) {
        start_minutes[i] = to_minutes(arr[i].S_hour, arr[i].S_min);
        end_minutes[i]   = to_minutes(arr[i].E_hour, arr[i].E_min);
        duration[i]      = end_minutes[i] - start_minutes[i];

        used[i] = false;

        if (duration[i] <= 0) {
            score[i] = -1.0f;  // invalid
        } else {
            score[i] = static_cast<float>(arr[i].Val) /
                       static_cast<float>(duration[i]);  // value per minute
        }
    }

    int   current_end = 0;      // earliest time we can start
    float total_value = 0.0f;
    int   total_time  = 0;

    // greedy selection: repeatedly pick best score that doesn't overlap
    while (true) {
        int   best_index = -1;
        float best_score = -1.0f;

        for (int i = 0; i < size; i++) {
            if (used[i])        continue;
            if (score[i] < 0.0f) continue;

            if (start_minutes[i] >= current_end) {  // non-overlapping
                if (score[i] > best_score) {
                    best_score = score[i];
                    best_index = i;
                }
            }
        }

        if (best_index == -1) {
            break;  // no more tickets fit
        }

        used[best_index] = true;
        total_value += arr[best_index].Val;
        total_time  += duration[best_index];
        current_end  = end_minutes[best_index];
    }

    float result = 0.0f;
    if (total_time > 0) {
        result = total_value / static_cast<float>(total_time);
    }

    delete [] start_minutes;
    delete [] end_minutes;
    delete [] duration;
    delete [] score;
    delete [] used;

    return result;
}

// Helper function to minutes
int to_minutes(int hour, int minute) {
    return hour * 60 + minute;
}
