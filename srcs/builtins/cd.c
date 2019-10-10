/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:40:27 by jebrocho          #+#    #+#             */
/*   Updated: 2019/10/08 13:40:48 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void old_pwd(char *old, t_var *data)
{
  char **cmd;
  if (!(cmd = (char**)malloc(sizeof(char*) * 3)))
    return ;
  cmd[0] = ft_strdup("setenv");
  cmd[1] = ft_strjoin("OLDPWD=", old);
  cmd[2] = 0;
  setenv_builtin(data, cmd);
}

void new_env(t_var *data, char *newp)
{
  char **cmd;
  char *old;

  old = get_env(data->environ, "PWD=");
  if (!(cmd = (char**)malloc(sizeof(char*) * 3)))
    return ;
  cmd[0] = ft_strdup("setenv");
  cmd[1] = ft_strjoin("PWD=", newp);
  cmd[2] = 0;
  setenv_builtin(data, cmd);
  old_pwd(old, data);
}

int   parse_cd(t_var *data, char **cmd)
{
  int ret;

  if (ft_strcmp(cmd[1], "-") == 0)
    ret = 0;
  else if (ft_strcmp(cmd[1], "-P") == 0)
    ret = 1;
  else if (ft_strcmp(cmd[1], "-L") == 0)
    ret = 2;
  else
    ret = -1;
  if (ret != -1)
    form_path(cmd[2], '/');
  else
    form_path(cmd[1], '/');
  return (ret);
}

char	*ft_get_link(char *pathname)
{
	int			nbytes;
	char		buff[255];

	nbytes = readlink(pathname, buff, sizeof(buff));
	buff[nbytes] = '\0';
  return (ft_strdup(buff));
}

char  *new_path(char *cmd, int opt, t_var *data)
{
  DIR   *dir;
  char	*s;
  char *tmp;
  struct stat st;

  s = parse_error(cmd, data);
  if (lstat(s, &st) < 0)
    return (error_cd(s, 0));
  if (opt == 1)
  {
    if (S_ISLNK(st.st_mode))
    {
      tmp = ft_strdup(s);
      rm_error(tmp);
      s = ft_strjoin(tmp, ft_get_link(s));
    }
  }
  if (ft_is_dir(s) == 0)
    return (error_cd(s, 2));
  dir = opendir(s);
  if (dir == NULL)
    return (error_cd(s, 1));
  closedir(dir);
  return (s);
}

int   cd_builtin(t_var *data, char **cmd)
{
  int opt;
  char *newp;

  if (!cmd[1])
    newp = get_env(data->environ, "HOME=");
  else
  {
    opt = parse_cd(data, cmd);
    if (opt == 0)
      newp = get_env(data->environ, "OLDPWD=");
    else if (opt != -1)
      newp = new_path(cmd[2], opt, data);
    else
      newp = new_path(cmd[1], opt, data);
    if (newp == 0)
      return (1);
  }
  new_env(data, newp);
  chdir(newp);
  return (1);
}
