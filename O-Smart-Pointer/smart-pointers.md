# Smart Pointers #

## Or, If C++ is so smart, why do I have to remember to delete? ##

C is bare bones, so the fact that we have to manually `malloc`/`free` makes
sense. But if everyone makes fun of C++ for including every language construct
ever, why do I still have to call `delete`?

Well, good news! With SmartPtr you don't have to!

What is it?  A C++ class that behaves like a pointer. That is, it points to a
chunk of memory on the heap, and can be dereferenced to get to it. It will let
us pass around pointers to objects, instead of the objects themselves.

Why?

* We want automatic life-time management of heap-allocated objects.
* We want value semantics without having to copy large objects.
* In short, we want behavior that mimics Java references!

SmartPtr:
* Is a light-weight handle for heap-allocated objects.
* Manages the object life-time using reference counting.
* Provides value semantics for the pointer, thus can be put into standard
  containers.


### Reference Counting ###

Reference Counting is a way to automatically manage the lifetime of heap
allocated objects.

### Key Behaviors ###

The key behaviors that SmartPtr must provide are fairly simple:
* It stores a real memory address of some type
* It can be dereferenced to return that memory address when asked
* When everybody is done with the object this smart pointer is pointing to, it
  will be deleted.

That last one is the key that drives the definition. 

It means that a group of smart pointers all pointing to the same object need to
coordinate their efforts. 

As a result, let's think about the private data members that a SmartPtr must have.
Obviously first is the underlying pointer we're wrapping - `T *ptr;`. 

But there's a second component to a SmartPtr, the current count of references to
that pointer. We need to keep this in sync across our entire program. 

Note: See ***24-smartptr.pdf*** for the actual definition. 


### Diagram SmartPtr ###
Let's [first attempt] (/O-Smart-Pointer/code/stack.gif) to keep track of count 
in the simplest way possible: an `int` inside the class.

As we can see, this will not properly synchronize the value and can even lead to
deleting the object too soon!

Let's [try again] (/O-Smart-Pointer/code/heap.gif) while holding a *pointer* to an `int` inside the class.

It works!  We're properly keeping track of the count!  This means we can delete the
object properly.

SmartPtr definition
--------------------
```c
template <class T>
class SmartPtr {

    private:
	T *ptr;  // the underlying pointer

	int *count;  // the reference count

    public:

	// constructor
	//
	// - p is assumed to point to an object created by "new T(...)"
	// - we hold the pointer and initialize ref count to 1.
	//
	//   note: explicit keyword
	//   note: default argument
	//
	explicit SmartPtr(T *p = 0) 
	{
	    ptr = p;
	    count = new int(1);
	}

	// copy constructor
	//
	// - copy the data members and increment the reference count 
	//
	//   note: member initialization syntax
	//
	SmartPtr(const SmartPtr<T>& sp)
	    : ptr(sp.ptr), count(sp.count)
	{
	    ++*count;
	}

	// destructor
	//
	// - delete the underlying object if this was the last owner
	//
	~SmartPtr()
	{
	    if (--*count == 0) {
		delete count;
		delete ptr;
	    }
	}

	// assignment operator
	//
	// - detach this SmartPtr from the underlying object and
	//   attach to the object that sp is pointing to.
	//
	SmartPtr<T>& operator=(const SmartPtr<T>& sp)
	{
	    if (this != &sp) {
		// first, detach.
		if (--*count == 0) {
		    delete count;
		    delete ptr;
		}
		// attach to the new object.
		ptr = sp.ptr;
		count = sp.count;
		++*count;
	    }
	    return *this;
	}

	// operator*() and operator->() make SmartPtr class behave
	// just like a regular pointer.

	T& operator*() const { return *ptr; }

	T* operator->() const { return ptr; }

	// access to the underlying pointer for those cases when you
	// need it.
	
	T* getPtr() const { return ptr; }

	// operator void*() makes "if (sp) ..." possible.
	
	operator void*() const { return ptr; }

};
```

### Reference Cycles ###

Imagine you have a doubly linked list. Each node points to the next node, but
also to the previous node. You also have a List object, that points to the head
and tail nodes.

Because SmartPtrs are awesome, you use SmartPtrs for all of the above head/next.

Unfortunately, there's a problem! When the list is destructed, it destructs its pointers to head and tail. That reduces their counts by 1. What we want to happen is that the head node is destructed, causing the node it's pointing to to be destructed.

However, the count of references to head node doesn't become 0, because there is still a reference to it -- the next node's previous pointer. So we have an orphaned cycle. One thing is pointing to the other, which is pointing back to the first. Thus neither will go to zero, and therefore won't be destructed.

This is called a reference cycle, which is the big problem with simple reference counting.

shared_ptr solves this with weak_ptr. Another option is to use some sort of garbage collection very occasionally to try to identify these objects (mark and sweep being a common basic one). Regardless, it needs to be addressed.


### Warnings ###

SmartPtrs can't point to objects on the stack. Think about what would happen if
you tried to make that happen?

An object managed by a SmartPtr **must** be managed exclusively by SmartPtr. If
you mix a SmartPtr and a regular pointer, the world will end. Okay, the world
won't really end, but bad things can happen - think about what might happen if 
the SmartPtr `delete`s the object before the regular pointer is done with it.

Don't forget the above discussion on Reference Cycles.


# shared_ptr ##

The C++11 standard includes a smart pointer template class (finally!)
called "shared_ptr":

* Works basically the same way as our SmartPtr, but more powerful.
* Atomic reference counting for thread safety.
* Can attach "weak_ptr", which does not participate in ref counting. These are
  used to break the cycles mentioned above.
* Delete operation customizable.

