/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:26:15 by chukim            #+#    #+#             */
/*   Updated: 2022/07/27 15:51:02 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno;

void	init_terminal(int argc)
{
	struct termios	term;

	if (argc != 1)
		exit_with_err("argument input error", NULL, 126, 1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**envp_copy_arr;
	t_cmd	*cmd;
	t_env	*envp_copy;
	t_token	*token;

	(void)argv;
	init_terminal(argc);
	envp_copy = copy_envp(envp);
	while (1)
	{
		input = readline("minishell $ ");
		if (input == NULL)
			break ;
		else if (*input != '\0')
		{
			add_history(input);
			token = parse(input, envp_copy);
			if (token)
			{
				envp_copy_arr = get_envp_copy_arr(envp_copy);
				cmd = get_cmd(token, envp_copy, envp_copy_arr);
				ft_exec(token, cmd);
				free_cmd(&cmd);
				free_token(&token);
				free_envp_copy_arr(&envp_copy_arr);
			}
			else
			{
				// 에러 출력!
			}
		}
		free(input);
	}
	return (0);
}
