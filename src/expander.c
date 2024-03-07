/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:21:17 by xav               #+#    #+#             */
/*   Updated: 2024/03/07 12:27:58 by xav              ###   ########.fr       */
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
    t_expander expander;

    ptr = dup->str;
    while (*ptr)
    {   
        if (*ptr == '$' && (ptr[1] != '\0' && ptr[1] != ' ' && ptr[1] != '.'))
        {
            if (ptr[1] > '0' && ptr[1] <= '9')
                expander.start = ptr + 2;
            else    
                expander.start = ptr + 1;
            expander.end = expander.start;
            while(*expander.end != ' ' && *expander.end != '$' && *expander.end && *expander.end != '"') 
                expander.end++;
            expander.len = expander.end - expander.start;
            expander.name = malloc(expander.len + 1);
            if (expander.name)
            {
                ft_memcpy(expander.name, expander.start, expander.len);
                expander.name[expander.len] = '\0';    
            }
            printf("var name : %s\n", expander.name);
            if (expander.name[0] == '?')
                expander.value = ft_itoa(data->exit_status);
            else if(expander.name[0] > '0' && expander.name[0] <= '9')
            {
                expander.value = expander.name;
            }
            else
                expander.value = getenv(expander.name);
            if (expander.value != NULL)
            {
                size_t str_len = ft_strlen(dup->str);
                size_t var_start_index = expander.start - dup->str - 1;
                size_t var_end_index = expander.end - dup->str;
                size_t new_len = str_len - expander.len + ft_strlen(expander.value);
                char *new_str = malloc(new_len + 1);
                if (new_str)
                {
                    ft_memcpy(new_str, dup->str, var_start_index); // Copier la partie avant la variable
                    ft_strcpy(new_str + var_start_index, expander.value); // Concaténer la valeur de la variable
                    ft_strcat(new_str, dup->str + var_end_index); // Concaténer la partie après la variable
                    free(dup->str); // Libérer l'ancien contenu de dup->str
                    dup->str = new_str; // Remplacer le contenu de dup->str par le nouveau tampon
                    printf("dup->str : %s\n", dup->str);
                    ptr = new_str;
                }
            }
            else
            {
                if (dup->str[0] == '"')
                {
                    printf("je suis dans dupstr quote\n");
                    size_t str_len = ft_strlen(dup->str);
                    size_t var_start_index = expander.start - dup->str - 1;
                    size_t var_end_index = expander.end - dup->str;
                    size_t new_len = str_len - expander.len;
                    char *new_str = malloc(new_len + 1);
                    if (new_str)
                    {
                        ft_memcpy(new_str, dup->str, var_start_index); // Copier la partie avant la variable
                        ft_strcat(new_str, dup->str + var_end_index); // Concaténer la partie après la variable
                        free(dup->str); // Libérer l'ancien contenu de dup->str
                        dup->str = new_str; // Remplacer le contenu de dup->str par le nouveau tampon
                        printf("dup->str : %s\n", dup->str);
                        ptr = new_str;
                    }
                }
                else
                {
                    dup->str = NULL;
                }
            }
            free(expander.name);
            
        }
        ptr++;
    }
    printf("%s\n", dup->str);
}



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
