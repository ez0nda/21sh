#include "../../includes/edition.h"

/*
void			odd_quotes(t_var *data)
{
	char buffer[6];
	ft_putstr("\n");
	add_to_string('\n', data);
	ft_putstr("quote>");
	read(0, buffer, sizeof(buffer));
	ft_putchar(buffer[0]);
}
*/
void			remove_quotes(t_var *data)
{
	int i;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == 39 || data->lex_str[i] == 34)
		{
			while (data->lex_str[i])
			{
				data->lex_str[i] = data->lex_str[i + 1];
				i++;
			}
			i = 0;
		}
		i++;
	}
}

void			parse_quotes(t_var *data)
{
	int i;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == 39)
			data->quotes++;
		else if (data->lex_str[i] == 34)
			data->dquotes++;
		i++;
	}
	if (data->quotes % 2 != 0 || data->dquotes % 2 != 0)
	{
		ft_putchar('\n');
		data->std_prompt = 0;
	}
	else
	{
		data->std_prompt = 1;
	}
}

void			stock_str(t_var *data)
{
	int		i;
	int		mod;
	char	*tmp;

	i = 0;
	mod = 1;
	if (!data->stock[0])
	{
		mod = 0;
		data->stock = ft_strdup(data->lex_str);
		while (data->stock[i])
			i++;
		data->stock[i++] = '\n';
		data->stock[i] = '\0';
	}
	while (data->stock[i])
		i++;
	data->stock[i++] = '\n';
	data->stock[i] = '\0';
	data->stock = ft_strjoin(data->stock, data->lex_str);
}


