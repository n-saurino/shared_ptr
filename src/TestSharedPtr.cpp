#include "SharedPtr.hpp"
#include <gtest/gtest.h>

// Test default constructor and dereferencing
TEST(SharedPtrTest, ConstructorAndDereference) {
    SharedPtr<int> sp(new int(42));
    EXPECT_EQ(*sp, 42);
}

// Test copy constructor increases reference count
TEST(SharedPtrTest, CopyConstructorIncreasesRefCount) {
    SharedPtr<int> sp1(new int(42));
    SharedPtr<int> sp2 = sp1; // Copy constructor
    EXPECT_EQ(sp1.ReferenceCount(), 2);
    EXPECT_EQ(sp2.ReferenceCount(), 2);
}

// Test move constructor transfers ownership
TEST(SharedPtrTest, MoveConstructorTransfersOwnership) {
    SharedPtr<int> sp1(new int(42));
    int refCountBeforeMove = sp1.ReferenceCount();
    SharedPtr<int> sp2 = std::move(sp1);
    EXPECT_EQ(sp2.ReferenceCount(), refCountBeforeMove);
    EXPECT_EQ(sp1.ReferenceCount(), 0); // sp1 should be null after move
}

// Test copy assignment operator
TEST(SharedPtrTest, CopyAssignmentOperator) {
    SharedPtr<int> sp1(new int(42));
    SharedPtr<int> sp2(new int(100));
    sp2 = sp1; // Copy assignment
    EXPECT_EQ(*sp2, 42);
    EXPECT_EQ(sp1.ReferenceCount(), 2);
    EXPECT_EQ(sp2.ReferenceCount(), 2);
}

// Test move assignment operator
TEST(SharedPtrTest, MoveAssignmentOperator) {
    SharedPtr<int> sp1(new int(42));
    SharedPtr<int> sp2(new int(100));
    int refCountBeforeMove = sp1.ReferenceCount();
    sp2 = std::move(sp1); // Move assignment
    EXPECT_EQ(*sp2, 42);
    EXPECT_EQ(sp2.ReferenceCount(), refCountBeforeMove);
    EXPECT_EQ(sp1.ReferenceCount(), 0); // sp1 should be null after move
}

// Test destructor decreases reference count
TEST(SharedPtrTest, DestructorDecreasesRefCount) {
    SharedPtr<int> sp1(new int(42));
    {
        SharedPtr<int> sp2 = sp1; // Copy constructor
        EXPECT_EQ(sp1.ReferenceCount(), 2);
    }
    // sp2 is out of scope, reference count should decrease
    EXPECT_EQ(sp1.ReferenceCount(), 1);
}

// Test operator-> access
TEST(SharedPtrTest, OperatorArrowAccess) {
    struct TestStruct {
        int value;
        TestStruct(int val) : value(val) {}
    };
    SharedPtr<TestStruct> sp(new TestStruct(42));
    EXPECT_EQ(sp->value, 42);
}

// Test null pointer initialization
TEST(SharedPtrTest, NullPointerInitialization) {
    SharedPtr<int> sp(nullptr);
    EXPECT_EQ(sp.ReferenceCount(), 0);
}

// Test self-assignment in copy
TEST(SharedPtrTest, SelfAssignmentCopy) {
    SharedPtr<int> sp(new int(42));
    int refCountBefore = sp.ReferenceCount();
    sp = sp; // Self-assignment
    EXPECT_EQ(sp.ReferenceCount(), refCountBefore); // Ref count should not change
    EXPECT_EQ(*sp, 42);
}

// Test self-assignment in move
TEST(SharedPtrTest, SelfAssignmentMove) {
    SharedPtr<int> sp(new int(42));
    int refCountBefore = sp.ReferenceCount();
    sp = std::move(sp); // Self-move assignment
    EXPECT_EQ(sp.ReferenceCount(), refCountBefore); // Ref count should not change
    EXPECT_EQ(*sp, 42);
}