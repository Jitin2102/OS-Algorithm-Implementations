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
    printf("Enter no of processes : ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time & Burst Time for p%d : ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int current_time = 0;
    float total_waiting_time = 0, total_turnaround = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival) current_time = p[i].arrival;
        current_time += p[i].burst;
        p[i].completion = current_time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        total_waiting_time += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT \n");
    for (int i = 0; i < n; i++) {
        printf("p%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }
    printf("\nAverage Waiting Time :%.2f", total_waiting_time / n);
    printf("\nAverage Waiting Time: %.2f", total_turnaround / n);

    return 0;
}
