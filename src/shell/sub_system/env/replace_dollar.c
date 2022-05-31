/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:07:10 by tchappui          #+#    #+#             */
/*   Updated: 2022/05/30 14:41:20 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/env.h"

static char	*is_alnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			arg[i] = 0;
		else
			i++;
	}
	return (arg);
}

static char	*ft_compart(char *arg, t_list *env, t_list *temp)
{
	int	i;

	arg = is_alnum(arg);
	i = ft_strlen(arg);
	while (env != NULL)
	{
		if (ft_strdcmp (env->content, "_=", '=') == 0
			&& ft_strcmp(arg, "_=") == 0)
			return (env->content + 13);
		if (ft_strdcmp(arg, env->content, '=') == 0)
			return (env->content + i + 1);
		env = env->next;
	}
	while (temp != NULL)
	{
		if (ft_strdcmp(arg, temp->content, '=') == 0)
			return (temp->content + i + 1);
		temp = temp->next;
	}
	return (NULL);
}

static char	*ft_end(char *arg, int i)
{
	char	*ret;
	int		j;

	ret = NULL;
	j = 0;
	if (ft_isalpha(arg[i]) == 0)
		i++;
	else
	{
		while (ft_isalnum(arg[i]) == 1 | arg[i] == '?' | arg[i] == '_')
			i++;
	}
	if (arg[i] != 0)
	{
		ret = malloc(ft_strlen(arg + i) + 1);
		while (arg[i])
		{
			ret[j] = arg[i];
			j++;
			i++;
		}
		ret[j] = 0;
		return (ret);
	}
	return (NULL);
}

static char	*ft_replace_dollar(char *arg, int i, t_env *env, int exit_s)
{
	char	*end;
	char	*retenv;
	char	*ret;
	char	*exit_status;

	exit_status = NULL;
	ret = NULL;
	end = ft_end(arg, i + 1);
	if (arg[i + 1] == '?')
	{
		exit_status = ft_itoa(exit_s);
		retenv = exit_status;
	}
	else
		retenv = ft_compart(arg + i + 1, env->list, env->temp);
	arg[i] = 0;
	if (retenv != NULL)
		ret = ft_strjoin(arg, retenv);
	else
		ret = ft_strdup(arg);
	if (end != NULL)
	{
		ret = ft_strjoin_custom(ret, end);
		free (end);
	}
	return (ret);
}

char	*replace_dollar(char *args, t_env *env, int exit_s)
{
	int		i;
	char	*ret;

	i = 0;
	while (args[i])
	{
		if (args[i] == '$' && args[i + 1] != 0)
		{
			ret = ft_replace_dollar(args, i, env, exit_s);
			i = -1;
		}
		i++;
	}
	return (ret);
}
