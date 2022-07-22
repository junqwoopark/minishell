# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chukim <chukim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 10:31:15 by chukim            #+#    #+#              #
#    Updated: 2022/07/22 14:12:54 by chukim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFTDIR = ./libft

INCLUDES =	-I ./readline/include/ \
			-I ./libft/
LIBS	 = 	-L ~/goinfre/.brew/opt/readline/lib/ -lreadline \
			-L ~/goinfre/.brew/opt/readline/lib/ -lhistory \
			-L ./libft/ -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -f

SRCS = minishell.c \
		signal.c \

OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -I.

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