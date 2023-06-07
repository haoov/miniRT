#include "mlx_app.h"
#include "miniRT.h"

int	app_key_action(int key_code, t_app *app)
{
	if (key_code == XK_Escape)
		return (app_exit(app));
	return (SUCCESS);
}

