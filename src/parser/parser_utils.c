/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:33:35 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:33:36 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*replace_tabs(char *str)
{
	int		i;
	char	*new;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\t' || str[i] == '\v')
			new[i] = ' ';
		else
			new[i] = str[i];
	}
	free(str);
	return (new);
}

int	matrix_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	free_matrix(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
