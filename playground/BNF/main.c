#include "bnf.h"

int main() {
    // 計算結果保持変数
    int res;
    // 一括代入（右結合の確認）
    const char *test = NULL;
    expr("tx = ty = tz = 6", &test);
    printf("\n== 一括代入（右結合の確認）tx ==\n");
    test = NULL;
    res = expr("tx", &test);
    print(6, res);
    printf("\n== 一括代入（右結合の確認）ty ==\n");
    test = NULL;
    res = expr("ty", &test);
    print(6, res);
    printf("\n== 一括代入（右結合の確認）tz ==\n");
    test = NULL;
    res = expr("tz", &test);
    print(6, res);

    // 20 - 単純な計算 : OK
    printf("\n== 単純な計算 ==\n");
    const char *one = NULL;
    res = expr("1+2*5+9", &one);
    print(20, res);

    // 100 - 複数桁の単純な計算 : OK
    printf("\n== 複数桁の単純な計算 ==\n");
    const char *two = NULL;
    res = expr("10+20+10+30*2", &two);
    print(100, res);

    // 35 - カッコを含む計算 : OK
    printf("\n== カッコを含む計算 ==\n");
    const char *three = NULL;
    res = expr("(2*5)+5*2+15", &three);
    print(35, res);

    // 50 - 複数のカッコを含む計算 : OK
    printf("\n== 複数のカッコを含む計算 ==\n");
    const char *four = NULL;
    res = expr("(2*5)+2*(5+15)", &four);
    print(50, res);

    // 20 - 空白を含む単純な計算 : OK
    printf("\n== 空白を含む単純な計算 ==\n");
    const char *five = NULL;
    res = expr("1 + 2 * 5 + 9", &five);
    print(20, res);

    // TODO: ネストされてると動かない
    // 50 - カッコにカッコが含まれる計算 : NG
    printf("\n== カッコにカッコが含まれる計算 ==\n");
    const char *six = NULL;
    res = expr("(5+(1+2*2))*5", &six);
    print(50, res);

    // 7 - 剰余演算子を含む計算 : OK
    printf("\n== 剰余演算子を含む計算 ==\n");
    const char *seven = NULL;
    res = expr("5 + 5 % 3", &seven);
    print(7, res);

    // 5 - 複数の変数が複数個を含んだ計算 : OK
    printf("\n== 複数の変数が複数個を含んだ計算 ==\n");
    const char *eight = NULL;
    expr("a = 3", &eight);
    eight = NULL;
    expr("b = 2", &eight);
    eight = NULL;
    res = expr("a+b", &eight);
    print(5, res);
    // 8 - 複数の変数が複数個を含んだ計算 : OK
    printf("\n== 複数の変数が複数個を含んだ計算 ==\n");
    const char *nine = NULL;
    expr("c = b", &nine);
    nine = NULL;
    expr("d = 1", &nine);
    nine = NULL;
    res = expr("a+b+c+d", &nine);
    print(8, res);
    // 8 - 複数文字の変数を含んだ計算 : OK
    printf("\n== 複数文字の変数を含んだ計算 ==\n");
    const char *ten = NULL;
    expr("nomunomu0504 = 1", &ten);
    ten = NULL;
    res = expr("9+nomunomu0504", &ten);
    print(10, res);
    return 0 ;
}
