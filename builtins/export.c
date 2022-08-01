/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:36:19 by chukim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 21:40:28 by chukim           ###   ########.fr       */
=======
/*   Updated: 2022/07/28 11:29:34 by chukim           ###   ########.fr       */
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
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
	while (current->key != NULL)
	{
<<<<<<< HEAD
		if (ft_strcmp(current->key, key_value[0]) == 0)
=======
		if (ft_strncmp(current->key, key_value[0],
				ft_strlen(key_value[0])) == 0)
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
		{
			free(current->value);
			current->value = key_value[1];
			free(key_value[0]);
			free(key_value);
			return ;
		}
		current = current->next;
	}
	add_env(envp, key_value[0], key_value[1]);
	free(key_value);
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
