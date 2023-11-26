#include "models/include/matrix.hpp"
#include "models/include/model.hpp"
#include "models/include/gauss_jacobi.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;





int main(int argc, char *argv[]) {
  
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << ".______    _______ .__   __. .___________.  ______      ___     ______  .___  ___.      ___      .______       __  ___" << std::endl;
    std::cout << "|   _  \\  |   ____||  \\ |  | |           | /  __  \\    /  /    /  /\\  \\ |   \\/   |     /   \\     |   _  \\     |  |/  /" << std::endl;
    std::cout << "|  |_)  | |  |__   |   \\|  | `---|  |----`|  |  |  |  /  /    /  /  \\  \\|  \\  /  |    /  ^  \\    |  |_)  |    |  '  /" << std::endl;
    std::cout << "|   _  <  |   __|  |  . `  |     |  |     |  |  |  | <  <    /  /    >  >  |\\/|  |   /  /_\\  \\   |      /     |    <" << std::endl;
    std::cout << "|  |_)  | |  |____ |  |\\   |     |  |     |  `--'  |  \\  \\  /  /    /  /|  |  |  |  /  _____  \\  |  |\\  \\----.|  .  \\" << std::endl;
    std::cout << "|______/  |_______||__| \\__|     |__|      \\______/    \\__\\/__/    /__/ |__|  |__| /__/     \\__\\ | _| `._____||__|\\__\\" << std::endl;
  std::cout << "\n\n\n\n\n";
  
  
  
  int n;

  
  std::cout << "Insira o tamanho da matriz N x N: ";
  while (!(std::cin >> n)) {
    std::cout << "Entrada inválida. Insira um número inteiro \n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Insira o tamanho da matriz N x N: ";
  };

  double matrizA[n][n];
  double vetorB[n];
  double vetorD[n];

  Matrix m(n);
  Vector v(n);
  
  double insert;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << "Insira o valor da posição [" << i << "][" << j << "]: ";
      while (!(std::cin >> insert)) {
        std::cout << "Entrada inválida. Insira um número real \n";
        std::cin.clear();
        std::cin.ignore(255, '\n');
        std::cout << "Insira o valor da posição [" << i << "][" << j << "]: ";
      };
      m.setValue(i, j, insert);
      matrizA[i][j] = insert;
    }
  }

  for (int i = 0; i < n; i++) {
    std::cout << "Insira o valor da posição [" << i << "] de  B: ";
    while (!(std::cin >> insert)) {
      std::cout << "Entrada inválida. Insira um número real \n";
      std::cin.clear();
      std::cin.ignore(255, '\n');
      std::cout << "Insira o valor da posição [" << i << "] de B: ";
    };
    
    vetorB[i] = insert;
    v.setValue(i, insert);
  }

  double error;
  std::cout << "Insira o valor do erro aceitável: ";
  while (!(std::cin >> error)) {
    std::cout << "Entrada inválida. Insira um número real \n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Insira o valor do erro aceitável: ";
  }
  std::cout << "\n\n\nMatriz A:\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        std::cout << std::setw(5) << matrizA[i][j];
    }
    std::cout << "\n";
  }
  std::cout << "\nVetor B:\n";
  for (int i =0; i < n; i++) {
    std::cout << std::setw(5) << vetorB[i]<< std::endl;
  }

  std::cout << "\n\n";

  Model* models[3];
  Model* jacobi = new GaussJacobi();

  jacobi->solve(m, v, error, 1000);
  Vector v2 = jacobi->getResult();
  std::cout << "Vetor D:\n";
  for(int i = 0; i < n; i++){
    vetorD[i] = v2.getValue(i);
    std::cout << std::setw(5) << vetorD[i]<< std::endl;
  }
  std::cout << "\n\n";

  return 0;
}
