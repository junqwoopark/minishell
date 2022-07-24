/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:32:50 by chukim            #+#    #+#             */
/*   Updated: 2022/07/24 14:27:31 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_token *token, size_t i) //빌트인 명령 실행부
{
	if (token[i].type == 3 && !ft_strncmp(token[i].str, "echo", 5))
		printf("execute echo\n");
	else if (token[i].type == 3 && !ft_strncmp(token[i].str, "cd", 3))
		printf("execute cd\n");
	else if (token[i].type == 3 && !ft_strncmp(token[i].str, "pwd", 4))
		printf("execute pwd\n");
	else if (token[i].type == 3 && !ft_strncmp(token[i].str, "export", 7))
		printf("execute export\n");
	else if (token[i].type == 3 && !ft_strncmp(token[i].str, "env", 4))
		printf("execute env\n");
	else if (token[i].type == 3 && !ft_strncmp(token[i].str, "exit", 5))
		printf("execute exit\n");
}

void	exec_redir(t_token *token, size_t i) //리디렉션 명령 실행부
{
	(void) token;
	(void) i;
	printf("execute redirection\n");
}

void	exec_pipe(t_token *token, size_t i) //파이프 명령 실행부
{
	(void) token;
	(void) i;
	printf("execute pipe\n");
}

void	exec_process(t_token *token) //리디렉션 파이프 빌트인 명령어를 구분
{
	size_t	i;

	i = 0;
	while (token[i].str != NULL)
	{
		if (token[i].type == T_REDIRECT)
			exec_redir(token, i);
		else if (token[i].type == T_PIPE)
			exec_pipe(token, i);
		else if (token[i].type == T_WORD)
			exec_builtins(token, i);
		i++;
	}
}
