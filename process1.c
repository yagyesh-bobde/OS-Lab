#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void calculateWaitingTime(struct Process processes[], int n) {
    int total_waiting_time = 0;
    processes[0].waiting_time = 0; // The first process has 0 waiting time

    for (int i = 1; i < n; i++) {
        // Calculate waiting time for process i
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time - processes[i].arrival_time;

        // Ensure waiting time is non-negative
        if (processes[i].waiting_time < 0) {
            processes[i].waiting_time = 0;
        }

        total_waiting_time += processes[i].waiting_time;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void bubbleSort(struct Process processes[], int n) {
    struct Process temp;
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0; // Flag to check if any swapping is done in this pass

        // Last i elements are already in place, so no need to compare them again
        for (int j = 0; j < n - i - 1; j++) {
            // If the current element is greater than the next element, swap them
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                // Swap arr[j] and arr[j + 1]
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
                swapped = 1; // Set the flag to true, indicating a swap occurred
            }
        }

        // If no two elements were swapped in this pass, the array is already sorted
        if (swapped == 0) {
            break;
        }
    }
}

void calculateAverageTime(struct Process processes[], int n) {
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    bubbleSort(processes, n);
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    calculateAverageTime(processes, n);

    return 0;
}
