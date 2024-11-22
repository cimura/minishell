// デストラクタ関数
static void free_token_list(t_token *head) {
    t_token *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free_ptr_array(tmp->command_line);  // 予め用意されたコマンド解放関数
        free(tmp);
    }
}

void test_lexer() {
	char *input = "echo hello | ls > output.txt";
	t_token *tokens = lexer(input);
	assert(tokens != NULL);

	// テスト1: 先頭トークンが"echo"で始まるか
	assert(tokens->command_line != NULL);
	assert(strcmp(tokens->command_line[0], "echo") == 0);
	assert(strcmp(tokens->command_line[1], "hello") == 0);

	// テスト2: 2つ目のトークンが"ls"であるか
	t_token *second_token = tokens->next;
	assert(second_token != NULL);
	assert(strcmp(second_token->command_line[0], "ls") == 0);
	assert(strcmp(second_token->command_line[1], ">") == 0);
	assert(strcmp(second_token->command_line[2], "output.txt") == 0);

	// 期待される出力が終わったら解放
	free_token_list(tokens);
	printf("\x1b[34m""All tests passed!\n""\x1b[0m");
}

int main() {
    test_lexer();
    return 0;
}