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

// // int	print_declare_x()
// // {
// // // }
// // int	ft_max(char **envp)
// // {
// // 	int	index;

// // 	index = 0;
// // 	while (envp[index])
// // 		++index;//возвращает значение уже измененной переменной
// // 	return (index);
// // }

// // int	sort_env(t_shell *shell)
// // {
// 	void	sort_tmp_env(t_env *env)
// {
// 	int		i;
// 	int		j;
// 	int		min;
// 	char	*tmp;

// 	i = 0;
// 	while (i < env->len - 1)
// 	{
// 		min = i;
// 		j = i + 1;
// 		while (j < env->len)
// 		{
// 			if (ft_strncmp(env->envp[j], env->envp[min], \
// 			ft_strlen(env->envp[min])) < 0)
// 				min = j;
// 			j++;
// 		}
// 		tmp = env->envp[i];
// 		env->envp[i] = env->envp[min];
// 		env->envp[min] = tmp;
// 		i++;
// 	}
// }

// char	sort_env(t_shell shell)
// {
// 	int		i;
// 	int		j;
// 	char	**envp;
// 	char	*tmp;

// 	envp = init_envp(shell);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		j = i + 1;
// 		while (envp[j])
// 		{
// 			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
// 			{
// 				tmp = envp[i];
// 				envp[i] = envp[j];
// 				envp[j] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (envp);
// }

// void	builtin_export(char **args, t_shell *shell)
// {
// 	int		i;
// 	t_shell	*tmp;

// 	i = 0;
// 	tmp = malloc(sizeof(char **) * (tmp->len + 1));
// 	if (args && !args[1])
// 	{
// 		while (i++ < tmp->len)
// 			tmp->envp[i] =  ft_strdup(shell->envp[i]);
// 		sort_tmp_env(tmp);
// 		i = 0;
// 		while (i < shell->len)
// 		{
			
// 		}
// 		//sort_env(shell);
// 		// return (shell);
// 	}

// }
