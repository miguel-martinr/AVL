#include "../include/DNI.hpp"

unsigned long DNI::cmpCount_;

DNI::DNI(void) {
    srand(time(NULL));
    num_ = rand() % 100000000;
}

DNI::DNI(unsigned long num) {
  num_ = num;
}

void DNI::operator=(const DNI& A) {
  setNum(A.getNum());
}

bool DNI::operator==(const DNI& A) {
  cmpCount_++;
  return (getNum() == A.getNum());
}

bool DNI::operator<(const DNI& A) {
  cmpCount_++;
  return (getNum() < A.getNum());
}

bool DNI::operator>(const DNI& A) {
  cmpCount_++;
  return (getNum() > A.getNum());
}
