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

---

## 2. Data and Operators

### 2.1 Types
The purpose of types is to make memory storage more efficient. The machine will allocate different storage size 
depending on types hence saving on memory space depending on the variables.

#### 2.1.1 Integer 
`short` (2 bytes), `int` (4 bytes), `long` (4 bytes under 32-bit OS and 8 under 64-bit OS) and `long long` (8 bytes) can all be used to store integers

To read the memory consumed by a variable or a type, use `sizeof()`.

#### 2.1.2 Float 
Mainly for the representation of decimals: `float` (4 bytes), `short` (8 bytes).

When declaring float type, write `f = 3.14f;`.

Scientific notations can be written as `flaot f = 3e-2;`

#### 2.1.3 Character 
A char type only takes one byte. It is not stored as the exact character but rather in the ASCII form. We can directly declare a
char type using its ASCII code, for example
```cpp
char ch = 'a';
ch = 97;
```

#### 2.1.4 String
String is an array of char (in C style)
```c
char str1[] = "hello world"; 
```
and in C++ we declare using the `string` keyword explicitly instead of `char`.

#### 2.1.5 Boolean
Takes only one byte: `0` represents false and `1` represents true. 

`~`: NEGATION

`&`: AND returns the same element only when two elements are the same, returns `0` when different)

`|`: OR returns the same element when two elements are the same, returns `1` when different

`^`: EXCLUSIVE-OR 

#### 2.1.2 Concrete Types 
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
// writing
char * p;
p = &a;
// is the equivalent of writing
char * p = &c;
// meaning p is a pointer to the memory address of c hence equivalently the memory address of 'a'
// We can read and mutate the stored data at the pointed memory address as follows
*p = 'b';
// means we take the data stored at the memory address associated with pointer p (which points to memory address storing 'a') and
// changes it to 'b'

```
which means we use a variable to point to the object referred to by `p` (that is, `a`) so `c2` essentially points to `a` now. 
We have removed the reference layer `p`.

We can therefore modify a variable's value using a pointer
```cpp
int myVariable = 10;
int* myPointer = &myVariable; // myPointer holds the memory address of myVariable
*myPointer = 20; // changes the value of myVariable to 20
```
#### 2.2.3 const Pointer

Using a `const` in front of a pointer means we can only read but not mutate the pointed data. However, we can change the referential link: the pointer can point
to something else. 

```cpp
int a = 10;
int b = 10;
const int* p = &a;

// We cannot change the pointed-to data
*p = 20; // INCORRECT

// But we can change the pointer's referential link
p = &b; // CORRECT, pointer p now points to b (10)
```

If we place  `const` after the pointer and before the variable name, we can muyate the referred data but cannot break the referential link

```cpp
int a = 10;
int b = 10;
int* const p = &a;

// We can change the pointed-to data
*p = 20; // CORRECT

// But we cannot change the pointer's referential link
p = &b; // INCORRECT
```

Finally if we want to keep both values and referential links fixed, 
```cpp
const int * const p = &a;
```

#### 2.2.4 const Pointer with Arrays
We can read the first element of an array using a pointer

```cpp
int main() {
     int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
     // initialize pointer
     int* p = arr;
     cout << *p << endl; // reads the first element arr[0]
     p++; // increment the memory address by 4 bits (because each int type consumes 4 bit memory space)
     cout << *p << endl; // reads the second element arr[1]
     ...
}
```

---

### 2.3 Functions

#### 2.3.1 Formal and Value parameters
Formal parameters are variables declared in the function's definition or signature.

Value parameters are a special case where a copy of the actual argument's value is passed to the function.

#### 2.3.2 Pass by Value
```cpp
// In the following function, num1 and num2 are formal parameters
void swap(int num1, int num2) {
     cout << num1 << endl;
     cout << num2 << endl;
     int temp = num1;
     num1 = num2;
     num2 = temp;
     cout << num1 << endl;
     cout << num2 << endl;
}

// In the main method, a and b are value parameters
int main() {
     int a = 10, b = 20;
     cout << a << endl; 
     cout << b << endl;
     swap(a, b);
     cout << a << endl;
     cout << b << endl;
}
```
Observe: formal parameters are swapped (num1, num2 change their referential links to 10, 20), but value parameters (a, b) remain the same (referential link to 10, 20 remian unchanged)

---

### 2.4 References

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







