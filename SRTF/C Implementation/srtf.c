#include <limits.h>
#include <stdio.h>
struct Process {
    int pid, arrival, burst, remaining, completion, turnaround, waiting;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival and burst time for P%d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        int minRemaining = INT_MAX;

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
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    return 0;
}
