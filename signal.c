/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:50:42 by chukim            #+#    #+#             */
/*   Updated: 2022/08/01 22:09:39 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	set_signal(int	type) // heredoc 일 때는 sigint->g_errno = 130; && 자식 프로세스에서는 in_process 그 외는 sigint_handler
{
	if (type == SHELL)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (type == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
