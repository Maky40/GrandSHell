/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:21:17 by xav               #+#    #+#             */
/*   Updated: 2024/03/05 17:19:39 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_strcat(char *dest, const char *src)
{
    char *ptr;
	
	ptr = dest + ft_strlen(dest);
    while (*src != '\0')
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}


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
            var_name = malloc(var_len + 1);
            if (var_name)
            {
                memcpy(var_name, var_start, var_len);
                var_name[var_len] = '\0';    
            }
            char *var_value = getenv(var_name); // Récupérer la valeur de la variable d'environnement
            printf("Env : %s\n", var_value);
			if (var_value != NULL)
            {
                size_t str_len = strlen(dup->str);
                size_t var_start_index = var_start - dup->str - 1;
                size_t var_end_index = var_end - dup->str;
                size_t new_len = str_len - var_len + strlen(var_value);
                char *new_str = malloc(new_len + 1);
                if (new_str)
                {
                    ft_memcpy(new_str, dup->str, var_start_index); // Copier la partie avant la variable
                    strcpy(new_str + var_start_index, var_value); // Concaténer la valeur de la variable
                    strcat(new_str, dup->str + var_end_index); // Concaténer la partie après la variable
                    free(dup->str); // Libérer l'ancien contenu de dup->str
                    dup->str = new_str; // Remplacer le contenu de dup->str par le nouveau tampon
                   // printf("%s\n", dup->str);
                    ptr = new_str;
                }
            }
            free(var_name);
        }
        ptr++;
    }
		printf("%s\n", dup->str);
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
