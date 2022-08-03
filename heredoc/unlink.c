/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:38:17 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 14:15:03 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_all(void)
{
	size_t	i;
	size_t	tmp_file_cnt;
	char	*tmp;
	char	*path;

	i = 0;
	tmp_file_cnt = get_or_set_tmp_file_cnt(0, 0);
	while (i < tmp_file_cnt)
	{
		path = "/tmp/tmpfile_minishell_";
		tmp = ft_itoa(i);
		path = ft_strjoin(path, tmp);
		free(tmp);
		unlink(path);
		free(path);
		i++;
	}
}
