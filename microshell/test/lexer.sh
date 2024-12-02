#!/bin/bash

# レキサーの実行ファイル（レキサーがコンパイルされているものとします）
parser="./parser"

# テストケースのディレクトリと出力ディレクトリ
TEST_DIR="./tests"
EXPECTED_DIR="./expected"

# テスト結果を格納するディレクトリ
RESULTS_DIR="./results"

# 結果ディレクトリを作成
mkdir -p "$RESULTS_DIR"

# テストケースを1つずつ実行
for test_file in "$TEST_DIR"/*.txt; do
    test_name=$(basename "$test_file" .txt)
    
    # レキサーを実行し、結果をファイルに保存
    $parser "$test_file" > "$RESULTS_DIR/$test_name.result"
    
    # 期待される結果ファイル
    expected_file="$EXPECTED_DIR/$test_name.expected"
    
    # 実際の出力と期待される出力を比較
    if diff -q "$RESULTS_DIR/$test_name.result" "$expected_file" > /dev/null; then
        echo "Test $test_name: Passed"
    else
        echo "Test $test_name: Failed"
        echo "Differences:"
        diff "$RESULTS_DIR/$test_name.result" "$expected_file"
    fi
done
