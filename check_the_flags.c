/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:25:23 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/04 19:25:24 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_the_flags2(t_p *p)
{
	if (p->fmt[p->i] == '%')
		funct_for_percent(p);
	else if (p->fmt[p->i] == 'c' && !p->l_on)
		funct_for_c(p);
	else if (p->fmt[p->i] == 's' && p->l_on != 1)
		funct_for_s(p);
	else if (p->fmt[p->i] == 'D')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_litoa_base(p->temp_st, 10);
		}
		else if (p->j_on)
		{
			p->temp_im = va_arg(p->ap, intmax_t);
			p->temp_s = ft_litoa_base(p->temp_im, 10);
		}
		else if (p->l_on > 1)
		{
			p->temp_ld = va_arg(p->ap, long long);
			p->temp_s = ft_litoa_base(p->temp_ld, 10);
		}
		else
		{
			p->temp_ld = va_arg(p->ap, long);
			p->temp_s = ft_litoa_base(p->temp_ld, 10);
		}
		funct_for_d(p);
	}
	else if (p->fmt[p->i] == 'd' || p->fmt[p->i] == 'i')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_litoa_base(p->temp_st, 10);
		}
		else if (p->j_on)
		{
			p->temp_im = va_arg(p->ap, intmax_t);
			p->temp_s = ft_litoa_base(p->temp_im, 10);
		}
		else if (p->l_on == 1)
		{
			p->temp_ld = va_arg(p->ap, long);
			p->temp_s = ft_litoa_base(p->temp_ld, 10);
		}
		else if (p->l_on > 1)
		{
			p->temp_ld = va_arg(p->ap, long long);
			p->temp_s = ft_litoa_base(p->temp_ld, 10);
		}
		else if (p->h_on == 1)
		{
			p->temp_d = (short)va_arg(p->ap, int);
			p->temp_s = ft_itoa_base(p->temp_d, 10);
		}
		else if (p->h_on > 1)
		{
			p->temp_d = (signed char)va_arg(p->ap, int);
			p->temp_s = ft_itoa_base(p->temp_d, 10);
		}
		else
		{
			p->temp_d = va_arg(p->ap, int);
			p->temp_s = ft_itoa_base(p->temp_d, 10);
		}
		funct_for_d(p);
	}
	else if (p->fmt[p->i] == 'U')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_ulxtoa_base(p->temp_st, 10);
		}
		else if (p->j_on)
		{
			p->temp_um = va_arg(p->ap, uintmax_t);
			p->temp_s = ft_ulxtoa_base(p->temp_um, 10);
		}
		else if (p->l_on > 1)
		{
			p->temp_ull = va_arg(p->ap, unsigned long long);
			p->temp_s = ft_ulxtoa_base(p->temp_ull, 10);
		}
		else
		{
			p->temp_ul = va_arg(p->ap, unsigned long);
			p->temp_s = ft_ulxtoa_base(p->temp_ul, 10);
		}
		funct_for_u(p);
	}
	else if (p->fmt[p->i] == 'u')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_ulxtoa_base(p->temp_st, 10);
		}
		else if (p->j_on)
		{
			p->temp_um = va_arg(p->ap, uintmax_t);
			p->temp_s = ft_ulxtoa_base(p->temp_um, 10);
		}
		else if (p->l_on == 1)
		{
			p->temp_ul = va_arg(p->ap, unsigned long);
			p->temp_s = ft_ulxtoa_base(p->temp_ul, 10);
		}
		else if (p->l_on > 1)
		{
			p->temp_ull = va_arg(p->ap, unsigned long long);
			p->temp_s = ft_ulxtoa_base(p->temp_ull, 10);
		}
		else if (p->h_on == 1)
		{
			p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 10);
		}
		else if (p->h_on > 1)
		{
			p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 10);	
		}
		else
		{
			p->temp_ui = va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 10);
		}
		funct_for_u(p);
	}
	else if (p->fmt[p->i] == 'p')
		funct_for_p(p);
	else if (p->fmt[p->i] == 'S' || (p->fmt[p->i] == 's' && p->l_on))
		funct_for_ws(p);
	else if (p->fmt[p->i] == 'C' || (p->fmt[p->i] == 'c' && p->l_on))
	{
		p->temp_wc = va_arg(p->ap, wint_t);
		if (p->prec_found && p->precision < 0)
			p->width = 0;
		p->awd = check_the_width(p);
		(p->width - p->awd) < 0 ? (p->width = 0) : (p->width -= p->awd);
		while (p->width && !p->minus_on)
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		funct_for_wc(p);
		while (p->width && p->minus_on)
		{
			check_the_buf(p, 1);
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
	}
	else if (p->fmt[p->i] == 'O')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_ulxtoa_base(p->temp_st, 8);
		}
		else if (p->j_on)
		{
			p->temp_um = va_arg(p->ap, uintmax_t);
			p->temp_s = ft_ulxtoa_base(p->temp_um, 8);
		}
		else if (p->l_on > 1)
		{
			p->temp_ull = va_arg(p->ap, unsigned long long);
			p->temp_s = ft_ulxtoa_base(p->temp_ull, 8);
		}
		else
		{
			p->temp_ul = va_arg(p->ap, unsigned long);
			p->temp_s = ft_ulxtoa_base(p->temp_ul, 8);
		}
		funct_for_o(p);
	}
	else if (p->fmt[p->i] == 'o')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_ulxtoa_base(p->temp_st, 8);
		}
		else if (p->j_on)
		{
			p->temp_um = va_arg(p->ap, uintmax_t);
			p->temp_s = ft_ulxtoa_base(p->temp_um, 8);
		}
		else if (p->l_on == 1)
		{
			p->temp_ul = va_arg(p->ap, unsigned long);
			p->temp_s = ft_ulxtoa_base(p->temp_ul, 8);
		}
		else if (p->l_on > 1)
		{
			p->temp_ull = va_arg(p->ap, unsigned long long);
			p->temp_s = ft_ulxtoa_base(p->temp_ull, 8);
		}
		else if (p->h_on == 1)
		{
			p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 8);
		}
		else if (p->h_on > 1)
		{
			p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 8);
		}
		else
		{
			p->temp_ui = va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 8);
		}
		funct_for_o(p);
	}
	else if (p->fmt[p->i] == 'X')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_uixtoa_base(p->temp_st, 16);
		}
		else if (p->j_on)
		{
			p->temp_um = va_arg(p->ap, uintmax_t);
			p->temp_s = ft_uixtoa_base(p->temp_um, 16);
		}
		else if (p->l_on == 1)
		{
			p->temp_ul = va_arg(p->ap, unsigned long);
			p->temp_s = ft_uixtoa_base(p->temp_ul, 16);
		}
		else if (p->l_on > 1)
		{
			p->temp_ull = va_arg(p->ap, unsigned long long);
			p->temp_s = ft_uixtoa_base(p->temp_ull, 16);
		}
		else if (p->h_on == 1)
		{
			p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
			p->temp_s = ft_uixtoa_base(p->temp_ui, 16);
		}
		else if (p->h_on > 1)
		{
			p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
			p->temp_s = ft_uixtoa_base(p->temp_ui, 16);
		}
		else
		{
			p->temp_ui = va_arg(p->ap, unsigned int);
			p->temp_s = ft_uixtoa_base(p->temp_ui, 16);
		}
		funct_for_big_x(p);
	}
	else if (p->fmt[p->i] == 'x')
	{
		if (p->z_on)
		{
			p->temp_st = va_arg(p->ap, size_t);
			p->temp_s = ft_ulxtoa_base(p->temp_st, 16);
		}
		else if (p->j_on)
		{
			p->temp_um = va_arg(p->ap, uintmax_t);
			p->temp_s = ft_ulxtoa_base(p->temp_um, 16);
		}
		else if (p->l_on == 1)
		{
			p->temp_ul = va_arg(p->ap, unsigned long);
			p->temp_s = ft_ulxtoa_base(p->temp_ul, 16);
		}
		else if (p->l_on > 1)
		{
			p->temp_ull = va_arg(p->ap, unsigned long long);
			p->temp_s = ft_ulxtoa_base(p->temp_ull, 16);
		}
		else if (p->h_on == 1)
		{
			p->temp_ui = (unsigned short)va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 16);
		}
		else if (p->h_on > 1)
		{
			p->temp_ui = (unsigned char)va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 16);
		}
		else
		{
			p->temp_ui = va_arg(p->ap, unsigned int);
			p->temp_s = ft_ulxtoa_base(p->temp_ui, 16);
		}
		funct_for_x(p);
	}
	else
		p->i--;
}

