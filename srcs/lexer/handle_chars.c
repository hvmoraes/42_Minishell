/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:53:32 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/14 18:19:57 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* Handle any default character */
static void	handle_def_char(t_suplex *suplex)
{
	suplex->tokens->content[suplex->j] = suplex->input[suplex->i];
	suplex->tokens->type = TOKEN;
	suplex->j++;
}

/* Handle quotes, double quotes, or parenthesis */
static void	handle_def_quotes(t_suplex *suplex)
{
	/* Update status */
	if (suplex->type == QUOTE_CHAR)
		suplex->state = IN_Q;
	else if (suplex->type == DQUOTE_CHAR)
		suplex->state = IN_DQ;
	/* Copy the character into the content of the current token */
	suplex->tokens->content[suplex->j] = suplex->input[suplex->i];
	suplex->tokens->type = TOKEN;
	suplex->j++;
}

/* Handle escape character \\ */
static void	handle_def_esc(t_suplex *suplex)
{
	suplex->tokens->content[suplex->j] = suplex->input[suplex->i];
	suplex->tokens->type = TOKEN;
	suplex->j++;
}

/* Handle terminators */
static int	handle_def_term(t_suplex *suplex)
{
	if (suplex->j > 0)
	{
		suplex->j = 0;
		suplex->tokens->next = (t_token *)malloc(sizeof(t_token));
		if (!suplex->tokens->next)
			return (0);
		suplex->tokens = suplex->tokens->next;
		if (!init_token(suplex->tokens, suplex->length))
			return (0);
	}
	suplex->tokens->content[0] = suplex->input[suplex->i];
	suplex->tokens->type = suplex->type;
	suplex->tokens->next = (t_token *)malloc(sizeof(t_token));
	if (!suplex->tokens->next)
		return (0);
	suplex->tokens = suplex->tokens->next;
	if (!init_token(suplex->tokens, suplex->length))
		return (0);
	return (1);
}

static int	handle_def_space(t_suplex *suplex)
{
	if (suplex->j > 0)
	{
		suplex->j = 0;
		suplex->tokens->next = (t_token *)malloc(sizeof(t_token));
		if (!suplex->tokens->next)
			return (0);
		suplex->tokens = suplex->tokens->next;
		if (!init_token(suplex->tokens, suplex->length))
			return (0);
	}
	return (1);
}

/*	Handle with chars outside brackets, quotes, and escape character	*/
int	handle_default(t_suplex *suplex)
{
	if (suplex->type == DEF_CHAR || suplex->type == USD_CHAR)
		handle_def_char(suplex);
	else if (suplex->type == DQUOTE_CHAR || suplex->type == QUOTE_CHAR || \
		suplex->type == OCB_CHAR)
		handle_def_quotes(suplex);
	else if (suplex->type == ESC_CHAR)
		handle_def_esc(suplex);
	else if (is_terminator(suplex->type))
	{
		if (!handle_def_term(suplex))
			return (0);
	}
	else if (suplex->type == SPACE_CHAR)
		if (!handle_def_space(suplex))
			return (0);
	return (1);
}

void	handle_in_state(t_suplex *suplex)
{
	if (suplex->state == IN_Q)
	{
		suplex->tokens->content[suplex->j] = suplex->input[suplex->i];
		if (suplex->type == QUOTE_CHAR)
			suplex->state = DEF;
	}
	else if (suplex->state == IN_DQ)
	{
		if (suplex->input[suplex->i] == '\\')
		{
			suplex->tokens->content[suplex->j] = suplex->input[suplex->i];
			suplex->j++;
			suplex->i++;
		}
		else if (suplex->type == DQUOTE_CHAR)
			suplex->state = DEF;
		suplex->tokens->content[suplex->j] = suplex->input[suplex->i];
	}
	suplex->j++;
}
