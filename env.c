/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:24:46 by chukim            #+#    #+#             */
/*   Updated: 2022/07/25 14:30:38 by chukim           ###   ########.fr       */
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

t_env	*env_new()
{
	t_env	*new;

	new = malloc(sizeof(t_env) * 1);
	if (new == NULL)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_env(t_env *env, char *key, char *value)
{
	t_env	*current;

	current = env;
	while (current->next != NULL)
		current = current->next;
	current->key = key;
	current->value = value;
	current->next = env_new();
}

t_env	*copy_env(char *envp[])
{
	size_t	i;
	t_env	*new;
	char	**temp;

	new = env_new();
	i = 0;
	while (envp[i] != NULL)
	{
		temp = ft_split(envp[i], '=');
		add_env(new, temp[0], temp[1]);
		i++;
	}
	return (new);
}

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current->next != NULL)
	{
		printf("[key = %s] [value = %s]\n", current->key, current->value);
		current = current->next;
	}
}
