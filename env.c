/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:24:46 by chukim            #+#    #+#             */
/*   Updated: 2022/07/24 14:26:45 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_envp(char *envp[])
{
	char	*path;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (*envp == NULL)
		exit_with_err("PATH error", NULL, 3, 1);
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*get_cmd_argv(char *path[], char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	fd = access(cmd, X_OK);
	if (fd != -1)
		return (cmd);
	path_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (NULL);
}

char	*get_env(char *envp[], char *key) //key 값을 넣으면 환경변수를 반환 ex) get_env(envp, "USER") => "chukim"
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
			return (envp[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}
