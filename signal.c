/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:50:42 by chukim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 22:09:39 by junkpark         ###   ########.fr       */
=======
/*   Updated: 2022/08/01 13:20:41 by junkpark         ###   ########.fr       */
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	sigint_handler(int sig)
{
=======
void	sigint_handler_in__child_process(int sig)
{
	(void) sig;
	printf("\n");
}

void	sigquit_handler_in_child_process(int sig)
{
	(void) sig;
	printf("Quit: %d\n", sig);
}

void	sigint_handler_no_nl(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

<<<<<<< HEAD
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
=======
void	set_signal(void) // heredoc 일 때는 sigint->g_errno = 130; && 자식 프로세스에서는 in_process 그 외는 sigint_handler로 해줘야함!!!
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
}
