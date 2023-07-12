#include "parser.h"

char	*replace_tabs(char *str)
{
	int		i;
	char	*new;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\t' || str[i] == '\v')
			new[i] = ' ';
		else
			new[i] = str[i];
	}
	free(str);
	return (new);
}

double	ft_atod(char *str)
{
	double	result;
	double	sign;
	int		i;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (str[i] && str[i] == '.')
		result += decimal_part(&str[i + 1]);
	return (result * sign);
}

double	decimal_part(char *str)
{
	double	decimal;
	int		i;

	i = 0;
	decimal = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		decimal = decimal * 10 + str[i] - '0';
		i++;
	}
	while (decimal >= 1.0)
		decimal = decimal / 10.0;
	return (decimal);
}

int	matrix_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	free_matrix(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
