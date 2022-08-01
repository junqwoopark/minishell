/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:49:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/01 21:30:29 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_token *token, size_t *tmp_file_cnt)
{
	int		fd;
	pid_t	pid;
	char	*tmp;
	char	*path;

	set_signal(HEREDOC);
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
	set_signal(IGNORE);
	waitpid(-1, &g_errno, 0);
	if (WIFEXITED(g_errno))
		g_errno = WEXITSTATUS(g_errno);
	else
	{
		printf("\n");
		g_errno = 1;
	}
	set_signal(SHELL);
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
				&& ft_strcmp("<<", cmd[i].token[j].str) == 0
				&& !g_errno)
				heredoc(&(cmd[i].token[j]), tmp_file_cnt);
			j++;
		}
		i++;
	}
	set_signal(SHELL);
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
