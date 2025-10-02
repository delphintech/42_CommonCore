/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:57:48 by dabouab           #+#    #+#             */
/*   Updated: 2024/06/05 13:00:33 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

int		ft_printf(const char *str, ...);
size_t	ft_strlen(const char *s);
char	*ft_itoa(long n);
int		ft_putchar(int c);
int		ft_putstr(const char *str);
int		ft_putlstr(const char *str, int length);
int		ft_putnbr(int num);
int		print_hexa(unsigned int nb);
int		print_hexa_upper(unsigned int nb);
int		ft_putunsigned(unsigned int num);
int		print_pointer(unsigned long pointer);
void	*ft_calloc(size_t nmemb, size_t size);

#endif