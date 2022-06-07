#include "minishell.h"

//add to minshell.h
//need to init
//this is a struct linked list for indiviual cmds
//cmds are deliminted by redirections, pipes, built-ins,
/*
//global	error code
int err_code;

//below is work-in-progress....may change
typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	int				redirect;
	int				redir_stdin;
	int				redir_stdout;
	//char			*infile;
	//char			*outfile;
	pid_t			pid;
	int				std_in;
	int				std_out;
	struct s_cmd	*next;
}				t_cmd;


//add inside struct t_var
// t_cmd *cmd
*/

void	built_in2(char **cmd, t_var *vars)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(cmd, vars);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(vars);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd, vars);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd, vars);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		ft_exit(cmd, vars);
}

//add to main after checking if buf is "exit"...if returns 0 then pipex it
int	built_in1(char **cmd, t_var *vars)
{
	char *str;

	str = cmd[0];
	if (!cmd || !vars || !cmd[0])
		return (0);
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "pwd", 4) == 0 || ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "export", 7) == 0 || ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

//if "-n " after echo then no new line
void	ft_echo(char **cmd)
{
	int		j;
	int		fd;
	int		flag;

	j = 1;
	flag = 0;
	fd = 1;
	//fd = cmd->std_out; this could be an issue Nousheen
	if (cmd[1][0] =='-' && cmd[1][1] =='n' && cmd[1][2] =='\0')
	{
		flag = 1;
		j++;
	}
	while (cmd[j])
	{
		ft_putstr_fd(cmd[j], fd);
		j++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
}


/*old echo

//if "-n " after echo then no new line
void	ft_echo(t_cmd *cmd)
{
	char	*str;
	int		j;
	int		flag_n;
	int		fd;

	str = cmd[1];
	j = 0;
	flag_n = 0;
	fd = cmd->std_out;
	while (str[j] && (str[j] == ' ' || str[j] == '\t'))
		j++;
	if (str[j + 2] && str[j] == '-' && str[j + 1] == 'n' && (str[j + 2] == ' ' || str(j + 2) == '\t'))
	{
		flag_n = 1;
		j + 2;
	}

	while (str[j])
	{
		while (str[j] == ' ' || str[j] == '\t')
			j++;
		if (str[j] != ' ' && str[j] != '\t')
		{
			ft_putchar_fd(' ', fd);
			while (str[j] != ' ' && str[j] != '\t')
			{
				ft_putchar_fd(str[j], fd);
				j++;
			}
		}
	}

	if (!flag_n)
		ft_putchar_fd('\n', fd);
}
*/

//getenv and chdir are built-in functions we are allowed to use
//char *getenv(const char *str) searches for environment pointed to by str and returns its value.
// so getenv("HOME") returns abosulte path to home of user, starting with '/'  example: "/rererwe/erw"
// getenv("PATH") gets you the path options you need for pipex.
//int chdir(char *str) changes the current working directory of the calling process to the directory specified in str
//it can accept both relative and absolute paths
//On success, zero is returned.  On error, -1 is returned, and errno is set to indicate the error (error number is 1)
void ft_cd(char **cmd, t_var *vars)
{

	char	*dir;
	char	*temp;
	char	old_pwd[300]; //randomly 300
	char	*new_pwd;

	getcwd(old_pwd, sizeof(old_pwd)); //see ft_pwd
	dir = getenv("HOME");
	temp = ft_strjoin(dir, cmd[1]);
	new_pwd = temp;
	free(temp);
// If cmd has no arguments or argument is '~' then we go HOME
	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
	{
		free(temp);
		temp = dir;
	}

		//no NEED to do anything can delete this if statement

//absolute chdir with ~
	else if (cmd[1] != NULL && cmd[1][0] == '~' && cmd[1][1] == '//') //just one '/'
	{
		temp = ft_strjoin(dir, cmd[1] + 1);  //+ 1 to ignore ~  //temp is malloced by strjoin so we need free
		dir = temp;
		free(temp);
	}

// Multiple arguments is invalid
	else if (cmd[2] != NULL)
	{
		err_code = 1;
		printf("cd: string not in pwd: %s", cmd[1]);
		return ;
	}

//else dir is relative or absolute, chdir accepts both
	else
		dir = cmd[1];

	if (chdir(dir) != 0)
	{
		printf("cd: %s: No such file or directory\n", dir);
		err_code = 1;
		return ;
	}
	err_code = 0;
	ft_oldpwd(vars, old_pwd); //updates OLDPWD in path;
	ft_newpwd(vars, new_pwd); //updates NEWPWD in path;
}

void	ft_newpwd(t_var *vars, char *new_pwd) //updates NEWPWD in path;
{
	int i;

	i = 0;
	while(vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], "PWD=", 4) == 0)
			break;
		i++;
	}
	free(vars->env_var[i]);
	vars->env_var[i] = ft_strjoin("PWD=",new_pwd);
}

void	ft_oldpwd(t_var *vars, char *old_pwd) //updates OLDPWD in path;
{
	int i;
	int j;
	char **temp;

	i = 0;
	while(vars->env_var[i])
	{
		if (ft_strncmp(vars->env_var[i], "OLDPWD=", 7) == 0)
			break;
		i++;
	}
	if (vars->env_var[i])
	{
			free(vars->env_var[i]);
			vars->env_var[i] = ft_strjoin("OLDPWD=",old_pwd);
	}
	else //if this is first time then need to add OLDPWD=
	{
		temp = (char **)malloc(sizeof(char *) * (i + 1));
		j = 0;
		while (j < i)
		{
			temp[j] = ft_strdup(vars->env_var[j]);
			j++;
		}
		temp[j] = ft_strjoin("OLDPWD=",old_pwd);
		temp[j + 1] = NULL;
		ft_free_env(vars);
		vars->env_var = temp;
	}
}
//use getcwd which returns the current working directory
//this code might have some upper case - lower case issues, will check in lab computers.
void	ft_pwd(void)
{
	char	pwd[300];   //I assume 300 is long enough, need to know size

	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		err_code = 0;
	}
	else
		err_code = 1;
}

void	ft_env(t_var *vars)
{
	int	i;

	i = 0;
	while(vars->env_var[i])
	{
		if (ft_strchr(vars->env_var[i], '=')) //..maybe can delete if statment,
			printf("%s\n", vars->env_var[i]);
		i++;
	}
}
