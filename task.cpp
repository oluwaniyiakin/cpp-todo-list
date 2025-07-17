// task.cpp
#include "task.h"
#include <string>

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

std::string Task::toString() const {
    return description + ";" + (completed ? "1" : "0");
}

Task Task::fromString(std::string line) {
    size_t separator = line.find(';');
    std::string desc = line.substr(0, separator);
    bool done = line.substr(separator + 1) == "1";
    Task t(desc);
    if (done) t.markCompleted();
    return t;
}
