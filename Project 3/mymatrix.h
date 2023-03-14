/*mymatrix.h*/

///* Header:
// * author/student: Maria Bezerra
// * netID: 676493398
// * course: CS 251 - spring 2023
// * assignment: My matrix
//
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023


//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)    ////DONE
  {
    if (R < 1)
      throw invalid_argument("mymatrix::constructor: # of rows");
    if (C < 1)
      throw invalid_argument("mymatrix::constructor: # of cols");
      Rows = new ROW[R];  // an array with 4 ROW structs:
      NumRows = R;

      // initialize each row to have C columns:
      for (int r = 0; r < NumRows; ++r)
      {
          Rows[r].Cols = new T[C];  // an array with 4 elements of type T:
          Rows[r].NumCols = C;

          // initialize the elements to their default value:
          for (int c = 0; c < Rows[r].NumCols; ++c)
          {
              Rows[r].Cols[c] = T{};  // default value for type T:
          }
      }
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other) ////DONE
  {
      NumRows = other.NumRows;
      this->Rows = new ROW[NumRows];

      for (int i = 0; i < NumRows; i++) { //create a copy of the entire Row
          Rows[i].NumCols = other.Rows[i].NumCols;
          Rows[i].Cols = new T[Rows[i].NumCols];

          for (int j = 0; j < Rows[i].NumCols; j++) {
              Rows[i].Cols[j] = other.Rows[i].Cols[j];
          }
      }
  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const    //// DONE
  {
      return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const //// DONE
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::numcols: row");

    return Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)   //// DONE
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");

    if(C<=Rows[r].NumCols){
        return;
    }

    T *temp;
    temp = new T[C];
      for (int i = 0; i < Rows[r].NumCols; i++) {
          temp[i] = Rows[r].Cols[i];
      }
      for (int j = Rows[r].NumCols; j < C; j++) {
          temp[j] = T{};
      }
      Rows[r].Cols = temp;
      Rows[r].NumCols = C;

  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 

    void grow(int R, int C)
    {
        ROW* new_rows = new ROW[R];
        int old = NumRows;

        if (R < 1) {
            throw std::invalid_argument("mymatrix::grow: # of rows");
        }
        if (C < 1) {
            throw std::invalid_argument("mymatrix::grow: # of cols");
        }

        if (R < old){
            R = old;
        }



        for (int i = 0; i < R; ++i) {
            if (i < NumRows) {
                ROW& old_row = Rows[i];
                ROW& new_row = new_rows[i];

                new_row.NumCols = std::max(C, old_row.NumCols);
                new_row.Cols = new T[new_row.NumCols];

                for (int j = 0; j < new_row.NumCols; ++j) {
                    if (j < old_row.NumCols) {
                        new_row.Cols[j] = old_row.Cols[j];
                    } else {
                        new_row.Cols[j] = T();
                    }
                }
            }

            else {
                ROW& new_row = new_rows[i];

                new_row.NumCols = C;
                new_row.Cols = new T[C];

                for (int j = 0; j < C; ++j) {
                    new_row.Cols[j] = T();
                }
            }
        }

        delete[] Rows;
        Rows = new_rows;
        NumRows = R;
    }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
   int count = 0;
      for (int i = 0; i < NumRows; ++i) {
          count += Rows[i].NumCols;
      }

    return count;
  } ////DONE


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c) const ////DONE
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");


    return Rows[r].Cols[c];
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c) const ////DONE
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    ROW &row = Rows[r];

    //T temp = {};  // we need to return something, so a temp for now:

    return row.Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar) ////DONE
  {
      mymatrix<T> result(*this); //copying const. to the results

      for (int i = 0; i < NumRows; i++){
          for (int j = 0; j < Rows[i].NumCols; j++) {
              result.Rows[i].Cols[j] = Rows[i].Cols[j] * scalar;
          }
      }
    return result;
  }


  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  //template<typename T>
  mymatrix<T> operator*(const mymatrix<T>& other) {
      mymatrix<T> result;
      result.NumRows = NumRows;
      result.Rows = new ROW[NumRows];

      int thisCols = Rows[0].NumCols;
      int otherCols = other.Rows[0].NumCols;

      bool isThisRectangular = true;
      bool isOtherRectangular = true;

      // Check if both matrices are rectangular
      for (int i = 1; i < NumRows; i++) {
          if (Rows[i].NumCols != thisCols) {
              isThisRectangular = false;
              break;
          }
      }
      for (int i = 1; i < other.NumRows; i++) {
          if (other.Rows[i].NumCols != otherCols) {
              isOtherRectangular = false;
              break;
          }
      }

      // Throw an error if either matrix is not rectangular
      if (!isThisRectangular) {
          throw runtime_error("mymatrix::*: this not rectangular");
      }
      if (!isOtherRectangular) {
          throw runtime_error("mymatrix::*: other not rectangular");
      }

      // Check if the matrices can be multiplied
      if (thisCols != otherCols) {
          throw runtime_error("mymatrix::*: size mismatch");
      }

      // Multiply the matrices
      for (int i = 0; i < NumRows; i++) {
          result.Rows[i].NumCols = other.Rows[0].NumCols;
          result.Rows[i].Cols = new T[other.Rows[0].NumCols];

          for (int j = 0; j < other.Rows[0].NumCols; ++j) {
              T total = 0;
              for (int k = 0; k < thisCols; ++k) {
                  total += Rows[i].Cols[k] * other.Rows[k].Cols[j];
              }
              result.Rows[i].Cols[j] = total;
          }
      }

      return result;
  }



  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
