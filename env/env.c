/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:24:46 by chukim            #+#    #+#             */
/*   Updated: 2022/08/01 21:51:28 by chukim           ###   ########.fr       */
=======
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 13:24:46 by chukim            #+#    #+#             */
/*   Updated: 2022/07/30 16:14:45 by junkpark         ###   ########.fr       */
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
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
<<<<<<< HEAD
		if (current->value != NULL)
		{
			ft_strlcat(envp_copy_arr[i], "=", len + 2);
			ft_strlcat(envp_copy_arr[i], current->value, len + 2);
		}
=======
		ft_strlcat(envp_copy_arr[i], "=", len + 2);
		ft_strlcat(envp_copy_arr[i], current->value, len + 2);
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
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
	t_env	*current;

	current = envp_copy;
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
<<<<<<< HEAD
		{
			if (current->value != NULL)
				return (current->value);
			else
				return ("");
		}
=======
			return (current->value);
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
		current = current -> next;
	}
	return ("");
}

t_env	*env_new(void)
{
	t_env	*new;

<<<<<<< HEAD
	new = calloc(1, sizeof(t_env));
=======
	new = malloc(sizeof(t_env) * 1);
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
	if (new == NULL)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}
