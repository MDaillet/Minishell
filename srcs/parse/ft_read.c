/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:42:57 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/23 15:51:08 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_prompt_print(int c, int *pos, int *len) // Go to insert mode to put the character on the user screen and also dd it to the global->input line
{
	const char *im;
	const char *ic;
	const char *ip;
	const char *ei;
	char	n;
	im = tgetstr("im", NULL);
	ic = tgetstr("ic", NULL);
	ip = tgetstr("ip", NULL);
	ei = tgetstr("ei", NULL);
	tputs(im, 1, ft_putchr);
	tputs(ic, 1, ft_putchr);
	(*len)++;
	(*pos)++;
	n = (char)c;
	ft_putchar_fd(n, 2);
	g_ms->input = ft_add_one_char(&g_ms->input, (*pos), n);
	tputs(ip, 1, ft_putchr);
	tputs(ei, 1, ft_putchr);
}

static int	ft_analyze_char(int i, int *pos, int *len) // Char can be coded on over 32 bits or 4 Bytes, so we try here to see if the character is printable as 8, 16, 24 or 32 bit. When it is printable we call the prompt function
{
	int	c;
	int	byte;

	c = i;
	byte = 0;
	while (c && byte < 4)
	{
		c = i >> (byte * 8);
		c = (char)c;
		if (ft_isprint(c))
			ft_prompt_print(c, pos, len);
		else if (c == '\n' || c == 3)
		{
			ft_history_add();
			return (SUCCESS);
		}
		byte++;
	}
	return (ERROR);
}

void	ft_read_init(int *len, int *pos) // Initialize and malloc the variables we need to gather and print the user input
{
	if (!ft_malloc(&g_ms->input, sizeof(char)))
		return ;
	g_ms->input[0] = 0;
	(*len) = 0;
	(*pos) = 0;
}

void	ft_read(void) // Checks for arrows movement and history calling before sending the input chars one by one the the analyzer Will call the terminals function
{
	int	i;

	i = 0;
	ft_read_init(&g_ms->pos, &g_ms->len);
	while(read(0, &i, sizeof(int)) > 0)
	{
		if (i == UP)
			ft_up(&g_ms->pos, &g_ms->len);
		else if (i == DOWN)
			ft_down(&g_ms->pos, &g_ms->len);
		else if (g_ms->pos < g_ms->len && i == RIGHT)
			ft_right(&g_ms->pos);
		else if (g_ms->pos > 0 && i == LEFT)
			ft_left(&g_ms->pos);
		else if (g_ms->pos > 0 && (i == BACKS || i == 31))
			ft_backs(&g_ms->pos, &g_ms->len);
		else if (i == '\n' || ft_isprint(i))
		{
			if (ft_analyze_char(i, &g_ms->pos, &g_ms->len) == SUCCESS)
				return ;
		}
		ft_exit_checker(i);
		i = 0;
	}
}
