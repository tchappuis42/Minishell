/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:19:00 by tchappui          #+#    #+#             */
/*   Updated: 2022/05/31 13:44:33 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/env.h"

void	ft_env(t_list **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		ft_lstadd_back(env, ft_lstnew(envp[i]));
		i++;
	}
}
