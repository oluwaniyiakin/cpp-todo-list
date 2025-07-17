#include <iostream>
#include <vector>
#include <fstream>
#include "task.h"  // Include the Task class header

using namespace std;

// Function declarations
void showMenu();
void addTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);
void saveTasks(const vector<Task>& tasks);
void loadTasks(vector<Task>& tasks);

// Displays menu
void showMenu() {
    cout << "\n=== TO-DO LIST MENU ===\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Save Tasks to File\n";
    cout << "5. Load Tasks from File\n";
    cout << "6. Exit\n";
    cout << "Choose an option (1-6): ";
}

// Adds a task
void addTask(vector<Task>& tasks) {
    cout << "Enter task description: ";
    cin.ignore();
    string desc;
    getline(cin, desc);
    Task t(desc);
    tasks.push_back(t);
    cout << "Task added!\n";
}

// Displays all tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\nYour Tasks:\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].getDescription();
        cout << (tasks[i].isCompleted() ? " [Completed]" : " [Pending]") << "\n";
    }
}

// Marks a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    cout << "Enter task number to mark as completed: ";
    int index;
    cin >> index;

    if (index < 1 || index > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[index - 1].markCompleted();
    cout << "Task marked as completed!\n";
}

// Saves tasks to file
void saveTasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (const Task& task : tasks) {
        file << task.toString() << "\n";
    }

    file.close();
    cout << "Tasks saved to tasks.txt!\n";
}

// Loads tasks from file
void loadTasks(vector<Task>& tasks) {
    ifstream file("tasks.txt");
    if (!file) {
        cout << "No saved file found.\n";
        return;
    }

    tasks.clear();
    string line;
    while (getline(file, line)) {
        Task t = Task::fromString(line);
        tasks.push_back(t);
    }

    file.close();
    cout << "Tasks loaded from file!\n";
}

// Main driver function
int main() {
    vector<Task> tasks;
    int choice;

    cout << "Welcome to your C++ To-Do List Manager!\n";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                saveTasks(tasks);
                break;
            case 5:
                loadTasks(tasks);
                break;
            case 6:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
