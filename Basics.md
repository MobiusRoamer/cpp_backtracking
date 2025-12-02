# Basics


## 1. Header Files (.cpp; .h)
When we have a large amount of functions we need to organize them in a smarter way.
We create a separate source `.cpp` file with functionalities and a header file that enables us to include the source file.

In particular we can
- In the root directory make a new `cpp` file called `main.cpp`
- Make a new directory, called "includes"
- Make a new `func.cpp` file, write functionalities we wish to outsource to this file
- Back in the `main.cpp`, at the top write `#include "includes/func.cpp"`
```
/root
|____main.cpp
|____/includes
     |____func.cpp
```
But this is bad practice. Doing so means all the cpp functionalities are public to the reader. In many situations we wish to
obscure the real functionalities' logic but only expose the high level framework.
Now:
- In dir "includes", create the same-name file called `func.h` but ending with a header.
- Transport all methods in `func.cpp` over but remove the method bodies, keep the signature only
- Now in `main.cpp`, at the top write `#include "includes/func.h"` (this is our source file)
```
/root
|____main.cpp
|____/includes
     |____func.cpp
     |____func.h
```

But don't compile directly, we are not accessing any functionalities yet. We need to first compile `func.cpp`.

## 2. Machine-Level Code

### 2.1 Types
The purpose of types is to make memory storage more efficient. The machine will allocate different storage size 
depending on types hence saving on memory space depending on the variables.

#### 2.1.1 Integer Types
`short` (2 bytes), `int` (4 bytes), `long` (4 bytes) and `long long` (8 bytes) can all be used to store integers

To read the memory consumed by a variable, use `sizeof()`
#### 2.1.2 Concrete type: 
   Can be instantiated using the `new` operator.
   The compiler knows the exact memory layout and size of objects at compile time, hence concrete types can be allocated on stack. 
#### 2.1.3 Arithmetic type
   ```cpp
   class complex {
        double re, im;

   // Constructors
   public:
        complex(double r, rouble i) :re{r}, im{i} {}
        complex(double r) :re{r}, im{0} {}
        complex(double i) :re{0}, im{i} {}
        complex() :re{0}, im(0) {}

   // getters
        double real() const { return re; } // const signifies that this member function will not modify any of the object's member variables
        double imag() const  {return im; } // const is for safety!
   // assignment
        void real(double d) { re = d; }
        void imag(double d) { im = d; }

   // operations
        complex& operator += (complex z) { re += z.re, im += z.im; return *this; }
        complex& operator -= (complex z) { re -= z.re, im -= z.im; return *this; }
        complex& operator *= (complex z);
        complex& operator /= (complex z);
   ```
   
---

### 2.2 Pointers
Pointers are abstraction that aim to help programmers avoid addressing errors. A pointer has two aspects, value and type. 
Value indicates the location of some object and the type indicates what kind of object is stored at that location. 

For a type `T`, `T*` is a variable of type `T*` that can hold the address of an object of type `T`. 

For a variable `V`, `*V` is the value at the address pointed to by the generic variable `V`.
 ```cpp
 int *up; // variable ip is  apointer to an object of type int
 char **cpp; // cpp is a pointer to an object that is itself a pointer to a character variable
 ```
The special type `void*` represents a generic pointer for which we do not know the type it refers to. 

We can assign variables using pointers, 
```cpp
char c = 'a';
char* p = &c; // p holds the address of c; & is the "address-of" operator
```

Before considering what pointers can do, it is useful to understand why we need pointers in C++.
C++ also C closest to machine-level thinking stores memory in a contiguous array. A pointer tells the machine
to look at a specific memory address to instruct it where the data lives. The concept is native to the hardware memory management. 
#### 2.2.1 Creating a Pointer
Pointers are created using the `&` operator. This operator can be applied to any C++ expression that is categorized as 
`lvalue`, an expression that can appear on teh left side of an assignment.
#### 2.2.2 Dereferencing 
Pointers are dereferenced using the `*` operator. This gives back a value having the type associated with the pointer. 
Note we can dereference as follows
```cpp
char c = 'a';
char* p = &c;
char c2 = *p;
```
which means we use a variable to point to the object referred to by `p` (that is, `a`) so `c2` essentially points to `a` now. 
We have removed the reference layer `p`.

We can therefore modify a variable's value using a pointer
```cpp
int myVariable = 10;
int* myPointer = &myVariable; // myPointer holds the memory address of myVariable
*myPointer = 20; // changes the value of myVariable to 20
```
### 2.3 References

Pointers initialize object's memory position, while references is a second name for an existing object. 

---
### Overloading
A compile time polymorphism in where the compiler infers which of the functions sharing the same name to call depending on input arguments. 

Overloading is usually applied to operators. An operator function must either be a member r take at least one argument of a user-defined type.

In particular, it is impossible to define an operator function that operates exclusively on pointers. 
The template of overloading, for example, the addition operator `+=`, with generic class, is 
```cpp
MyClass& operator += (const MyClass& other) {
   // Implementation to add 'other' to 'this' object
   //...
   // return *this;
}

// for example
enum Day { sun, mon, tue, wed, thu, fri, sat }
Day& operator++(Day& d)
{
   return d = (sat == d) ? sum : static_cast<Day>(d + 1); // data type cast
}
```


### Class
Concepts are defined using classes. There are concrete, abstract classes, also those in hierarchies. 

A struct works the same way as a class, except for the difference that members of a class are private by 
default and members of a structure are public by default. 
