#include "Combinations.h"
#include "Permutations.h"
#include "Subset.h"
#include "SumPath.h"



int main() {
    Combinations p;
    auto res = p.combine(4, 2);
    for (int i = 0; i < res.size(); i++) {
        printVector(res[i]);
    }
}
