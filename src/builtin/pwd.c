#include "minishell.h"

void	ft_pwd(t_command *cmd)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	print_to_outfiles(buffer, cmd);
	write(1, "\n",1);
	free(buffer);
	buffer = NULL;
}
