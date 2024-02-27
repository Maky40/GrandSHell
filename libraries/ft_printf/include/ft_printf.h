/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:16:58 by mnie              #+#    #+#             */
/*   Updated: 2023/10/23 12:41:31 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_puthex(unsigned long n, const char *base);
int	ft_printf(const char *str, ...);
int	ft_len_hexa(unsigned long num);
int	ft_len_putnbr(int num);
int	ft_len_unsigned_putnbr(unsigned int num);

#endif
