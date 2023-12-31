#include "models/include/model.hpp"
#include <cmath>
#include <vector>

using namespace Models;
void Model::set_model_result(const Algebra::Vector &vec1,
                       const Algebra::Vector &vec2)
{
  results.steps.push_back(results.next_step());
  results.errors.push_back(getError(vec1, vec2));
  results.xs.push_back(vec2);
}

Model_Result Model::get_model_result() const {return results;}

Algebra::Vector Model::getResult() const { return this->result.front(); }

double Model::getError(const Algebra::Vector &vec1,
                       const Algebra::Vector &vec2) const {
  size_t size = vec1.getSize();

  double max = 0, max2 = 0;
  double current;
  for (int i = 0; i < size; i++) {
    current = std::abs(vec1.getValue(i) - vec2.getValue(i));
    if (current > max) {
      max = current;
    }
    if (std::abs(vec2.getValue(i)) > max2) {
      max2 = std::abs(vec2.getValue(i));
    }
  }

  return max/max2;
}

Algebra::Matrix Model::solveInverse(const Algebra::Matrix &mat, double error, int maxIttr) {
  size_t size = mat.getSize();

  std::vector<Algebra::Vector> columns;
  Algebra::Matrix inverse(size);
  Algebra::Vector aux(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        aux.setValue(j, 1);
      } else {
        aux.setValue(j, 0);
      }
    }

    this->solve(mat, aux, error, maxIttr);
    columns.push_back(this->getResult());
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
        inverse.setValue(i, j, columns[j].getValue(i)); 
    }
  }

  return inverse;
}
