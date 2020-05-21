/**********************************************************************
* Project           : Árboles Binarios de Búsqueda
*
* Class             : Experimento
*
* Author            : Miguel Alejandro Martín Reyes (miguel-martinr)
* e-mail            : alu0101209777@ull.edu.es
* github            : https://github.com/miguel-martinr
*
* Date created      : 20200405
*
* References  :
*
*
*
* Revision History  :
*
* Date        Author              Ref    Revision
* 20200415    miguel-martinr      1      ...
* 20200511    miguel-martinr      2      Modif para árboles
* 20200520    miguel-martinr      3      Modif para AVL
**********************************************************************/
#pragma once
#include "Estadistica.hpp"
#include "../DNI.hpp"
#include "../arbol_avl.hpp"

#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class exp {
 public:
   exp(int tree_size, int nPruebas, arbol_avl<DNI>* arbol);
   ~exp(void) { delete testRepo_; }

   int resizeRepo(void);
   int initRepo(void);
   int loadTree(void);
   int run(ostream& os = cout);

   int search(void);
   int insert(void);

   ostream& print(ostream& os = cout);

   Estadistica srch_;
   Estadistica insrt_;


 private:
   int tree_size_;
   int nPruebas_;
   vector<DNI>* testRepo_;
   arbol_avl<DNI>* arbol_;

};

exp::exp(int tree_size, int nPruebas, arbol_avl<DNI>* arbol) {
  nPruebas_ = nPruebas;
  tree_size_ = tree_size;
  arbol_ = arbol;
  resizeRepo();
  initRepo();
  loadTree();
}


int exp::initRepo(void) {
  if (testRepo_->size() == 0)
  return 0;
  srand(time(NULL));
  (*testRepo_)[0] = DNI(rand() % 100000000);
  for (int i = 1; i < testRepo_->size(); i++) {
    srand((*testRepo_)[i-1]);
    (*testRepo_)[i] = DNI(rand() % 100000000);
  }
  return 0;
}

int exp::resizeRepo(void) {
  int sizeRepo = 2*tree_size_;
  testRepo_ = new vector<DNI>(sizeRepo);
  return 0;
}

int exp::loadTree(void) {
  for (int i = 0; i < testRepo_->size()/2; i++)
    arbol_->insertar((*testRepo_)[i]);
  return 0;
}

int exp::search(void) {
  srch_.reset();
  srand(time(NULL));
  int aleat_pos;
  for (int i = 0; i < nPruebas_; i++) {
    DNI::cmpCount_ = 0;
    aleat_pos = rand() % (testRepo_->size()/2)+1;
    arbol_->buscar((*testRepo_)[aleat_pos]);
    srch_.update(DNI::cmpCount_);
    srand(rand());
  }
  return 0;
}

int exp::insert(void) {
  insrt_.reset();
  srand(time(NULL));
  int aleat_pos;
  int mid = testRepo_->size()/2;
  for (int i = 0; i < nPruebas_; i++) {
    DNI::cmpCount_ = 0;
    aleat_pos = (rand() % mid) + mid;  //Posiciones en el rango [mid, size()-1]
    arbol_->buscar((*testRepo_)[aleat_pos]);
    insrt_.update(DNI::cmpCount_);
    srand(rand());
  }
  return 0;
}


int exp::run(ostream& os) {
  search();
  insert();
  print(os);
  return 0;
}



ostream& exp::print(ostream& os) {
  os << "\n         Tamaño Árbol    Nº Pruebas";
  os << "\n              " << tree_size_ << "           " << nPruebas_ << endl;

  os << "\n                     Número de comparaciones";
  os << "\n\n               Mínimo    Medio     Máximo" << endl;
  os << ' ';
  srch_.print(os, "Búsquedas");
  cout << endl;
  insrt_.print(os, "Inserciones");
  cout << endl;
  return os;
}
