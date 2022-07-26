/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:20:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/26 14:01:05 by junkpark         ###   ########.fr       */
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
	size_t	cnt_of_cmd;
	size_t	i;
	size_t	j;
	size_t	k;
	// size_t	to_print;

	cnt_of_cmd = get_cnt_of_cmd(token);
	cmd = ft_calloc(cnt_of_cmd + 1, sizeof(t_cmd));
	i = 0;
	j = 0;
	while (i < cnt_of_cmd)
	{
		k = 0;
		while (token[j + k].type != T_PIPE && token[j + k].type)
			k++;
		if (token[j + k].type == T_PIPE)
		{
			token[j + k].type = T_NULL;
			k++;
		}
		cmd[i].token = &(token[j]);
		// to_print = 0;
		// printf ("-----cmd[%zu]-----\n", i);
		// while (cmd[i].token[to_print].type)
		// {
		// 	printf("%s\n", cmd[i].token[to_print].str);
		// 	to_print += 1;
		// }
		j += k;
		i++;
	}
	return (cmd);
}
