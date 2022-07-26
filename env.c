/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:24:46 by chukim            #+#    #+#             */
/*   Updated: 2022/07/26 16:37:11 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**get_envp(char *envp[])
// {
// 	char	*path;

// 	while (*envp && ft_strncmp("PATH=", *envp, 5))
// 		envp++;
// 	if (*envp == NULL)
// 		exit_with_err("PATH error", NULL, 3, 1);
// 	path = *envp + 5;
// 	return (ft_split(path, ':'));
// }

// char	*get_cmd_argv(char *path[], char *cmd)
// {
// 	int		i;
// 	int		fd;
// 	char	*path_cmd;
// 	char	*tmp;

// 	fd = access(cmd, X_OK);
// 	if (fd != -1)
// 		return (cmd);
// 	path_cmd = ft_strjoin("/", cmd);
// 	i = 0;
// 	while (path[i])
// 	{
// 		tmp = ft_strjoin(path[i], path_cmd);
// 		fd = access(tmp, X_OK);
// 		if (fd != -1)
// 		{
// 			free(path_cmd);
// 			return (tmp);
// 		}
// 		close(fd);
// 		free(tmp);
// 		i++;
// 	}
// 	free(path_cmd);
// 	return (NULL);
// }

char	*get_env(t_env *envp_copy, char *key) // key 값을 넣으면 환경변수를 반환 ex) get_env(envp, "USER") => "chukim"
{
	t_env	*current;

	current = envp_copy;
	while (current->next != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
			return (ft_strdup(current->value));
		current = current -> next;
	}
	return (ft_strdup(""));
}

t_env	*env_new(void)
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

void	add_env(t_env *envp_copy, char *key, char *value)
{
	t_env	*current;

	current = envp_copy;
	while (current->next != NULL)
		current = current->next;
	current->key = key;
	current->value = value;
	current->next = env_new();
}

char	**divide_with_equal(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**ret;

	i = 0;
	ret = calloc(2, sizeof(char *));
	while (str[i] != '=' && str[i] != '\0')
		i++;
	ret[0] = ft_calloc(i + 1, sizeof(char));
	ret[1] = ft_calloc(ft_strlen(str) - i, sizeof(char));
	j = -1;
	while (++j < i)
		ret[0][j] = str[j];
	if (ft_strlen(str) - i == 0)
		{
			ret[1] = "\0";
			return (ret);
		}
	k = 0;
	while (str[j + 1] != '\0')
	{
		ret[1][k] = str[j + 1];
		j++;
		k++;
	}
	return (ret);
}

// '='으로 split 했을 경우! 문제 해결할 것인가?
t_env	*copy_envp(char *envp[])
{
	int		i;
	char	**ret;
	t_env	*envp_copy;

	envp_copy = env_new();
	i = 0;
	while (envp[i] != NULL)
	{
		ret = divide_with_equal(envp[i]);
		add_env(envp_copy, ret[0], ret[1]);
		i++;
	}
	return (envp_copy);
}

void	print_env(t_env *envp_copy)
{
	t_env	*current;

	current = envp_copy;
	while (current->next != NULL)
	{
		printf("[key = %s] [value = %s]\n", current->key, current->value);
		current = current->next;
	}
}
