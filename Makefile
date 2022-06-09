# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 14:07:19 by rtwitch           #+#    #+#              #
#    Updated: 2022/05/17 16:27:53 by rtwitch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	main.c\
		parser/read_lines.c\
		parser/read_lines_1.c\
		parser/substitute_envp.c\
		parser/substitute_envp_1.c\
		utils/utils.c\
#		builtins/cd.c\
		builtins/echo.c\
		builtins/env.c\
		builtins/export.c\
		builtins/pwd.c\
		builtins/unset.c\
		builtins/builtins.c\
		env/init_env.c\
		env/get_env.c\
		env/set_env.c\
		env/del_env.c\
		
HEADER = minishell.h

CC		=	cc

FLAGS = -Wall -Werror -Wextra -g

RM			=	@rm -f

OBJ 	= $(SRCS:.c=.o)

LIB	= libft.a

all : $(NAME) 

$(NAME) : $(OBJ) $(LIB)
	$(CC) -lreadline $(FLAGS) $(OBJ) libft/libft.a  -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

$(LIB):
	@gcc -c $(FLAGS) libft/*.c -I libft/libft.h
	@ar -q libft/$(LIB) *.o

libft :
	make -C libft

clean :
	make -C libft clean
	$(RM) *.o

fclean : clean
	$(RM) $(OBJ)
	$(RM) $(NAME)
	$(RM) libft/libft.a
	$(RM) -rf libft/$(LIB)

re : fclean all

run : all
	./minishell

.PHONY: all clean fclean re libft