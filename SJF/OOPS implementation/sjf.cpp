#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Process {
   public:
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    bool done;

    Process(int id, int at, int bt) {
        pid = id;
        arrival = at;
        burst = bt;
        completion = turnaround = waiting = 0;
        done = false;
    }
};

class SJF {
   private:
    vector<Process> processes;

   public:
    void addProcess(int pid, int arrival, int burst) {
        processes.push_back(Process(pid, arrival, burst));
    }

    void schedule() {
        int n = processes.size();
        int current_time = 0, completed = 0;
        double total_waiting = 0, total_turnaround = 0;

        while (completed < n) {
            int idx = -1;
            int min_burst = 1e9;

            for (int i = 0; i < n; i++) {
                if (!processes[i].done &&
                    processes[i].arrival <= current_time &&
                    processes[i].burst < min_burst) {
                    min_burst = processes[i].burst;
                    idx = i;
                }
            }

            if (idx == -1) {
                current_time++;
            } else {
                current_time += processes[idx].burst;
                processes[idx].completion = current_time;
                processes[idx].turnaround =
                    processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting =
                    processes[idx].turnaround - processes[idx].burst;

                total_waiting += processes[idx].waiting;
                total_turnaround += processes[idx].turnaround;
                processes[idx].done = true;
                completed++;
            }
        }

        cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
        for (auto& p : processes) {
            cout << "P" << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
                 << p.completion << "\t\t" << p.turnaround << "\t\t"
                 << p.waiting << endl;
        }

        cout << "\nAverage Waiting Time: " << total_waiting / n;
        cout << "\nAverage Turnaround Time: " << total_turnaround / n << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    SJF scheduler;

    for (int i = 0; i < n; i++) {
        int at, bt;
        cout << "Enter Arrival Time and Burst Time for P" << i + 1 << ": ";
        cin >> at >> bt;
        scheduler.addProcess(i + 1, at, bt);
    }

    scheduler.schedule();

    return 0;
}
