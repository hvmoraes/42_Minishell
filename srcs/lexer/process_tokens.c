/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:12:13 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/15 13:27:39 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	check_state(int *state, int *count, int i, char *str)
{
	if (str[i] == '\'')
	{
		if (*state == DEF)
			*state = IN_Q;
		else if (*state == IN_Q)
			*state = DEF;
		else
			return ;
		(*count) ++;
	}
	else if (str[i] == '\"')
	{
		if (*state == DEF)
			*state = IN_DQ;
		else if (*state == IN_DQ)
			*state = DEF;
		else
			return ;
		(*count) ++;
	}
}

static int	needs_trimming(char *str)
{
	int	state;
	int	i;
	int	count;

	state = DEF;
	i = 0;
	count = 0;
	while (i < (int)ft_strlen(str))
	{
		if (state != IN_Q)
		{
			if (str[i] == '\\')
				i += 2;
		}
		check_state(&state, &count, i, str);
		i++;
	}
	return (count);
}

void	trim_str(char *str, char *trimmed)
{
	int		i;
	int		j;
	int		len;
	char	l_quote;

	len = ft_strlen(str);
	l_quote = 0;
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			trimmed[j++] = str[i++];
			trimmed[j++] = str[i];
		}
		else if ((str[i] == '\'' || str[i] == '\"') && l_quote == 0)
			l_quote = str[i];
		else if (str[i] == l_quote)
			l_quote = 0;
		else
			trimmed[j++] = str[i];
	}
}

/* Remove quotes and double quotes*/
static int trim_quotes(t_token *curr)
{
	char	*trimmed;

	if (!needs_trimming(curr->content))
		return (1);
	trimmed = ft_calloc(ft_strlen(curr->content) + 1, sizeof(char));
	if (!trimmed)
		return (0);
	trim_str(curr->content, trimmed);
	free(curr->content);
	curr->content = trimmed;
	return (1);
}

static int parse_tokens(t_suptok *suptok, t_token *curr, t_token *prev,
	t_lexer *lex)
{
	suptok->count = 0;
	suptok->here = 0;
	suptok->semaphore = 0;
	suptok->curr = curr;
	suptok->prev = prev;
	(void)lex;
	while (suptok->curr)
	{
		if (suptok->curr->type == TOKEN)
		{
			handle_expand(suptok->curr);
			if (!trim_quotes(suptok->curr))
			return (-1);
		}
    	if (suptok->prev && suptok->prev->type == INRED_CHAR &&
			suptok->curr->type == INRED_CHAR)
			suptok->here = 1;
    	else
			suptok->here = 0;
		suptok->prev = suptok->curr;
		suptok->curr = suptok->curr->next;
  	}
	return (suptok->count);
}

int process_tokens(t_lexer *lex) {
	t_suptok suptok;
	t_token *curr;
	t_token *prev;
	int count;

	prev = NULL;
	curr = lex->token_list;
	count = parse_tokens(&suptok, curr, prev, lex);
	return (count);
}
