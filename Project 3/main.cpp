#include <iostream>
#include <vector>
#include <cassert>
#include "mymatrix.h"


using namespace std;


bool test_default_constructor() {
    mymatrix<int> M;

    // check the number of rows and columns
    assert(M.numrows() == 4);
    assert(M.numcols(0) == 4);
    assert(M.numcols(1) == 4);
    assert(M.numcols(2) == 4);
    assert(M.numcols(3) == 4);

    // check the values of the elements
    assert(M(0, 0) == 0);
    assert(M(0, 1) == 0);
    assert(M(0, 2) == 0);
    assert(M(0, 3) == 0);
    assert(M(1, 0) == 0);
    assert(M(1, 1) == 0);
    assert(M(1, 2) == 0);
    assert(M(1, 3) == 0);
    assert(M(2, 0) == 0);
    assert(M(2, 1) == 0);
    assert(M(2, 2) == 0);
    assert(M(2, 3) == 0);
    assert(M(3, 0) == 0);
    assert(M(3, 1) == 0);
    assert(M(3, 2) == 0);
    assert(M(3, 3) == 0);

    return true;
}

bool test_parameterized_constructor() {
    mymatrix<int> M(3, 5);

    // check the number of rows and columns
    assert(M.numrows() == 3);
    assert(M.numcols(0) == 5);
    assert(M.numcols(1) == 5);
    assert(M.numcols(2) == 5);

    // check the values of the elements
    assert(M(0, 0) == 0);
    assert(M(0, 1) == 0);
    assert(M(0, 2) == 0);
    assert(M(0, 3) == 0);
    assert(M(0, 4) == 0);
    assert(M(1, 0) == 0);
    assert(M(1, 1) == 0);
    assert(M(1, 2) == 0);
    assert(M(1, 3) == 0);
    assert(M(1, 4) == 0);
    assert(M(2, 0) == 0);
    assert(M(2, 1) == 0);
    assert(M(2, 2) == 0);
    assert(M(2, 3) == 0);
    assert(M(2, 4) == 0);

    return true;
}

bool test_copy_constructor() {
    mymatrix<int> M1(3, 5);
    M1(1, 2) = 123;
    mymatrix<int> M2(M1);

    // check the number of rows and columns
    assert(M2.numrows() == 3);
    assert(M2.numcols(0) == 5);
    assert(M2.numcols(1) == 5);
    assert(M2.numcols(2) == 5);

    // check the values of the elements
    assert(M2(0, 0) == 0);
    assert(M2(0, 1) == 0);
    assert(M2(0, 2) == 0);

}

bool test_resize() {
    mymatrix<int> M(3, 5);

// check the number of rows and columns
assert(M.numrows() == 2);
assert(M.numcols(0) == 4);
assert(M.numcols(1) == 4);

// check the values of the elements
assert(M(0, 0) == 0);
assert(M(0, 1) == 0);
assert(M(0, 2) == 0);
assert(M(0, 3) == 0);
assert(M(1, 0) == 0);
assert(M(1, 1) == 0);
assert(M(1, 2) == 0);
assert(M(1, 3) == 0);

return true;

}

bool test_assignment_operator() {
    mymatrix<int> M1(3, 5);
    M1(1, 2) = 123;
    mymatrix<int> M2 = M1;
    // check the number of rows and columns
    assert(M2.numrows() == 3);
    assert(M2.numcols(0) == 5);
    assert(M2.numcols(1) == 5);
    assert(M2.numcols(2) == 5);

// check the values of the elements
    assert(M2(0, 0) == 0);
    assert(M2(0, 1) == 0);
    assert(M2(0, 2) == 0);
    assert(M2(0, 3) == 0);
    assert(M2(0, 4) == 0);
    assert(M2(1, 0) == 0);
    assert(M2(1, 1) == 0);
    assert(M2(1, 2) == 123);
    assert(M2(1, 3) == 0);
    assert(M2(1, 4) == 0);
    assert(M2(2, 0) == 0);
    assert(M2(2, 1) == 0);
    assert(M2(2, 2) == 0);
    assert(M2(2, 3) == 0);
    assert(M2(2, 4) == 0);

    return true;
}

bool test_index_out_of_range() {
    mymatrix<int> M(3, 5);
    // try to access an invalid index
    try {
        int x = M(4, 3);
    }
    catch (std::out_of_range &e) {
        return true;
    }

    return false;
}

bool test_non_square_matrix() {
    mymatrix<int> M(2, 4);
    M(0, 2) = 123;
    M(1, 1) = 456;


    // check the number of rows and columns
    assert(M.numrows() == 2);
    assert(M.numcols(0) == 4);
    assert(M.numcols(1) == 4);

// check the values of the elements
    assert(M(0, 0) == 0);
    assert(M(0, 1) == 0);
    assert(M(0, 2) == 123);
    assert(M(0, 3) == 0);
    assert(M(1, 0) == 0);
    assert(M(1, 1) == 456);
}


int main() {
    test_default_constructor();
    test_parameterized_constructor();
    test_copy_constructor();
    test_resize();
    test_assignment_operator();
    test_index_out_of_range();
    test_non_square_matrix();


return 0;
}
