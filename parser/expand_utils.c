/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:35:33 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 13:09:49 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_with_find_key(char **str, t_env *envp_copy)
{
	size_t	i;
	char	*ret;
	char	*key;

	i = 0;
	while ((ft_isalnum((*str)[i]) || (*str)[i] == '_')
		&& !ft_isspace((*str)[i]))
		i++;
	key = ft_strndup(*str, i);
	ret = get_env(envp_copy, key);
	free(key);
	*str += i;
	return (ret);
}

char	*get_env_expanded_str(char **str, t_env *envp_copy)
{
	*str += 1;
	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(g_errno));
	}
	else if (ft_isdigit(**str))
	{
		while (ft_isdigit(**str))
			(*str)++;
		return (ft_strdup(""));
	}
	else if (ft_isalnum(**str) || **str == '_')
		return (ft_strdup(get_env_with_find_key(str, envp_copy)));
	else
		return (ft_strdup("$"));
}

char	*get_squote_expanded_str(char **str)
{
	size_t	i;
	char	*ret;

	*str += 1;
	i = 0;
	while ((*str)[i] != '\'')
		i++;
	ret = ft_strndup(*str, i);
	*str += i + 1;
	return (ret);
}

char	*get_str_stop_at_quote_and_dollar(char **str, int in_quote)
{
	size_t	i;
	char	*ret;

	i = 0;
	while ((*str)[i] && (*str)[i] != '$' && (*str)[i] != '\"'
		&& (in_quote || (*str)[i] != '\''))
		i++;
	ret = ft_strndup(*str, i);
	*str += i;
	return (ret);
}

void	skip_dquote_and_set_in_quote(char **str, int *in_quote)
{
	*str += 1;
	if (*in_quote)
		*in_quote = 0;
	else
		*in_quote = 1;
}
