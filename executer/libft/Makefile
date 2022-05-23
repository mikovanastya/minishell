# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 17:54:12 by rtwitch           #+#    #+#              #
#    Updated: 2021/10/22 19:34:00 by rtwitch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =	ft_bzero.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memset.c\
		ft_memmove.c\
		ft_strncmp.c\
		ft_strlcpy.c\
		ft_memchr.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_atoi.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_strtrim.c\
		ft_itoa.c\
		ft_striteri.c\
		ft_strmapi.c\
		ft_split.c

OBJ = $(SRCS:.c=.o)

HEADER = libft.h

RM = rm -rf

.PHONY: all clean fclean re

all:  $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar crs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all