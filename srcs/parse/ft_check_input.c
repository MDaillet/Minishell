/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:06:11 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/08 19:17:36 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_guill(char *input, int *f, int *i, char c) // Will go through the input to look for the other guill caus it inhibit all other chars
{
	if (input[(*i)])
		(*i)++;
	while (input[(*i)] != c && input[(*i)])
		(*i)++;
	(*f) = 1;
}

int	ft_check_first_arg(char *input) // If no input before | or ; not valid
{
	int i;

	i = 0;
	while (input[i] == 32)
		i++;
	if (ft_strchr("|;", input[i]))
	{
		g_ms->status = INVALID_ARG;
		ft_errorsyntax(input[i]);
		free(input);
		return (INVALID_ARG);
	}
	return (SUCCESS);
}

int	ft_special_char(char *input, int *f, int *i) // # is separator for examples. Errors if < # > # | # banane || # banane << # banane >> # banane < # banane > # banane | < # banane | > # banane
{
	char	c;

	if (ft_strchr("><;|", input[*i]) && input[(*i)])
	{
		c = input[(*i)];
		(*i)++;
		while (input[(*i)] == 32)
			(*i)++;
		if ((!input[(*i)] && ((c == ';' && *i == 0) ||
			ft_strchr1("><|", c))) ||
			(input[(*i)] && (ft_strchr1("|;", input[(*i)]) ||
			(c == input[(*i)] && !input[(*i + 1)]))))
		{
			ft_errorsyntax(c);
			g_ms->status = INVALID_ARG;
			ft_free(input);
			return (INVALID_ARG);
		}
	}
	if (input[*i] == '\'')
		*f = -1;
	else if (input[(*i)] == '"')
		*f = -2;
	return (SUCCESS);
}

int	ft_check_input(char *input) // check the input for syntaxes errors
{
	int	i;
	int	f;

	i = 0;
	f = 1;
	if (!input)
		return (ERROR);
	if (ft_check_first_arg(input) != SUCCESS)
		return (INVALID_ARG);
	while (input[i])
	{
		if (f == 1)
			if (ft_special_char(input, &f, &i) != SUCCESS)
				return (INVALID_ARG);
		if (input[i] == '\'' && f == -1)
			ft_guill(input, &f, &i, '\'');
		else if (input[i] == '"' && f == -2)
			ft_guill(input, &f, &i, '"');
		if (input[i])
			i++;
	}
	return (SUCCESS);
}
