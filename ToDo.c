#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_LENGTH 256

typedef struct {
    char task[TASK_LENGTH];
    int completed;
} ToDo;

void loadTasks(ToDo tasks[], int *taskCount, const char *filename);
void saveTasks(ToDo tasks[], int taskCount, const char *filename);
void addTask(ToDo tasks[], int *taskCount, const char *task);
void completeTask(ToDo tasks[], int taskCount, int taskIndex);
void listTasks(ToDo tasks[], int taskCount);

int main() {
    ToDo tasks[MAX_TASKS];
    int taskCount = 0;
    char filename[] = "tasks.txt";

    loadTasks(tasks, &taskCount, filename);

    int choice;
    char task[TASK_LENGTH];
    int taskIndex;

    //To-do list Check
    while (1) {
        printf("\nTo-Do List Manager\n");
        printf("1. List tasks\n");
        printf("2. Add task\n");
        printf("3. Complete task\n");
        printf("4. Save and exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                listTasks(tasks, taskCount);
                break;
            case 2:
                printf("Enter the task: ");
                fgets(task, TASK_LENGTH, stdin);
                task[strcspn(task, "\n")] = '\0'; // Remove newline character
                addTask(tasks, &taskCount, task);
                break;
            case 3:
                printf("Enter the task number to complete: ");
                scanf("%d", &taskIndex);
                completeTask(tasks, taskCount, taskIndex - 1);
                break;
            case 4:
                saveTasks(tasks, taskCount, filename);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Load tasks from a file
void loadTasks(ToDo tasks[], int *taskCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    while (fscanf(file, "%255[^\t]\t%d\n", tasks[*taskCount].task, &tasks[*taskCount].completed) != EOF) {
        (*taskCount)++;
    }

    fclose(file);
}

// Save tasks to a file
void saveTasks(ToDo tasks[], int taskCount, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file for writing");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\t%d\n", tasks[i].task, tasks[i].completed);
    }

    fclose(file);
}

// Add a new task to the list
void addTask(ToDo tasks[], int *taskCount, const char *task) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    strcpy(tasks[*taskCount].task, task);
    tasks[*taskCount].completed = 0;
    (*taskCount)++;
}

// Mark a task as completed
void completeTask(ToDo tasks[], int taskCount, int taskIndex) {
    if (taskIndex < 0 || taskIndex >= taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    tasks[taskIndex].completed = 1;
}

// List all tasks
void listTasks(ToDo tasks[], int taskCount) {
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s [%s]\n", i + 1, tasks[i].task, tasks[i].completed ? "Completed" : "Not Completed");
    }
}