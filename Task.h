//
// Created by anatolie on 15/07/25.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <ctime>

#ifndef TASK_H
#define TASK_H


enum class Priority { LOW, MEDIUM, HIGH }; // Task priority levels

struct DueDate { // Structure to represent a due date
    int year, month, day;
    std::string toString() const {
        char buf[11];
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", year, month, day);
        return buf;
    }
};

class Task { // Class representing a task in the to-do list

public:
    // Constructor to initialize a task with description empty, completion status, priority, and optional due date
    Task(const std::string& tit,const std::string& desc = "",const bool done = false, const Priority& prio= Priority::MEDIUM,const std::optional<DueDate>& dueDate = std::nullopt)
        : title(tit),description(std::move(desc)), completed(done),priority(prio), due(dueDate) {}


    void markCompleted() { completed = true; } // finish the task

    bool isCompleted() const { return completed; } // control if the task is completed

    const std::string& getTitle() const { return title; } // get the title of the task

    const std::string& getDescription() const { return description; } //get the description of a task

    Priority getPriority() const { return priority; } // get priority of a task

    void setPriority( const Priority& prio) { priority = prio; }

    std::optional<DueDate> getDueDate() const { return due; } // get the due date of a task

    // task -> string(to save on file)
    std::string serialize() const { // format {1 | MEDIUM |2025-10-13| fare le pulizie | fare le pulizie in casa}
        std::string s = (completed ? "1" : "0") + std::string("|")
                        + std::to_string(static_cast<int>(priority)) + "|"
                        + (due ? due->toString() : "") + "|"
                        + title + "|"
                        + description;
        return s;
    }

    //string(got from file) -> task
    static Task deserialize(const std::string& line);

    std::string toString() const { // format {1 | MEDIUM |2025-10-13| fare le pulizie | fare le pulizie in casa}
        return serialize();
    }

private:
    std::string title;
    std::string description;
    bool completed;
    Priority priority;
    std::optional<DueDate> due;

};




#endif //TASK_H
