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

    Process(int id, int at, int bt) {
        pid = id;
        arrival = at;
        burst = bt;
        completion = turnaround = waiting = 0;
    }
};

class FCFS {
   private:
    vector<Process> processes;

   public:
    void addProcess(int pid, int arrival, int burst) {
        processes.push_back(Process(pid, arrival, burst));
    }

    void schedule() {
        // Sort by arrival time
        sort(processes.begin(), processes.end(),
             [](Process& a, Process& b) { return a.arrival < b.arrival; });

        int current_time = 0;
        for (auto& p : processes) {
            if (current_time < p.arrival) {
                current_time = p.arrival;  // CPU idle until process arrives
            }
            current_time += p.burst;
            p.completion = current_time;
            p.turnaround = p.completion - p.arrival;
            p.waiting = p.turnaround - p.burst;
        }
    }

    void displayResults() {
        double total_waiting = 0, total_turnaround = 0;

        cout << "\nPID\tAT\tBT\tCT\t\tTAT\t\tWT\n";
        for (auto& p : processes) {
            cout << "P" << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
                 << p.completion << "\t\t" << p.turnaround << "\t\t"
                 << p.waiting << endl;
            total_waiting += p.waiting;
            total_turnaround += p.turnaround;
        }

        cout << "\nAverage Waiting Time: " << total_waiting / processes.size();
        cout << "\nAverage Turnaround Time: "
             << total_turnaround / processes.size() << endl;
    }
};

int main() {
    FCFS scheduler;

    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int at, bt;
        cout << "Enter Arrival Time and Burst Time for P" << i + 1 << ": ";
        cin >> at >> bt;
        scheduler.addProcess(i + 1, at, bt);
    }

    scheduler.schedule();
    scheduler.displayResults();

    return 0;
}

