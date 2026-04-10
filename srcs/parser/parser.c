/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:55:34 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/15 12:01:15 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parser(t_lexer *lex, t_ast **root)
{
	g_data.token = lex->token_list;
	g_data.ast_root = (t_ast **)ft_calloc(1, sizeof(t_ast *));
	if (!g_data.ast_root)
		return (0);
	*root = cmd_line();
	return (1);
}
