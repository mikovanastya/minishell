#include "minishell.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell shell;

// 	//init_env(env,&shell);
// 	shell.line = readline("minishell > ");

// }
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground

int main(void)
{
    while (1)
    {
        char * str = readline(BEGIN(49, 34)"Myshell $ "CLOSE);
        free(str);
    }
}