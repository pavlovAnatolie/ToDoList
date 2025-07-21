#include <iostream>
#include <limits>
#include <unistd.h>
#include <linux/limits.h>

#include "ToDoList.h"

void printMenu() {
    std::cout << "\033[1;34m" << std::string(60, '=') << "\033[0m" << std::endl;
    std::cout << "\n====== ToDo List Menu ======" << std::endl;
    std::cout << "1. List tasks" << std::endl;
    std::cout << "2. Add task" << std::endl;
    std::cout << "3. Remove task" << std::endl;
    std::cout << "4. Complete task" << std::endl;
    std::cout << "5. Sort by due date" << std::endl;
    std::cout << "6. Sort by priority" << std::endl;
    std::cout << "7. Save to file" << std::endl;
    std::cout << "8. Load from file" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Select an option: ";
}

Priority inputPriority() {
    int p;
    std::cout << "Priority (0=LOW, 1=MEDIUM, 2=HIGH): ";
    std::cin >> p;

    while (p < 0 || p > 2) {
        /*std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');*/
        std::cout << "Invalid. Enter 0, 1, or 2: ";
        std::cin >> p;
    }
    return static_cast<Priority>(p);
}

std::optional<DueDate> inputDueDate() {
    std::cout << "Add due date? (y/n): ";
    char yn;
    std::cin >> yn;
    if (yn == 'y' || yn == 'Y') {
        DueDate d;
        std::cout << "Year: "; std::cin >> d.year;
        std::cout << "Month: "; std::cin >> d.month;
        std::cout << "Day: "; std::cin >> d.day;
        return d;
    }
    return std::nullopt;
}

int main() {
    // Get the current working directory to understand where the file is saved
    /*char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current working directory: " << cwd << std::endl;
    }*/

    std::string filename = "todolist.txt";
    TodoList todo(filename);
    todo.loadFromFile();

    std::cout << "\033[1;35mWelcome to the ToDo List App made by Anatolie Pavlov!\033[0m" << std::endl;

    int choice;
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                todo.listTasks();
                break;
            case 2: {
                std::string title, desc;
                std::cout << "Title: ";
                std::getline(std::cin, title);
                std::cout << "Description: ";
                std::getline(std::cin, desc);
                Priority prio = inputPriority();
                auto due = inputDueDate();
                todo.addTask(Task(title, desc, false, prio, due));
                std::cout << "Task added." << std::endl;
                break;
            }
            case 3: {
                size_t idx;
                std::cout << "Task number to remove: ";
                std::cin >> idx;
                if (todo.removeTask(idx))
                    std::cout << "Task removed." << std::endl;
                else
                    std::cout << "Invalid task number." << std::endl;
                break;
            }
            case 4: {
                size_t idx;
                std::cout << "Task number to complete: ";
                std::cin >> idx;
                todo.completeTask(idx);
                std::cout << "Task marked as completed." << std::endl;
                break;
            }
            case 5:
                todo.sortByDue();
                std::cout << "Tasks sorted by due date." << std::endl;
                break;
            case 6:
                todo.sortByPriority();
                std::cout << "Tasks sorted by priority." << std::endl;
                break;
            case 7:
                todo.saveToFile();
                std::cout << "Tasks saved to file." << std::endl;
                break;
            case 8:
                todo.loadFromFile();
                std::cout << "Tasks loaded from file." << std::endl;
                break;
            case 0:
                todo.saveToFile();
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
        }

    } while (choice != 0);
    return 0;
}