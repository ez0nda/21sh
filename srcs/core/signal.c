/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:24:39 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 10:32:03 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

static void		signal_quit(int sig)
{
	int		i;
	t_var	*data;

	data = update_data(1, data);
	i = ft_strlen(data->lex_str);
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		ft_bzero(data->lex_str, i);
		while (i >= 0)
			data->tab[i--] = 0;
		data->pos = 0;
		data->p_prompt = 0;
		data->c_prompt = 0;
		data->h_prompt = 0;
		data->n_prompt = 0;
		data->q_prompt = 0;
		data->dq_prompt = 0;
		data->pos = 0;
		prompt(data);
		return ;
	}
	else if (sig == SIGTERM)
		exit_shell(data);
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
