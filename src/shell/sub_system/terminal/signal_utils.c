/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:34:53 by tchappui          #+#    #+#             */
/*   Updated: 2022/06/05 16:39:07 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sub_system/terminal.h"
#include "minishell.h"

void	signal_here_document(int signal)
{
	(void)signal;
	g_data.exit_status = 1;
	write(1, "\n", 1);
	exit(1);
}

void	exit_minishell(int sig)
{
	(void)sig;
	exit(EXIT_SUCCESS);
}
