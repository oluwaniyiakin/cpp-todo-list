// task.h
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    std::string description;
    bool completed;

public:
    Task(std::string desc);
    std::string getDescription() const;
    bool isCompleted() const;
    void markCompleted();
    std::string toString() const;
    static Task fromString(std::string line);
};

#endif
