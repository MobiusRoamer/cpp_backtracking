# Handling Numbers in C, C++

## 1. Binary

### 1. Binary Exponentiation
**See Leetcode 50. Pow(x, n)**
An algorithm that calculates large powers of numbers in the form of `a^n`

The following solution works, but runs into stack overflow for large `n`
```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) { return 1; }
        double res;
        if (n < 0) { 
            res = 1 / recurse(x, x, abs(n + 1));
        }
        res = recurse(x, x, n - 1);
        return res;
    }

private: 
    double recurse(double x, double currNum, int n) {
        if (n == 0) { return currNum; }
        currNum *= x;
        return recurse(x, currNum, n-1);
    }
};
```

For example, if the base is `x = 1.0` but `n = 100000000`, the stack explodes. 

Steps: 
- Convert exponent n to binary
- Initialize result - 1, base = a
- Iterate through each bit of the binary rep of `n` from right to left. If current bit is 1, multiply result by current base and square the base
