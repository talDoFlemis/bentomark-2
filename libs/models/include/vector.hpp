#ifndef Vector_H
#define Vector_H

class Vector {
private:
  int size;
  double *values;

public:
  Vector(int);
  int getSize();
  void setValue(int, double);
  double getValue(int);
  void printVector();

  Vector operator+(Vector);
  void operator<<(Vector);
};

#endif