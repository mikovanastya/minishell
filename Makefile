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
		env/init_env.c\
		env/get_env.c\
		env/set_env.c\
		env/del_env.c\
		builtins/cd.c\
		builtins/echo.c\
		builtins/env.c\
		builtins/export.c\
		builtins/pwd.c\
		builtins/unset.c\
		builtins/builtins.c\
		
HEADER = minishell.h

CC		=	cc

FLAGS = 

RM			=	rm -f

OBJ 	= $(SRCS:.c=.o)

all : $(NAME) 

$(NAME) : $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) libft/libft.a  -o $(NAME)

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