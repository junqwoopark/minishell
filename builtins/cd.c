/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chukim <chukim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:36:09 by chukim            #+#    #+#             */
/*   Updated: 2022/07/27 15:48:30 by chukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_env *envp)
{
	char	*old_pwd;
	char	*cur_pwd;
	char	*tmp;

	tmp = calloc(4096, sizeof(char));
	cur_pwd = ft_strjoin("PWD=", getcwd(tmp, 4096));
	old_pwd = ft_strjoin("OLDPWD=", get_env(envp, "PWD"));
	add_or_update_env(cur_pwd, envp);
	add_or_update_env(old_pwd, envp);
	free(cur_pwd);
	free(old_pwd);
}

void	cd_home(t_cmd *cmd)
{
	char *path;

	path = get_env(cmd->envp_copy, "HOME");
	if (cmd->argv[1] == NULL)
	{
		if (chdir(path) == -1)
			exit_with_err("cd", "HOME not set", 2, 0);
	}
	else if (cmd->argv[1][1] == '~')
		exit_with_err("cd", "No such file or directory", 2, 0);
	else
	{
		if (chdir(getenv("HOME")) == -1)
			exit_with_err("cd",  "No such file or directory", 2, 0);
	}
}

void	cd_env(t_cmd *cmd)
{
	char	*path;
	path = get_env(cmd->envp_copy, &(cmd->argv[1][1]));
	if (chdir(path) == -1)
		chdir(get_env(cmd->envp_copy, "HOME"));
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->argv[1] != NULL && cmd->argv[1][0] != '~' && cmd->argv[1][0] != '$')
	{
		path = cmd->argv[1];
		if (chdir(path) == -1)
			exit_with_err(path, "No such file or directory", 2, 0);
		set_pwd(cmd->envp_copy);
	}
	else if (cmd->argv[1] == NULL || cmd->argv[1][0] == '~')
	{
		cd_home(cmd);
	}
	else if (cmd->argv[1][0] == '$')
		cd_env(cmd);
}
