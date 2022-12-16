#include <iostream>
using namespace std;

template <typename T>
class CPoint
{
public:
  T x;
  T y;

  CPoint(T x, T y);
  void Move(T x, T y);
  void Print();
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
void CPoint<T>::Print() { cout << '(' << x << ", " << y << ')' << "\n"; }

int main()
{
  CPoint<int> P1(1, 2);
  CPoint<double> P2(1.1, 2.2);

  P1.Move(2, 3);
  P2.Move(2.2, 3.3);
  P1.Print();
  P2.Print();

  return 0;
}