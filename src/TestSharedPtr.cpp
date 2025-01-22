#include "SharedPtr.hpp"
#include "gtest/gtest.h"

// A helper struct for testing
struct TestStruct {
    int value;
    TestStruct(int v) : value(v) {}
    ~TestStruct() { /* Destructor to confirm cleanup */ }
};

// Test default constructor
TEST(SharedPtrTest, DefaultConstructor) {
    SharedPtr<int> sp(nullptr);
    EXPECT_EQ(sp.RefCount(), -1);
}

// Test constructor with valid pointer
TEST(SharedPtrTest, ConstructorWithPointer) {
    SharedPtr<int> sp(new int(42));
    EXPECT_EQ(sp.RefCount(), 1);
    EXPECT_EQ(*sp, 42);
}

// Test copy constructor
TEST(SharedPtrTest, CopyConstructor) {
    SharedPtr<int> sp1(new int(42));
    EXPECT_EQ(sp1.RefCount(), 1);

    SharedPtr<int> sp2(sp1);
    EXPECT_EQ(sp1.RefCount(), 2);
    EXPECT_EQ(sp2.RefCount(), 2);
    EXPECT_EQ(*sp2, 42);
}

// Test copy assignment operator
TEST(SharedPtrTest, CopyAssignment) {
    SharedPtr<int> sp1(new int(42));
    SharedPtr<int> sp2;

    sp2 = sp1;

    EXPECT_EQ(sp1.RefCount(), 2);
    EXPECT_EQ(sp2.RefCount(), 2);
    EXPECT_EQ(*sp2, 42);
}

// Test move constructor
TEST(SharedPtrTest, MoveConstructor) {
    SharedPtr<int> sp1(new int(42));
    EXPECT_EQ(sp1.RefCount(), 1);

    SharedPtr<int> sp2(std::move(sp1));
    EXPECT_EQ(sp2.RefCount(), 1);
    EXPECT_EQ(sp1.RefCount(), -1); // sp1 no longer manages the object
    EXPECT_EQ(*sp2, 42);
}

// Test move assignment operator
TEST(SharedPtrTest, MoveAssignment) {
    SharedPtr<int> sp1(new int(42));
    SharedPtr<int> sp2;

    sp2 = std::move(sp1);

    EXPECT_EQ(sp2.RefCount(), 1);
    EXPECT_EQ(sp1.RefCount(), -1); // sp1 no longer manages the object
    EXPECT_EQ(*sp2, 42);
}

// Test reference count decrements correctly
TEST(SharedPtrTest, RefCountDecrement) {
    SharedPtr<int> sp1(new int(42));
    {
        SharedPtr<int> sp2(sp1);
        EXPECT_EQ(sp1.RefCount(), 2);
    } // sp2 goes out of scope here

    EXPECT_EQ(sp1.RefCount(), 1);
}

// Test destructor cleans up memory
TEST(SharedPtrTest, DestructorCleansUpMemory) {
    bool deleted = false;
    struct DeleterTest {
        bool* deleted_flag;
        DeleterTest(bool* flag) : deleted_flag(flag) {}
        ~DeleterTest() { *deleted_flag = true; }
    };

    {
        SharedPtr<DeleterTest> sp(new DeleterTest(&deleted));
    } // sp goes out of scope here

    EXPECT_EQ(true, deleted);
}

// Test dereference operator
TEST(SharedPtrTest, DereferenceOperator) {
    SharedPtr<TestStruct> sp(new TestStruct(42));
    EXPECT_EQ(sp->value, 42);
    EXPECT_EQ((*sp).value, 42);
}

// Test null pointer behavior
TEST(SharedPtrTest, NullPointerBehavior) {
    SharedPtr<int> sp(nullptr);
    EXPECT_EQ(sp.RefCount(), -1);
    EXPECT_EQ(sp.operator->(), nullptr);
}

// Test self-assignment with copy operator
TEST(SharedPtrTest, SelfAssignmentCopy) {
    SharedPtr<int> sp(new int(42));
    sp = sp; // Self-assignment
    EXPECT_EQ(sp.RefCount(), 1);
    EXPECT_EQ(*sp, 42);
}

// Test self-assignment with move operator
TEST(SharedPtrTest, SelfAssignmentMove) {
    SharedPtr<int> sp(new int(42));
    sp = std::move(sp); // Self-assignment
    EXPECT_EQ(sp.RefCount(), 1);
    EXPECT_EQ(*sp, 42);
}