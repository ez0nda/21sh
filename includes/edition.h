/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:19:08 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 11:18:50 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITION_H
# define EDITION_H

# include "core.h"

struct termios		term;
struct termios		og_term;
struct winsize		wind;

typedef struct	s_var
{
	char	**environ;
	char	*home;
	int		pos;
	int		char_count;
	char	*lex_str;
	char	**history;
	int		new_history;
	int		nb_cols;
	int		nb_rows;
	int		in_selection;
	char	*selection;
	int		*tab;
	int		left;
	int		right;
	int		std_prompt;
	char	*stock;
	int		quotes;
	int		dquotes;
	int		mod_quotes;
	char	**argv;
	char	**cmds;
	int		cmd_index;
	int		p_prompt;
	int		h_prompt;
	int		n_prompt;
	int		c_prompt;
	int		q_prompt;
	int		dq_prompt;
	char	*herend;
	char	*here_stock;
	int		cat_here;
	char	*files;
	int		test;
	int		redir_count;
	char	*qstr;
	int		qlen;
	int		hist_pos;
}				t_var;

void			get_input(t_var *data);
int				check_overflow(t_var *data);
void			get_key(t_var *data, char *buffer);
void			join_cmds(t_var *data, int index);
int				parse_error_pipe(t_var *data);

void			move_left(t_var *data);
void			move_right(t_var *data);
void			move_up(t_var *data);
void			move_down(t_var *data);

void			add_to_string(char c, t_var *data);
void			realloc_str(char c, t_var *data);
void			remove_prev_char(t_var *data);
void			remove_cur_char(t_var *data);

void			add_to_history(t_var *data);
void			show_history(t_var *data, int mod);
void			update_history(t_var *data);
void			manage_history(t_var *data);
int				is_empty(t_var *data);

void			prompt(t_var *data);
void			get_winsize(t_var *data);
void			get_curs_pos(t_var *data, int index);

void			jump(t_var *data, int mod);
void			get_prev_word(t_var *data);
void			get_next_word(t_var *data);
void			move_first_last(t_var *data, int mod);

void			select_mode(t_var *data);
void			copy_cut_mode(t_var *data, int mod);
void			paste_mode(t_var *data);
void			abort_selection(t_var *data);

void			odd_quotes(t_var *data);

void			check_single_pipes(t_var *data);
void			get_last_pipe(t_var *data, int index);

void			add_to_here_stock(char c, t_var *data);
void			check_first_last_char(t_var *data, int mod);
char			*rm_char(char *str, char c);
void			rm_herend(t_var *data);

void			init_subshells(t_var *data, char *buffer);
void			display_subshells(t_var *data, char *buffer);
void			new_prompt(t_var *data);
void			newline_loop(t_var *data);
void			cursh_prompt(t_var *data);
void			cursh_loop(t_var *data);
void			pipe_prompt(t_var *data, int index);
void			heredoc_prompt(t_var *data);
void			heredoc_loop(t_var *data);

void			add_this(char *car, t_var *data);

#endif
