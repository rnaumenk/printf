/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs_for_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 18:06:17 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/06 18:06:18 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	funct_for_percent(t_p *p)
{
	check_the_buf(p, (1 > p->width ? 1 : p->width));
	while ((p->width - 1) > 0 && !p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	p->buf[p->ret++] = '%';
	while ((p->width - 1) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
}

void	funct_for_c(t_p *p)
{
	p->temp_c = va_arg(p->ap, int);
	check_the_buf(p, (1 > p->width ? 1 : p->width));
	while ((p->width - 1) > 0 && !p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	p->buf[p->ret++] = p->temp_c;
	while ((p->width - 1) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
}

void	cut(t_p *p)
{
	char	*temp;
	int		i;

	if (!(temp = (char*)ft_memalloc(sizeof(char) * (p->precision + 1))))
		p->error = 1;
	i = -1;
	while (++i < p->precision)
		temp[i] = p->temp_s[i];
	p->temp_s = temp;
	p->cut = 1;
}

void	funct_for_s(t_p *p)
{
	p->temp_s = va_arg(p->ap, char*);
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (!p->temp_s)
	{
		p->temp_s = ft_strdup("(null)");
		if (p->precision >= 0 && ft_strlen(p->temp_s) > (size_t)p->precision)
			p->temp_s[p->precision] = 0;
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && !p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		// free(p->temp_s);
	}
	else
	{
		if (p->sharp_undef || p->minus_undef)
			p->temp_s = "";
		if (p->precision >= 0 && ft_strlen(p->temp_s) > (size_t)p->precision)
			cut(p);
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && !p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		while (p->precision < 0 && p->prec_found)
		{
			p->buf[p->ret++] = 32;
			p->precision++;
		}
		// if (p->cut)
			// free(p->temp_s);
	}
}

void	minus_del(t_p *p)
{
	int		i;

	i = 0;
	while (p->temp_s[++i])
		p->temp_s[i - 1] = p->temp_s[i];
	p->temp_s[--i] = 0;
	p->width--;
	p->minus_del = 1;
}

void	funct_for_d(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == '-' && ((p->width && p->zero_on) || p->prec_found))
	{
		if ((p->width && p->zero_on) || ((p->precision >= p->width) || (p->precision < 0)))
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = '-';
		}
		p->plus_on = 0;
		minus_del(p);
	}
	if (p->plus_on && p->temp_s[0] != '-' && p->zero_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '+';
	}
	if (p->spaces && p->temp_s[0] != '-')
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = 32;
	}
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->width >= ft_abs(p->precision))
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while (!p->minus_on && (p->width - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - p->spaces - (p->temp_s[0] == '-' ? 0 : p->plus_on) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		if (p->plus_on && p->temp_s[0] != '-' && !p->zero_on)
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = '+';
		}
		if (p->minus_del && p->precision <= p->width && p->precision > 0)
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = '-';
		}
		while ((p->precision - (int)ft_strlen(p->temp_s) - p->j++) > 0)
			p->buf[p->ret++] = 48;
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->minus_on && (p->width - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - p->spaces - (p->temp_s[0] == '-' ? 0 : p->plus_on) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->width--;
		}
	}
	else
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ? ft_strlen(p->temp_s) : ft_abs(p->precision));
		while (p->precision >= 0 && (p->precision - p->spaces - (p->minus_del ? 0 : p->plus_on) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 48;
			p->precision--;
		}
		if (p->plus_on && p->temp_s[0] != '-' && !p->zero_on)
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = '+';
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) - p->spaces - (p->minus_del ? 1 : p->plus_on) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->precision++;
		}
	}
	// free(p->temp_s);
}

