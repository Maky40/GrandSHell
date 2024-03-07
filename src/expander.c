/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xav <xav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:21:17 by xav               #+#    #+#             */
/*   Updated: 2024/03/07 14:47:30 by xav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char *get_env_value(char **envp, char *var_name)
{
    while (*envp != NULL)
    {
        if (ft_strncmp(*envp, var_name, ft_strlen(var_name)) == 0 && (*envp)[ft_strlen(var_name)] == '=')
            return (*envp + ft_strlen(var_name) + 1);
        envp++;
    }
    return NULL;
}


void find_expander_len(char *ptr, t_expander *expander) 
{
    if (ptr[1] > '0' && ptr[1] <= '9')
        expander->start = ptr + 2;
    else    
        expander->start = ptr + 1;
    expander->end = expander->start;
    while (*expander->end != ' ' && *expander->end != '$' 
	&& *expander->end && *expander->end != '"') 
        expander->end++;
}

void	get_value(t_data *data, t_lexer *dup, t_expander *expander, char **ptr)
{
	expander->len = expander->end - expander->start;
	expander->name = malloc(sizeof(char *) * (expander->len + 1));
	if (expander->name)
	{
		ft_memcpy(expander->name, expander->start, expander->len);
		expander->name[expander->len] = '\0'; 
	}
	if (expander->name[0] == '?')
        expander->value = ft_itoa(data->exit_status);
    else if (expander->name[0] > '0' && expander->name[0] <= '9')
        expander->value = expander->name;
    else
	{
    	expander->value = get_env_value(data->env, expander->name);
	}
	if (expander->value == NULL)
		return;
	if (expander->name[0] > '0' && expander->name[0] <= '9')
		new_str_number(dup, expander, ptr);
	else
		new_str(dup, expander, ptr);
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
			find_expander_len(ptr, &expander);
			get_value(data, dup, &expander, &ptr);
            if (expander.value == NULL)
            {
                if (dup->str[0] == '"')
					new_str_null(dup, &expander, &ptr);
                else
					dup->str = NULL;            
            }
    	}
        ptr++;
	}
    printf("dup->str : %s\n", dup->str);
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
