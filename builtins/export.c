/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:36:19 by chukim            #+#    #+#             */
/*   Updated: 2022/07/27 13:56:18 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int compare_str(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] - str2[i] < 0)
			return (1);
		else if (str1[i] - str2[i] > 0)
			return (0);
		i++;
	}
	if (str1[i] == '\0')
		return (1);
	else
		return (0);
}

void	print_str_arr(char *argv[])
{
	size_t	i;
	size_t	j;
	int		flag;

	i = 0;
	flag = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		printf("declare -x ");
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == '=' && flag != 1)
			{
				printf("\"");
				flag = 1;
			}
			printf("%c", argv[i][j]);
			j++;
		}
		printf("\"");
		printf("\n");
		flag = 0;
		i++;
	}
}

void	print_export(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	char	*temp;

	// if (argc < 2)
	// 	return (1);
	i = 0;
	while (cmd->envp_copy_arr[i] != NULL)
	{
		j = i + 1;
		while (cmd->envp_copy_arr[j] != NULL)
		{
			if (compare_str(cmd->envp_copy_arr[i], cmd->envp_copy_arr[j]) == 0)
			{
				temp =cmd->envp_copy_arr[i];
				cmd->envp_copy_arr[i] = cmd->envp_copy_arr[j];
				cmd->envp_copy_arr[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_str_arr(cmd->envp_copy_arr);
}

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
		if (ft_strncmp(current->key, key_value[0], ft_strlen(key_value[0])) == 0)
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
