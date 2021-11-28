#include <stdio.h>
 
int main(void) {

  int num = 1; // int型変数
  int *p_num; // int型ポインタ変数
  p_num = &num; // ポインタ変数p_numに変数numアドレスを代入
  
  printf("num: %d\n", num);
  printf("p_num: %p\n", p_num);

  return 0;
  
}
