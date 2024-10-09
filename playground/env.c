#include <stdio.h>
#include <stdlib.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

int	count_env(char **envp)
{
	int	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int main(int argc, char **argv, char **envp) {
	t_env *env_list;
	int env_len = count_env(envp);
	env_list = malloc(sizeof(t_env) * env_len);		

	int	i = 0;
	while (envp[i])
	{
		env_list->key = envp
	}
}
