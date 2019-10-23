/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:19:08 by ezonda            #+#    #+#             */
/*   Updated: 2019/10/15 14:01:10 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITION_H
# define EDITION_H

# include "core.h"

# define KEY_U		(char[4]){ 27, 91, 65, 0}
# define KEY_D		(char[4]){ 27, 91, 66, 0}
# define KEY_L		(char[4]){ 27, 91, 68, 0}
# define KEY_R		(char[4]){ 27, 91, 67, 0}
# define OPT_C		(char[4]){ -61, -89, 0, 0}
# define OPT_V		(char[4]){ -30, -120, -102, 0}
# define OPT_X		(char[4]){ -30, -119, -120, 0}
# define OPT_S		(char[4]){ -61, -97, 0, 0}
# define OPT_L		(char[5]){ 27, 27, 91, 68, 0}
# define OPT_R		(char[5]){ 27, 27, 91, 67, 0}
# define OPT_U		(char[5]){ 27, 27, 91, 65, 0}
# define OPT_D		(char[5]){ 27, 27, 91, 66, 0}
# define RET		(char[4]){ 10, 0, 0, 0}
# define HOME		(char[4]){ 27, 91, 72, 0}
# define END		(char[4]){ 27, 91, 70, 0}
# define UNDO		(char[4]){ 127, 0, 0, 0}
# define DEL		(char[5]){ 27, 91, 51, 126, 0}

# define TERMCAP(x) tputs(tgetstr(x, NULL), 1, ft_putchar_v2)

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
	int  	mod_quotes;
	char	**argv;
	char	**cmds;
	int		cmd_index;
}				t_var;

void			get_input(t_var *data);
int				check_overflow(t_var *data);
void			get_key(t_var *data, char *buffer);

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

#endif
