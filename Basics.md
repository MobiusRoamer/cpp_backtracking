# Basics

## Header Files (.cpp; .h)
When we have a large amount of functions we need to organise them in a smarter way. 
We create a separate source `.cpp` file with functionalities and a header file that enables us to include the source file. 

In particular we can
- In the root directory make a new `cpp` file called `main.cpp`
- Make a new directory, called "includes"
- Make a new `func.cpp` file, write functionalities we wish to outsource to this file
- Back in the `main.cpp`, at the top write `#include "includes/func.cpp"`

But this is bad practice. Doing so means all the cpp functionalities are public to the reader. In many situations we wish to 
obscure the real functionalities' logic but only expose the high level framework. 
Now: 
- In dir "includes", create the same-name file called `func.h` but ending with a header. 
- Transport all methods in `func.cpp` over but remove the method bodies, keep the signature only
- now in `main.cpp`, at the top write `#include "includes/func.h"` (this is our source file)


But don't compile directly, we are not accessing any functionalities yet. We need to compile `func.cpp` 
