/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:32:50 by chukim            #+#    #+#             */
/*   Updated: 2022/08/03 18:57:20 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child_process(void)
{
	while (wait(&g_errno) != -1)
		;
	if (WIFEXITED(g_errno))
		g_errno = WEXITSTATUS(g_errno);
	else if (WIFSIGNALED(g_errno))
	{
		if (WTERMSIG(g_errno) == SIGINT)
			printf("^C\n");
		else if (WTERMSIG(g_errno) == SIGQUIT)
			printf("^\\");
		g_errno = WTERMSIG(g_errno) + 128;
	}
}

void	exec_single_builtin_cmd(t_cmd *cmd)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	redirect_in(cmd, 0);
	redirect_out(cmd, 0);
	if (!g_errno)
		run_builtin(cmd);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
}

void	exec_multiple_cmd_in_child_process(t_cmd *cmd)
{
	ft_close(cmd->read_pipe[WRITE]);
	ft_close(cmd->write_pipe[READ]);
	ft_dup2(cmd->read_pipe[READ], STDIN_FILENO);
	ft_dup2(cmd->write_pipe[WRITE], STDOUT_FILENO);
	redirect_in(cmd, 1);
	redirect_out(cmd, 1);
	if (cmd->argc != 0)
		run_cmd(cmd);
	exit(g_errno);
}

void	exec_multiple_cmd(t_cmd *cmd, size_t cnt_of_cmd)
{
	int		read_pipe[2];
	int		write_pipe[2];
	pid_t	pid;
	size_t	i;

	i = 0;
	init_pipe(read_pipe, write_pipe);
	while (i < cnt_of_cmd)
	{
		update_pipe(read_pipe, write_pipe, i, cnt_of_cmd);
		cmd[i].read_pipe = read_pipe;
		cmd[i].write_pipe = write_pipe;
		pid = fork();
		if (pid == 0)
			exec_multiple_cmd_in_child_process(&cmd[i]);
		ft_close(read_pipe[READ]);
		ft_close(read_pipe[WRITE]);
		i++;
	}
	set_signal(IGNORE);
	wait_child_process();
}

void	exec(t_cmd *cmd)
{
	size_t	cnt_of_cmd;

	set_signal(DEFAULT);
	cnt_of_cmd = get_cnt_of_cmd(cmd);
	if (cnt_of_cmd == 1 && cmd[0].argc && is_builtin(&(cmd[0])))
		exec_single_builtin_cmd(cmd);
	else
		exec_multiple_cmd(cmd, cnt_of_cmd);
	set_signal(SHELL);
}
