/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:27:44 by chukim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 21:49:44 by chukim           ###   ########.fr       */
=======
/*   Updated: 2022/07/28 11:29:38 by chukim           ###   ########.fr       */
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	print_end(int flag)
{
	if (flag == 1)
		printf("\"\n");
	else
		printf("\n");
}

=======
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
int	compare_str(char *str1, char *str2)
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
<<<<<<< HEAD
			if (argv[i][j - 1] == '=' && flag != 1)
=======
			if (argv[i][j] == '=' && flag != 1)
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
			{
				printf("\"");
				flag = 1;
			}
			printf("%c", argv[i][j]);
			j++;
		}
<<<<<<< HEAD
		print_end(flag);
=======
		printf("\"");
		printf("\n");
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
		flag = 0;
		i++;
	}
}

void	print_export(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (cmd->envp_copy_arr[i] != NULL)
	{
		j = i + 1;
		while (cmd->envp_copy_arr[j] != NULL)
		{
			if (compare_str(cmd->envp_copy_arr[i], cmd->envp_copy_arr[j]) == 0)
			{
				temp = cmd->envp_copy_arr[i];
				cmd->envp_copy_arr[i] = cmd->envp_copy_arr[j];
				cmd->envp_copy_arr[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_str_arr(cmd->envp_copy_arr);
}
