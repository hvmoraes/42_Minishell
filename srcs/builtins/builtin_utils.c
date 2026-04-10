/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:57:40 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/09 16:07:39 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_builtin(t_built **list, char *cmd, int (*f)(char **))
{
	t_built	*new;
	t_built	*temp;

	new = (t_built *)malloc(sizeof(t_built));
	if (!new)
		exit(EXIT_FAILURE);
	new->cmd = cmd;
	new->f = f;
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}