/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:53:13 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/13 16:55:11 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var_name(t_token *token, t_supexp *supexp, int i)
{
	int		end;
	char	*var_name;
	char	*temp;

	end = i;
	while (token->content[end] && (ft_isalnum(token->content[end]) || token->content[end] == '_'))
		end++;
	supexp->end = end;
	if (end == i)
		return (ft_strdup(""));
	temp = ft_substr(token->content, i, end - i);
	if (!temp)
		return (NULL);
	var_name = ft_strjoin(temp, "=");
	if (!var_name)
		return (NULL);
	free(temp);
	return (var_name);
}

int	replace_content(t_token *token, t_supexp *supexp)
{
	char	*temp;
	char	*left_side;
	char	*right_side;

	left_side = ft_substr(token->content, 0, supexp->start);
	if (!left_side)
		return (0);
	temp = ft_strjoin(left_side, supexp->new_cont);
	if (!temp)
	{
		free(left_side);
		return (0);
	}
	right_side = ft_substr(token->content, supexp->end,
			ft_strlen(token->content));
	if (!right_side)
	{
		free(left_side);
		free(temp);
		return (0);
	}
	free(token->content);
	token->content = ft_strjoin(temp, right_side);
	free(left_side);
	free(right_side);
	free(temp);
	if (!token->content)
		return (0);
	return (1);
}

static int	expand(t_token *token, t_supexp *supexp, int *i)
{
	supexp->start = *i;
	supexp->end = *i;
	supexp->new_cont = NULL;
	supexp->var_name = NULL;
	(*i)++;
	if (token->content[*i] == QM_CHAR)
		supexp->new_cont = ft_itoa(g_data.status);
	else if (token->content[*i] == ' ' || !token->content[*i])
		return (1);
	else
	{
		supexp->var_name = get_var_name(token, supexp, *i);
		if (!supexp->var_name)
			return (0);
		supexp->new_cont = ft_strdup(get_env_value(supexp->var_name));
	}
	replace_content(token, supexp);
	if (supexp->new_cont)
		free(supexp->new_cont);
	if (supexp->var_name)
		free(supexp->var_name);
	return (1);
}

static int	def_state(t_token *token, t_supexp *supexp, int *i, int *state)
{
	if (token->content[*i] == ESC_CHAR)
	{
		(*i) ++;
		return (1);
	}
	if (token->content[*i] == USD_CHAR)
	{
		if (!expand(token, supexp, i))
			return (0);
	}
	else if (token->content[*i] == DQUOTE_CHAR)
		*state = IN_DQ;
	else if (token->content[*i] == QUOTE_CHAR)
		*state = IN_Q;
	return (1);
}

static int in_state(t_token *token, t_supexp *supexp, int *i, int *state)
{
	if (*state == IN_Q)
	{
		if (token->content[*i] == QUOTE_CHAR)
			*state = DEF;
	}
	else if (*state == IN_DQ)
	{
		if (token->content[*i] == ESC_CHAR)
		{
			(*i) ++;
			return (1);
		}
		if (token->content[*i] == USD_CHAR)
		{
			if (!expand(token, supexp, i))
				return (0);
		}
		else if (token->content[*i] == DQUOTE_CHAR)
			*state = DEF;
	}
	return (1);
}

int	handle_expand(t_token *token)
{
	int			i;
	int			state;
	t_supexp	supexp;

	i = -1;
	state = DEF;
	supexp.curr = token;
	while (i < (int)ft_strlen(token->content) && token->content[++i])
	{
		if (state == DEF)
		{
			if (!def_state(token, &supexp, &i, &state))
				return (0);
		}		
		else
		{
			if (!in_state(token, &supexp, &i, &state))
				return (0);
		}
	}
	return (1);
}
