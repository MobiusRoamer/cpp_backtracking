# Basics

---
**Table of Contents**

**1 Header Files**

**2 Primitive Data Types**

**3 Generic Data Type**

**4 Pointers and References**

**5 Functions**

**6 (IMPORTANT) Memory Management**

---

## 1. Header Files
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

## 2. Primitive Data Types

The purpose of types is to make memory storage more efficient. The machine will allocate different storage size 
depending on types hence saving on memory space depending on the variables.

#### 2.1 Integer 
`short` (2 bytes), `int` (4 bytes), `long` (4 bytes under 32-bit OS and 8 under 64-bit OS) and `long long` (8 bytes) can all be used to store integers

To read the memory consumed by a variable or a type, use `sizeof()`.

#### 2.2 Float 
Mainly for the representation of decimals: `float` (4 bytes), `short` (8 bytes).

When declaring float type, write `f = 3.14f;`.

Scientific notations can be written as `flaot f = 3e-2;`

#### 2.3 Character 
A char type only takes one byte. It is not stored as the exact character but rather in the ASCII form. We can directly declare a
char type using its ASCII code, for example
```cpp
char ch = 'a';
ch = 97;
```

#### 2.4 String
String is an array of char (in C style)
```c
char str1[] = "hello world"; 
```
and in C++ we declare using the `string` keyword explicitly instead of `char`.

#### 2.5 Boolean
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
## 3. Generic Data Types

### 3.1 Struct

#### 3.1.1 Defining `struct`
Suppose we define a 2D location data type
```cpp
struct Location { int x, y; };
```

We can create a `Location` in three different ways
- Method 1: field value assignment
```cpp
// first create an instance, then assign field values
struct Location l1;
l1.x = 3;
l1.y = 3;
```
- Method 2: direct creation using `{}`
```cpp
Location l1 = {3, 3};
```
- Method 3 (not recommended for most cases, but works)
```cpp
// initalize location named l1
struct Location { int x, y; }l1;
// then assign values
s3.x = 3;
s3.y = 3;
```

#### 3.1.2 Array of `struct`
Suppose we wish to create an array of a `struct` data type
```cpp
struct Location locArr[2] =
{
     {2, 1};
     {2, 2};
};
```
and we can mutate the field value of a `struct` item in the array as follows
```cpp
locArr[2].y = 3;
```

#### 3.1.3 Pointers to `struct`
Suppose 
```cpp
struct Location l1 = {3, 3};
```
We can link a pointer to the struct field variable as follows 
```cpp
// A pointer Location* means the pointer points to a data type "Location"'s memory address
struct Location* p = &l1;
```
We can use the pointer to access the field values of the struct. Importantly, accessing a field value using a pointer requires the arrow `->` 
```cpp
int xLoc = p -> x;
```
#### 3.1.4 Nested `struct` 
```cpp
struct Location { int x, y; };
struct Machine {
     int id;
     struct Location location;
     double gpu;
     ...
};
```
---


## 4. Pointers and References

### 4.1 Pointers
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
to look at a specific memory address to instruct it where the data lives. 
#### 4.1.1 Creating a Pointer
Pointers are created using the `&` operator. This operator can be applied to any C++ expression that is categorized as 
`lvalue`, an expression that can appear on teh left side of an assignment.
#### 4.1.2 Dereferencing 
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
#### 4.1.3 const Pointer

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

#### 4.1.4 Reading the First Element of Array using Pointer
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

### 4.2 Reference
A reference variable declared using a `&` in front is commonly used for giving variables an alias. It creates a referential link between two variables. 

For example
```cpp
int main() {
     int a = 10;
     // Let b be an alias of a, so both a and b are variable names pointing to the same memory address
     &b = a;

     cout << a << endl;
     cout << b << endl;
     // Expect: 10, 10

     // When mutating the reference b, we expect a to change synchronously
     b = 100;

     cout << a << endl;
     cout << b << endl;
     // Expect: 100, 100
}
```

References must be initialized. For example
```cpp
int a = 10;
&b = a;
// CORRECT

// however,
int &b; // The line by itself is incorrect
```

Once initialized, the referential link cannot be mutated. For example
```cpp
int a = 10;
int &b = a;
int c = 20;
b = c; // means we mutate the value that b points to. Since a and b point to the same memory address, a will be mutated to 20 as well.
```

---

## 5. Functions

### 5.1 Formal and Value parameters
Formal parameters are variables declared in the function's definition or signature.

Value parameters are a special case where a copy of the actual argument's value is passed to the function.

### 5.2 Passing by Value
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

### 5.3 Passing by Address
Still consider the swap function defined as before, now
```cpp
// Note in the following function we are passing the memory addresses of num1 and num2 into the function 
void swap(int *num1, int *num2) {
     int temp = *num1;
          // temp stores the data located at the memory address pointed to by num1 (10 in this case)

     *num1 = *num2;
          // this mutates the value parameter, the data stored by pointer num2 is given to the address pointed to by num1

     *num2 = temp;
          // num 2 is given the data stored at temp (and temp stores the data pointed to by num1)
          // Hence, num2 is assigned the data pointed to by num1 
}

int main() {
     int a = 10, b = 20;
     swap(&a, &b);
     cout << a << endl;
     cout << b << endl;
}
```
In the main method we are passing by address. This changes the value parameters, contrasting the mutation of formal paraneters in the case
of passing by values.


Passing by address also enables us to pass an array into a function without explicitly declaring the array [] as an input, rather by referencing the 
first element's memory address: 
```cpp
void bubbleSort(int* arr, int length) {
               // Because one can access an array by accessing its first element (arrays are contiguous), let the pointer refer to the memory address of element indexed 0
               // alternatively write int[] arr
     for (int i = 0; i < length; i++) {
          for (int j = 0; j < length - i - 1; j++) {
               if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j] = temp;
               }
          } 
     }
}
```

### 5.4 Passing by Reference
Passing by reference means we pass an alias pointing to a variable. When fed into functions as argument, the function can mutate the referenced variable on th eobject level. 

Do not return references to local constants. 
For example, 
```cpp
int& func() {
     int a = 10; // a local constant
     return a;
}

int main() {
     int &ref = func();
     cout << ref << endl; // works fine, prints 10 
     cout << ref << endl; // doesn't work anymore, local variables are released upon termination of the function
}
```

---


## 3. (IMPORTANT) Machine Level Language
### 3.1 Object Oriented
When executing programs, memory management is peformed by four components. 

Upon successful compilation, an `.exe` file is generated wich contains the executable programs. Prior to execution
1. Code/Text:
   
   stores the binary code to be executed by CPU. It is generated once (to handle repeated executions of the same code), and read-only. 
2. Global:

   stores global constants. The operating system instead of the developer determines the life / death of data stored here. They are usually variables declared outside any functions, or using `static` if placed within a function. 

3. Stack
4. Heap
   
   

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



























