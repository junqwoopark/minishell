/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:29:01 by chukim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 14:42:58 by chukim           ###   ########.fr       */
=======
/*   Updated: 2022/07/30 19:09:43 by junkpark         ###   ########.fr       */
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
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

<<<<<<< HEAD
=======
void	echo_env(t_cmd *cmd, int i)
{
	char	*value;

	if (cmd->argv[1][0] == '$' && cmd->argv[1][1] == '?')
		printf("%d\n", g_errno);
	value = get_env(cmd->envp_copy, &(cmd->argv[i][1]));
	printf("%s", value);
}

>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
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
