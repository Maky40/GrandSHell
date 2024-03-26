/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:20:52 by mnie              #+#    #+#             */
/*   Updated: 2024/03/26 16:51:24 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_error_export(char *str)
{
	char *quote;

	quote = malloc(sizeof(char) * 2);
	quote[0] = '"';
	quote[1] = '\0';
	ft_printf("if 1 : %d, if 2 : %d, if 3 : %d - %d\n", ft_strchr(str, " "), ft_isdigit(str[0]), ft_strchr(str, "'"), ft_strchr(str, quote));
	if (ft_strchr(str, " ") == 1)
	{
		free (quote);
		return (ft_printf_error_export("ERROR"));
	}
	if (ft_isdigit(str[0]) == 1)
	{
		free (quote);
		return (ft_printf_error_export("ERROR"));
	}
	if (ft_strchr(str, "'") == 1 && ft_strchr(str, quote) == 1)
	{
		free (quote);
		return (ft_printf_error_export("ERROR"));
	}
	free (quote);
	return (0);
}