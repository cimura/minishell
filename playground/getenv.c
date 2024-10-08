#include <stdio.h>
#include <stdlib.h>

/*
 * getenvの使い方サンプル
 */
int main(int argc, char *argv[]) {
  char *envp = getenv("PATH");
  int debug = 0;

  if (envp != NULL) {
    // 環境変数 PATH の定義がある場合、debug = 1
    fprintf(stdout, "PATH=%s\n", envp);
    debug = 1;
  }
//  if (debug) {
//    // debug = 1の時だけ
//    fprintf(stdout, "PATH:%s\n", "<<<debug start>>>");
//  }
//
//  fprintf(stdout, "getenv sample program!\n");
//
//  if (debug) {
//    // debug = 1の時だけ
//    fprintf(stdout, "PATH:%s\n", "<<<program end>>>");
//  }
  return 0;
}
