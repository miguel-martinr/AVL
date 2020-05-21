/**********************************************************************
* Project           : Árboles Binarios de Búsqueda AVL
*
* Class             : arbol_avl
*
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
#include "nodo_avl.hpp"

#include <queue>

using namespace std;

template <class Clave>
using node_lvl = pair<nodo_avl<Clave>*,int>;

template <class Clave>
class arbol_avl {
 public:

   arbol_avl(void): root_(NULL) {}
   arbol_avl(nodo_avl<Clave>* root): root_(root) {}


   nodo_avl<Clave>* buscar(Clave dato);
   nodo_avl<Clave>* buscar_rama(nodo_avl<Clave>* nodo, Clave dato);

   void insertar(Clave dato);
   void insert_bal(nodo_avl<Clave>* &nodo, nodo_avl<Clave>* nuevo, bool& crece);
   void insert_rebal_izq(nodo_avl<Clave>* &nodo, bool& crece);
   void insert_rebal_dch(nodo_avl<Clave>* &nodo, bool& crece);


   void eliminar(Clave dato);
   void elimina_rama(nodo_avl<Clave>* &nodo, Clave dato, bool& decrece);
   void eliminar_rebal_izq(nodo_avl<Clave>* &nodo, bool& decrece);
   void eliminar_rebal_dch(nodo_avl<Clave>* &nodo, bool& decrece);
   void sustituye(nodo_avl<Clave>* &eliminado, nodo_avl<Clave>* &sust, bool &decrece);

   void rotacion_DD(nodo_avl<Clave>* &nodo);
   void rotacion_DI(nodo_avl<Clave>* &nodo);
   void rotacion_ID(nodo_avl<Clave>* &nodo);
   void rotacion_II(nodo_avl<Clave>* &nodo);



   ostream& print(ostream& os = cout);

 private:

   nodo_avl<Clave>* root_;

};

template <class Clave>
void arbol_avl<Clave>::eliminar(Clave dato) {
  bool decrece = false;
  elimina_rama(root_,dato,decrece);
}

template <class Clave>
void arbol_avl<Clave>::elimina_rama(nodo_avl<Clave>* &nodo, Clave dato, bool& decrece) {
  if (nodo == NULL)
    return;
  if (dato < nodo->get_dato()) {
    elimina_rama(nodo->izq_, dato, decrece);
    if (decrece)
      eliminar_rebal_izq(nodo,decrece);
  } else if (dato > nodo->get_dato()) {
    elimina_rama(nodo->dch_,dato,decrece);
    if (decrece)
      eliminar_rebal_dch(nodo,decrece);
  } else {
    nodo_avl<Clave>* eliminado = nodo;
    if (nodo->izq_ == NULL) {
      nodo = nodo->get_dch();
      decrece = true;
    } else if (nodo->get_dch() == NULL) {
      nodo = nodo->get_izq();
      decrece = true;
    } else {
      sustituye(eliminado,nodo->izq_,decrece);
      if (decrece)
        eliminar_rebal_izq(nodo,decrece);
    }
    delete eliminado;
  }

}

template <class Clave>
void arbol_avl<Clave>::sustituye(nodo_avl<Clave>* &eliminado, nodo_avl<Clave>* &sust, bool &decrece) {
  if (sust->get_dch() != NULL) {
    sustituye(eliminado, sust->dch_, decrece);
    if (decrece)
      eliminar_rebal_dch(sust,decrece);
  } else {
    eliminado->set_dato(sust->get_dato());
    eliminado = sust; // ??
    sust = sust->get_izq();
    decrece = true;
  }
}

template <class Clave>
void arbol_avl<Clave>::eliminar_rebal_dch(nodo_avl<Clave>* &nodo, bool& decrece) {
  nodo_avl<Clave>* nodo1 = nodo->get_izq();
  switch (nodo->get_bal()) {
    case 1:
      if (nodo1->get_bal() < 0)
        rotacion_ID(nodo);
      else {
        if (nodo1->get_bal() == 0)
          decrece = false;
        rotacion_II(nodo);
      }
      break;
    case 0:
      nodo->set_bal(1);
      decrece = false;
      break;
    case -1:
      nodo->set_bal(0);
  }
}


template <class Clave>
void arbol_avl<Clave>::eliminar_rebal_izq(nodo_avl<Clave>* &nodo, bool& decrece) {
  nodo_avl<Clave>* nodo1 = nodo->get_dch();
  switch (nodo->get_bal()) {
    case -1:
      if (nodo1->get_bal() > 0)
        rotacion_DI(nodo);
      else {
        if (nodo1->get_bal() == 0)
          decrece = false;
        rotacion_DD(nodo);
      }
      break;
    case 0:
      nodo->set_bal(-1);
      decrece = false;
      break;
    case 1:
      nodo->set_bal(0);
      break;
  }
}




template <class Clave>
nodo_avl<Clave>* arbol_avl<Clave>::buscar(Clave dato) {
  return buscar_rama(root_, dato);
}

template <class Clave>
nodo_avl<Clave>* arbol_avl<Clave>::buscar_rama(nodo_avl<Clave>* nodo, Clave dato) {
  if (nodo == NULL)
    return NULL;
  if (dato == nodo->get_dato())
    return nodo;
  if (dato < nodo->get_dato())
    return buscar_rama(nodo->get_izq(), dato);
  return buscar_rama(nodo->get_dch(), dato);
}


template <class Clave>
void arbol_avl<Clave>::insertar(Clave dato) {
  nodo_avl<Clave>* nuevo = new nodo_avl<Clave>(dato);
  bool crece = false;
  insert_bal(root_,nuevo,crece);
}

template <class Clave>
void arbol_avl<Clave>::insert_bal(nodo_avl<Clave>* &nodo, nodo_avl<Clave>* nuevo, bool& crece) {
  if (nodo == NULL) {
    nodo = nuevo;
    crece = true;
  } else if (nuevo->get_dato() < nodo->get_dato()) {
    insert_bal(nodo->izq_,nuevo,crece);
    crece ? insert_rebal_izq(nodo,crece) : (void)0;
  } else {
    insert_bal(nodo->dch_,nuevo,crece);
    crece ? insert_rebal_dch(nodo,crece) : (void)0;
  }

}

template <class Clave>
void arbol_avl<Clave>::insert_rebal_izq(nodo_avl<Clave>* &nodo, bool& crece) {
  switch (nodo->get_bal()) {
    case -1:
      nodo->set_bal(0);
      crece = false;
      break;
    case 0:
      nodo->set_bal(1);
      break;
    case 1:
      nodo_avl<Clave>* nodo1 = nodo->get_izq();
      (nodo1->get_bal() == 1) ? (rotacion_II(nodo)) : (rotacion_ID(nodo));
      crece = false;
      break;
  }
}

template <class Clave>
void arbol_avl<Clave>::insert_rebal_dch(nodo_avl<Clave>* &nodo, bool& crece) {
  switch (nodo->get_bal()) {
    case 1:
      nodo->set_bal(0);
      crece = false;
      break;
    case 0:
      nodo->set_bal(-1);
      break;
    case -1:
      nodo_avl<Clave>* nodo1 = nodo->get_dch();
      (nodo1->get_bal() == -1) ? (rotacion_DD(nodo)) : (rotacion_DI(nodo));
      crece = false;
      break;
  }
}

template <class Clave>
void arbol_avl<Clave>::rotacion_DI(nodo_avl<Clave>* &nodo) {
  nodo_avl<Clave>* nodo1 = nodo->get_dch();
  nodo_avl<Clave>* nodo2 = nodo1->get_izq();

  if (nodo1 && nodo2) {
    nodo->dch_ = nodo2->izq_;
    nodo2->izq_ = nodo;
    nodo1->izq_ = nodo2->dch_;
    nodo2->dch_ = nodo1;

    if (nodo2->get_bal() == 1)
      nodo1->set_bal(-1);
      else
      nodo1->set_bal(0);
    if (nodo2->get_bal() == -1)
      nodo->set_bal(1);
      else
      nodo->set_bal(0);
    nodo2->set_bal(0);
    nodo = nodo2;
  }
}

template<class Clave>
void arbol_avl<Clave>::rotacion_DD(nodo_avl<Clave>* &nodo) {
  nodo_avl<Clave>* nodo1 = nodo->get_dch();
  if (nodo1) {
    nodo->dch_ = nodo1->izq_;
    nodo1->izq_ = nodo;

    if(nodo1->get_bal() == -1) {
        nodo->set_bal(0);
        nodo1->set_bal(0);
    } else {
        nodo->set_bal(-1);
        nodo1->set_bal(1);
    }
    nodo = nodo1;
  }
}

template <class Clave>
void arbol_avl<Clave>::rotacion_ID(nodo_avl<Clave>* &nodo) {
  nodo_avl<Clave>* nodo1 = nodo->get_izq();
  nodo_avl<Clave>* nodo2 = nodo->get_dch();
  if (nodo1 && nodo2) {
    nodo->izq_ = nodo2->get_dch();
    nodo2->dch_ = nodo;
    nodo1->dch_ = nodo2->get_izq();
    nodo2->izq_ = nodo1;

    if (nodo2->get_bal() == -1)
      nodo1->set_bal(1);
      else
      nodo1->set_bal(0);
    if (nodo2->get_bal() == 1)
      nodo->set_bal(-1);
      else
      nodo->set_bal(0);
    nodo2->set_bal(0);
    nodo = nodo2;
  }
}

template <class Clave>
void arbol_avl<Clave>::rotacion_II(nodo_avl<Clave>* &nodo) {
  nodo_avl<Clave>* nodo1 = nodo->get_izq();
  nodo->izq_ = nodo->dch_;
  if (nodo1) {
    nodo1->dch_ = nodo;
    if (nodo->get_bal() == 1) {
      nodo->set_bal(0);
      nodo1->set_bal(0);
    } else {
      nodo->set_bal(1);
      nodo1->set_bal(1);
    }
    nodo = nodo1;
  }
}


template <class Clave>
ostream& arbol_avl<Clave>::print(ostream& os) {
  queue<node_lvl<Clave>> myQueue; //En la cola se guarda el nodo junto a su nivel
  int lvl = 0, current_lvl = 0;
  node_lvl<Clave> duo_aux;
  duo_aux.first = root_;
  myQueue.push(duo_aux);

  os << "Nivel 0:";

  while (!myQueue.empty()) {
    duo_aux = myQueue.front();
    myQueue.pop();

    if (duo_aux.second > current_lvl) {
      current_lvl = duo_aux.second;
      os << "\nNivel " << current_lvl << ": ";
    }
    duo_aux.first->print(os);
    if (duo_aux.first != NULL) {
      nodo_avl<Clave>* nodo_aux = duo_aux.first;
      duo_aux.first = duo_aux.first->get_izq();
      duo_aux.second++;
      myQueue.push(duo_aux);
      duo_aux.first = nodo_aux->get_dch();
      myQueue.push(duo_aux);
    }
  }
  return os;
}
