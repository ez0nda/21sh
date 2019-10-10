/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:27:27 by jebrocho          #+#    #+#             */
/*   Updated: 2019/10/08 14:27:42 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void form_path(char *str, char c)
{
  int j;
  int i;

  i = -1;
  j = 0;
  if (!str)
    return ;
  while (str[++i])
  {
    if ((str[i] == c && str[i + 1] != c) || str[i] != c)
    {
      str[j] = str[i];
      j++;
    }
  }
  str[j] = '\0';
}

char	*error_cd(char *str, int mod)
{
	if (mod == 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (mod == 1)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (mod == 2)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	free(str);
	return (0);
}

char  *get_env(char **environ, char *selec)
{
  int i;
  char *val;

  i = -1;
  while (environ[++i])
  {
    val = ft_strstr(environ[i], selec);
    if (val != 0)
      return (ft_strdup(val + ft_strlen(selec)));
  }
  return (NULL);
}

char	*add_error(char *s, char *new)
{
	s = ft_strjoin_free(s, "/", 0);
	s = ft_strjoin_free(s, new, 0);
	return (s);
}

void	rm_error(char *s)
{
	int j;

	j = 0;
	while (s[j])
		j++;
	if (j == 1)
		return ;
	while (s[j] != '/')
		j--;
	if (j > 1)
		s[j] = '\0';
	else
		s[++j] = '\0';
}

char  *parse_error(char *s, t_var *data)
{
  char	*save;
  char	**arg;
  int		i;

  i = -1;
  arg = ft_split(s, '/');
  if (s[0] == '/')
    save = ft_strdup("/");
  else
    save = get_env(data->environ, "PWD=");
  while (arg[++i])
  {
    if (ft_strcmp(arg[i], "..") == 0)
      rm_error(save);
    else if (s[i])
      save = add_error(save, arg[i]);
    free(arg[i]);
  }
  form_path(save, '/');
  free(arg);
  return (save);
}
