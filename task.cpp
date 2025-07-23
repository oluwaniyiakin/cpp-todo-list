// task.cpp
#include "task.h"
#include <string>

// --- Task Base Class ---

Task::Task(std::string desc) {
    description = desc;
    completed = false;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::markCompleted() {
    completed = true;
}

// Marked as virtual for polymorphism
std::string Task::toString() const {
    return description + ";" + (completed ? "1" : "0");
}

// Static method to parse a string into a Task object
Task Task::fromString(std::string line) {
    size_t separator = line.find(';');
    std::string desc = line.substr(0, separator);
    bool done = line.substr(separator + 1) == "1";
    Task t(desc);
    if (done) t.markCompleted();
    return t;
}

// --- ImportantTask Derived Class ---

ImportantTask::ImportantTask(std::string desc, int priority)
    : Task(desc), priority(priority) {}

int ImportantTask::getPriority() const {
    return priority;
}

// Override toString to include priority
std::string ImportantTask::toString() const {
    return "[IMPORTANT] " + getDescription() + " (Priority: " + std::to_string(priority) + ")" +
           (isCompleted() ? " [Done]" : " [Pending]");
}
