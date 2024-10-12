#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    // 初回の入力を取得
    char *input = readline("Input something: ");
    if (input && *input) {
        // 履歴に追加
        add_history(input);
    }

    // 新しい行に移動
    rl_on_new_line();

    // 入力行を置き換え
    //rl_replace_line("Replaced line!", 1);

    // 入力行を再表示
    rl_redisplay();

    // 新しい入力を受け付ける前に、履歴をクリア
    clear_history();  // rl_clear_historyではなくclear_historyを使用

    // 新しい入力を取得
    char *new_input = readline("\nNew Input: ");
    if (new_input && *new_input) {
        add_history(new_input);
    }

    // メモリ解放
    free(input);
    free(new_input);

    return 0;
}

