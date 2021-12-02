/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:58:19 by mdaillet          #+#    #+#             */
/*   Updated: 2021/12/02 11:54:44 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_builtin(t_builtin *node, t_list **venv) // Scan the cmd and call the appropriate builtin cmd
{
	int	ret;
	
	ft_replace_venv(node->cmd, *venv);
	ft_remove_q(node->cmd);
	if (!node->cmd || !node)
		return (EXIT_FAILURE);
	if (ft_strncmp(node->cmd->str, "pwd", 3))
		ret = ft_cmd_pwd(node);
	else if (ft_strncmp(node->cmd->str, "echo", 4))
		ret = ft_cmd_echo(node);
	else if (ft_strncmp(node->cmd->str, "cd", 2))
		ret = ft_cmd_cd(node, venv);
	else if (ft_strncmp(node->cmd->str, "unset", 5))
		ret = ft_cmd_unset(node, venv);
	else if (ft_strncmp(node->cmd->str, "env", 3))
		ret = ft_cmd_env(node, *venv);
	else if (ft_strncmp(node->cmd->str, "export", 6))
		ret = ft_cmd_export(node, venv);
	else if (ft_strncmp(node->cmd->str, "exit", 4))
		ret = ft_cmd_exit(node);
	else
		ret = ft_execve(node, *venv);
	g_ms->status_prec = ret;
	return (ret);
}
