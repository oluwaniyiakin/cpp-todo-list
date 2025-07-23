#include <iostream>
#include <vector>
#include <fstream>
#include "task.h"

using namespace std;

// Function declarations
void showMenu();
void addTask(vector<Task*>& tasks);
void viewTasks(const vector<Task*>& tasks);
void markTaskCompleted(vector<Task*>& tasks);
void saveTasks(const vector<Task*>& tasks);
void loadTasks(vector<Task*>& tasks);
void cleanupTasks(vector<Task*>& tasks);

// Display menu
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

// Add task dynamically using `new`
void addTask(vector<Task*>& tasks) {
    cin.ignore(); // clear input buffer
    string desc;
    cout << "Enter task description: ";
    getline(cin, desc);

    Task* t = new Task(desc); // dynamic allocation
    tasks.push_back(t);
    cout << "Task added!\n";
}

// View tasks
void viewTasks(const vector<Task*>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\nYour Tasks:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". ";
        tasks[i]->display();  // virtual function call
    }
}

// Mark task completed
void markTaskCompleted(vector<Task*>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index < 1 || index > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[index - 1]->markCompleted();
    cout << "Task marked as completed!\n";
}

// Save tasks to file
void saveTasks(const vector<Task*>& tasks) {
    ofstream file("tasks.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (const auto& task : tasks) {
        file << task->toString() << endl;
    }

    file.close();
    cout << "Tasks saved to tasks.txt!\n";
}

// Load tasks from file using `new`
void loadTasks(vector<Task*>& tasks) {
    ifstream file("tasks.txt");
    if (!file) {
        cout << "No saved file found.\n";
        return;
    }

    // Clean up existing tasks
    cleanupTasks(tasks);

    string line;
    while (getline(file, line)) {
        Task* t = Task::fromString(line); // create dynamically
        if (t) tasks.push_back(t);
    }

    file.close();
    cout << "Tasks loaded from file!\n";
}

// Free dynamically allocated memory
void cleanupTasks(vector<Task*>& tasks) {
    for (auto task : tasks) {
        delete task;
    }
    tasks.clear();
}

int main() {
    vector<Task*> tasks;
    int choice;

    cout << "Welcome to your C++ To-Do List Manager!\n";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: viewTasks(tasks); break;
            case 3: markTaskCompleted(tasks); break;
            case 4: saveTasks(tasks); break;
            case 5: loadTasks(tasks); break;
            case 6:
                cout << "Goodbye!\n";
                saveTasks(tasks);
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    cleanupTasks(tasks);
    return 0;
}
