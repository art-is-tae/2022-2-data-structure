#include <iostream>
using namespace std;

template <typename T>
class CPoint
{
public:
  T x;
  T y;
  const char *s;

  CPoint(T x, T y);
  void Move(T x, T y);
  template <typename CP>
  friend ostream &operator<<(ostream &os, const CPoint<CP> &cp);
};

template <typename T>
CPoint<T>::CPoint(T x, T y)
{
  this->x = x;
  this->y = y;
}

template <typename T>
void CPoint<T>::Move(T x, T y)
{
  this->x = (this->x) + x;
  this->y = (this->y) + y;
}

template <typename T>
ostream &operator<<(ostream &os, const CPoint<T> &cp)
{
  os << "(" << cp.x << ", " << cp.y << ")"
     << "\n";
  return os;
}

int main()
{
  CPoint<int> P1(1, 11);
  CPoint<double> P2(1.1, 2.2);

  P1.Move(8, 13);
  P2.Move(8.97, 20.39);
  cout << P1 << P2;

  return 0;
}