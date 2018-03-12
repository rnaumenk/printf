#include "ft_printf.h"

static void		funct_for_u3(t_p *p)
{
	check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ?
		ft_strlen(p->temp_s) : ft_abs(p->precision));
	while (p->precision >= 0 && (p->precision -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 48;
		p->precision--;
	}
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

static void		funct_for_u2(t_p *p)
{
	check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ?
		ft_strlen(p->temp_s) : p->width);
	while (!p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) -
			(int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	while ((p->precision - (int)ft_strlen(p->temp_s) - p->j++) > 0)
		p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
	while (p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) -
			(int)ft_strlen(p->temp_s)) : 0) - (int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
}

void			funct_for_u(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->width >= ft_abs(p->precision))
		funct_for_u2(p);
	else
		funct_for_u3(p);
	ft_strdel(&p->temp_s);
}