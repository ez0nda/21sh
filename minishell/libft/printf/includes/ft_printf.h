/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 10:57:48 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/02 14:59:33 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct	s_struct
{
	va_list		ap;
	int			index;
	int			modl;
	char		indic;
	int			min_field;
	int			prec;
	int			count_char;
	int			valid;
	int			stock_pre;
	int			stock_pre2;
	int			stock_pad;
	int			stock_pre_f;
	int			flag[11];
	int			nb_carac;
}				t_struct;

typedef struct	s_stock
{
	long		stock_h;
	int			stock_i;
	intmax_t	stock_il;
	double		stock_f;
	char		stock_c;
	char		*stock_s;
	char		*stock_free;
}				t_stock;

int				ft_printf(const char *format, ...);
int				ft_find_indicator(const char *format, t_struct *stru);
void			ft_check_flags(const char *format, t_struct *stru,
				t_stock *stock);
int				ft_check_flags_p2(const char *format, t_struct *stru, int i);
void			ft_check_width(const char *format, t_struct *stru);
void			ft_check_precision(const char *format, t_struct *stru);
int				ft_check_format(const char *format, t_struct *stru);
void			ft_dispatch(t_struct *stru, t_stock *stock);
void			ft_indic_c(t_struct *stru, t_stock *stock);
void			ft_indic_di(t_struct *stru, t_stock *stock);
void			ft_indic_s(t_struct *stru, t_stock *stock);
void			ft_indic_p(t_struct *stru, t_stock *stock);
void			ft_indic_u(t_struct *stru, t_stock *stock);
void			ft_indic_mod(t_struct *stru);
void			ft_initialize_flags(t_struct *stru);
int				ft_nbrsize(long nb);
void			ft_stock(t_stock *stock, t_struct *stru);
void			ft_apply_flags(t_struct *stru, t_stock *stock, int i);
void			ft_apply_flags2(t_struct *stru, t_stock *stock);
void			ft_print_str(t_struct *stru, t_stock *stock);
void			ft_print_str2(t_struct *stru, t_stock *stock);
char			*ft_convert_o(uintmax_t octal_int);
void			ft_indic_o(t_struct *stru, t_stock *stock);
void			ft_indic_x(t_struct *stru, t_stock *stock);
void			ft_indic_f(t_struct *stru, t_stock *stock);
void			ft_putstr_free(char *s, t_struct *stru);
void			ft_print_hexa(t_struct *stru, t_stock *stock);
void			ft_print_hexa2(t_struct *stru, t_stock *stock);
void			ft_print_has_hexa(t_struct *stru, t_stock *stock);
void			ft_flag_u(char *s, t_struct *stru);
long			pf_abs(long nb);
void			ft_print_hs(t_struct *stru, t_stock *stock);
void			ft_indic_p(t_struct *stru, t_stock *stock);
void			ft_print_hexa(t_struct *stru, t_stock *stock);
void			ft_prec_p(t_struct *stru, t_stock *stock);
char			*ft_toupper_mod(char *s);
void			ft_print_numbers(t_struct *stru, t_stock *stock, int i);
void			ft_apply_signe(t_struct *stru, t_stock *stock);

long			pf_atoi(const char *str);
int				pf_isdigit(int c);
char			*pf_itoa(long n);
void			pf_putchar(char c, t_struct *stru);
void			pf_putnbr(long n, t_struct *stru);
void			pf_putnbr_l(uintmax_t n, t_struct *stru);
void			pf_putstr(const char *str, t_struct *stru);
char			*pf_strnew(size_t size);
char			*pf_strrev(char *s);
long			pf_strlen(const char *str);
char			*pf_strdup(const char *s);
int				pf_strcmp(const char *s1, const char *s2);
char			*pf_strsub(const char *s, unsigned int start, size_t len);

#endif
