/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:56:53 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 15:00:53 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_rules_1(const char letter, va_list args)
{
	int				len;
	unsigned long	p;

	len = 0;
	if (letter == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (letter == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (letter == 'p')
	{
		p = va_arg(args, unsigned long);
		if (p == 0)
			len += ft_putstr("(nil)");
		else
		{
			len += ft_putstr("0x");
			len += ft_puthex(p, "0123456789abcdef");
		}
	}
	return (len);
}

int	ft_rules_2(const char letter, va_list args)
{
	int	len;

	len = 0;
	if (letter == 'd' || letter == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (letter == 'u')
		len += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (letter == 'x')
		len += ft_puthex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (letter == 'X')
		len += ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (letter == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_rules_1(str[i], args);
			len += ft_rules_2(str[i], args);
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
// #include <stdio.h>
// int	main()
// {
// 	char	*str = "astek";
// 	ft_printf("\nlen : %d\n", ft_printf(" %p --", str));
// 	printf("valeur vrai printf : %p", str);
// 	printf("\n valeur vrai printf : %p", str);
// }
