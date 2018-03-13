/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uixtoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:23:35 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/21 17:23:36 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void		create_res(uintmax_t value, unsigned int base, char *res,
	int len)
{
	while (len >= 0)
	{
		if (value % base > 9)
			res[len] = (value % base) + 87;
		else
			res[len] = (value % base) + 48;
		len--;
		value /= base;
	}
}

static int		base_count(uintmax_t value, unsigned int base, int len)
{
	while (value > base - 1)
	{
		len++;
		value /= base;
	}
	return (len + 1);
}

char			*ft_ulxtoa_base(uintmax_t value, int base)
{
	char			*res;
	int				len;

	if (!(base > 1 && base < 17))
		return (0);
	len = 0;
	len = base_count(value, base, len);
	// if (!(res = (char*)ft_memalloc(sizeof(char) * (len + 1))))
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	res[0] = 0;
	res[len] = 0;
	create_res(value, base, res, (len - 1));
	return (res);
}
