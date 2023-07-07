#*********PROJECT**********#

PROJDIR	=	$(realpath $(CURDIR))
TARGET	=	miniRT
LIBDIR	=	$(PROJDIR)/lib
SRCDIR	=	$(PROJDIR)/srcs
HDDIR	=	$(PROJDIR)/inc
OBJDIR	=	$(PROJDIR)/objs
DEPDIR	=	$(PROJDIR)/deps

#*********FILES************#

LIBFT	=	$(LIBDIR)/libft/libft.a
LIBMLX	=	$(LIBDIR)/mlx/libmlx.a
SRCS	=	$(SRCDIR)/main.c\
			$(SRCDIR)/app/mlx_app.c\
			$(SRCDIR)/app/app_key_action.c\
			$(SRCDIR)/app/mlx_image.c\
			$(SRCDIR)/scene.c\
			$(SRCDIR)/ray.c\
			$(SRCDIR)/camera.c\
			$(SRCDIR)/math/vector.c\
			$(SRCDIR)/math/matrix4.c\
			$(SRCDIR)/math/matrix3.c\
			$(SRCDIR)/objects/object.c\
			$(SRCDIR)/objects/sphere.c\
			$(SRCDIR)/objects/plane.c\
			$(SRCDIR)/objects/cylinder.c\
			$(SRCDIR)/objects/cone.c\
			$(SRCDIR)/lights/light.c\
			$(SRCDIR)/lights/pointlight.c\
			$(SRCDIR)/materials/material.c\
			$(SRCDIR)/materials/simple_mat.c\
			$(SRCDIR)/textures/textures.c\
			$(SRCDIR)/textures/flat.c\
			$(SRCDIR)/textures/checker.c\
			$(SRCDIR)/textures/img.c\
			$(SRCDIR)/gtfm.c\
			$(SRCDIR)/clean.c
HD		=	$(HDDIR)/miniRT.h\
			$(HDDIR)/mlx_app.h\
			$(HDINC)/scene.h\
			$(HDINC)/ray.h\
			$(HDINC)/vector.h
OBJS	=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
DEPS	=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.d))

#*********COMPILER*********#

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address -Ofast
HDINC	=	-I $(HDDIR) -I $(LIBDIR)/libft/inc -I $(LIBDIR)/mlx
LIBINC	=	-L $(LIBDIR)/mlx -lm -lmlx -lXext -lX11

#*********COLORS***********#

GREEN	=	\e[32m
BLUE	=	\e[34m
NC		=	\e[0m

#*********RULES************#

all : $(TARGET)

$(TARGET) : $(LIBFT) $(OBJS)
	@printf "$(GREEN)Build complete\n$(NC)"
	@printf "Linking $(BLUE)$@\n$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LIBINC)
	@printf "$(GREEN)Done\n$(NC)"

$(LIBFT) :
	@printf "Compiling $(notdir $@)\n"
	@make -s -C $(LIBDIR)/libft/
	@printf "$(GREEN)Done\n$(NC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $@))
	@printf "Building $(BLUE)$(notdir $@)\n$(NC)"
	@$(CC) $(CFLAGS) $(HDINC) -c $< -o $@ \
		-MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))

-include $(DEPS)

clean :
	@printf "Cleaning object files...\n"
	@make -s clean -C $(LIBDIR)/libft/
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)Done\n$(NC)"
	@printf "Cleaning dependency files...\n"
	@rm -rf $(DEPDIR)
	@printf "$(GREEN)Done\n$(NC)"

fclean : clean
	@printf "Cleaning target files...\n"
	@make -s fclean -C $(LIBDIR)/libft/
	@rm -f $(TARGET)
	@printf "$(GREEN)Done\n$(NC)"

re : fclean all

.PHONY : all debug clean fclean re