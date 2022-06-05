/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:32:32 by tchappui          #+#    #+#             */
/*   Updated: 2022/06/05 17:00:11 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/command.h"
#include "environment/env.h"

int	manage_commands(t_group *all_tokens)
{
	t_command	**all_commands;

	all_commands = shell_commands(all_tokens);
	shell_execution(all_tokens, all_commands);
	if (all_commands != NULL)
	{
		clean_commands(all_commands);
		all_commands = NULL;
	}
	return (1);
}

void	manage_tokens(char *input)
{
	t_group	*all_tokens;

	all_tokens = tokenizer(input);
	if (all_tokens != NULL)
		manage_commands(all_tokens);
	if (all_tokens != NULL)
	{
		clean_tokens(all_tokens);
		free(all_tokens);
		all_tokens = NULL;
	}
}

void	manage_user_input(void)
{
	char	*input;

	input = get_user_input();
	manage_tokens(input);
	free(input);
	input = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;

	(void)argv;
	if (argc == 1)
	{
		env.list = NULL;
		env.temp = NULL;
		ft_env(&env.list, envp);
		g_data.env = &env;
		init_terminal();
		while (RUNNING)
		{
			manage_user_input();
		}
		return (1);
	}
	return (0);
}
