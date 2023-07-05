NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = ./srcs
FT_PRINTF_SRCDIR = ./srcs/ft_printf_srcs
SRCS =	$(SRCDIR)/ft_isalpha.c\
		$(SRCDIR)/ft_isdigit.c\
		$(SRCDIR)/ft_isalnum.c\
		$(SRCDIR)/ft_isascii.c\
		$(SRCDIR)/ft_isprint.c\
		$(SRCDIR)/ft_strlen.c\
		$(SRCDIR)/ft_memset.c\
		$(SRCDIR)/ft_memcpy.c\
		$(SRCDIR)/ft_memmove.c\
		$(SRCDIR)/ft_strlcpy.c\
		$(SRCDIR)/ft_strlcat.c\
		$(SRCDIR)/ft_toupper.c\
		$(SRCDIR)/ft_tolower.c\
		$(SRCDIR)/ft_strchr.c\
		$(SRCDIR)/ft_strcmp.c\
		$(SRCDIR)/ft_strncmp.c\
		$(SRCDIR)/ft_memchr.c\
		$(SRCDIR)/ft_memcmp.c\
		$(SRCDIR)/ft_strnstr.c\
		$(SRCDIR)/ft_atoi.c\
		$(SRCDIR)/ft_calloc.c\
		$(SRCDIR)/ft_strdup.c\
		$(SRCDIR)/ft_substr.c\
		$(SRCDIR)/ft_strjoin.c\
		$(SRCDIR)/ft_strtrim.c\
		$(SRCDIR)/ft_split.c\
		$(SRCDIR)/ft_itoa.c\
		$(SRCDIR)/ft_putchar_fd.c\
		$(SRCDIR)/ft_putstr_fd.c\
		$(SRCDIR)/ft_putnbr_fd.c\
		$(SRCDIR)/get_next_line.c\
		$(SRCDIR)/ft_strnchr.c\
		$(SRCDIR)/ft_atoi_base.c\
		$(FT_PRINTF_SRCDIR)/ft_printf.c\
		$(FT_PRINTF_SRCDIR)/ft_putnbr_base.c\
		$(FT_PRINTF_SRCDIR)/get_conf.c\
		$(FT_PRINTF_SRCDIR)/get_flag.c\
		$(FT_PRINTF_SRCDIR)/get_len.c\
		$(FT_PRINTF_SRCDIR)/get_precision.c\
		$(FT_PRINTF_SRCDIR)/get_specifier.c\
		$(FT_PRINTF_SRCDIR)/get_value.c\
		$(FT_PRINTF_SRCDIR)/get_width.c\
		$(FT_PRINTF_SRCDIR)/print_addr.c\
		$(FT_PRINTF_SRCDIR)/print_conv.c\
		$(FT_PRINTF_SRCDIR)/print_nb.c\
		$(FT_PRINTF_SRCDIR)/print_value.c
OBJ = $(SRCS:.c=.o)
HDIR = ./inc
HD =	$(HDIR)/libft.h\
		$(HDIR)/ft_printf.h

all : $(NAME)

%.o : %.c
	$(CC) -I $(HDIR) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(HD)
	ar -src $(NAME) $^

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
