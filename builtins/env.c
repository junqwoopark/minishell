/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:35:52 by chukim            #+#    #+#             */
/*   Updated: 2022/08/01 19:38:34 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	t_env	*current;

	if (cmd->argc >= 2)
	{
		exit_with_err(cmd->argv[1], "No such file or directory", 2, 0);
		return ;
	}
	current = cmd->envp_copy;
	while (current->next != NULL)
	{
		if (strcmp(current->value, "") != 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
