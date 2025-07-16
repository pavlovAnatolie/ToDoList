#include <gtest/gtest.h>
#include "Task.h"

TEST(TaskTest, ConstructorAndGetters) {
    Task t("Title", "Description", false, Priority::HIGH, DueDate{2025, 10, 13});
    EXPECT_EQ(t.getTitle(), "Title");
    EXPECT_EQ(t.getDescription(), "Description");
    EXPECT_FALSE(t.isCompleted());
    EXPECT_EQ(t.getPriority(), Priority::HIGH);
    ASSERT_TRUE(t.getDueDate().has_value());
    EXPECT_EQ(t.getDueDate()->year, 2025);
    EXPECT_EQ(t.getDueDate()->month, 10);
    EXPECT_EQ(t.getDueDate()->day, 13);
}

TEST(TaskTest, MarkCompleted) {
    Task t("Title");
    EXPECT_FALSE(t.isCompleted());
    t.markCompleted();
    EXPECT_TRUE(t.isCompleted());
}

TEST(TaskTest, SetPriority) {
    Task t("Title");
    EXPECT_EQ(t.getPriority(), Priority::MEDIUM);
    t.setPriority(Priority::LOW);
    EXPECT_EQ(t.getPriority(), Priority::LOW);
}

TEST(TaskTest, SerializeAndDeserialize) {
    Task t("Title", "Description", true, Priority::HIGH, DueDate{2025, 10, 13});
    std::string serialized = t.serialize();
    Task t2 = Task::deserialize(serialized);
    EXPECT_EQ(t2.getTitle(), "Title");
    EXPECT_EQ(t2.getDescription(), "Description");
    EXPECT_TRUE(t2.isCompleted());
    EXPECT_EQ(t2.getPriority(), Priority::HIGH);
    ASSERT_TRUE(t2.getDueDate().has_value());
    EXPECT_EQ(t2.getDueDate()->year, 2025);
    EXPECT_EQ(t2.getDueDate()->month, 10);
    EXPECT_EQ(t2.getDueDate()->day, 13);
}

TEST(TaskTest, NoDueDate) {
    Task t("Title");
    EXPECT_FALSE(t.getDueDate().has_value());
} 