/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:20:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/25 17:48:33 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_cnt_of_cmd(t_token *token)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (token[i].type)
	{
		if (token[i].type == T_PIPE)
			cnt++;
		i++;
	}
	return (cnt + 1);
}

t_cmd	*get_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(get_cnt_of_cmd(token), sizeof(t_cmd) + 1);
	return (cmd);
}
