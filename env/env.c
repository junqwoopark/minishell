/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:24:46 by chukim            #+#    #+#             */
/*   Updated: 2022/07/28 13:22:51 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_envp_copy_size(t_env *envp_copy)
{
	size_t	size;
	t_env	*current;

	size = 0;
	current = envp_copy;
	while (current->next)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	**set_envp_copy_arr(char **envp_copy_arr, t_env *envp_copy)
{
	size_t	i;
	size_t	len;
	t_env	*current;

	current = envp_copy;
	i = 0;
	while (current->next)
	{
		len = ft_strlen(current->key) + ft_strlen(current->value);
		envp_copy_arr[i] = ft_calloc(len + 2, sizeof(char *));
		ft_strlcat(envp_copy_arr[i], current->key, len + 2);
		ft_strlcat(envp_copy_arr[i], "=", len + 2);
		ft_strlcat(envp_copy_arr[i], current->value, len + 2);
		i++;
		current = current->next;
	}
	return (envp_copy_arr);
}

char	**get_envp_copy_arr(t_env *envp_copy)
{
	size_t	envp_copy_size;
	char	**envp_copy_arr;

	envp_copy_size = get_envp_copy_size(envp_copy);
	envp_copy_arr = ft_calloc(envp_copy_size + 1, sizeof(char *));
	envp_copy_arr = set_envp_copy_arr(envp_copy_arr, envp_copy);
	return (envp_copy_arr);
}

char	*get_env(t_env *envp_copy, char *key)
{
	size_t	len;
	t_env	*current;

	current = envp_copy;
	while (current->next != NULL)
	{
		len = ft_strlen(key);
		if (len < ft_strlen(current->key))
			len = ft_strlen(current->key);
		if (ft_strcmp(current->key, key) == 0)
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
