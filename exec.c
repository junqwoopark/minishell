/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:32:50 by chukim            #+#    #+#             */
/*   Updated: 2022/08/01 21:33:09 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd);
	else if(ft_strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd);
	else if(ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(cmd);
	else if(ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(cmd);
	else if(ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(cmd);
	else if(ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(cmd);
	else if(ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd);
	else
		return ;
}

size_t	get_cnt_of_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].token)
		i++;
	return (i);
}

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0
		|| ft_strcmp(cmd->argv[0], "echo") == 0
		|| ft_strcmp(cmd->argv[0], "pwd") == 0
		|| ft_strcmp(cmd->argv[0], "export") == 0
		|| ft_strcmp(cmd->argv[0], "unset") == 0
		|| ft_strcmp(cmd->argv[0], "env") == 0
		|| ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

void	init_pipe(int *read_pipe, int *write_pipe)
{
	read_pipe[0] = -1;
	read_pipe[1] = -1;
	write_pipe[0] = -1;
	write_pipe[1] = -1;
}

void	update_pipe(int *read_pipe, int *write_pipe, int i, int	cnt_of_cmd)
{
	if (0 < i && i + 1 <= cnt_of_cmd) // 중간과 끝에 있는 명령어
	{
		read_pipe[READ] = write_pipe[READ];
		read_pipe[WRITE] = write_pipe[WRITE];
	}
	if (i == 0 && i + 1 == cnt_of_cmd)
	{
		write_pipe[READ] = -1;
		write_pipe[WRITE] = STDOUT_FILENO;
	}
	else if (i + 1 == cnt_of_cmd)
	{
		write_pipe[READ] = -1;
		write_pipe[WRITE] = STDOUT_FILENO;
	}
	else if (0 <= i && i + 1 < cnt_of_cmd) // 중간에 있는 명령어
		pipe(write_pipe);
}

void	redirect_in(t_cmd *cmd)
{
	int		fd;
	size_t	i;

	i = 0;
	while (cmd->token[i].type)
	{
		if (cmd->token[i].type == T_REDIRECT
			&& (ft_strcmp(cmd->token[i].str, "<") == 0
			|| ft_strcmp(cmd->token[i].str, "<<") == 0))
		{
			close(cmd->read);
			fd = open(cmd->token[i + 1].str, O_RDONLY);
			if (fd == -1) // 에러메세지출력
				exit(1);
			cmd->read = fd;
		}
		i++;
	}
}

void	redirect_out(t_cmd *cmd)
{
	int		fd;
	size_t	i;

	i = 0;
	while (cmd->token[i].type)
	{
		if (cmd->token[i].type == T_REDIRECT
			&& ft_strcmp(cmd->token[i].str, ">>") == 0)
		{
			close(cmd->write);
			fd = open(cmd->token[i + 1].str, O_WRONLY | O_CREAT | O_APPEND, 420);
			cmd->write = fd;
		}
		else if (cmd->token[i].type == T_REDIRECT
			&& ft_strcmp(cmd->token[i].str, ">") == 0)
		{
			close(cmd->write);
			fd = open(cmd->token[i + 1].str, O_WRONLY | O_CREAT | O_TRUNC, 420);
			if (fd == -1) // 엑시트 코드
				exit(1);
			cmd->write = fd;
		}
		i++;
	}
}

int	is_excutable(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	if (S_ISDIR(sb.st_mode))
	{
		errno = EISDIR;
		return (0);
	}
	if (sb.st_mode & S_IXUSR)
		return (1);
	else
		errno = EACCES;
	return (0);
}

char	**get_env_path(char *envp[])
{
	char	*path;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
    if (*envp == NULL)
		path = "PATH=.:";
    path = *envp + 5;
    return (ft_split(path, ':'));
}

int	is_cmd_contain_slash(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->argv[0][i])
	{
		if (cmd->argv[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char    *get_cmd_path(char *path[], t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	if (is_cmd_contain_slash(cmd))
	{
		if (!is_excutable(cmd->argv[0]))
			return (NULL);
		return (ft_strdup(cmd->argv[0]));
	}
    tmp = ft_strjoin("/", cmd->argv[0]);
    i = 0;
    while (path[i])
    {
        cmd_path = ft_strjoin(path[i], tmp);
        if (is_excutable(cmd_path))
		{
			free(tmp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(tmp);
	return (NULL);
}

void	run_cmd(t_cmd *cmd)
{
	char	*cmd_path;
	char	**env_path;

	if (is_builtin(cmd))
	{
		run_builtin(cmd);
		exit(g_errno);
	}
	env_path = get_env_path(cmd->envp_copy_arr);
	cmd_path = get_cmd_path(env_path, cmd);
	free_env_path(&env_path);
	if (cmd_path)
	{
		free(cmd->argv[0]);
		cmd->argv[0] = cmd_path;
		execve(cmd_path, cmd->argv, cmd->envp_copy_arr);
	}
	else if (!is_cmd_contain_slash(cmd))
		exit_with_err(cmd->argv[0], "command not found", 127, 1);
	else
		exit_with_err(cmd->argv[0], strerror(errno), 126, 1);
}

void	ft_exec(t_cmd *cmd)
{
	int		read_pipe[2];
	int		write_pipe[2];
	pid_t	pid;
	size_t	i;
	size_t	cnt_of_cmd;

	cnt_of_cmd = get_cnt_of_cmd(cmd);
	if (cnt_of_cmd == 1 && cmd[0].argc && is_builtin(&(cmd[0])))
	{
		// redirection -> STD IN, OUT 복제해서 복구해야함!!!
		run_builtin(cmd);
		return ;
	}
	set_signal(CHILD_PROCESS);
	i = 0;
	init_pipe(read_pipe, write_pipe);
	while (i < cnt_of_cmd)
	{
		update_pipe(read_pipe, write_pipe, i, cnt_of_cmd);
		if (i == 0) // 첫 명령어
		{
			cmd[i].read = STDIN_FILENO;
			cmd[i].write = write_pipe[WRITE];
		}
		else if (0 < i && i + 1 < cnt_of_cmd) // 중간 명령어
		{
			cmd[i].read = read_pipe[READ];
			cmd[i].write = write_pipe[WRITE];
		}
		else if (i + 1 == cnt_of_cmd) // 마지막 명령어의 경우
		{
			cmd[i].read = read_pipe[READ];
			cmd[i].write = STDOUT_FILENO;
		}
		pid = fork();
		if (pid == 0) // 자식 프로세스
		{
			close(read_pipe[WRITE]);
			close(write_pipe[READ]);
			redirect_in(&(cmd[i]));
			redirect_out(&(cmd[i]));
			if (cmd[i].read != 0)
				{
					dup2(cmd[i].read, STDIN_FILENO);
					close(cmd[i].read);
				}
			if (cmd[i].write != 1)
			{
				dup2(cmd[i].write, STDOUT_FILENO);
				close(cmd[i].write);
			}
			// 실행부
			if (cmd[i].argc != 0)
				run_cmd(&cmd[i]);
			exit(g_errno);
		}
		set_signal(IGNORE);
		close(read_pipe[READ]);
		close(read_pipe[WRITE]);
		i++;
	}
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
	set_signal(SHELL);
}
