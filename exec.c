/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:32:50 by chukim            #+#    #+#             */
/*   Updated: 2022/07/26 22:29:45 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_cnt_of_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].token)
		i++;
	return (i);
}

int	is_builtin(t_cmd cmd)
{
	if (ft_strcmp(cmd.argv[0], "cd") == 0
		|| ft_strcmp(cmd.argv[0], "echo") == 0
		|| ft_strcmp(cmd.argv[0], "pwd") == 0
		|| ft_strcmp(cmd.argv[0], "export") == 0
		|| ft_strcmp(cmd.argv[0], "unset") == 0
		|| ft_strcmp(cmd.argv[0], "env") == 0
		|| ft_strcmp(cmd.argv[0], "exit") == 0)
		return (1);
	return (0);
}

void	update_pipe(int *read_pipe, int *write_pipe)
{
	close(read_pipe[0]);
	close(read_pipe[1]);
	read_pipe[0] = write_pipe[0];
	read_pipe[1] = write_pipe[1];
	pipe(write_pipe);
}

void	ft_exec(t_token *token, t_cmd *cmd)
{
	int		read_pipe[2];
	int		write_pipe[2];
	pid_t	pid;
	size_t	i;
	size_t	cnt_of_cmd;

	(void)token;
	cnt_of_cmd = get_cnt_of_cmd(cmd);
	if (cnt_of_cmd == 1 && is_builtin(cmd[0]))
	{
		// 빌트인 실행
		return ;
	}
	i = 0;
	read_pipe[0] = -1;
	read_pipe[1] = -1;
	while (i < cnt_of_cmd)
	{
		update_pipe(read_pipe, write_pipe);
		if (i == 0) // 첫 명령어
		{
			cmd[i].read = STDIN_FILENO;
			cmd[i].write = write_pipe[1];
		}
		else if (i + 1 < cnt_of_cmd) // 중간에 있는 명령어
		{
			cmd[i].read = read_pipe[0];
			cmd[i].write = write_pipe[1];
		}
		else // 마지막 명령어의 경우
		{
			cmd[i].read = read_pipe[0];
			cmd[i].write = STDOUT_FILENO;
			close(write_pipe[0]);
			close(write_pipe[1]);
		}
		pid = fork();
		if (pid == 0) // 자식 프로세스
		{
			close(read_pipe[1]);
			close(write_pipe[0]);
			// redirection_in 체크 -> 오픈 가능 여부 및 read 바꿔주기!
			// redirection_out 체크 -> 파일 다 만들고, write 바꿔주기!
			// 실행 (is_builtin?, 오픈 가능한지???)
			// exit 해야할 듯?(builtin인 경우 실행 후 exit???, 그 외는 execve)
			exit(3);
		}
		i++;
	}
	waitpid(pid, &g_errno, 0);
	if (WIFEXITED(g_errno))
		g_errno = WEXITSTATUS(g_errno);
}

