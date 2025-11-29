# Basics

## Abstraction Mechanisms
### Types
1. Concrete type: 
   Can be instantiated using the `new` operator.
   The compiler knows the exact memory layout and size of objects at compile time, hence concrete types can be allocated on stack. 
2. Arithmetic type
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
### Class
Concepts are defined using classes. There are concrete, abstract classes, also those in hierarchies. 

A struct works the same way as a class, except for the difference that members of a class are private by 
default and members of a structure are public by default. 

## Header Files (.cpp; .h)
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




