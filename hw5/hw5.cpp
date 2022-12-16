#include <iostream>
#include "post.h"
using namespace std;
void Postfix(Expression);
int main()
{
  char line[MAXLEN];
  while (cin.getline(line, MAXLEN))
  {
    Expression e(line); // line 버퍼를 이용하여 Expression을 읽음
    try
    {
      // cout << "C011060\n";
      Postfix(e);
    }
    catch (char const *msg)
    {
      cerr << "Exception: " << msg << endl;
    }
  }
  return 0;
}