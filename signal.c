/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:50:42 by chukim            #+#    #+#             */
/*   Updated: 2022/08/01 13:20:41 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	set_signal(void) // heredoc 일 때는 sigint->g_errno = 130; && 자식 프로세스에서는 in_process 그 외는 sigint_handler로 해줘야함!!!
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
