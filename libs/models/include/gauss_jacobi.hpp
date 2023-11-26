#include "models/include/model.hpp"

class GaussJacobi : public Model {
public:
  void solve(const Matrix &, const Vector &, double, int) override;
};
