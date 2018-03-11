/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:17:35 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/10 13:17:38 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		create_res(unsigned int value, unsigned int base, char *res,
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

static int		base_count(unsigned int value, unsigned int base, int len)
{
	while (value > base - 1)
	{
		len++;
		value /= base;
	}
	return (len + 1);
}

char			*ft_uitoa_base(unsigned int nb, int base)
{
	char			*res;
	int				len;

	if (!(base > 1 && base < 17))
		return (0);
	len = 0;
	len = base_count(nb, base, len);
	if (!(res = ft_strnew((size_t)len)))
		return (0);
	create_res(nb, base, res, (len - 1));
	return (res);
}
