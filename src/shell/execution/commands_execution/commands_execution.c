/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:46:52 by tweimer           #+#    #+#             */
/*   Updated: 2022/06/05 22:50:20 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"
#include "environment/env.h"

void	execute_builtin(t_tree *node, int ok)
{
	replace_input(node->cmd);
	if (ok == CMD_ECHO)
		ft_echo(node->cmd);
	else if (ok == CMD_CD)
		ft_cd(node->cmd, g_data.env);
	else if (ok == CMD_PWD)
		ft_pwd(node->cmd);
	else if (ok == CMD_EXIT)
		ft_exit(node->cmd);
	else if (ok == CMD_EXPORT)
		ft_export(g_data.env, g_data.env->list, node->cmd);
	else if (ok == CMD_UNSET)
		ft_unset(g_data.env, node->cmd->args);
	else if (ok == CMD_ENV)
		printenv(node->cmd, g_data.env, g_data.env->list);
	ft_lastcmd(ok);
}

int	execute_not_builtin(t_tree *node, int type, int ok)
{
	if (type != PIPE)
		ok = base_builtin(node->cmd->args);
	else
		ok = pipe_base_builtin(node);
	if (ok == YES)
	{
		g_data.exit_status = 127;
		node->cmd->status = 1;
		dup2(g_data.stdin_fd, STDIN_FILENO);
		dup2(g_data.stdout_fd, STDOUT_FILENO);
		return (1);
	}
	else
	{
		node->cmd->status = 0;
		dup2(g_data.stdin_fd, STDIN_FILENO);
		dup2(g_data.stdout_fd, STDOUT_FILENO);
		return (0);
	}
}

int	execute_cmd(t_tree *node, int type)
{
	int	ok;

	ok = 0;
	if (node->cmd->args == NULL)
		return (1);
	ok = ft_checkequal(node->cmd->args);
	input_redirection(node->cmd);
	output_redirection(node->cmd);
	if (ok == 0)
		ok = is_builtin(node->cmd->args[0]);
	if (ok <= 0)
		return (execute_not_builtin(node, type, ok));
	else if (ok < 9)
	{
		execute_builtin(node, ok);
		node->cmd->status = 1;
		dup2(g_data.stdout_fd, STDOUT_FILENO);
		dup2(g_data.stdin_fd, STDIN_FILENO);
		return (1);
	}
	return (1);
}

void	shell_execution(t_group *all_token, t_command **all_command)
{
	t_tree	*root;

	root = binary_tree(all_token, all_command);
	manage_node_execution(root);
	clean_tree(root);
	if (root != NULL)
		root = NULL;
}
