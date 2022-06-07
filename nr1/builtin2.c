#include "minishell.h"


void	ft_unset2(int j, t_var *vars)
{
	while(vars->env_var[j])
	{
		vars->env_var[j] = vars->env_var[j + 1];
		j++;
	}
	free(vars->env_var[j]);
	err_code = 0;
}

//the unset on my home computer did not display any error message if  unset not given argument or wrong arguments,
//just simply returned to new line prompt, so that is what i have done here
//can check if same in labs

//unset in bash removes export variable from env
//in my home computer unset can take many arguments, even ones not in env(ignore them) and works on correct ones
//unset also ignores spaces between arguments....
//I accounted for unnecessary spaces in ft_echo, but now i think you should cut that code and use it when parsing char **cmd, it would be easier.
void	ft_unset(char **cmd, t_var *vars)
{
	int i;
	int j;
	char *temp;

	i = 1;
	while(cmd[i])
	{
		j = 0;
		temp = ft_strjoin(cmd[i], "=");
		while(vars->env_var[j])
		{
			if(ft_strncmp(vars->env_var[j], temp, ft_strlen(temp)) == 0)
			{
				ft_unset2(j, vars);
				break;
			}
			j++;
		}
		free(temp);
		i++;
	}
}

//export puts variable in env
//it needs to be name=value   value is char*
//no space allowed between 'name' and '=', or '=' and 'value'
//when using $name, there is substituition to value (I think your part)
//it can take multiple arguments, if even one argument is valid, any order, it does not give error on wrong arguemnts, and it completes till end of argument list
// if 'name' already exists, then it replaces it
// it only gives error for arguments if first character of words is not alpha, or if there is no "name" before '=' .

//also it can be used with no arguments, in which case it returns env sorted, with "declare -x " infront of each line.

void	ft_export(char **cmd, t_var *vars)
{
	int i;
	int j;
	char *err; //if anyone argument has error, will not work.

	if (!cmd[1])
		return(ft_export2(vars));
	err = ft_is_export(cmd, vars)
	if (err != NULL)
	{
		err_code = 1;
		return (printf("export: \'%s\': not a valid identifier", err));
	}

	i = 1;
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j] != '=')
			j++;
		if(cmd[i][j] == '=')
			ft_export3(cmd[i], j, k, vars);
		i++;
	}
}

char *ft_is_export(char **cmd, t_var *vars)
{
	int i;
	int j;

	if (!cmd[1])
		return(ft_export2(vars));
	i = 1;
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			while(cmd[i][j] != '=')
				j++;
			if(cmd[i][j] == '=')
				if (!ft_isalpha(cmd[i][0]))//no symbols or spaces only alphanumeric && first character of name should be alpha (no numbers)
					return(cmd[i]);
				else
				{
					j--;
					while (cmd[i][j])
						{
							if (!ft_isalnum(cmd[i][j]))
							return(cmd[i]);
							j--;
						}
				}
		}
		i++;
	}
	return (NULL);
}


void	ft_export3(char *cmd, int j, t_var *vars)
{
	char	*name;
	char 	*value;
	char	*new;
	int		i;

	i = 0;
	while(i < j)
	{
		name[i] = cmd[i];
		i++;
	}
	name[i] = '=';
	name[i + 1] = '\0';
	i = 0;
	j++;
	while(cmd[j] != ' ' || cmd[j] != ' \t')
	{
		value[i] = cmd[j];
		i++;
		j++;
	}
	value[i] = '\0';
	new = ft_strjoin(name, value);
	ft_export4(name, new, vars);
	//free(new);  maybe because in ft_export4 this address is being added to vars->env_var so can free on program exit instead
}

//i noticed that variables are added maybe randomly to env, i just appended to the  end.
void	ft_export4(char *name, char *new, t_var *vars)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	while(vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], name, ft_strlen(name)) == 0)
			break;
		i++;
	}
	if(vars->env_var[i])  //if found, and not NULL (at end) then replace (if same name used then just replace string)
		{
			free(vars->env_var[i]);
			vars->env_var[i] = new;
		}

	else	//below is a little simmiliar ft_oldpwd so maybe can optimize later
	{
		temp = (char **)malloc(sizeof(char *) * (i + 1));
		j = 0;
		while (j < i)
		{
			temp[j] = ft_strdup(vars->env_var[j]);
			j++;
		}
		temp[j] = new;
		temp[j + 1] = NULL;
		ft_free_env(vars);
		vars->env_var = temp;
	}
}


//when export used with no arguments
//need to sort char** env into temp using website
//	https://pencilprogrammer.com/c-programs/sort-names-in-alphabetical-order/
void	ft_export2(t_var *vars)
{
	int		i;
	int 	j;
	int		len;
	char 	**array;
	char 	*temp;

	len = 0;
	while(vars->env_var[len])
		len++;
	array = (char **) malloc(sizeof(char *) * len + 1);
	i = 0;
	while (vars->env_var[i])
	{
		array[i] = (Char *)malloc(sizeof(char) * (len + 1));
		array[i] = vars->env_var[i];
		i++;
	}
	array[i] = NULL;
	i = 0;
	while(i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			//arbritrarilty chose length of array[j]
			if(ft_strncmp(array[j], array[j + 1], ft_strlen(array[j])) > 0)
			{
				temp = ft_strdup(array[j]);
				free(array[j]);
				array[j] = ft_strdup(array[j + 1]);
				free(array[j + 1]);
				array[j + 1] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (array[i] != NULL)
	{
		//printf("declare -x %s\n", array[i]);
		printf("%s\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
}


//will need to update main since exit can have arguments
void	ft_exit(char **cmd, t_var *vars)
{
	int	i;
	int	flag;

	flag = 0;
	if(!cmd[1]) //if no arguments
	{
		err_code = 0;
		flag = 1;
	}
	else if (cmd[2] != NULL)
	{
		err_code = 1;
		flag = 1;
		printf("exit: too many arguments\n");
	}
	else if (cmd[1] && cmd[1][0])
	{
		if (cmd[1][0] == '-') 	//can be negative number too
			i = 1;
		else
			i = 0;
		while(cmd[1][i])
		{
			if(!ft_isdigit(cmd[1][i]))
			{
				err_code = 2; //reason?
				printf("exit: %s: numeric argument required\n", cmd[i]);
				flag = 1;
				break;
			}
			i++;
		}
	}
	if (flag == 0 && cmd[1][0] == '-')
		err_code = err_code + ft_atoi(cmd[1]);
	if (flag == 0 && cmd[1][0] != '-')
		err_code = ft_atoi(cmd[1]);
	ft_free_env(vars); //(I assume this does  not exit program
	exit(err_code);
}
