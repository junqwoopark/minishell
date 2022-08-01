/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:28:49 by chukim            #+#    #+#             */
/*   Updated: 2022/07/30 19:09:32 by junkpark         ###   ########.fr       */
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
	T_FILE,
	T_ERROR
};

# define READ 0
# define WRITE 1

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
	char	**envp_copy_arr;
	t_env	*envp_copy;
	t_token	*token;
}	t_cmd;

extern int	g_errno;

// heredoc.c
void	ft_heredoc(t_cmd *cmd, size_t *tmp_file_cnt);
void	ft_unlink(size_t *tmp_file_cnt);

// free.c
void	free_token(t_token **token);
void	free_envp_copy_arr(char ***envp_copy_arr);
void	free_cmd(t_cmd **cmd);
void	free_env_path(char ***envp_path);

char	*ft_strndup(const char *s, size_t n);

t_token	*parse(char *input, t_env *envp_copy);

// print.c
void	print_str_arr(char *argv[]);
void	print_export(t_cmd *cmd);

// ./env/env.c
char	**get_envp_copy_arr(t_env *envp_copy);
char	*get_env(t_env *envp_copy, char *key);
t_env	*env_new(void);

// ./env/env_utils.c
char	**divide_with_equal(char *str);
void	add_env(t_env *envp_copy, char *key, char *value);
t_env	*copy_envp(char *envp[]);

// cmd.c
t_cmd	*get_cmd(t_token *token, t_env *envp_copy, char **envp_copy_arr);
void	add_or_update_env(char *str, t_env *envp);

// error.c
void	exit_with_err(char *str1, char *str2, int exit_code, int to_exit);
void	print_err(char *s1, char *s2, char *s3);
void	print_token_error(char *error_token);

// exec.c
size_t	get_cnt_of_cmd(t_cmd *cmd);
void	ft_exec(t_cmd *cmd);

// signal.c
void	set_signal(void);

// export.c
void	ft_export(t_cmd *cmd);

// unset.c
void	ft_unset(t_cmd *cmd);

// env.c
void	ft_env(t_env *envp_copy);

// pwd.c
void	ft_pwd(t_cmd *cmd);

// echo.c
void	ft_echo(t_cmd *cmd);

// cd.c
void	ft_cd(t_cmd *cmd);

// exit.c
void	ft_exit(t_cmd *cmd);

#endif
