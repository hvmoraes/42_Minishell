/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:17:36 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/10 13:57:40 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	Initializes a token pointed to by token with an empty content of size 
	length + 2, allocated using malloc. Returns 1 on success, and 0 otherwise	*/
int	init_token(t_token *token, int length)
{
	token->content = (char *)ft_calloc((length + 2), sizeof(char));
	if (!token->content)
		return (0);
	token->type = NULL_CHAR;
	token->next = NULL;
	return (1);
}
