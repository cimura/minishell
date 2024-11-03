#!/bin/bash

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

# テスト関数
run_test() {
    expected_output="$1"
    input="$2"

    # テスト用プログラムを実行し、その出力をキャプチャ
    output=$(./../expander/expander "$input")
    
    # 出力を確認
    if [[ "$output" == "$expected_output" ]]; then
        echo -e "${GREEN}Test passed${RESET}-> Input: '$input'"
    else
        echo -e "${RED}Test failed: Input: '$input'${RESET}"
        echo "Expected: '$expected_output'"
        echo "Got: '$output'"
    fi
}

# テスト実行
# パイプが来るまではカンマ区切り、パイプはタブで区切ってる

run_test "echo,hello	ls" "echo hello | ls"
run_test "ls	grep,txt" "ls | grep txt"
run_test "cat,file.txt	sort	uniq" "cat file.txt | sort | uniq"
run_test 'echo,hello"$USER",>,cat,out	ls,<<,INFILE' 'echo hello"$USER" >cat out| ls  <<INFILE'
# クリーンアップ
# rm ../lexer/lexer
