/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:54:19 by tchappui          #+#    #+#             */
/*   Updated: 2022/05/19 18:38:18 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/env.h"
#include "execution/execution.h"

static char	*find_path3(t_list *list)
{
	char	*rtn;
	int		i; 

	i = 0;
	while (list != NULL)
	{
		if (ft_strncmp(list->content, "PATH=", 5) == 0)
			break ;
		list = list->next;
		i++;
	}
	rtn = ft_substr(list->content, 5, ft_strlen(list->content) - 5);
	return (rtn);
}

static char	**find_path2(t_list *list)
{
	char	*arg;
	char	**path;
	int		i;

	arg = NULL;
	arg = find_path3(list);
	path = ft_split(arg, ':');
	free(arg);
	i = 0;
	while (path[i] != NULL)
	{
		arg = ft_strdup(path[i]);
		free(path[i]);
		path[i] = NULL;
		path[i] = ft_strjoin(arg, "/");
		free(arg);
		i++;
	}
	return (path);
}

static char	*find_path(t_list *list, char *arg)
{
	char	*cmd;
	char	**path;
	int		i;

	if (access(arg, F_OK) != -1)
	{
		if (ft_strncmp(arg, "./", 2) == 0)
			return (arg);
		return (NULL);
	}
	i = 0;
	path = find_path2(list);
	while (path[i] != 0)
	{
		cmd = ft_strjoin(path[i], arg);
		if (access(cmd, F_OK) == -1)
		{
			free(cmd);
			cmd = NULL;
			i++;
		}
		else
			return (cmd);
	}
	return (NULL);
}

int	base_builtin(char **str, t_env *env) //execute les commande de base
{
	char	*cmd;
	pid_t	out;
	int		ret;
	int		status;

	cmd = NULL;
	out = fork();
	ret = 0;
	if (out == 0)
	{
		cmd = find_path(env->list, str[0]);
		if (!cmd)
		{
			printf("Minishell: %s: command not found\n", str[0]);
			exit(0);
		}
		if (execve(cmd, str, NULL) == -1)
		{
			if (cmd != NULL)
				free (cmd);
			cmd = NULL;
			ret = 1;
			exit(0);
		}
		free (cmd);
		cmd = NULL;
		ft_addenv(env, env->list, ft_strcat("_=", str[0]));
	}
	else
		waitpid(out, &status, WCONTINUED);
	if (ret == 0)
		return (8);
	return (0);
}
