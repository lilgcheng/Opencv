#include <stdio.h>
#include<stdlib.h>
int ack(int m, int n);

int main()
{
  for (int i = 0; i < 3; ++i){
    for (int j = 0; j < 3; ++j){
      printf("ack(%d,%d) = %d\n", i, j, ack(i,j));
	}
  }
  system("pause");
}

int ack(int m, int n)
{
  if (m == 0) return n+1;
  if (n == 0) return ack( m - 1, 1 );
  return ack( m - 1, ack( m, n - 1 ) );
}
