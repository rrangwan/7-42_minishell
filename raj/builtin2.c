#include "builtin.c" //delete later
//continuation of builtin.c


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
void	ft_unset(t_cmd *cmd, t_var *vars)
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
// it only gives error for arguments if first character of words is not alpha, unless it is '=' with no spaces.

//also it can be used with no arguments, in which case it returns env sorted, with "declare -x " infront of each line.

void	ft_export(t_cmd *cmd, t_var *vars)
{
	int i;
	int j;

	if (!cmd.cmd[1])
		return(ft_export2(vars));
	i = 1;
	while(cmd->cmd[i])
	{
		j = 0;
		while(cmd->cmd[i][j])
		{
			while(cmd->cmd[i][j] != '=')
				j++;
			if(cmd->cmd[i][j] == '=')
			{
				if (ft_isalnum(cmd->cmd[i][j - 1]) &&  ft_isalpha(cmd->cmd[i][0]))//no symbols or spaces only alphanumeric && first character of name should be alpha (no numbers)
				{
					ft_export3(cmd->cmd[i], j, k, vars);
					break; //back to i++; line
				}
				else
					{
						printf("export: \'%s\': not a valid identifier", cmd->cmd[i]);
						err_code = 1;
					}
			}
		}
		i++;
	}
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
		vars->env_var[i] = new;
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
void	ft_export2(t_var *vars)
{
	int		i;
	char **temp;
//need to sort char** env into temp using website
//	https://pencilprogrammer.com/c-programs/sort-names-in-alphabetical-order/
//still in progress
	i = 0;
	while (temp[i])
	{
		printf("declare -x %s\n", temp[i]);
		i++;
	}

}

//will need to update main since exit can have arguments
ft_exit(t_cmd *cmd, t_var *vars)
{
	if(!cmd->cmd[1]) //if no arguments
	{
		err_code = 0;
		ft_free_env(vars);
	}
//still in progress,
}