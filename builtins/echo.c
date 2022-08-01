/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:29:01 by chukim            #+#    #+#             */
/*   Updated: 2022/08/01 14:42:58 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_option(char *str)
{
	size_t	i;

	if (ft_strncmp(str, "-n", 2) != 0)
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (cmd->argv[1] == NULL)
	{
		printf("\n");
		return ;
	}
	while (check_echo_option(cmd->argv[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd->argv[i] != NULL)
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag != 1)
		printf("\n");
}
