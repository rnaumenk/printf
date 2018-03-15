#include "../include/ft_printf.h"

static void		funct_for_o4(t_p *p)
{
	check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ?
		ft_strlen(p->temp_s) : ft_abs(p->precision));
	while (p->precision >= 0 && (p->precision - p->sharp_on -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 48;
		p->precision--;
	}
	if (p->sharp_on && ((p->prec_found && !p->dotnull) ||
		(!p->prec_found && p->temp_s[0] != 48)))
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '0';
	}
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret +=
		ft_strlen(p->temp_s)));
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) -
		p->sharp_on - (int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

static void		funct_for_o3(t_p *p)
{
	while (p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)ft_strlen(p->temp_s) ? 0 : (p->temp_s[0] == 48 ? 0 : p->sharp_on)) -
		(ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ?
		(ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
}

static void		funct_for_o2(t_p *p)
{
	check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ?
		ft_strlen(p->temp_s) : p->width);
	while (!p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)ft_strlen(p->temp_s) ? 0 : (p->temp_s[0] == 48 ? 0 : p->sharp_on)) -
		(ft_abs(p->precision) > (int)ft_strlen(p->temp_s) ?
		(ft_abs(p->precision) - (int)ft_strlen(p->temp_s)) : 0) -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	if (p->sharp_on && ((p->prec_found && !p->dotnull) ||
		(!p->prec_found && p->temp_s[0] != 48)))
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '0';
	}
	while ((p->precision - (int)ft_strlen(p->temp_s) -
		p->sharp_on - p->j++) > 0)
		p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret +=
		ft_strlen(p->temp_s)));
	funct_for_o3(p);
}

void			funct_for_o(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->temp_s[0] == 48 && p->precision == 1)
		p->dotnull = 1;
	if (p->width >= ft_abs(p->precision))
		funct_for_o2(p);
	else
		funct_for_o4(p);
	ft_strdel(&p->temp_s);
}