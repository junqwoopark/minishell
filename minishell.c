/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:26:15 by chukim            #+#    #+#             */
/*   Updated: 2022/07/26 16:38:37 by chukim           ###   ########.fr       */
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

void	free_token(t_token **token)
{
	size_t	i;

	i = 0;
	while ((*token)[i].str)
	{
		free((*token)[i].str);
		i++;
	}
	free(*token);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	// char	**envp_copy_arr;
	t_cmd	*cmd;
	t_env	*envp_copy;
	t_token	*token;

	(void) argc;
	(void) argv;
	(void) cmd;
	(void) envp;
	init_terminal(argc);
	envp_copy = copy_envp(envp);
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	cmd->argc = 3;
	cmd->argv = malloc(sizeof(char *) * 4);
	cmd->argv[0] = "export";
	cmd->argv[1] = "GGSD=sdad";
	cmd->argv[2] = "HELLO= hiasd";
	cmd->argv[3] = NULL;
	cmd->read = 0;
	cmd->write = 0;
	cmd->envp_copy_arr = envp;
	cmd->is_pipe = 0;
	cmd->envp_copy = envp_copy;
	ft_export(cmd);
	print_env(cmd->envp_copy);
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
				// envp_copy_arr = get_envp_copy_arr(envp_copy);
				cmd = get_cmd(token);

				free_token(&token);
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
