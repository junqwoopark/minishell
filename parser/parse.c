/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:31:28 by chukim            #+#    #+#             */
/*   Updated: 2022/07/24 18:55:24 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid_quote(char *input)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*input)
	{
		if (*input == '\'' && (squote == 0 && dquote == 0))
			squote = 1;
		else if (*input == '\"' && (squote == 0 && dquote == 0))
			dquote = 1;
		else if (*input == '\'' && squote == 1)
			squote = 0;
		else if (*input == '\"' && dquote == 1)
			dquote = 0;
		input++;
	}
	if (squote == 1 || dquote == 1)
		return (0);
	return (1);
}

void	init_in_quote(char *input, char *in_quote)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*input)
	{
		if (*input == '\'' && (squote == 0 && dquote == 0))
		{
			squote = 1;
			*input = ' ';
		}
		else if (*input == '\"' && (squote == 0 && dquote == 0))
		{
			dquote = 1;
			*input = ' ';
		}
		else if (*input == '\'' && squote == 1)
		{
			squote = 0;
			*input = ' ';
		}
		else if (*input == '\"' && dquote == 1)
		{
			dquote = 0;
			*input = ' ';
		}
		else if (squote == 1)
			*in_quote = 1;
		else if (dquote == 1)
			*in_quote = 2;
		else
			*in_quote = 0;
		input++;
		in_quote++;
	}
}

size_t	get_token_size(char *input, char *is_in_quote)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	while (*input)
	{
		while (ft_isspace(*input) && !*is_in_quote)
		{
			input++;
			is_in_quote++;
		}
		i = 0;
		while (input[i] && is_in_quote[i])
			i++;
		if (i == 0)
		{
			while (input[i] && !is_in_quote[i] && !ft_isspace(input[i]))
				i++;
		}
		if (i != 0)
		{
			input += i;
			is_in_quote += i;
			ret += 1;
		}
	}
	return (ret);
}

// strndup 실패 시 ft_split처럼 free 해주고 return (NULL) 해줘야함,,
t_token	*get_token(char *input, char *in_quote)
{
	t_token	*token;
	size_t	token_size;
	size_t	i;
	size_t	j;

	j = 0;
	token_size = get_token_size(input,in_quote);
	token = calloc(sizeof(t_token),  token_size + 1);
	if (token == NULL)
		return (NULL);
	while (*input)
	{
		while (ft_isspace(*input) && !*in_quote)
		{
			input++;
			in_quote++;
		}
		i = 0;
		while (input[i] && in_quote[i])
			i++;
		if (i != 0)
		{
			token[j].str = ft_strndup(input, i);
			token[j].type = *in_quote;
			j++;
			input += i;
			in_quote += i;
		}
		i = 0;
		while (input[i] && !in_quote[i] && !ft_isspace(input[i]))
			i++;
		if (i != 0)
		{
			token[j].str = ft_strndup(input, i);
			token[j].type = T_NULL;
			j++;
			input += i;
			in_quote += i;
		}
	}
	token[token_size].str = NULL;
	token[token_size].type = T_NULL;
	return (token);
}

t_token	*label_token(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].str && !token[i].type)
	{
		if (!ft_strncmp(token[i].str, "|", 2))
			token[i].type = T_PIPE;
		else if (!ft_strncmp(token[i].str, "<", 2))
			token[i].type = T_REDIRECT;
		else if (!ft_strncmp(token[i].str, "<<", 3))
			token[i].type = T_REDIRECT;
		else if (!ft_strncmp(token[i].str, ">", 2))
			token[i].type = T_REDIRECT;
		else if (!ft_strncmp(token[i].str, ">>", 3))
			token[i].type = T_REDIRECT;
		else if (!ft_strncmp(token[i].str, "||", 3))
			token[i].type = T_ERROR;
		else if (!ft_strncmp(token[i].str, "&&", 3))
			token[i].type = T_ERROR;
		else if (!ft_strncmp(token[i].str, "&", 2))
			token[i].type = T_ERROR;
		else if (!ft_strncmp(token[i].str, ";", 2))
			token[i].type = T_ERROR;
		else if (!ft_strncmp(token[i].str, ";;", 3))
			token[i].type = T_ERROR;
		else
			token[i].type = T_WORD;
		i++;
	}
	return (token);
}

// get_token 실패 시, return (NULL);
t_token	*lexcial_analysis(char *input, char *in_quote)
{
	t_token *token;

	token = get_token(input, in_quote);
	token = label_token(token);
	// size_t	i = 0;
	// while (token[i].str != NULL)
	// {
	// 	printf("token[%zu].str is [%s] & token[%zu].type is [%d]\n", i, token[i].str, i, token[i].type);
	// 	i++;
	// }
	return (token);
}


void	init_expanded(char *input, char *in_quote, char *expanded_input, char *expanded_in_quote)
{
	while (*input)
	{
		if (*in_quote)
		{
			*expanded_input = *input;
			*expanded_in_quote = *in_quote;
		}
		else
		{
			if (*input == '>' || *input == '<' || *input == '|' || *input == ';' || *input == '&')
			{
				*expanded_input = ' ';
				expanded_input += 1;
				expanded_in_quote += 1;
				*expanded_input = *input;
				if (*(input + 1) == *(input))
				{
					input += 1;
					in_quote += 1;
					expanded_input += 1;
					expanded_in_quote += 1;
					*expanded_input = *input;
				}
				expanded_input += 1;
				expanded_in_quote += 1;
				*expanded_input = ' ';
			}
			else
				*expanded_input = *input;
		}
		input += 1;
		in_quote += 1;
		expanded_input += 1;
		expanded_in_quote += 1;
		*expanded_input = '\0';
	}
}

t_token	*syntax_analysis(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].str)
	{
		if (token[i].type == T_PIPE)
		{
			if (token[i + 1].type != T_WORD)
				token[i].type = T_ERROR;
		}
		else if (token[i].type == T_REDIRECT)
		{
			if (token[i + 1].type != T_WORD)
				token[i].type = T_ERROR;
		}
		i++;
	}
	return (token);
}

int	is_token_error(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].str)
	{
		if (token[i].type == T_ERROR)
			return (1);
		i++;
	}
	return (0);
}

// expanded, in_quote 할당 안될 경우 예외처리
t_token	*parse(char *input)
{
	char	*in_quote;
	char	*expanded_input;
	char	*expanded_in_quote;
	t_token	*token;

	if (!is_valid_quote(input))
		return (NULL);
	in_quote = ft_calloc(ft_strlen(input) + 1, 1);
	expanded_input = ft_calloc(ft_strlen(input) * 3 + 1, 1);
	expanded_in_quote = ft_calloc(ft_strlen(input) * 3 + 1, 1);
	init_in_quote(input, in_quote);
	init_expanded(input, in_quote, expanded_input, expanded_in_quote);
	token = lexcial_analysis(expanded_input, expanded_in_quote);
	token = syntax_analysis(token);
	if (is_token_error(token))
	{
		free(token);
		token = NULL;
	}
	free(expanded_in_quote);
	free(expanded_input);
	free(in_quote);
	return (token);
}
