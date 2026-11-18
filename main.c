#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX_TASKS 100

// Structure to store task details
struct Task {
    int id;
    char title[100];
    char assignee[50];
    int priority;       // 1 = High, 2 = Medium, 3 = Low
    char deadline[11];  // Format: YYYY-MM-DD
    float estimatedHours;
    char tag[30];
    int completed;     // 0 = Pending, 1 = Complete
};

// Array of structures
struct Task*tasks=NULL;
int taskCount = 0;

// Function declarations
void addTask(void);
void viewTasks(void);
void sortTasksByPriority(void);
void markTaskComplete(void);
void editTask(void);
void filterTasksByStatus(void);
void searchTasksById(void);
void searchTasksByAssignee(void);
void weeklyProductivityReport(void);
void searchTasksByTag(void);
void sortTasksByDeadline(void);
void saveTasksToFile(void);
void loadTasksFromFile(void);
void searchTaskByld(void);

int main(void) {
    int choice;

    do {
        printf("\n====================================\n");
        printf("     MULTI-USER TO-DO MANAGER\n");
        printf("====================================\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks\n");
        printf("3. Sort Tasks by Priority\n");
        printf("4. Mark Test Complete\n");
        printf("5. Edit Task\n");
        printf("6. Filter Tasks by Status\n");
        printf("7. Search Task by ID\n");
        printf("8. Search Tasks by Assignee\n");
        printf("9. Weekly Productivity Report\n");
        printf("10. Search Tasks by Tag\n");
        printf("11. Sort Tasks by Deadline\n");
        printf("12. Save Taks to File\n");
        printf("13. Load Tasks from File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
            sortTasksByPriority();
            break;
            case 4:
            markTaskComplete();
            break;
            case 5:
            editTask();
            break;
            case 6:
            filterTasksByStatus();
            break;
            case 7:
            searchTasksById();
            break;
            case 8:
            searchTasksByAssignee();
            break;
            case 9:
            weeklyProductivityReport();
            break;
            case 10:
            searchTasksByTag();
            break;
            case 11:
            sortTasksByDeadline();
            break;
            case 12:
            saveTasksToFile();
            break;
            case 13:
            loadTasksFromFile();
            break;

            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    free(tasks);
    return 0;
}

// Function to add a task
void addTask(void) {
    struct Task *temp = realloc(
    tasks,
    (taskCount + 1) * sizeof(struct Task)
);

if (temp == NULL) {
    printf("Memory allocation failed!\n");
    return;
}

tasks = temp;

struct Task *t = &tasks[taskCount];

    t->id = taskCount + 1;

    printf("Enter task title: ");
    scanf(" %99[^\n]", t->title);

    printf("Enter assignee name: ");
    scanf(" %49[^\n]", t->assignee);

    printf("Priority (1=High, 2=Medium, 3=Low): ");
    scanf("%d", &t->priority);

    if (t->priority < 1 || t->priority > 3) {
        printf("Invalid priority. Task not added.\n");
        return;
    }

    printf("Deadline (YYYY-MM-DD): ");
    scanf("%10s", t->deadline);

    printf("Estimated hours: ");
    scanf("%f", &t->estimatedHours);

    printf("Enter task tag: ");
    scanf("%29s", t->tag);

    t->completed = 0;
    taskCount++;

    printf("Task added successfully!\n");
}

// Function to display all tasks
void viewTasks(void) {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n========== TASK LIST ==========\n");

    for (int i = 0; i < taskCount; i++) {
        printf("\nTask ID: %d\n", tasks[i].id);
        printf("Title: %s\n", tasks[i].title);
        printf("Assignee: %s\n", tasks[i].assignee);

        printf("Priority: ");
        if (tasks[i].priority == 1)
            printf("High\n");
        else if (tasks[i].priority == 2)
            printf("Medium\n");
        else
            printf("Low\n");

        printf("Deadline: %s\n", tasks[i].deadline);
        printf("Estimated Hours: %.2f\n",
               tasks[i].estimatedHours);
        printf("Tag: %s\n", tasks[i].tag);
        printf("Status: %s\n",
               tasks[i].completed ? "Completed" : "Pending");
    }
}
void sortTasksByPriority(void) {
    if (taskCount == 0) {
        printf("No tasks available to sort.\n");
        return;
    }

    // Bubble sort: High priority comes first
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {

            if (tasks[j].priority > tasks[j + 1].priority) {
                struct Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("Tasks sorted by priority successfully!\n");
    viewTasks();
}
void markTaskComplete(void) {
    int id;

    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("Enter task ID to complete: ");
    scanf("%d", &id);

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            tasks[i].completed = 1;
            printf("Task marked as completed!\n");
            return;
        }
    }

    printf("Task ID not found.\n");
}
void editTask(void) {
    int id;
    int found = 0;

    if (taskCount == 0) {
        printf("No tasks available to edit.\n");
        return;
    }

    printf("Enter task ID to edit: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid task ID.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            found = 1;

            printf("Enter new task title: ");
            scanf(" %99[^\n]", tasks[i].title);

            printf("Enter new assignee name: ");
            scanf(" %49[^\n]", tasks[i].assignee);

            printf("Enter new priority (1=High, 2=Medium, 3=Low): ");
            if (scanf("%d", &tasks[i].priority) != 1 ||
                tasks[i].priority < 1 ||
                tasks[i].priority > 3) {
                printf("Invalid priority. Please edit the task again.\n");
                return;
            }

            printf("Enter new deadline (YYYY-MM-DD): ");
            scanf("%10s", tasks[i].deadline);

            printf("Enter new estimated hours: ");
            scanf("%f", &tasks[i].estimatedHours);

            printf("Enter new tag: ");
            scanf("%29s", tasks[i].tag);

            printf("Task updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Task ID not found.\n");
    }
}
void filterTasksByStatus(void) {
    int status;
    int found = 0;

    printf("\nFilter Tasks:\n");
    printf("1. Pending Tasks\n");
    printf("2. Completed Tasks\n");
    printf("Enter your choice: ");

    if (scanf("%d", &status) != 1 ||
        (status != 1 && status != 2)) {
        printf("Invalid choice!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        if ((status == 1 && tasks[i].completed == 0) ||
            (status == 2 && tasks[i].completed == 1)) {

            printf("\nTask ID: %d\n", tasks[i].id);
            printf("Title: %s\n", tasks[i].title);
            printf("Assignee: %s\n", tasks[i].assignee);
            printf("Status: %s\n",
                   tasks[i].completed ? "Completed" : "Pending");

            found = 1;
        }
    }

    if (!found) {
        printf("No matching tasks found.\n");
    }
}
void searchTasksById(void) {
    int id;
    int found = 0;

    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("Enter task ID to search: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            printf("\n--- Task Found ---\n");
            printf("ID: %d\n", tasks[i].id);
            printf("Title: %s\n", tasks[i].title);
            printf("Assignee: %s\n", tasks[i].assignee);
            printf("Priority: %d\n", tasks[i].priority);
            printf("Deadline: %s\n", tasks[i].deadline);
            printf("Estimated Hours: %.2f\n",
                   tasks[i].estimatedHours);
            printf("Tag: %s\n", tasks[i].tag);
            printf("Status: %s\n",
                   tasks[i].completed ? "Completed" : "Pending");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Task ID not found.\n");
    }
}
void searchTasksByAssignee(void) {
    char name[50];
    int found = 0;

    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("Enter assignee name: ");
    scanf(" %49[^\n]", name);

    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].assignee, name) == 0) {
            printf("\nTask ID: %d\n", tasks[i].id);
            printf("Title: %s\n", tasks[i].title);
            printf("Assignee: %s\n", tasks[i].assignee);
            printf("Status: %s\n",
                   tasks[i].completed ? "Completed" : "Pending");
            printf("Deadline: %s\n", tasks[i].deadline);

            found = 1;
        }
    }

    if (!found) {
        printf("No tasks found for this assignee.\n");
    }
}
void weeklyProductivityReport(void) {
    int completed = 0;
    int pending = 0;
    float totalHours = 0;

    if (taskCount == 0) {
        printf("\nNo tasks available for the report.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        totalHours += tasks[i].estimatedHours;

        if (tasks[i].completed == 1) {
            completed++;
        } else {
            pending++;
        }
    }

    printf("\n===== Productivity Report =====\n");
    printf("Total Tasks       : %d\n", taskCount);
    printf("Completed Tasks   : %d\n", completed);
    printf("Pending Tasks     : %d\n", pending);
    printf("Estimated Hours   : %.2f\n", totalHours);
    printf("Completion Rate   : %.2f%%\n",
           (completed * 100.0) / taskCount);
    printf("================================\n");
}
void searchTasksByTag(void) {
    char searchTag[30];
    int found = 0;

    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("Enter tag to search: ");
    scanf(" %29[^\n]", searchTag);

    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].tag, searchTag) == 0) {
            printf("\nTask ID: %d\n", tasks[i].id);
            printf("Title: %s\n", tasks[i].title);
            printf("Assignee: %s\n", tasks[i].assignee);
            printf("Tag: %s\n", tasks[i].tag);
            printf("Status: %s\n",
                   tasks[i].completed ? "Completed" : "Pending");
            found = 1;
        }
    }

    if (!found) {
        printf("No tasks found with this tag.\n");
    }
}
void sortTasksByDeadline(void) {
    if (taskCount < 2) {
        printf("Not enough tasks to sort.\n");
        return;
    }

    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (strcmp(tasks[j].deadline,
                       tasks[j + 1].deadline) > 0) {
                struct Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("Tasks sorted by deadline successfully!\n");
    viewTasks();
}
void saveTasksToFile(void) {
    FILE *fp = fopen("tasks.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(fp, "%d\n", tasks[i].id);
        fprintf(fp, "%s\n", tasks[i].title);
        fprintf(fp, "%s\n", tasks[i].assignee);
        fprintf(fp, "%d\n", tasks[i].priority);
        fprintf(fp, "%s\n", tasks[i].deadline);
        fprintf(fp, "%.2f\n", tasks[i].estimatedHours);
        fprintf(fp, "%s\n", tasks[i].tag);
        fprintf(fp, "%d\n", tasks[i].completed);
    }

    fclose(fp);
    printf("Tasks saved to tasks.txt successfully!\n");
}
void loadTasksFromFile(void) {
    FILE *fp = fopen("tasks.txt", "r");

    if (fp == NULL) {
        printf("No saved tasks file found.\n");
        return;
    }

    struct Task *loaded = NULL;
    int count = 0;
    int id, priority, completed;
    char title[100], assignee[50], deadline[11], tag[30];
    float hours;

    while (fscanf(fp, "%d\n", &id) == 1) {
        if (fscanf(fp, "%99[^\n]\n", title) != 1 ||
            fscanf(fp, "%49[^\n]\n", assignee) != 1 ||
            fscanf(fp, "%d\n", &priority) != 1 ||
            fscanf(fp, "%10s\n", deadline) != 1 ||
            fscanf(fp, "%f\n", &hours) != 1 ||
            fscanf(fp, "%29[^\n]\n", tag) != 1 ||
            fscanf(fp, "%d\n", &completed) != 1) {
            printf("Invalid data in tasks.txt.\n");
            free(loaded);
            fclose(fp);
            return;
        }

        struct Task *temp = realloc(
            loaded, (count + 1) * sizeof(struct Task)
        );

        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            free(loaded);
            fclose(fp);
            return;
        }

        loaded = temp;
        loaded[count].id = id;
        strcpy(loaded[count].title, title);
        strcpy(loaded[count].assignee, assignee);
        loaded[count].priority = priority;
        strcpy(loaded[count].deadline, deadline);
        loaded[count].estimatedHours = hours;
        strcpy(loaded[count].tag, tag);
        loaded[count].completed = completed;
        count++;
    }

    fclose(fp);
    free(tasks);
    tasks = loaded;
    taskCount = count;

    printf("%d tasks loaded successfully!\n", taskCount);
}
