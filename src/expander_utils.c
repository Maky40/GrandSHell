/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:44:56 by xav               #+#    #+#             */
/*   Updated: 2024/04/03 14:57:35 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}

void	new_str_null(t_lexer *dup, t_expander *expander, char **ptr)
{
	size_t	str_len;
	size_t	start_index;
	size_t	end_index;
	size_t	new_len;
	char	*new_str;

	str_len = ft_strlen(dup->str);
	start_index = expander->start - dup->str - 1;
	end_index = expander->end - dup->str;
	new_len = str_len - expander->len;
	new_str = malloc(sizeof(char *) * (new_len + 1));
	if (!new_str)
		return ;
	ft_memcpy(new_str, dup->str, start_index);
	ft_strcpy(new_str + start_index, dup->str + end_index);
	new_str[new_len] = '\0';
	free(dup->str);
	dup->str = new_str;
	printf("dup->str : %s\n", dup->str);
	*ptr = new_str;
}

void	new_str(t_lexer *dup, t_expander *expander, char **ptr)
{
	size_t	str_len;
	size_t	start_index;
	size_t	end_index;
	size_t	new_len;
	char	*new_str;

	str_len = ft_strlen(dup->str);
	start_index = expander->start - dup->str - 1;
	end_index = expander->end - dup->str;
	new_len = str_len - expander->len + ft_strlen(expander->value);
	new_str = malloc(sizeof(char *) * (new_len + 1));
	if (!new_str)
		return ;
	ft_memcpy(new_str, dup->str, start_index);
	ft_strcpy(new_str + start_index, expander->value);
	ft_strcat(new_str, dup->str + end_index);
	free(dup->str);
	dup->str = new_str;
	*ptr = new_str;
}

void	new_str_number(t_lexer *dup, t_expander *expander, char **ptr)
{
	size_t	str_len;
	size_t	start_index;
	size_t	end_index;
	size_t	new_len;
	char	*new_str;

	str_len = ft_strlen(dup->str);
	start_index = expander->start - dup->str - 2;
	end_index = expander->end - dup->str;
	new_len = str_len - expander->len + ft_strlen(expander->value);
	new_str = malloc(sizeof(char *) * (new_len + 1));
	if (!new_str)
		return ;
	ft_memcpy(new_str, dup->str, start_index);
	ft_strcpy(new_str + start_index, expander->value);
	ft_strcat(new_str, dup->str + end_index);
	free(dup->str);
	dup->str = new_str;
	printf("dup->str : %s\n", dup->str);
	*ptr = new_str;
}