void	funct_for_p(t_p *p)
{
	p->temp_ul = va_arg(p->ap, unsigned long);
	p->temp_s = ft_ulxtoa_base(p->temp_ul, 16);
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	check_the_buf(p, (ft_strlen(p->temp_s) + 2 > (size_t)p->width ? (ft_strlen(p->temp_s) + 2) : p->width));
	while ((p->width - (p->precision > (int)ft_strlen(p->temp_s) ? (p->precision - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s) - 2) > 0 && !p->minus_on && !p->zero_on)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
	p->buf[p->ret++] = '0';
	p->buf[p->ret++] = 'x';
	while ((p->width - (p->precision > (int)ft_strlen(p->temp_s) ? (p->precision - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s) - 2) > 0 && !p->minus_on && p->zero_on)
	{
		p->buf[p->ret++] = 48;
		p->width--;
	}
	while ((p->precision - (int)ft_strlen(p->temp_s) - p->j++) > 0)
			p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
	while ((p->width - (p->precision > (int)ft_strlen(p->temp_s) ? (p->precision - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s) - 2) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) - (int)ft_strlen(p->temp_s) - 2) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
	// free(p->temp_s);
}

int		check_the_width(t_p *p)
{
	if (p->temp_wc < 0 || p->temp_wc > 1114111 || (p->temp_wc > 55295 &&
		p->temp_wc < 57344))
		p->error = 1;
	else if (MB_CUR_MAX == 1 && p->temp_wc > 255)
		p->error = 1;
	else if (MB_CUR_MAX == 1 && p->temp_wc < 256)
		return (1);
	else if (MB_CUR_MAX == 4)
	{
		p->sl_on = 1;
		if (p->temp_wc <= 127)
			return (1);
		else if (p->temp_wc <= 2047)
			return (2);
		else if (p->temp_wc <= 65535)
			return (3);
		else if (p->temp_wc <= 1114111)
			return (4);
	}
	return (0);
}

void	funct_for_wc(t_p *p)
{
	p->wd = check_the_width(p);
	if (p->wd <= p->awd)
		check_the_buf(p, p->wd);
	if (p->wd == 1 && p->awd >= 1)
		p->buf[p->ret++] = p->temp_wc;
	else if (p->wd == 2 && p->awd >= 2)
	{
		p->buf[p->ret++] = (p->temp_wc >> 6) | 192;
		p->buf[p->ret++] = (p->temp_wc | 128) & 191;
	}
	else if (p->wd == 3 && p->awd >= 3)
	{
		p->buf[p->ret++] = (p->temp_wc >> 12) | 224;
		p->buf[p->ret++] = ((p->temp_wc >> 6) | 128) & 191;
		p->buf[p->ret++] = (p->temp_wc | 128) & 191;
	}
	else if (p->wd == 4 && p->awd >= 4)
	{
		p->buf[p->ret++] = (p->temp_wc >> 18) | 240;
		p->buf[p->ret++] = ((p->temp_wc >> 12) | 128) & 191;
		p->buf[p->ret++] = ((p->temp_wc >> 6) | 128) & 191;
		p->buf[p->ret++] = (p->temp_wc | 128) & 191;
	}
	if (p->wd >= 1 && p->awd >= p->wd)
		p->awd -= p->wd;
	else
		p->stop = 1;
}

void	funct_for_ws(t_p *p)
{
	p->temp_ws = va_arg(p->ap, wchar_t*);
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (!p->temp_ws)
	{
		p->temp_s = ft_strdup("(null)");
		if (p->precision >= 0 && ft_strlen(p->temp_s) > (size_t)p->precision)
			p->temp_s[p->precision] = 0;
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && !p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		// free(p->temp_s);
		return ;
	}
	if (p->sharp_undef || p->minus_undef)
		p->temp_ws = (wchar_t*)"\0";
	p->j = -1;
	while (p->temp_ws[++p->j])
	{
		p->temp_wc = p->temp_ws[p->j];
		p->wd = check_the_width(p);
		if (p->precision < 0 || (p->precision - p->wd >= 0))
		{
			p->awd += p->wd;
			p->precision -= p->wd;
		}
	}
	(p->width - p->awd) < 0 ? (p->width = 0) : (p->width -= p->awd);
	while (p->width && !p->minus_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	while (*p->temp_ws)
	{
		if (p->stop)
			break ;
		p->temp_wc = (unsigned int)(*p->temp_ws++);
		funct_for_wc(p);
	}
	while (p->width && p->minus_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	while (p->precision < 0 && p->prec_found)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

void	funct_for_u(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->width >= ft_abs(p->precision))
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while (!p->minus_on && (p->width - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		while ((p->precision - (int)ft_strlen(p->temp_s) - p->j++) > 0)
			p->buf[p->ret++] = 48;
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->minus_on && (p->width - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->width--;
		}
	}
	else
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ? ft_strlen(p->temp_s) : ft_abs(p->precision));
		while (p->precision >= 0 && (p->precision - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 48;
			p->precision--;
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->precision++;
		}
	}
	// free(p->temp_s);
}

void	funct_for_o(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->width >= ft_abs(p->precision))
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while (!p->minus_on && (p->width - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? 0 : p->sharp_on) - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		if (p->sharp_on && p->temp_s[0] != 48)
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = '0';
		}
		while ((p->precision - (int)ft_strlen(p->temp_s) - p->sharp_on - p->j++) > 0)
			p->buf[p->ret++] = 48;
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->minus_on && (p->width - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? 0 : p->sharp_on) - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->width--;
		}
	}
	else
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ? ft_strlen(p->temp_s) : ft_abs(p->precision));
		while (p->precision >= 0 && (p->precision - p->sharp_on - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 48;
			p->precision--;
		}
		if (p->sharp_on && p->temp_s[0] != 48)
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = '0';
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) - p->sharp_on - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->precision++;
		}
	}
	// free(p->temp_s);
}

