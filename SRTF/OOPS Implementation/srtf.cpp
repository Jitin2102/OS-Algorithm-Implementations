#include <climits>
#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid, arrival, burst, remaining, completion, turnaround, waiting;
};

void inputProcesses(vector<Process>& p, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival and burst time for P" << i + 1 << ": ";
        p[i].pid = i + 1;
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
    }
}

void srtfScheduling(vector<Process>& p, int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, minRemaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 &&
                p[i].remaining < minRemaining) {
                minRemaining = p[i].remaining;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].remaining--;
            time++;
            if (p[idx].remaining == 0) {
                completed++;
                p[idx].completion = time;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
            }
        } else {
            time++;  // CPU idle
        }
    }
}

void printTable(const vector<Process>& p, int n) {
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].completion << "\t" << p[i].turnaround << "\t"
             << p[i].waiting << "\n";
    }
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    inputProcesses(p, n);
    srtfScheduling(p, n);
    printTable(p, n);

    return 0;
}
