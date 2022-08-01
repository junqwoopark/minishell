/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:49:32 by junkpark          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 21:30:29 by junkpark         ###   ########.fr       */
=======
/*   Updated: 2022/08/01 13:18:13 by junkpark         ###   ########.fr       */
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_token *token, size_t *tmp_file_cnt)
{
	int		fd;
	pid_t	pid;
	char	*tmp;
	char	*path;

<<<<<<< HEAD
	set_signal(HEREDOC);
=======
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
	pid = fork();
	if (pid == 0)
	{
		path = "/tmp/tmpfile_minishell_";
		tmp = ft_itoa(*tmp_file_cnt);
		path = ft_strjoin(path, tmp);
		free(tmp);
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 420);
		while (1)
		{
			tmp = readline("> ");
			if (!tmp)
				break ;
			if (ft_strcmp(tmp, (token + 1)->str) == 0)
			{
				free(tmp);
				break ;
			}
			ft_putendl_fd(tmp, fd);
			free(tmp);
		}
		free((token + 1)->str);
		(token + 1)->str = path;
		close(fd);
		exit(g_errno);
	}
<<<<<<< HEAD
	set_signal(IGNORE);
=======
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
	waitpid(-1, &g_errno, 0);
	if (WIFEXITED(g_errno))
		g_errno = WEXITSTATUS(g_errno);
	else
<<<<<<< HEAD
	{
		printf("\n");
		g_errno = 1;
	}
	set_signal(SHELL);
=======
		g_errno = WTERMSIG(g_errno) + 128;
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
	return (g_errno);
}

void	heredoc_all(t_cmd *cmd, size_t *tmp_file_cnt)
{
	size_t	i;
	size_t	j;

	i = 0;
	*tmp_file_cnt = 0;
	while (cmd[i].token)
	{
		j = 0;
		while (cmd[i].token[j].type)
		{
			if (cmd[i].token[j].type == T_REDIRECT
<<<<<<< HEAD
				&& ft_strcmp("<<", cmd[i].token[j].str) == 0
				&& !g_errno)
=======
				&& ft_strcmp("<<", cmd[i].token[j].str) == 0)
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
				heredoc(&(cmd[i].token[j]), tmp_file_cnt);
			j++;
		}
		i++;
	}
<<<<<<< HEAD
	set_signal(SHELL);
=======
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
}

void	unlink_all(size_t *tmp_file_cnt)
{
	size_t	i;
	char	*tmp;
	char	*path;

	i = 0;
	while (i < *tmp_file_cnt + 1)
	{
		path = "/tmp/tmpfile_minishell_";
		tmp = ft_itoa(i);
		path = ft_strjoin(path, tmp);
		free(tmp);
		unlink(path);
		free(path);
		i++;
	}
}
