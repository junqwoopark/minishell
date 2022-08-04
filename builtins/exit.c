/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:27:32 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 17:04:10 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_errno(void)
{
	printf("exit\n");
	exit(g_errno);
}

void	ft_exit(t_cmd *cmd)
{
	if (cmd->argc == 1)
		exit_errno();
	else if (cmd->argc == 2 && ft_isdigit_str(cmd->argv[1]))
		g_errno = ft_atoi(cmd->argv[1]);
	else if (cmd->argc > 2 && ft_isdigit_str(cmd->argv[1]))
	{
		printf("exit\n");
		exit_with_err("exit", "too many arguments", 1, 0);
		return ;
	}
	else
	{
		printf("exit\n");
		exit_with_err(cmd->argv[1], "numeric argument required", 255, 1);
	}
	exit_errno();
}

void	ft_exit_multiple_cmd(t_cmd *cmd)
{
	if (cmd->argc == 1)
		exit(g_errno);
	else if (cmd->argc == 2 && ft_isdigit_str(cmd->argv[1]))
		g_errno = ft_atoi(cmd->argv[1]);
	else if (cmd->argc > 2 && ft_isdigit_str(cmd->argv[1]))
	{
		exit_with_err("exit", "too many arguments", 1, 0);
		return ;
	}
	else
		exit_with_err(cmd->argv[1], "numeric argument required", 255, 1);
	exit(g_errno);
}
