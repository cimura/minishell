#include <stdlib.h>
#include <libc.h>

char	*expand(char *lst_line)
{
	int	i;
  char  *to_expand;
  int len = 0;
  char  *env_value = NULL;
  char  *new = malloc(1024);

	i = 0;
	while (lst_line[i])
	{
		if (lst_line[i] == '$')
    {
      i++;
      // ホワイトスペースとかまで数える
      to_expand = ft_strndup(&lst_line[i], ft_count_until_char(&lst_line[i], " \t\n*")); 
      env_value = getenv(to_expand);
      if (!env_value)
        env_value = "";
      free(to_expand);
      new = ft_strjoin(new, env_value);
      i += ft_count_until_char(&lst_line[i], " \t\n*");
    }
    else
    {
      len = strlen(new);
      new[len] = lst_line[i];
      i++;
    }
	}
  new[len + 1] = '\0';
  return (new);
}

int main() {
  char	*line = "\'echo \'hello$hello world";
  char *result = expand(line);
}