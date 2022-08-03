/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:39:32 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 14:49:14 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_or_set_tmp_file_cnt(size_t x, int option)
{
	static size_t	tmp_file_cnt;

	if (option == 0)
		return (tmp_file_cnt);
	tmp_file_cnt = x;
	return (tmp_file_cnt);
}

char	*get_tmp_file_path(void)
{
	char	*tmp;
	char	*tmp_file_path;

	tmp_file_path = "/tmp/tmpfile_minishell_";
	tmp = ft_itoa(get_or_set_tmp_file_cnt(0, 0));
	tmp_file_path = ft_strjoin(tmp_file_path, tmp);
	free(tmp);
	return (tmp_file_path);
}
