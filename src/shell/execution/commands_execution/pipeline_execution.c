/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:46:28 by tweimer           #+#    #+#             */
/*   Updated: 2022/06/05 17:32:33 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"
#include "minishell.h"

void	redirect_input(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
}

void	redirect_output(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close (fd[1]);
}

void	manage_input(t_tree *main_pipe, t_tree *sub_node, int side)
{
	if (side == LEFT)
	{
		if (main_pipe->previous != NULL
			&& main_pipe->previous->token->type == PIPE)
		{
			redirect_input(main_pipe->previous->fd);
			free(main_pipe->previous->fd);
		}
	}
	else if (side == RIGHT)
	{
		if (main_pipe->previous == NULL || sub_node->cmd != NULL)
		{
			redirect_input(main_pipe->fd);
			if (sub_node->cmd == NULL && sub_node->token->type != PIPE)
				free(main_pipe->fd);
			else if (sub_node->cmd != NULL)
				free(main_pipe->fd);
		}
		else if (main_pipe->previous->token->type == PIPE)
		{
			redirect_input(main_pipe->previous->fd);
			free(main_pipe->previous->fd);
		}
	}
}

void	manage_output(t_tree *main_pipe, t_tree *sub_node, int side)
{
	if (side == LEFT)
	{
		redirect_output(main_pipe->fd);
	}
	else if (side == RIGHT)
	{
		if (sub_node->token != NULL && sub_node->token->type == PIPE)
		{
			redirect_output(main_pipe->fd);
		}
	}
}

void	child(t_tree *main_pipe, t_tree *sub_node, int side)
{
	exec_signals();
	if (side == LEFT)
	{
		manage_input(main_pipe, sub_node, side);
		manage_output(main_pipe, sub_node, side);
		execute_cmd(sub_node, PIPE);
	}
	else if (side == RIGHT)
	{
		if (sub_node->token != NULL)
		{
			manage_node_execution(sub_node);
		}
		else
		{
			manage_input(main_pipe, sub_node, side);
			manage_output(main_pipe, sub_node, side);
			execute_cmd(sub_node, PIPE);
		}
	}
	exit(0);
}
