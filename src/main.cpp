/**********************************************************************
* Project           : Árboles Binarios de Búsqueda
*
* file              : Programa que contiene dos modos (demo y estadístico) para
*                     el uso de árboles binarios de búsqueda balanceados
*                     * Demo:        Permite insertar y eliminar elementos de un árbol a mano, visualizando el árbol en cada paso.
*
*                     * Estadístico: Permite realizar un experimento con los parámetros introducidos por el usuario y visualizar
*                                    los resultados del mismo (éstudio de comparaciones entre claves).
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
* 20200520   miguel-martinr      1      ...
*
**********************************************************************/
#include "../include/DNI.hpp"
#include "../include/arbol_avl.hpp"
#include "../include/experimento/exp.hpp"

#include <iostream>
#include <string>

using namespace std;


int estad(void) {
  int tree_size, nPruebas; // Parámetros del experimento
  cout << "\n\n      MODO ESTADÍSTICO\n\n";
  cout << endl << "Introduzca los parámetros del experimento:" << endl
       << "  * Tamaño del árbol > "; cin >> tree_size;
  cout << "  * Número de pruebas > "; cin >> nPruebas;
  arbol_avl<DNI> myTree;
  exp myExp(tree_size, nPruebas, &myTree);
  myExp.run(cout);
  return 0;
};




int demo(void) {
  cout << "\n\n      MODO DEMOSTRACIÓN\n\n";
  arbol_avl<DNI> myTree;
  cout << "\nÁrbol vacío\n";
  cout << endl;

  int opt;
  bool quit = false;
  do {
    cout << endl;
    cout << "\n           TRAZA AVL";
    cout << "\n  Miguel Alejandro Martín Reyes\n\n";
    myTree.print();
/*    cout << "\nEl árbol" << (myTree.equilibrado() ? "  " : " no ")
         << "está equilibrado.\n";*/
    cout << endl;
    do {
      cout <<  "\n[0] Salir\n"
           <<  "[1] Insertar Clave\n"
           <<  "[2] Eliminar Clave\n\n"
           <<  "Seleccione una opción > ";
      cin >> opt;
    } while (opt < 0 || opt > 2);

    long int mydni;
    switch (opt) {
      case 0:
        quit = true;
        break;
      case 1:
        cout << "\nIntroduzca una clave >";
        cin >> mydni;
        myTree.insertar(DNI(mydni));
        break;
      case 2:
        cout << "Introduzca la clave a eliminar >";
        cin >> mydni;
        myTree.eliminar(DNI(mydni));
        break;

      default:
        break;
    }
  } while (!quit);

  return 0;
}



int main(void) {

  cout << "       Árboles Binarios de Búsqueda " << endl << endl;


  int modo = 0;
  bool quit = false;

  do {
    do {
      cout << "[0] Salir" << endl
           << "[1] Demostración" << endl
           << "[2] Estadistico" << endl << endl
           << "Seleccione una opción >";
      cin >>modo;
    } while (modo < 0 || modo > 2);

    if (modo == 0)
      quit = true;
      else if (modo == 1)
        demo();
      else
        estad();
    cout << endl << endl;
  } while (!quit);
  return 0;
}
