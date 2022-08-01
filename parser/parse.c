/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:31:28 by chukim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 19:37:05 by junkpark         ###   ########.fr       */
=======
/*   Updated: 2022/07/30 19:23:27 by junkpark         ###   ########.fr       */
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
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
	if (squote == 1)
		print_token_error("'");
	else if (dquote == 1)
		print_token_error("\"");
	else
		return (1);
	return (0);
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
			*in_quote = 1;
		}
		else if (*input == '\"' && (squote == 0 && dquote == 0))
		{
			dquote = 1;
			*in_quote = 2;
		}
		else if (*input == '\'' && squote == 1)
		{
			squote = 0;
			*in_quote = 1;
		}
		else if (*input == '\"' && dquote == 1)
		{
			dquote = 0;
			*in_quote = 2;
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
	size_t	i;
	size_t	ret;

	ret = 0;
	while (*input)
	{
		while (ft_isspace(*input))
		{
			input++;
			is_in_quote++;
		}
		i = 0;
		while (input[i] && ((!ft_isspace(input[i]) && !is_in_quote[i]) || is_in_quote[i]))
			i++;
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
t_token	*get_token(char *input, char *is_in_quote)
{
	t_token	*token;
	size_t	token_size;
	size_t	i;
	size_t	j;

	j = 0;
	token_size = get_token_size(input, is_in_quote);
	token = ft_calloc(sizeof(t_token),  token_size + 1);

	while (*input)
	{
		while (ft_isspace(*input))
		{
			input++;
			is_in_quote++;
		}
		i = 0;
		while (input[i] && ((!ft_isspace(input[i]) && !is_in_quote[i]) || is_in_quote[i]))
			i++;
		if (i != 0)
		{
			token[j].str = ft_strndup(input, i);
			j++;
		}
		input += i;
		is_in_quote += i;
	}
	token[token_size].str = NULL;
	token[token_size].type = T_NULL;
	return (token);
}

t_token	*label_token(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].str)
	{
		if (!ft_strcmp(token[i].str, "|"))
			token[i].type = T_PIPE;
		else if (!ft_strcmp(token[i].str, "<"))
			token[i].type = T_REDIRECT;
		else if (!ft_strcmp(token[i].str, "<<"))
			token[i].type = T_REDIRECT;
		else if (!ft_strcmp(token[i].str, ">"))
			token[i].type = T_REDIRECT;
		else if (!ft_strcmp(token[i].str, ">>"))
			token[i].type = T_REDIRECT;
		else if (!ft_strcmp(token[i].str, "||"))
			token[i].type = T_ERROR;
		else if (!ft_strcmp(token[i].str, "&&"))
			token[i].type = T_ERROR;
		else if (!ft_strcmp(token[i].str, "&"))
			token[i].type = T_ERROR;
		else if (!ft_strcmp(token[i].str, ";"))
			token[i].type = T_ERROR;
		else if (!ft_strcmp(token[i].str, ";;"))
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
	return (token);
}


void	init_expanded(char *input, char *in_quote, char *increased_input, char *increased_in_quote)
{
	while (*input)
	{
		if (*in_quote)
		{
			*increased_input = *input;
			*increased_in_quote = *in_quote;
		}
		else
		{
			if (*input == '>' || *input == '<' || *input == '|' || *input == ';' || *input == '&')
			{
				*increased_input = ' ';
				increased_input += 1;
				increased_in_quote += 1;
				*increased_input = *input;
				if (*(input + 1) == *(input))
				{
					input += 1;
					in_quote += 1;
					increased_input += 1;
					increased_in_quote += 1;
					*increased_input = *input;
				}
				increased_input += 1;
				increased_in_quote += 1;
				*increased_input = ' ';
			}
			else
				*increased_input = *input;
		}
		input += 1;
		in_quote += 1;
		increased_input += 1;
		increased_in_quote += 1;
		*increased_input = '\0';
	}
}

<<<<<<< HEAD
char	*get_expanded_str(char *str, t_env *envp_copy)
=======
// 시간 복잡도 엄청 남, 수정 필요!
t_token	*env_analysis(t_token *token, t_env *envp_copy) // 환경변수 parsing 시, heredoc은 parsing 하면 안됨!!! -> 수정 예정
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
{
	size_t	i;
	int		in_quote;
	char	*tmp;
	char	*key;
	char	*to_free;
	char	*env_analyzed_str;

	env_analyzed_str = ft_strdup("");
	in_quote = 0;
	while (*str)
	{
		i = 0;
		if (*str == '\'' && !in_quote)
		{
			str++;
			while (str[i] != '\'')
				i++;
			if (i != 0)
			{
<<<<<<< HEAD
				tmp = ft_strndup(str, i);
				to_free = env_analyzed_str;
				env_analyzed_str = ft_strjoin(env_analyzed_str, tmp);
				free(tmp);
				free(to_free);
=======
				j = 0;
				if (token[i].str[j + k] == '$')
				{
					token[i].str[j + k] = '\0';
					tmp = str;
					str = ft_strjoin(str, &(token[i].str[k]));
					free(tmp);
					j++;
					if (token[i].str[k + j] == '?')
					{
						env = ft_itoa(g_errno);
						tmp = str;
						str = ft_strjoin(str, env);
						free(tmp);
						free(env);
						j++;
					}
					else if (ft_isdigit(token[i].str[k + j]))
					{
						while (ft_isdigit(token[i].str[k + j]))
							j++;
					}
					else
					{
						while (!ft_isspace(token[i].str[k + j]) && (ft_isalnum(token[i].str[k + j]) || token[i].str[k + j] == '_'))
							j++;
						if (j == 1)
						{
							tmp = str;
							str = ft_strjoin(str, "$");
							free(tmp);
						}
						else
						{
							key = ft_strndup(&(token[i].str[k + 1]), j - 1);
							env = get_env(envp_copy, key);
							tmp = str;
							str = ft_strjoin(str, env);
							free(key);
							free(tmp);
						}
					}
				}
				else
				{
					while (token[i].str[k + j] && token[i].str[k + j] != '$')
						j++;
					if (token[i].str[k + j] == '$')
					{
						token[i].str[k + j] = '\0';
						tmp = str;
						str = ft_strjoin(str, &(token[i].str[k]));
						free(tmp);
						token[i].str[k + j] = '$';
					}
					else
					{
						tmp = str;
						str = ft_strjoin(str, &(token[i].str[k]));
						free(tmp);
					}
				}
				k += j;
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
			}
			str += i + 1;
		}
		else if (*str == '$')
		{
			str++;
			if (*str == '?')
			{
				tmp = ft_itoa(g_errno);
				to_free = env_analyzed_str;
				env_analyzed_str = ft_strjoin(env_analyzed_str, tmp);
				free(tmp);
				free(to_free);
				str++;
			}
			else if (ft_isdigit(*str))
			{
				while (ft_isdigit(*str))
					str++;
			}
			else if (ft_isalnum(*str) || *str == '_')
			{
				while ((ft_isalnum(str[i]) || str[i] == '_') && !ft_isspace(str[i]))
					i++;
				key = ft_strndup(str, i);
				tmp = get_env(envp_copy, key);
				free(key);
				to_free = env_analyzed_str;
				env_analyzed_str = ft_strjoin(env_analyzed_str, tmp);
				free(to_free);
				str += i;
			}
			else
			{
				to_free = env_analyzed_str;
				env_analyzed_str = ft_strjoin(env_analyzed_str, "$");
				free(to_free);
			}
		}
		else if (*str == '\"')
		{
			str++;
			if (in_quote)
				in_quote = 0;
			else
				in_quote = 1;
		}
		i = 0;
		while (str[i] && str[i] != '$' && str[i] != '\"' && (in_quote || str[i] != '\''))
			i++;
		if (i != 0)
		{
			tmp = ft_strndup(str, i);
			to_free = env_analyzed_str;
			env_analyzed_str = ft_strjoin(env_analyzed_str, tmp);
			free(tmp);
			free(to_free);
		}
		str += i;
	}
	return (env_analyzed_str);
}

t_token	*expand_token(t_token *token, t_env *envp_copy) // 환경변수 parsing 시, heredoc은 parsing 하면 안됨!!! -> 수정 예정
{
	size_t	i;
	char	*expanded_str;

	i = 0;
	while (token[i].str)
	{
		expanded_str = get_expanded_str(token[i].str, envp_copy);
		free(token[i].str);
		token[i].str = expanded_str;
		i++;
	}
	return (token);
}

t_token	*syntax_analysis(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].str)
	{
		if (token[i].type == T_PIPE)
		{
			if (token[i + 1].type != T_WORD
				&& token[i + 1].type != T_DQUOTES
				&& token[i + 1].type != T_SQUOTES
				&& token[i + 1].type != T_REDIRECT)
				token[i].type = T_ERROR;
		}
		else if (token[i].type == T_REDIRECT)
		{
			if (token[i + 1].type != T_WORD
				&& token[i + 1].type != T_DQUOTES
				&& token[i + 1].type != T_SQUOTES)
				token[i].type = T_ERROR;
			else if (token[i + 1].type != T_NULL)
				token[i + 1].type = T_FILE;
		}
		// if (token[i].type == T_WORD)
		// 	printf("word\t|%s|\n", token[i].str);
		// else if (token[i].type == T_FILE)
		// 	printf("file\t|%s|\n", token[i].str);
		// else if (token[i].type == T_ERROR)
		// 	printf("error\t|%s|\n", token[i].str);
		// else if (token[i].type == T_PIPE)
		// 	printf("pipe\t|%s|\n", token[i].str);
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
		{
			print_token_error(token[i].str);
			return (1);
		}
		i++;
	}
	return (0);
}

