/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:28:49 by chukim            #+#    #+#             */
/*   Updated: 2022/07/24 14:24:56 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include "libft/libft.h"

enum	e_types
{
	T_NULL,
	T_SQUOTES,
	T_DQUOTES,
	T_WORD,
	T_PIPE,
	T_REDIRECT,
	T_ERROR
};

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*str;
	int				type;
}	t_token;

typedef struct s_cmd {
	int		argc;
	char	**argv;

	int		read;
	int		write;
	char	**path;
}	t_cmd;

char	*ft_strndup(const char *s, size_t n);

t_token	*parse(char *inputmak);

char	**get_envp(char *envp[]);
char	*get_cmd_argv(char *path[], char *cmd);
char	*get_env(char *envp[], char *key);

void	exit_with_err(char *str1, char *str2, int exit_code, int to_exit);

void	exec_process(t_token *token);

void	set_signal(void);

#endif
