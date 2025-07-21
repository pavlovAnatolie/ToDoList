//
// Created by anatolie on 16/07/25.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <optional>
#include "Task.h"

#ifndef TODOLIST_H
#define TODOLIST_H



class TodoList {


public:

    explicit TodoList(const std::string& file) : filename(file) {}

    void addTask(const Task& t) { tasks.push_back(t); }

    bool removeTask(size_t idx) {
        if (idx >= 1 && idx <= tasks.size()) {// considering items starts from position 1 and go to size()
            tasks.erase(tasks.begin() + idx - 1);
            return true;
        }
        return false;
    }

    void completeTask(size_t idx) {
        if (idx >= 1 && idx <= tasks.size())
            tasks[idx - 1].markCompleted();
    }

    void sortByDue() {
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                if (a.getDueDate() && b.getDueDate()) {
                    return a.getDueDate()->toString() < b.getDueDate()->toString();
                }
                return a.getDueDate().has_value();
            });
    }

    void sortByPriority() {
        std::sort(tasks.begin(), tasks.end(),[](const Task& a, const Task& b) {
                return static_cast<int>(a.getPriority()) > static_cast<int>(b.getPriority());
            });
    }

    void listTasks() const {
        for (size_t i = 0; i < tasks.size(); ++i) {
            const auto& t = tasks[i];

            std::cout << i + 1 << ". "
                      << (t.isCompleted() ? "[X] " : "[ ] ")
                      << "[" << static_cast<int>(t.getPriority()) << "] "
                      << (t.getDueDate() ? t.getDueDate()->toString() + " - " : "")
                      << t.getDescription() << "\n";
        }
    }

    void saveToFile() const {
        if (filename.empty()) {
            std::cerr << "Filename not set. Cannot save.\n";
            return;
        }
        std::ofstream f(filename);
        for (const auto& t : tasks) {
            f << t.serialize() << "\n";
        }
        f.close();

    }

    void loadFromFile() {
        if (filename.empty()) {
            std::cerr << "Filename not set. Cannot load.\n";
            return;
        }
        tasks.clear();
        std::ifstream f(filename);
        std::string line;
        while (std::getline(f, line)) {
            tasks.push_back(Task::deserialize(line));
        }
    }

    ~TodoList() = default;

private:
    std::vector<Task> tasks;
    std::string filename;
};




#endif //TODOLIST_H
