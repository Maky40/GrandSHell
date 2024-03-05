/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:21:17 by xav               #+#    #+#             */
/*   Updated: 2024/03/05 15:47:00 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void expand_variable(t_data *data, t_lexer *dup)
{
	char *ptr;
	char *var_start;
	char *var_end;
	char *var_name;
	size_t var_len;

	(void)data;
	ptr = dup->str;
	while (*ptr)
	{
		if (*ptr == '$' && ptr[1] != '\0')
		{
			var_start = ptr + 1;
			var_end = var_start;
			while(*var_end != ' ' && *var_end != '$' && *var_end && *var_end != '"') 
				var_end++;
			var_len = var_end - var_start;
			var_name = malloc(sizeof(char *) *(var_len + 1));
			if (var_name)
			{
				ft_strncpy(var_name, var_start, var_len);
				var_name[var_len] = '\0';
				printf("%s\n", var_name);	
			}
			char *var_value = getenv(var_name);
			if (var_value != NULL)
			{
				size_t str_len = strlen(dup->str);
				size_t new_len = str_len - (var_end - var_start) + strlen(var_value);
				char *new_str = malloc(new_len + 1);
				if (new_str)
				{
					strncpy(new_str, dup->str, var_start - dup->str - 1); // Copie la partie avant la variable
					strcat(new_str, var_value); // Concatène la valeur de la variable
					strcat(new_str, var_end); // Concatène la partie après la variable
					free(dup->str); // Libère l'ancien contenu de dup->str
					dup->str = new_str; // Remplace le contenu de dup->str par le nouveau tampon
					printf("%s\n", dup->str);
					ptr = new_str;
				}
			}
			free(var_name);
		}
		ptr++;
	}
	}

/*
void handle_multiple_expand(t_data *data, t_lexer *dup)
{
	(void)data;
	(void)dup;
		printf("Je suis multiple\n");
}

void handle_single_expand(t_data *data, t_lexer *dup)
{
	int len;

	len = ft_strlen(dup->str);
	(void)data;
	(void)dup;
	printf("Je suis single\n");
	printf("%s\n", dup->str);
	if (ft_strnstr(dup->str, "$?", len))
		expand_exit_status(data, dup);
	else
		expand_env(data, dup);
	
}

void	count_expander(t_data *data, t_lexer *dup)
{
	int	nb_expander;
	int	i;

	nb_expander = 0;
	i = -1; 
	while (dup->str[++i])
	{
		if (dup->str[i] == '$')
			nb_expander++;
	}
	if (nb_expander > 1)
		handle_multiple_expand(data, dup);
	else
		handle_single_expand(data, dup);
}

*/
void	expander(t_data *data, t_lexer **lexer)
{
	t_lexer	*dup; 

	dup = *lexer;
	while (dup)
	{
		if (dup->str[0] != '\'')
			expand_variable(data, dup);
		dup = dup->next;
	}
}