// expanded, in_quote 할당 안될 경우 예외처리
t_token	*parse(char *input, t_env *envp_copy)
{
	char	*in_quote;
	char	*increased_input;
	char	*increased_in_quote;
	t_token	*token;

	if (!is_valid_quote(input))
		return (NULL);
	in_quote = ft_calloc(ft_strlen(input) + 1, 1);
	increased_input = ft_calloc(ft_strlen(input) * 3 + 1, 1);
	increased_in_quote = ft_calloc(ft_strlen(input) * 3 + 1, 1);
	init_in_quote(input, in_quote);
<<<<<<< HEAD
	init_expanded(input, in_quote, increased_input, increased_in_quote);
	token = lexcial_analysis(increased_input, increased_in_quote);
	token = expand_token(token, envp_copy);
=======
	init_expanded(input, in_quote, expanded_input, expanded_in_quote);
	token = lexcial_analysis(expanded_input, expanded_in_quote);
>>>>>>> fce57a0447d231b5f440f1e4b40b07da838d904f
	token = syntax_analysis(token);
	token = env_analysis(token, envp_copy);
	if (is_token_error(token))
	{
		free_token(&token);
		token = NULL;
	}
	free(increased_in_quote);
	free(increased_input);
	free(in_quote);
	return (token);
}
