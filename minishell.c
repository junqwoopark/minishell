/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:26:15 by chukim            #+#    #+#             */
/*   Updated: 2022/07/23 14:04:37 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_main(int argc, char **argv, t_cmd *cmd, char **envp)
{
	struct termios	term;

	if (argc != 1)
		exit_with_err("argument input error", NULL, 126, 1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal();
	cmd->path = get_envp(envp);
	(void)argv;
	(void)envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;

	init_main(argc, argv, &cmd, envp);
	while (1)
	{
		input = readline("minishell $> ");
		if (input == NULL)
			break ;
		if (!check_white_space(input))
			parse(input);
		free(input);
	}
	return (0);
}
