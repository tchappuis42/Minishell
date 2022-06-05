/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:44:37 by tweimer           #+#    #+#             */
/*   Updated: 2022/06/05 21:35:26 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(char *message_extra, char *command, char *erreur_message)
{
	write(STDERR_FILENO, "bash: ", 6);
	if (command != NULL)
		write(STDERR_FILENO, command, ft_strlen(command));
	if (message_extra != NULL)
	{
		write(STDERR_FILENO, message_extra, ft_strlen(message_extra));
		write(STDERR_FILENO, ": ", 2);
	}
	if (erreur_message != NULL)
		write(STDERR_FILENO, erreur_message, ft_strlen(erreur_message));
	else
		perror(NULL);
	write(STDERR_FILENO, NEWLINE, 1);
}

void	write_syntax_token_error(int token_type)
{
	write(2, "tsh: syntax error near unexpected token ", 40);
	if (token_type == PIPE)
		write(2, "\'|\'\n", 4);
	else if (token_type == OR_IF)
		write(2, "\'||\'\n", 5);
	else if (token_type == AND_IF)
		write(2, "\'&&\'\n", 5);
	else if (token_type == MORE)
		write(2, "\'>\'\n", 4);
	else if (token_type == LESS)
		write(2, "\'<\'\n", 4);
	else if (token_type == DGREAT)
		write(2, "\'>>\'\n", 5);
	else if (token_type == DLESS)
		write(2, "\'<<\'\n", 5);
}
