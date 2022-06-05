/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:44:14 by tweimer           #+#    #+#             */
/*   Updated: 2022/06/05 21:02:28 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sub_system/terminal.h"
#include "minishell.h"

void	new_prompt(int sig)
{
	(void)sig;
	g_data.exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	block_signals_from_keyboard(void)
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

static void	quit_process(int signal)
{
	(void)signal;
	g_data.exit_status = 131;
	write(2, "Quit: 3\n", 8);
}

static void	interrupt_process(int signal)
{
	(void)signal;
	g_data.exit_status = 130;
	write(1, "\n", 1);
}

void	exec_signals(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}
