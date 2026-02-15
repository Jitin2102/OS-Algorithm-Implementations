#include <stdbool.h>
#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
};

int main() {
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    bool done[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time of of P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        done[i] = false;
    }

    int current_time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= current_time &&
                p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            current_time++;
        } else {
            current_time += p[idx].burst;
            p[idx].completion = current_time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            total_waiting += p[idx].waiting;
            total_turnaround += p[idx].turnaround;
            done[idx] = true;
            completed++;
        }
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    printf("Avg WT: %.2f\n", total_waiting / n);
    printf("Avg TAT: %.2f\n", total_turnaround / n);

    return 0;
}
