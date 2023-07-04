#include "mlx_app.h"
#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_app	app;

	(void)argc;
	(void)argv;
	if (app_execute(&app) == FAILURE)
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
