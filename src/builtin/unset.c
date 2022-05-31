/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:47:49 by tweimer           #+#    #+#             */
/*   Updated: 2022/05/31 13:41:30 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/env.h"
#include "execution/execution.h"
#include <stdlib.h>

void	ft_envfree(t_list *env, char *args)
{
	t_list	*lastenv;
	int		i;

	i = 0;
	lastenv = env;
	args = ft_strcat(args, "=");
	i = 0;
	while (env != NULL)
	{
		if (ft_strdcmp(args, env->content, '=') == 0)
		{
			lastenv->next = env->next;
			free(env->content);
			free(env);
			return ;
		}
		if (i == 1)
			lastenv = lastenv->next;
		i = 1;
		env = env->next;
	}
}

int	check_arg_unset(char *args)
{
	int	i;

	i = 0;
	if (ft_isalpha(args[i++]) == NO)
		return (NO);
	while (args[i])
	{
		if (ft_isalnum(args[i]) == NO)
			return (NO);
		i++;
	}
	return (YES);
}

void	ft_unset(t_env *env, char **args)
{
	int	i;

	i = 1;
	while(args[i] != NULL)
	{
		if (check_arg_unset(args[i]) == NO)
		{
			printf("bash: unset: `%s': not a valid identifier\n", args[i]); // mettre su la sortie d erreur
			g_data.exit_status = 1;
		}
		else
		{
			ft_envfree(env->list, args[i]);
			ft_envfree(env->temp, args[i]);
		}
		i++;
	}
}
