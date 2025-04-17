#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct ComparePriorityEndStart {
    bool operator()(const pair<pair<int,int>, int>& a, const pair<pair<int,int>, int>& b) {
        if (a.second != b.second)
            return a.second > b.second; //if priority not equal pick greater
        if (a.first.second != b.first.second)
            return a.first.second < b.first.second; //if priority equal then pick early end time
        return a.first.first < b.first.first; //if everything equal pick the earliest meeting start time
    }
};

struct CompareEndStart {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
        return a.first < b.first;
    }
};

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    //int test_cases;
    //inputFile >> test_cases;

    //while (test_cases > 0)
    //{
    int openHours;
    inputFile >> openHours;

    int closeHours;
    inputFile >> closeHours;

    vector<pair<pair<int, int>, int>> rooms; //data structure to store the rooms
    int meetingStart, meetingEnd, priority;

    while (inputFile >> meetingStart >> meetingEnd >> priority) //continue until nothing in input file
    {
        rooms.push_back({{meetingStart, meetingEnd}, priority});
    }

    auto start_time = high_resolution_clock::now();

    sort(rooms.begin(), rooms.end(), ComparePriorityEndStart()); //sorts using comparator

    vector<bool> check(closeHours - openHours, false); //checks if used already

    vector<pair<int, int>> answer;
    int meetingCounter = 0;

    for (auto room : rooms)
    {
        if (room.first.first >= openHours && room.first.second <= closeHours) //check if valid room
        {
            bool canSchedule = true;
            int startTime = room.first.first - openHours;
            int endTime = room.first.second - openHours;

            for (int i = startTime; i < endTime; i++)
            {
                if (check[i])
                {
                    canSchedule = false;
                    break;
                }
            }

            if (canSchedule)
            {
                for (int i = startTime; i < endTime; i++)
                {
                    check[i] = true;
                }
                cout << room.first.first << endl;
                cout << room.first.second << endl;
                answer.push_back(room.first);
                meetingCounter++;
            }
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    sort(answer.begin(), answer.end(), CompareEndStart());
    for (const auto& room : answer)
    {
        outputFile << "[" << room.first << ", " << room.second << "] ";
    }
    outputFile << meetingCounter;
    outputFile << "\nExecution time: " << duration.count() << " microseconds" << endl;
    //test_cases--;
    //}

    inputFile.close();
    outputFile.close();
    return 0;
}