# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 14:07:19 by rtwitch           #+#    #+#              #
#    Updated: 2022/05/31 14:51:13 by rtwitch          ###   ########.fr        #
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
		executer/pipe/pipex.c\
		#parser/read_lines.c\
		#parser/read_lines_1.c

		
HEADER = minishell.h

RL_INCLUDE  =   ~/.brew/opt/readline/include
RL_LIB      =   ~/.brew/opt/readline/lib

CC		=	cc

FLAGS = #-lreadline

RM			=	rm -f

OBJ 	= $(SRCS:.c=.o)

all : $(NAME) 

$(NAME) : $(OBJ) 
#$(CC) $(FLAGS) $(OBJ) libft/libft.a  -o $(NAME)
	$(CC) $(FLAGS) -lreadline -L $(RL_LIB) -I $(RL_INCLUDE) $(OBJ) libft/libft.a -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

libft :
	make -C libft

clean :
	make -C libft clean
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	$(RM) libft/libft.a


re : fclean all

run : all
	./minishell

.PHONY: all clean fclean re libft