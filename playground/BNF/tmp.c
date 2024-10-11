#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// BNF: <variable> ::= <letter> { <letter> | <digit> | '_' }

char *push_back(char *str, char ch) {
	size_t len = str ? strlen(str) : 0;
	char *new_str = realloc(str, len + 2); // 1 for the new character, 1 for the null terminator
	if (!new_str) {
		printf("Memory allocation error!\n");
		exit(EXIT_FAILURE);
	}
	new_str[len] = ch;
	new_str[len + 1] = '\0'; // Null-terminate the string
	return new_str;
}

int variable(const char *pc, const char **endp) {
	char *name = NULL;

	// スペースをスキップ
	while (isspace(*pc))
		pc++;

	// 変数名はアルファベットで始まるべき
	if (!isalpha(*pc)) {
		printf("Error: variable must start with a letter.\n");
		return -1;
	}

	// 変数名の構築
	while (isalnum(*pc) || *pc == '_') {
		name = push_back(name, *pc);
		pc++;
	}

	*endp = pc; // 最後の位置を endp にセット

	if (name == NULL) {
		return 0; // 空の変数名はエラー
	} else {
		printf("Parsed variable: %s\n", name);
		free(name);
		return 1; // 成功
	}
}

int main() {
	const char *input = "my_variable123";
	const char *endp;

	int result = variable(input, &endp);

	if (result == 1) {
		printf("Parsing succeeded.\n");
	} else {
		printf("Parsing failed.\n");
	}

	return 0;
}

