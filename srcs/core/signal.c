/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:24:39 by ezonda            #+#    #+#             */
/*   Updated: 2019/11/20 00:56:55 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

static void		signal_quit(int sig)
{
	t_var *data;
	int i;

	data = update_data(1, data);
	i = ft_strlen(data->lex_str);
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		ft_bzero(data->lex_str, i);
		while (i >= 0)
			data->tab[i--] = 0;
		data->pos = 0;
		data->quotes = 0;
		data->dquotes = 0;
		data->mod_quotes = 0;
		data->p_prompt = 0;
		data->h_prompt = 0;
//		get_input(data);//////////
		prompt(data);
		return ;
	}
	else if (sig == SIGQUIT)
		ft_printf("\nSIGQUIT\n");
	else if (sig == SIGTERM)
	{
		ft_putchar('\n');
		exit_shell(data);
	}
}

static void		signal_inter(int sig)
{
	t_var *data;

	(void)sig;
	data = update_data(1, data);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDOUT_FILENO, TIOCSTI, "\x1A");
}

static void		signal_restart(int sig)
{
	t_var *data;

	(void)sig;
	data = update_data(1, data);
	set_termcanon(data);
	signal(SIGTSTP, signal_inter);
	get_input(data);
}

static void		signal_resize(int sig)
{
	t_var *data;

	(void)sig;
	data = update_data(1, data);
	get_winsize(data);
	prompt(data);
}

void			signal_handler(void)
{
	unsigned int sig;

	sig = 0;
	while (++sig < 32)
	{
		if (sig == SIGINT || sig == SIGQUIT || sig == SIGTERM)
			signal(sig, signal_quit);
		if (sig == SIGTSTP)
			signal(sig, signal_inter);
		if (sig == SIGCONT)
			signal(sig, signal_restart);
		if (sig == SIGWINCH)
			signal(sig, signal_resize);
	}
}