void		more_spec(t_p *p)
{
	char	*temp;

	temp = p->spec;
	if (!(p->spec = (char*)ft_memalloc(sizeof(char) * ((p->spec_size += 256) + 1))))
		p->error = 1;
	ft_memcpy(p->spec, temp, p->j);
	ft_strdel(&temp);
}

void		check_the_flags(t_p *p)
{
	while (p->fmt[++p->i] && !(A(p->fmt[p->i])))
	{
		if (!(p->fmt[p->i] >= 48 && p->fmt[p->i] <= 57) && !(B(p->fmt[p->i])))
		{
			p->found = 0;
			break ;
		}
		if ((size_t)p->j == p->spec_size)
			more_spec(p);
		p->spec[p->j++] = p->fmt[p->i];
	}
	p->j = -1;
	while (p->spec[++p->j])
		look_for_specificators(p);
	p->j = 0;
	if (p->found)
		check_the_flags2(p);
	else
	{
		while (p->fmt[p->i] != '%' && p->fmt[p->i])
		{
			p->i++;
			p->j++;
		}
		if (!(p->without_spec = (char*)ft_memalloc(sizeof(char) * (p->j + 1))))
			p->error = 1;
		p->i -= p->j;
		ft_memcpy(p->without_spec, p->fmt + p->i, (size_t)p->j);
		check_the_buf(p, ft_strlen(p->without_spec) > (size_t)p->width ? ft_strlen(p->without_spec) : p->width);
		while ((p->width - 1) > 0 && !p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		p->buf[p->ret++] = p->without_spec[0];
		while ((p->width - 1) > 0 && p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		ft_memcpy(p->buf + p->ret, p->without_spec + 1, (p->ret += ft_strlen(p->without_spec) - 1));
		ft_strdel(&p->without_spec);
		p->i += p->j - 1;
	}
}
