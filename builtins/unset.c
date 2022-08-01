/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:24:09 by chukim            #+#    #+#             */
/*   Updated: 2022/08/01 21:36:52 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_vaild_unset(char *str)
{
	int	i;

	i = -1;
	if ((!ft_isalpha(str[0])) && str[0] != '_')
		return (0);
	while (str[++i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}

void	delete_env(char *str, t_env *envp)
{
	t_env	*current;
	t_env	*front;

	current = envp;
	front = envp;
	while (current->next != NULL)
	{
		if (ft_strncmp(str, current->key, ft_strlen(str) + 1) == 0)
		{
			front->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
		}
		front = current;
		current = current->next;
	}
}

void	ft_unset(t_cmd *cmd)
{
	size_t	i;

	if (cmd->argc == 1)
		return ;
	else
	{
		i = 1;
		while (cmd->argv[i] != NULL)
		{
			if (is_vaild_unset(cmd->argv[i]) == 1)
				delete_env(cmd->argv[i], cmd->envp_copy);
			else
				exit_with_err(cmd->argv[i], "not a valid identifier", 1, 0);
			i++;
		}
	}
}
