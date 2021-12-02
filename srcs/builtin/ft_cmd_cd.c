/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:31:01 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/06 09:28:35 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_construct_str(t_builtin *node, int *f) // Constuct the path needed
{
	char	*rtn;
	char	*tmp;
	t_list	*l;

	rtn = 0;
	l = node->cmd->next->next;
	if (*(l->str) == '/')
		rtn = 0;
	else if (*(l->str) == '~')
		(*f) = 0;
	else
	{
		rtn = getcwd(0, BUFF_SIZE);
		tmp = ft_strjoin(rtn, "/");
		ft_free(rtn);
		rtn = tmp;
	}
	return (rtn);
}

static int	ft_change_pwd(t_list **venv, char *dest, char *prev) // Update the PWD variable in the venv list
{
	int	ret;

	ret = chdir(dest);
	ft_add_venv(venv, ft_strdup2("PWD", 3), getcwd(0, BUFF_SIZE));
	if (ret < 0)
	{
		ret = ERROR;
		ft_error2(dest, 0);
	}
	ft_free(prev);
	ft_free(dest);
	return (ret);
}

int	ft_cmd_cd(t_builtin *node, t_list **venv) // The cd cmd, changing the working directory so its where we want to be
{
	t_list	*l;
	char	*prev;
	char	*dest;
	int	f;
	int	ret;

	f = 1;
	if (node->cmd->next && node->cmd->next->next)
		prev = ft_construct_str(node, &f);
	else
		f = 0;
	if (f)
	{
		l = node->cmd->next->next;
		dest = ft_strjoin(prev, l->str);
	}
	else
	{
		prev = ft_getvenv(*venv, "HOME", 4);
		dest = ft_strdup2(prev, ft_strlen(prev));
	}
	ret = ft_change_pwd(venv, dest, prev);
	return (ret);
}
