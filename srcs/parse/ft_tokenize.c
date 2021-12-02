/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:14:46 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/01 14:47:30 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_tok(t_list **tok, char **start, int *q_f, int *q_t) // Initialize the variables we need to tokenize the input
{
	(*q_f) = 0;
	(*q_t) = 0;
	(*tok) = 0;
	(*start) = 0;
}

static int	ft_quotes_check(char c, int	*q_t) // Check if the character c is a simple or double quote and returns it
{
	static char t = 0;

	if (c == t || !c)
		t = 0;
	else if (ft_strchr("\"\'", c) && !t)
		t = c;
	if (q_t && t)
		*q_t = t;
	return (t);
}

static t_list *ft_build(t_list *tok, char **start, int len, int id) // Create a new node in the list tok and append it to the end
{
	int		ret;
	t_list	*new;
	char	*input_id;

	if (!(**start) || len == 0)
		return (tok);
	input_id = 0;
	if (id)
	{
		ret = ft_malloc(&input_id, sizeof(char) * 2);
		if (!ret)
			ft_error("Memory allocation error");
		input_id[0] = (char)id;
		input_id[1] = 0;
	}
	new = ft_listnew(ft_substr(*start, 0, len), input_id);
	ft_listadd_tail(&tok, &new);
	return (tok);
}

static int	ft_tok_split(t_list **tok, char **start, char **input, int *q_t) // go through the input until it encounters a space or a special character and then call ft_build that will create a node for the corresponding word
{
	int	i;

	i = 1;
	if (**input == 32 && (**start))
    {
        (*tok) = ft_build((*tok), start, (*input) - (*start), *q_t);
        (*q_t) = 0;
        (*start) = 0;
	}
	else if (ft_strchr("><;|", **input))
	{
		(*tok) = ft_build((*tok), start, (*input) - (*start), *q_t);
		(*q_t) = 0;
		if (ft_strchr("><", **input) && **input == *((*input) + 1) && **input)
			i++;
		(*tok) = ft_build((*tok), input, i, **input);
		(*start) = 0;
	}
	return (i);
}	

t_list	*ft_tokenize(char *input) // take the input string and split it into different nodes composing a linked chained composing the tokens or words of the input
{
	t_list	*tok;
	char	*start;
	int	q_f;
	int	q_t;
	int	i;

	ft_init_tok(&tok, &start, &q_f, &q_t);
	while (*input != 0)
	{
		i = 1;
		if (!start)
		{
			while (*input == 32)
				input++;
			start = input;
		}
		q_f = ft_quotes_check(*input, &q_t);
		if (!q_f)
			i = ft_tok_split(&tok, &start, &input, &q_t);
		input += i;
	}
	if (q_f)
	{
		ft_quotes_check(0, 0);
		ft_error2(0, "error : unclosed quote");
		ft_free(g_ms->input);
		return (0);
	}
	if (start)
		tok = ft_build(tok, &start, input - start, q_t);
	ft_quotes_check(0, 0);
	return (tok);
}
