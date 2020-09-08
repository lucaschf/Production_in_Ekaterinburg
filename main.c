#include <stdio.h>
#include <stdlib.h>

#define INCORRECT_SYNTAX "Sintaxe incorreta"
#define UNABLE_TO_OPEN_FILE "Falha ao abrir arquivo"

typedef struct {
    int startTime;
    int processingTime;
} Task;

int comparator(const void *a, const void *b) {
    Task *task = (Task *) a;
    Task *another = (Task *) b;

    if (task->startTime > another->startTime) {
        return 1;
    }

    if (task->startTime < another->startTime)
        return -1;

    return (task->startTime - another->startTime);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("%s", INCORRECT_SYNTAX);
        return 1;
    }

    FILE *output;
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        printf("%s", UNABLE_TO_OPEN_FILE);
        return 1;
    }

    output = fopen(argc == 3 ? argv[2] : "out.txt", "w");
    if (!output) {
        printf("%s", UNABLE_TO_OPEN_FILE);
        return 1;
    }

    int numberOfTasks;
    int time;
    int i;

    while (fscanf(input, "%d", &numberOfTasks) != EOF && numberOfTasks > 0) {
        time = 0;
        Task tasks[numberOfTasks];

        for (i = 0; i < numberOfTasks; i++) {
            fscanf(input, "%d %d", &tasks[i].startTime, &tasks[i].processingTime);
        }

        qsort(tasks, numberOfTasks, sizeof(Task), comparator);

        for (i = 0; i < numberOfTasks; i++)
            if (time >= tasks[i].startTime) {
                time += tasks[i].processingTime;
            } else {
                time = tasks[i].startTime + tasks[i].processingTime;
            }

        fprintf(output, "%d\n", time);
        numberOfTasks = 0;
    }

    return 0;
}