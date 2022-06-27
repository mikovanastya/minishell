# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 14:07:19 by rtwitch           #+#    #+#              #
#    Updated: 2022/06/27 21:26:24 by rtwitch          ###   ########.fr        #
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
		executer/pipe/create_pipe.c\
		executer/pipe/pipex.c\
		executer/signal/signal.c\
		executer/pipe/heredoc.c\
		executer/pipe/redirect.c\
		executer/pipe/free.c\
		parser/read_lines.c\
		parser/read_lines_1.c\
		parser/substitute_envp.c\
		parser/substitute_envp_1.c\
		parser/substitute_envp_2.c\
		parser/to_tree.c\
		parser/to_tree_1.c\
		parser/to_tree_2.c\
		parser/check.c\
		parser/free_memory.c\
		\
		utils/utils.c\
		


HEADER = minishell.h

#RL_INCLUDE  =   ~/.brew/opt/readline/include
#RL_LIB      =   ~/.brew/opt/readline/lib

CC		=	cc

FLAGS = 

RM			=	rm -f

OBJ 	= $(SRCS:.c=.o)

LIB	= libft.a


all : $(NAME) 

$(NAME) : $(OBJ) ./libft/*.c
	make -C ./libft
	$(CC) -g -lreadline $(FLAGS) $(OBJ) -L libft ./libft/libft.a  -o $(NAME)

%.o: %.c  */*.h $(HEADER)
	$(CC) -g $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)
	make clean -C libft/

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft/

re : fclean all

.PHONY: all clean fclean re