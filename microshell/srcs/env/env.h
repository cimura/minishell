#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef    struct s_env
{
    char    *key;
    char    *value;
    struct s_env    *next;
}    t_env;