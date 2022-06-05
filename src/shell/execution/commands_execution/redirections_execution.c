/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:46:21 by tweimer           #+#    #+#             */
/*   Updated: 2022/06/05 20:54:32 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"

void	replace_input(t_command *cmd)
{
	t_redirection	*actual;

	if (cmd->input == NULL)
		return ;
	actual = cmd->input;
	while (actual != NULL)
	{
		if (actual->type == LESS)
		{
			actual->fd = open(actual->file_name, O_RDONLY);
			dup2(actual->fd, STDIN_FILENO);
			close(actual->fd);
		}
		else if (actual->type == DLESS)
		{
			actual->fd = execute_here_doc(actual->content);
			close(actual->fd);
			actual->fd = open(TMP_FILE, O_RDONLY);
			dup2(actual->fd, STDIN_FILENO);
			close(actual->fd);
			unlink(TMP_FILE);
		}
		actual = actual->next;
	}
}

int	redirection_files(t_command *cmd)
{
	t_redirection	*actual;
	t_redirection	*last;

	last = NULL;
	actual = NULL;
	if (cmd->output == NULL)
		return (0);
	actual = cmd->output;
	while (actual != NULL)
	{
		last = actual;
		actual = actual->next;
	}
	if (last->type == DGREAT)
	{
		last->fd = open(last->file_name, O_WRONLY | O_CREAT
				| O_APPEND, S_IWUSR | S_IRUSR);
	}
	else if (last->type == MORE)
	{
		last->fd = open(last->file_name, O_RDWR | O_TRUNC | O_CREAT,
				S_IWUSR | S_IRUSR);
	}
	return (last->fd);
}

void	output_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->output == NULL)
		return ;
	fd = redirection_files(cmd);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	input_redirection(t_command *cmd)
{
	if (cmd->input == NULL)
		return ;
	replace_input(cmd);
}
