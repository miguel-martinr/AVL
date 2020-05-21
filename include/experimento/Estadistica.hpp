/**********************************************************************
* Project           : Árboles Binarios de búsqueda
*
* Class             : Estadística
*
* Author            : Miguel Alejandro Martín Reyes (miguel-martinr)
* e-mail            : alu0101209777@ull.edu.es
* github            : https://github.com/miguel-martinr
*
* Date created      : 20200420
*
* References  :
*
*
* Revision History  :
*
* Date        Author              Ref    Revision
* 20200420    miguel-martinr      1      ...
*
**********************************************************************/
#pragma once


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Estadistica {
 public:
  Estadistica(void): min_(1.79769e+308), avg_(0), max_(0), its_(0),
                     cmps_(0) {}
  ~Estadistica(void) {}

  void reset(void);
  void update(double data);

  ostream& print(ostream& os, string rot);


   double min_;
   double avg_;
   double max_;
   double its_;
   double cmps_;
};

void Estadistica::reset(void) {
  min_ = 1.79769e+308;
  avg_ = 0;
  max_ = 0;
  its_ = 0;
  cmps_ = 0;
}
void Estadistica::update(double data) {
  its_++;
  cmps_ += data;
  avg_ = cmps_ / its_;
  if (data > max_)
    max_ = data;
  if (data < min_)
    min_ = data;
}

ostream& Estadistica::print(ostream& os, string rot) {
  os << setw(15) << left << rot << setw(10) << left << min_
                                << setw(10) << left << avg_
                                << setw(10) << left << max_;
  return os;
}
