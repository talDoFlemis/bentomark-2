#include "models/include/model.hpp"

class GaussJacobi : public Model {
public:
  void solve(Matrix, Vector, double, int);
};