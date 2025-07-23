// task.h
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
protected:
    std::string description;
    bool completed;

public:
    Task(std::string desc);
    std::string getDescription() const;
    bool isCompleted() const;
    void markCompleted();
    virtual std::string toString() const; // virtual for polymorphism
    static Task fromString(std::string line);
    virtual ~Task() {} // virtual destructor
};

// Derived class: ImportantTask
class ImportantTask : public Task {
private:
    int priority;

public:
    ImportantTask(std::string desc, int priority);
    int getPriority() const;
    std::string toString() const override;
};

#endif
