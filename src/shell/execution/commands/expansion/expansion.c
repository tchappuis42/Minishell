/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchappui <tchappui@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:46:04 by tweimer           #+#    #+#             */
/*   Updated: 2022/06/05 18:28:52 by tchappui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"

void	delete_quotes(t_token *actual)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(actual->word);
	free(actual->word);
	actual->word = NULL;
	actual->word = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
	free(tmp);
	tmp = NULL;
}

int	manage_quotes(t_group *token_group)
{
	t_token	*actual;

	actual = token_group->first;
	while (actual != NULL)
	{
		if (actual->word != NULL && is_quote(actual->word[0]) != NONE)
		{
			delete_quotes(actual);
		}
		actual = actual->next;
	}
	return (OK);
}

int	chr_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != 0)
			return (YES);
		i++;
	}
	return (NO);
}

void	remplace_content(t_group *all_token)
{
	t_token	*actual;

	if (all_token == NULL || all_token->first == NULL)
		return ;
	actual = all_token->first;
	while (actual != NULL)
	{
		if (actual->word != NULL && actual->word[0] != '\'')
		{
			while (chr_dollar(actual->word) == YES)
			{
				actual->word = replace_dollar(actual->word, g_data.env,
						g_data.exit_status);
				if (actual->word == NULL)
					break ;
			}
		}
		actual = actual->next;
	}
}

int	expansion_arguments(t_group *token_group)
{
	remplace_content(token_group);
	if (manage_quotes(token_group) == ERROR)
		return (ERROR);
	return (OK);
}
