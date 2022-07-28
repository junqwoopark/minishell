/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:36:19 by chukim            #+#    #+#             */
/*   Updated: 2022/07/28 11:29:34 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_vaild_export(char *argv)
{
	size_t	i;
	int		flag;

	if (argv[0] == '=' || ft_isdigit(argv[0]) || argv[0] == '\0')
		return (0);
	i = -1;
	flag = 0;
	while (argv[++i] != '\0')
	{
		if (argv[i] == '=')
			flag = 1;
		if ((!ft_isalnum(argv[i]) && argv[i] != '=' && argv[i] != ' ')
			|| (argv[i] == ' ' && flag == 0))
			return (0);
	}
	return (1);
}

void	add_or_update_env(char *str, t_env *envp)
{
	t_env	*current;
	char	**key_value;

	key_value = divide_with_equal(str);
	current = envp;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key_value[0],
				ft_strlen(key_value[0])) == 0)
		{
			free(current->key);
			free(current->value);
			current->key = key_value[0];
			current->value = key_value[1];
			return ;
		}
		current = current->next;
	}
	add_env(envp, key_value[0], key_value[1]);
}

void	ft_export(t_cmd *cmd)
{
	size_t	i;

	if (cmd->argc == 1)
		print_export(cmd);
	else
	{
		i = 1;
		while (cmd->argv[i] != NULL)
		{
			if (is_vaild_export(cmd->argv[i]) != 0)
				add_or_update_env(cmd->argv[i], cmd->envp_copy);
			else
				exit_with_err("export", "not a valid identifier", 1, 0);
			i++;
		}
	}
}
