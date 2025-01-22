Design and implement a class MySharedPtr that mimics the functionality of std::shared_ptr. A shared_ptr is a smart pointer that manages the ownership of a dynamically allocated object through reference counting. When the last shared_ptr that owns a shared object is destroyed or reset, the object is deleted.

Your implementation should include the following:
	1.	Reference Counting:
	   •	Maintain a reference count to track how many MySharedPtr instances share ownership of the same object.
	   •	Ensure the reference count is thread-safe (optional for simplicity).
	2.	Copy Semantics:
	   •	Implement a copy constructor to increase the reference count when a new MySharedPtr is created from an existing one.
	3.	Move Semantics:
	   •	Implement a move constructor to transfer ownership of the managed object without increasing the reference count.
	4.	Destructor:
	   •	Decrease the reference count and delete the managed object when the reference count reaches zero.
	5.	Operators:
	   •	Overload the dereference operator (*) and member access operator (->) to access the underlying object.

    You must implement the following functions in the MySharedPtr class:
	1.	MySharedPtr(T* ptr):
	   •	Initializes the shared pointer with a raw pointer ptr.
	2.	MySharedPtr(const MySharedPtr& other):
	   •	Copy constructor that increases the reference count.
	3.	MySharedPtr(MySharedPtr&& other):
	   •	Move constructor that transfers ownership.
	4.	~MySharedPtr():
	   •	Destructor that decreases the reference count and deletes the object if the reference count reaches zero.
	5.	T& operator*():
	   •	Overload to dereference the managed object.
	6.	T* operator->():
	   •	Overload to access members of the managed object.