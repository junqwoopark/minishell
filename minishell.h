/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:28:49 by chukim            #+#    #+#             */
/*   Updated: 2022/07/23 14:44:42 by junkpark         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd {
	int		argc;
	char	**argv;

	int		read;
	int		write;
	char	**path;
}	t_cmd;

void	set_signal(void);
int		check_white_space(char *input);
void	parse(char *input);
char	**get_envp(char *envp[]);
char	*get_cmd_argv(char *path[], char *cmd);
void	exit_with_err(char *str1, char *str2, int exit_code, int to_exit);

#endif
