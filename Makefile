# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chukim <chukim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 10:31:15 by chukim            #+#    #+#              #
#    Updated: 2022/07/23 14:03:19 by chukim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFTDIR = ./libft

INCLUDES =	-I ~/goinfre/.brew/opt/readline/include \
			-I ./libft/ \
			-I .
LIBS	 = 	-lreadline -L ~/goinfre/.brew/opt/readline/lib/ \
			-lhistory -L ~/goinfre/.brew/opt/readline/lib/ \
			-L ./libft/ -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -f

SRCS =	minishell.c \
		signal.c \
		pipe.c \
		error.c \
		./parser/util_parse.c \
		./parser/parse.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

$(NAME) : $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

all : $(NAME)

clean :
	make -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re : clean all

.PHONY : all clean fclean re
