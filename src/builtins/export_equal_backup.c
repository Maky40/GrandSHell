// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   export_equal.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/20 10:09:45 by mnie              #+#    #+#             */
// /*   Updated: 2024/03/25 17:09:29 by mnie             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// void	delete_after_equal(char **env, int pos)
// {
// 	int		i;
// 	int		j;
// 	char	*new_str;

// 	i = 0;
// 	j = 0;
// 	while (env[pos][i] != '=')
// 		i++;
// 	while (env[pos][i])
// 	{
// 		i++;
// 		j++;
// 	}
// 	new_str = malloc(sizeof(char) * (i - j + 1));
// 	j = 0;
// 	while (env[pos][j] != '=')
// 	{
// 		new_str[j] = env[pos][j];
// 		j++;
// 	}
// 	new_str[j] = env[pos][j];
// 	new_str[j + 1] = '\0';
// 	free (env[pos]);
// 	env[pos] = new_str;
// }

// char	*str_without_plus(char *str)
// {
// 	int		i;
// 	int		pos;
// 	char	*new_str;

// 	pos = 0;
// 	i = 0;
// 	ft_printf("la1\n");
// 	new_str = malloc(sizeof(char) * ft_strlen(str));
// 	ft_printf("la2\n");
// 	while (str[pos] != '=')
// 		pos++;
// 	ft_printf("la3\n");
// 	while (i < pos - 1)
// 	{
// 		new_str[i] = str[i];
// 		i++;
// 	}
// 	ft_printf("la4\n");
// 	while (str[pos])
// 	{
// 		new_str[i] = str[pos];
// 		i++;
// 		pos++;
// 	}
// 	ft_printf("la5\n");
// 	new_str[i] = '\0';
// 	ft_printf("la6\n");
// 	free (str);
// 	ft_printf("la7\n");
// 	return (new_str);
// }

// int		pos_variable_env(char **env, char *str)
// {
// 	int		i;
// 	char	*variable_tmp;

// 	i = 0;
// 	variable_tmp = ft_dup_var(str);
// 	while (env[i])
// 	{
// 		if (ft_strncmp(variable_tmp, env[i], ft_strlen(variable_tmp)) == 0 \
// 			&& env[i][ft_strlen(variable_tmp)] == '=')
// 			return (i);
// 		i++;
// 	}
// 	free (variable_tmp);
// 	return (0);
// }

// void	variable_add2(char **env, char *str, int pos)
// {
// 	int		i;
// 	char	*tmp;
// 	int		j;
// 	char	*new_str;

// 	i = 0;
// 	j = 0;
// 	while (str[i] != '=')
// 		i++;
// 	i++;
// 	tmp = malloc(sizeof(char) * (ft_strlen(str) - i));
// 	while (((unsigned int) i + j++)< ft_strlen(str))
// 		tmp[j] = str[i + j];
// 	tmp[j] = '\0';
// 	new_str = ft_strjoin(env[pos], tmp);
// 	free(tmp);
// 	free(env[pos]);
// 	env[pos] = ft_strdup(new_str);
// 	free(new_str);

// }
// void	variable_add1(t_env *env, char *str)
// {
// 	if (search_variable(env, str) == 1)
// 		variable_add2(env -> modified_env, str, pos_variable_env(env -> modified_env, str));
// 	if (search_variable(env, str) == 2)
// 	{
// 		do_unset2(env, str, 2);
// 		create_variable(env, str);
// 	}
// }

// void	export_with_equal(t_env *env, char *str)
// {
// 	if (ft_strncmp(str, "_=", 2) == 0)
// 		return ;
// 	else if (before_equal(str) == '+')
// 	{
// 		str = str_without_plus(str);
// 		ft_printf("str = %s\n", str);
// 		if (search_variable(env, str) == 0)
// 			create_variable(env, str);
// 		else
// 			variable_add1(env, str);
// 	}
// 	else if (before_equal(str) == '-')
// 		ft_printf("ERROR\n");
// 	else if (search_variable(env, str) == 0)
// 		create_variable(env, str);
// 	else if (search_variable(env, str) == 1)
// 	{
// 		do_unset2(env, str, 1);
// 		create_variable(env, str);
// 	}
// 	else if (search_variable(env, str) == 2)
// 	{
// 		do_unset2(env, str, 2);
// 		create_variable(env, str);
// 	}
// 	// else
// 	// {
// 	// 	if (before_equal(str) == '+')
// 	// 		variable_add(env, str, pos_variable_env(env, str));
// 	// 	else if (before_equal(str) == '-')
// 	// 		ft_printf("ERROR PAS DE -");
// 	// 	else
// 	// 	{
// 	// 		delete_after_equal(env, pos_variable_env(env, str));
// 	// 		variable_add(env, str, pos_variable_env(env, str));
// 	// 	}
// 	// }
// }
