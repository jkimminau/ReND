#Colors
red=\e[1;31m
grn=\e[1;32m
yel=\e[1;33m
pink=\e[1;94m
mag=\e[1;35m
cyn=\e[1;36m
end=\e[0m

NAME = libft.a

LIBC_SRC =	ft_memset.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memccpy.c		\
		ft_memmove.c		\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_strlen.c		\
		ft_strdup.c		\
		ft_strcpy.c		\
		ft_strncpy.c		\
		ft_strcat.c		\
		ft_strncat.c		\
		ft_strlcat.c		\
		ft_strchr.c		\
		ft_strrchr.c		\
		ft_strstr.c		\
		ft_strnstr.c		\
		ft_strcmp.c		\
		ft_strncmp.c		\
		ft_atoi.c		\
		ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c

LIBC =		$(addprefix libc/, $(LIBC_SRC))

STD_SRC =	ft_memalloc.c		\
		ft_memdel.c		\
		ft_strnew.c		\
		ft_strdel.c		\
		ft_strclr.c		\
		ft_striter.c		\
		ft_striteri.c		\
		ft_strmap.c		\
		ft_strmapi.c		\
		ft_strequ.c		\
		ft_strnequ.c		\
		ft_strsub.c		\
		ft_strjoin.c		\
		ft_strtrim.c		\
		ft_strsplit.c		\
		ft_itoa.c		\
		ft_putchar.c		\
		ft_putstr.c		\
		ft_putendl.c		\
		ft_putnbr.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		

STD =		$(addprefix standard/, $(STD_SRC))

BONUS_SRC =	ft_lstnew.c		\
		ft_lstdelone.c		\
		ft_lstdel.c		\
		ft_lstadd.c		\
		ft_lstiter.c		\
		ft_lstmap.c		\

BONUS =		$(addprefix bonus/, $(BONUS_SRC))

MORE_SRC =	ft_addprefix.c		\
		ft_itoa_base.c		\
		ft_putwchar.c		\
		ft_putwstr.c		\
		ft_wstrcpy.c		\
		ft_wstrlen.c		\
		ft_wstrsub.c		\
		ft_uitoa.c		\
		ft_uitoa_base.c		\
		ft_sitoa.c		\
		ft_nextspace.c		\
		ft_nextword.c		\
		ft_nextl.c		\
		ft_pow.c		\
		ft_abs.c		\
		ft_strndup.c		\
		ft_strtointarr.c	\
		ft_wordcount.c		\
		ft_putintarr.c		\
		ft_capitalize.c		\
		ft_atof.c


MORE =		$(addprefix more/, $(MORE_SRC))

GNL_SRC =	get_next_line.c

GNL =		$(addprefix gnl/, $(GNL_SRC))

PRINTF_SRC = 	ft_printf.c		\
		ft_printf_flags.c	\
		ft_printf_conv.c	\
		conv_special.c		\
		conv_char.c		\
		grab_num.c		\
		conv_num.c		\
		ft_printf_struct.c		

PRINTF =	$(addprefix printf/, $(PRINTF_SRC))

OBJ =		$(LIBC_SRC:.c=.o)	\
		$(STD_SRC:.c=.o)	\
		$(BONUS_SRC:.c=.o)	\
		$(MORE_SRC:.c=.o)	\
		$(GNL_SRC:.c=.o)	\
		$(PRINTF_SRC:.c=.o)

OBJ_F =		object_files/

CFLAGS = -c -Wall -Werror -Wextra

HEADERFLG = -Ignl -Iprintf -I.

all: $(NAME)

$(NAME):
	@printf "Making $(pink)libft$(end) . . . "
	@gcc $(CFLAGS) $(HEADERFLG) $(LIBC) $(STD) $(BONUS) $(MORE) $(GNL) $(PRINTF)
	@ar rc $(NAME) $(OBJ)
	@mkdir $(OBJ_F)
	@mv $(OBJ) $(OBJ_F)
	@ranlib $(NAME)
	@printf "$(grn)Done$(end)\n"

clean:
	@/bin/rm -rf $(OBJ_F) libft.h.gch

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
