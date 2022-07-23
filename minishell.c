/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:26:15 by chukim            #+#    #+#             */
/*   Updated: 2022/07/23 21:48:09 by junkpark         ###   ########.fr       */
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
	t_cmd	*cmd;
	t_env	*env;
	t_token	*token;

	(void) argc;
	(void) argv;
	(void) envp;
	(void) cmd;
	(void) env;
	// init_main(argc, argv, &cmd, envp);
	while (1)
	{
		input = readline("minishell $ ");
		if (input == NULL)
			break ;
		else if (*input != '\0')
		{
			add_history(input);
			token = parse(input);
			if (token)
			{
				// 토큰화 출력 코드!
				// int	idx = 0;
				// printf ("str: ");
				// while (token[idx].str)
				// {
				// 	printf("|%s|\t", token[idx].str);
				// 	idx++;
				// }
				// printf ("\ntype: ");
				// idx = 0;
				// while (token[idx].type)
				// {
				// 	printf("|%d|\t", token[idx].type);
				// 	idx++;
				// }
				// printf("\n");
				free_token(&token);
			}
		}
		free(input);
	}
	return (0);
}
