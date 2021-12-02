/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:29:20 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/02 11:56:23 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_pwd(t_builtin *node) // The pwd cmd
{
	char	*cwd;

	if (node->cmd->next)
	{
		ft_error2(0, " pwd : too many arguments");
		return (ERROR);
	}
	cwd = getcwd(0, BUFF_SIZE);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	ft_free(cwd);
	return (SUCCESS);
}
