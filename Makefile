# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 14:07:19 by rtwitch           #+#    #+#              #
#    Updated: 2022/07/16 16:56:02 by rtwitch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	main.c\
		executer/env/init_env.c\
		executer/env/get_env.c\
		executer/env/set_env.c\
		executer/env/del_env.c\
		executer/builtins/cd.c\
		executer/builtins/echo.c\
		executer/builtins/env.c\
		executer/builtins/export.c\
		executer/builtins/export2.c\
		executer/builtins/export3.c\
		executer/builtins/pwd.c\
		executer/builtins/unset.c\
		executer/builtins/builtins.c\
		executer/pipe/execute.c\
		executer/pipe/pipex.c\
		executer/signal/ft_signal.c\
		executer/pipe/redirect.c\
		\
		parser/parse_heredocs.c\
		parser/read_lines.c\
		parser/read_lines_1.c\
		parser/substitute_envp.c\
		parser/substitute_envp_1.c\
		parser/substitute_envp_2.c\
		parser/to_tree.c\
		parser/to_tree_1.c\
		parser/to_tree_2.c\
		parser/to_tree_3.c\
		parser/check.c\
		parser/add_filenames.c\
		parser/add_filenames_1.c\
		\
		utils/utils.c\
		


HEADER = minishell.h

CC		=	cc
FLAGS = -g -Wall -Werror -Wextra -I $(HEADER) -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include

RM			=	rm -f

OBJ 	= $(SRCS:.c=.o)

LIB	= libft.a


all : $(NAME) 

$(NAME) : $(OBJ) ./libft/*.c
	make -C ./libft
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -lreadline -L./libft -lft

%.o: %.c  */*.h $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)
	make clean -C libft/

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft/

re : fclean all

.PHONY: all clean fclean re