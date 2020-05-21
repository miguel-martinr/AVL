/**********************************************************************
* Project           : Árboles Binarios de Búsqueda AVL
*
* Class             : nodo_avl
* Author            : Miguel Alejandro Martín Reyes (miguel-martinr)
* e-mail            : alu0101209777@ull.edu.es
* github            : https://github.com/miguel-martinr
*
* Date created      : 20200520
*
* References  :
*
*
*
* Revision History  :
*
* Date        Author              Ref    Revision
* 20200520    miguel-martinr      1      ...
*
**********************************************************************/
#pragma once

#include <iostream>

using namespace std;

template <class Clave>
class nodo_avl {
 public:

   nodo_avl(void): izq_(NULL), dch_(NULL), dato_(), bal_(0) {}
   nodo_avl(Clave clave, nodo_avl<Clave>* izq = NULL, nodo_avl<Clave>* dch = NULL):
           dato_(clave), izq_(izq_), dch_(dch_), bal_(0) {}

   Clave get_dato(void) { return dato_; }
   nodo_avl<Clave>* get_izq(void) { return izq_; }
   nodo_avl<Clave>* get_dch(void) { return dch_; }
   int              get_bal(void) { return bal_; }

   void set_dato(Clave dato) { dato_ = dato; }
   void set_bal(int bal) { bal_ = bal; }

   void set_izq(nodo_avl<Clave>* nodo) { izq_ = nodo; } //*
   void set_dch(nodo_avl<Clave>* nodo) { dch_ = nodo; } //*

   ostream& print(ostream& os = cout);

   nodo_avl<Clave>* izq_;
   nodo_avl<Clave>* dch_;

 private:
   int bal_;
   Clave dato_;
};


template <class Clave>
ostream& nodo_avl<Clave>::print(ostream& os) {
  if (this == NULL)
   os << "[.]";
   else
   os << '[' << dato_ << ']';
  return os;
}
