/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:24:46 by chukim            #+#    #+#             */
/*   Updated: 2022/07/25 18:22:53 by junkpark         ###   ########.fr       */
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

// '='으로 split 했을 경우! 문제 해결할 것인가?
t_env	*copy_envp(char *envp[])
{
	size_t	i;
	size_t	j;
	t_env	*new;
	char	**temp;

	new = env_new();
	i = 0;
	while (envp[i] != NULL)
	{
		temp = ft_split(envp[i], '=');
		add_env(new, ft_strdup(temp[0]), ft_strdup(temp[1]));
		j = 0;
		while (temp[j])
		{
			free(temp[j]);
			j++;
		}
		free(temp);
		i++;
	}
	return (new);
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
