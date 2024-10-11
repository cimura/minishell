/**
 * バッカスナウア記法(BNF)
 *
 * ## 式は項のみ or (+, -)演算子を含む式 ##
 * expr ::= term
 *        | term '+' expr
 *        | term '-' expr
 *        ;
 *
 * ## 項は因子 or (*, /)演算子を含む項 ##
 * term ::= factor
 *        | factor '*' term
 *        | factor '/' term
 *        ;
 *
 * ## 因子は数値 or カッコを含む（式, 項）or 演算子を含む##
 * factor ::= DIGIT
 *          | VARIABLE
 *          | VARIABLE OPERATOR expr
 *          | '(' expr ')'
 *          ;
 *
 * ## 数値 ##
 * DIGIT ::= [0-9]+ ;
 *
 * ## 変数名 ##
 * VARIABLE ::= _a-zA-Z [_a-zA-Z0-9]+ ;
 *
 * ## 演算子 ##
 * OPERATOR ::= '='
 */
