//this is temp file, can delete

//will need to update main since exit can have arguments
void	ft_exit(char **cmd, t_var *vars)
{
	int	i;
	int	flag;

	flag = 0;
	if (!cmd[1])
	{
		g_err = 0;
		flag = 1;
	}
	else if (cmd[2] != NULL)
	{
		g_err = 1;
		flag = 1;
		printf("exit: too many arguments\n");
	}
	else if (cmd[1] && cmd[1][0])
	{
		if (cmd[1][0] == '-')
			i = 1;
		else
			i = 0;
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				g_err = 2;
				printf("exit: %s: numeric argument required\n", cmd[i]);
				flag = 1;
				break ;
			}
			i++;
		}
	}
	if (flag == 0 && cmd[1][0] == '-')
		g_err = g_err + ft_atoi(cmd[1]);
	if (flag == 0 && cmd[1][0] != '-')
		g_err = ft_atoi(cmd[1]);
	ft_free_env(vars);
	exit(g_err);
}

int	ft_is_export(char **cmd)
{
	int		i;
	int		j;
	char	*ret;

	i = 1;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (ft_export7(cmd[i]) == 0)
			j++;
		if (cmd[i] != NULL)
		{
			if (cmd[i][0] == '=')
			{
				if (cmd[i][1] != '\0')
				{
					ret = ft_export6(cmd[i]);
					printf("%s not found\n", ret);
					free(ret);
					return (1);
				}
				else if (cmd[i][1] == '\0')
				{
					printf("bad assignment\n");
					return (1);
				}
			}
		}
		i++;
	}
	if ((ft_array_len(cmd) - 1) == j)
		return (1);
	return (0);
}
