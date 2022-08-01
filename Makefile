# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 10:31:15 by chukim            #+#    #+#              #
#    Updated: 2022/07/31 18:20:12 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFTDIR = ./libft

# # 제 컴퓨터에서 실행하기 위한 경로입니다.
# INCLUDES =	-I /opt/homebrew/opt/readline/include \
# 			-I ./libft/ \
# 			-I .
# LIBS	 = 	-lreadline -L /opt/homebrew/opt/readline/lib/ \
# 			-lhistory -L /opt/homebrew/opt/readline/lib/ \
# 			-L ./libft/ -lft

INCLUDES =	-I ~/goinfre/.brew/opt/readline/include \
			-I ./libft/ \
			-I .
LIBS	 = 	-lreadline -L ~/goinfre/.brew/opt/readline/lib/ \
			-lhistory -L ~/goinfre/.brew/opt/readline/lib/ \
			-L ./libft/ -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs
RM = rm -f

SRCS =	minishell.c \
		signal.c \
		error.c \
		exec.c \
		free.c \
		print.c \
		heredoc.c \
		./env/env.c \
		./env/env_utils.c \
		./parser/parse.c \
		./parser/parse_utils.c \
		./builtins/echo.c \
		./builtins/export.c \
		./builtins/unset.c \
		./builtins/cd.c \
		./builtins/env.c \
		./builtins/pwd.c \
		./builtins/exit.c \
		./cmd/cmd.c \

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
