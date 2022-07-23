/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:31:28 by chukim            #+#    #+#             */
/*   Updated: 2022/07/23 16:14:58 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_quotes(char *line, char *is_in_quote)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*line)
	{
		if (*line == '\'' && (squote == 0 && dquote == 0))
		{
			squote = 1;
			*line = ' ';
		}
		else if (*line == '\"' && (squote == 0 && dquote == 0))
		{
			dquote = 1;
			*line = ' ';
		}
		else if (*line == '\'' && squote == 1)
		{
			squote = 0;
			*line = ' ';
		}
		else if (*line == '\"' && dquote == 1)
		{
			dquote = 0;
			*line = ' ';
		}
		else if (squote == 1)
			*is_in_quote = 1;
		else if (dquote == 1)
			*is_in_quote = 2;
		else
			*is_in_quote = 0;
		line++;
		is_in_quote++;
	}
	if (squote == 1 || dquote == 1)
		return (0);
	return (1);
}

// char	**tokenize(char *line, char *is_in_quote)
// {
// }

t_token	*parse(char *input)
{
	char	*line;
	char	*is_in_quote;
	// t_token	*token;

	line = ft_strtrim(input, "\f\r \t\v");
	if (line == NULL)
		return (NULL);
	is_in_quote = ft_strdup(line);
	if (is_in_quote == NULL)
		return (NULL);
	if (!is_valid_quotes(line, is_in_quote))
	{
		free(line);
		free(is_in_quote);
		return (NULL);
	}
	printf("%s\n", line);
	// token = tokenize(line, is_in_quote);
	free(line);
	// return (token);
	return (NULL);
}
