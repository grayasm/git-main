    C++ Interview Questions.
	
	Part 1.
	http://www.geeksforgeeks.org/commonly-asked-c-interview-questions-set-1/

  1. What are the differences between references and pointers?
	 Once a reference is created it cannot be modified modified later.
	 References cannot be NULL.
	 A reference must be initialized when declared.
	 References don't need a dereference operator.
  2. What are virtual functions - Write an example?
	 class B {
	 public:
		virtual void show() { cout << "B" << endl; }
	 };
	 class A : public B {
	 public:
		void show() { cout << "A" << endl; }
	 };
	 B* a = new A;
	 a->show();
  3. What is this pointer?
	 Is passed as a hidden argument in all non-static member function calls.
	 Is available as a local variable within the body of non-static functions.
	 'this' is a constant pointer that holds the memory address of the current
	 object.
  4. Can we do "delete this"?
	 It can be used when current object was created using new operator, otherwise
	 the behavior is undefined. Once the delete is done any member of the object
	 should not be accessed.
  5. What are VTABLE and VPTR?
	 vtable is a table of function pointers. It is maintained per class.
	 vptr is a pointer to vtable. It is maintained per object.
	 
	Part.2
	https://www.toptal.com/c-plus-plus/interview-questions
  1. What will the line of code below print out and why?
	 cout << 25u - 50;  // not -25 but 4294967271, assuming 32 bit integers
  2. C++ supports multiple inheritance. What is the "diamond problem" that can
	 occur with multiple inheritance.
  3. Assuming buf is a valid pointer, what is the problem with the code below?
	 size_t sz = buf->size();
	 while (--sz >= 0)
	 { /* do something */ }
  4. 
	 
	 
	 
	 
	 
	