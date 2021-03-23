#include "cub3d.h"

void	display_error(char *msg, int code)
{
	printf("%s\n", msg);
	//handle close fd && leaks
	exit(code);
}
int		main(int argc, char **argv)
{
	int fd;
	t_param	*param;

	if (argc < 2 || argc > 3)
		display_error("wrong parameter number", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		display_error("wrong configuration file", EXIT_FAILURE);
	param = malloc(sizeof(t_param) * 1);

	if (param == NULL)
		return EXIT_FAILURE;
	ft_parse_file(param, fd);
	close(fd);
	return EXIT_SUCCESS;
}
