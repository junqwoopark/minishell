/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:49:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 14:54:41 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_in_child_process(char *tmp_file_path, char *delimiter)
{
	int		fd;
	char	*tmp;

	fd = open(tmp_file_path, O_WRONLY | O_CREAT | O_TRUNC, 420);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			close(fd);
			fd = open(tmp_file_path, O_WRONLY | O_CREAT | O_TRUNC, 420);
			close(fd);
			break ;
		}
		if (ft_strcmp(tmp, delimiter) == 0)
		{
			free(tmp);
			break ;
		}
		ft_putendl_fd(tmp, fd);
		free(tmp);
	}
	close(fd);
	exit(g_errno);
}

void	wait_heredoc(void)
{
	waitpid(-1, &g_errno, 0);
	if (WIFEXITED(g_errno))
		g_errno = WEXITSTATUS(g_errno);
	else if (WIFSIGNALED(g_errno))
	{
		printf("\n");
		g_errno = 1;
	}
}

int	heredoc_one(t_token *delimiter_token)
{
	pid_t	pid;
	char	*tmp_file_path;
	char	*delimiter;

	set_signal(HEREDOC);
	tmp_file_path = get_tmp_file_path();
	delimiter = delimiter_token->str;
	pid = fork();
	if (pid == 0)
		heredoc_in_child_process(tmp_file_path, delimiter);
	else
	{
		set_signal(IGNORE);
		free(delimiter_token->str);
		delimiter_token->str = tmp_file_path;
		wait_heredoc();
	}
	set_signal(SHELL);
	return (g_errno);
}

t_token	*find_delimiter_token(t_cmd *cmd, size_t *i, size_t *j)
{
	while (cmd[*i].token)
	{
		while (cmd[*i].token[*j].type)
		{
			if (cmd[*i].token[*j].type == T_REDIRECT
				&& ft_strcmp("<<", cmd[*i].token[*j].str) == 0)
				return (&(cmd[*i].token[++*j]));
			*j += 1;
		}
		*i += 1;
		*j = 0;
	}
	return (NULL);
}

void	heredoc_all(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	size_t	tmp_file_cnt;
	t_token	*delimiter_token;

	i = 0;
	j = 0;
	tmp_file_cnt = get_or_set_tmp_file_cnt(0, 1);
	while (!g_errno)
	{
		delimiter_token = find_delimiter_token(cmd, &i, &j);
		if (delimiter_token == NULL)
			break ;
		heredoc_one(delimiter_token);
		tmp_file_cnt = get_or_set_tmp_file_cnt(0, 0);
		get_or_set_tmp_file_cnt(tmp_file_cnt + 1, 1);
	}
}