void	funct_for_x(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->width >= ft_abs(p->precision))
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while (!p->minus_on && !p->zero_on && (p->width - 2 * p->sharp_on - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->width--;
		}
		if (p->sharp_on && p->temp_s[0] != 48 && p->temp_s[0] != 0)
		{
			check_the_buf(p, 2);
			p->buf[p->ret++] = '0';
			p->buf[p->ret++] = 'x';
		}
		while (!p->minus_on && p->zero_on && (p->width - 2 * p->sharp_on - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 48;
			p->width--;
		}
		while ((p->precision - (int)ft_strlen(p->temp_s) - p->j++) > 0)
			p->buf[p->ret++] = 48;
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->minus_on && (p->width - 2 * p->sharp_on - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->width--;
		}
	}
	else
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ? ft_strlen(p->temp_s) : ft_abs(p->precision));
		if (p->sharp_on && p->temp_s[0] != 48 && p->temp_s[0] != 0)
		{
			check_the_buf(p, 2);
			p->buf[p->ret++] = '0';
			p->buf[p->ret++] = 'x';
		}
		while (p->precision >= 0 && (p->precision - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 48;
			p->precision--;
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) - 2 * p->sharp_on - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->precision++;
		}
	}
	// free(p->temp_s);
}

void	funct_for_big_x(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->width >= ft_abs(p->precision))
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ? ft_strlen(p->temp_s) : p->width);
		while (!p->minus_on && !p->zero_on && (p->width - 2 * p->sharp_on - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->width--;
		}
		if (p->sharp_on && p->temp_s[0] != 48 && p->temp_s[0] != 0)
		{
			check_the_buf(p, 2);
			p->buf[p->ret++] = '0';
			p->buf[p->ret++] = 'X';
		}
		while (!p->minus_on && p->zero_on && (p->width - 2 * p->sharp_on - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 48;
			p->width--;
		}
		while ((p->precision - (int)ft_strlen(p->temp_s) - p->j++) > 0)
			p->buf[p->ret++] = 48;
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->minus_on && (p->width - 2 * p->sharp_on - (ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->width--;
		}
	}
	else
	{
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ? ft_strlen(p->temp_s) : ft_abs(p->precision));
		if (p->sharp_on && p->temp_s[0] != 48 && p->temp_s[0] != 0)
		{
			check_the_buf(p, 2);
			p->buf[p->ret++] = '0';
			p->buf[p->ret++] = 'X';
		}
		while (p->precision >= 0 && (p->precision - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 48;
			p->precision--;
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) - 2 * p->sharp_on - (int)ft_strlen(p->temp_s)) > 0)
		{
			p->buf[p->ret++] = 32;
			p->precision++;
		}
	}
	// free(p->temp_s);
}
