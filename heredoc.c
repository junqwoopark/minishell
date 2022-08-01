/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:49:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/31 02:17:05 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_cmd *cmd, size_t *tmp_file_cnt)
{
	int		fd;
	size_t	i;
	size_t	j;
	char	*path;
	char	*tmp;

	i = 0;
	*tmp_file_cnt = 0;
	while (cmd[i].token)
	{
		j = 0;
		while (cmd[i].token[j].type)
		{
			if (cmd[i].token[j].type == T_REDIRECT
				&& ft_strcmp("<<", cmd[i].token[j].str) == 0)
			{
				path = "/tmp/minishell_tmp_";
				tmp = ft_itoa(*tmp_file_cnt);
				path = ft_strjoin(path, tmp);
				free(tmp);
				fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 420);
				while (1)
				{
					tmp = readline("> ");
					if (ft_strcmp(tmp, cmd[i].token[j + 1].str) == 0)
					{
						free(tmp);
						break ;
					}
					write(fd, tmp, ft_strlen(tmp));
					write(fd, "\n", 1);
					free(tmp);
				}
				free(cmd[i].token[j + 1].str);
				*tmp_file_cnt += 1;
				cmd[i].token[j + 1].str = path;
				close(fd);
			}
			j++;
		}
		i++;
	}
}

void	ft_unlink(size_t *tmp_file_cnt)
{
	size_t	i;
	char	*tmp;
	char	*path;

	i = 0;
	while (i < *tmp_file_cnt + 1)
	{
		path = "/tmp/minishell_tmp_";
		tmp = ft_itoa(i);
		path = ft_strjoin(path, tmp);
		free(tmp);
		unlink(path);
		free(path);
		i++;
	}
}
