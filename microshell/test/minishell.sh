#!/bin/bash

# Minishell実行ファイルのパス
MINISHELL="../microshell"

# テストケースを定義（コマンドリスト）
TEST_CASES=(
	"cd PATH"
	"cd PATH1 PATH2"
	"cd .."
	"cd /tmp .."
	"cd /tmp | pwd"
    "echo Hello, World!"
    "echo 'Test' > /dev/null"
	"echo hello |cat << EOF"
	"echo hello > infile/cannot_write"	
    "pwd"
	"pwd hi"
    "env"
	"env hi"
	"export"
	"export HOGE=PIYO
	env"
    "exit"
	"exit 5"
	"exit 1000"
	"ls | exit 8"
	"exit 10 | ls"
    "ls -l | grep -v 'tmp'"
    "cat /dev/null"
	"cat infile/hello.txt| grep world"
	"cat hogehoge"
	"cat << EOF
	line 1
	line 2
	EOF"
	"hogehoge"
	"cat infile/cannot_read"
	"hoge '"
	"hoge \""
)

# 一時ファイルを定義
BASH_OUTPUT="bash_output.tmp"
MINISHELL_OUTPUT="minishell_output.tmp"
MINISHELL_INPUT="minishell_input.tmp"

# テスト結果
PASS_COUNT=0
FAIL_COUNT=0

# 色付け用
GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# ログディレクトリの設定
LOG_DIR="log"
rm -rf "$LOG_DIR"
mkdir -p "$LOG_DIR"  # ディレクトリが存在しなければ作成

chmod -r infile/cannot_read

echo -e "${CYAN}Starting tests...${NC}"
echo "==================="

# テストケースを1つずつ実行
for CMD in "${TEST_CASES[@]}"; do
    echo -e "${CYAN}Testing: $CMD${NC}"

    # Bashで実行
    bash -c "$CMD" > "$BASH_OUTPUT" 2>&1
    BASH_EXIT_CODE=$?

    # Minishell用の入力スクリプトを作成
    echo "$CMD" > "$MINISHELL_INPUT"
    #echo "exit" >> "$MINISHELL_INPUT"  # Minishellを終了させるためのexitコマンド

    # Minishellで実行
    $MINISHELL < "$MINISHELL_INPUT" > "$MINISHELL_OUTPUT" 2>&1
    MINISHELL_EXIT_CODE=$?

    # 結果を比較
    if diff "$BASH_OUTPUT" "$MINISHELL_OUTPUT" > /dev/null && [ $BASH_EXIT_CODE -eq $MINISHELL_EXIT_CODE ]; then
        echo -e "${GREEN}PASS${NC}"
        ((PASS_COUNT++))
    else
        echo -e "${RED}FAIL${NC}"

        # ログファイル名を生成（コマンド名を整形して使用）
        LOG_FILE="$LOG_DIR/$(echo "$CMD" | sed 's/ /_/g' | sed 's/[^a-zA-Z0-9_]/_/g').log"
        {
            echo "===  Test: $CMD ==="
            echo "  Bash output:"
            cat "$BASH_OUTPUT"
			echo ""
			echo "================================================="
            echo "  Minishell output:"
            cat "$MINISHELL_OUTPUT"
			echo ""
            echo "  Exit codes: Bash=$BASH_EXIT_CODE, Minishell=$MINISHELL_EXIT_CODE"
        } > "$LOG_FILE"

        echo "  save -> $LOG_FILE"
        ((FAIL_COUNT++))
    fi
    echo "-------------------"
done

# 結果を出力
echo "==================="
echo -e "${CYAN}Tests completed.${NC}"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
echo -e "${RED}Failed: $FAIL_COUNT${NC}"

# 一時ファイルを削除
rm -f "$BASH_OUTPUT" "$MINISHELL_OUTPUT" "$MINISHELL_INPUT"
