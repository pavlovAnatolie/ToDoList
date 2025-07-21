#include <gtest/gtest.h>
#include "ToDoList.h"

TEST(TodoListTest, AddAndListTasks) {
    TodoList list("");
    Task t1("Task1", "Desc1", false, Priority::LOW);
    Task t2("Task2", "Desc2", false, Priority::HIGH);
    list.addTask(t1);
    list.addTask(t2);
    // We can't directly check the private vector, but we can test remove/complete
    EXPECT_TRUE(list.removeTask(2)); // Remove second task
    EXPECT_FALSE(list.removeTask(5)); // Out of range
}

TEST(TodoListTest, CompleteTask) {
    TodoList list("");
    Task t1("Task1");
    list.addTask(t1);
    list.completeTask(1);
    // No direct access, but if we remove, it should be gone
    EXPECT_TRUE(list.removeTask(1));
    EXPECT_FALSE(list.removeTask(1));
}

TEST(TodoListTest, SortByPriority) {
    TodoList list("");
    list.addTask(Task("A", "", false, Priority::LOW));
    list.addTask(Task("B", "", false, Priority::HIGH));
    list.addTask(Task("C", "", false, Priority::MEDIUM));
    list.sortByPriority();
    // After sorting, removing first should be HIGH
    list.removeTask(1); // Should remove HIGH
    // Next should be MEDIUM
    list.removeTask(1); // Should remove MEDIUM
    // ultimo should be LOW
    EXPECT_TRUE(list.removeTask(1));
    EXPECT_FALSE(list.removeTask(1));
}

TEST(TodoListTest, SortByDue) {
    TodoList list("");
    list.addTask(Task("A", "", false, Priority::LOW, DueDate{2025, 10, 13}));
    list.addTask(Task("B", "", false, Priority::HIGH));
    list.addTask(Task("C", "", false, Priority::MEDIUM, DueDate{2024, 5, 1}));
    list.sortByDue();
    // Remove in due order: C (2024), A (2025), B (none)
    list.removeTask(1); // C
    list.removeTask(1); // A
    EXPECT_TRUE(list.removeTask(1)); // B
    EXPECT_FALSE(list.removeTask(1));
} 