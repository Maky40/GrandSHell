/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:21:17 by xav               #+#    #+#             */
/*   Updated: 2024/03/06 16:25:42 by xav              ###   ########.fr       */
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


char *ft_strcpy(char *dest, const char *src)
{
    char *ptr = dest;
    while (*src)
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}


void expand_variable(t_data *data, t_lexer *dup)
{
    char *ptr;
    char *var_start;
    char *var_end;
    char *var_name;
	char *var_value;
    size_t var_len;

    ptr = dup->str;
    while (*ptr)
    {	
        if (*ptr == '$' && (ptr[1] != '\0' && ptr[1] != ' ' && ptr[1] != '.'))
        {
			if (ptr[1] > '0' && ptr[1] <= '9')
				var_start = ptr + 2;
			else	
            	var_start = ptr + 1;
            var_end = var_start;
            while(*var_end != ' ' && *var_end != '$' && *var_end && *var_end != '"') 
                var_end++;
            var_len = var_end - var_start;
            var_name = malloc(var_len + 1);
            if (var_name)
            {
                ft_memcpy(var_name, var_start, var_len);
                var_name[var_len] = '\0';    
            }
			printf("var name : %s\n", var_name);
			if (var_name[0] == '?')
				var_value = ft_itoa(data->exit_status);
			else if(var_name[0] > '0' && var_name[0] <= '9')
			{
				printf("je suis var_name number\n");
			}
			else
				var_value = getenv(var_name);
			if (var_value != NULL)
            {
                size_t str_len = ft_strlen(dup->str);
                size_t var_start_index = var_start - dup->str - 1;
                size_t var_end_index = var_end - dup->str;
                size_t new_len = str_len - var_len + ft_strlen(var_value);
                char *new_str = malloc(new_len + 1);
                if (new_str)
                {
                    ft_memcpy(new_str, dup->str, var_start_index); // Copier la partie avant la variable
                    ft_strcpy(new_str + var_start_index, var_value); // Concaténer la valeur de la variable
                    ft_strcat(new_str, dup->str + var_end_index); // Concaténer la partie après la variable
                    free(dup->str); // Libérer l'ancien contenu de dup->str
                    dup->str = new_str; // Remplacer le contenu de dup->str par le nouveau tampon
                    ptr = new_str;
                }
			/*
			else
			{
				delete_expand();
			}
            }
			*/
            free(var_name);
        }
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
