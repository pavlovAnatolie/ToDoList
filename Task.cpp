//
// Created by anatolie on 15/07/25.
//

#include "Task.h"

Task Task::deserialize(const std::string& line) {
    std::vector<std::string> parts;
    size_t start = 0, pos;

    while ((pos = line.find('|', start)) != std::string::npos) {

        parts.push_back(line.substr(start, pos - start));
        start = pos + 1;

    }

    parts.push_back(line.substr(start));

    bool done = (parts[0] == "1"); // check if the task is completed

    Priority prio = static_cast<Priority>(std::stoi(parts[1]));// convert string to Priority enum

    std::optional<DueDate> due = std::nullopt; // initialize due date as nullopt
    if (!parts[2].empty()) {
        DueDate d{};
        sscanf(parts[2].c_str(), "%d-%d-%d", &d.year, &d.month, &d.day);
        due = d;
    }

    std::string tit = parts[3]; // get the title of the task
    std::string desc = parts[4]; // get the description of the task


    return Task(tit, desc, done, prio, due);
}
