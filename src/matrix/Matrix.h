#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
   friend std::ostream &operator<<(std::ostream &, const Matrix &);
   friend std::istream &operator>>(std::istream &, const Matrix &);
   friend Matrix operator*(double escalar, const Matrix &m);

public:
   explicit Matrix(unsigned int rows = 2, unsigned int columns = 2);
   ~Matrix();
   Matrix(const Matrix &);

   const Matrix &operator=(const Matrix &);
   Matrix operator+(const Matrix &) const;
   Matrix operator*(const Matrix &) const;
   Matrix operator*(double escalar) const;

   void transposed();
   Matrix adjunta() const;
   double determinant() const;
   unsigned get_rows() const;
   unsigned get_columns() const;
   unsigned get_elements() const;
   double get_elmentij(const unsigned i, const unsigned j) const;
   void set_elementij(const unsigned i, const unsigned j, double value);
   Matrix inverse();

private:
   static double get_cofactorij(unsigned i, unsigned j, const Matrix &m);
   double *data;
   unsigned int rows, columns;
};

#endif
