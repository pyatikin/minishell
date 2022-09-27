NAME			= minishell

SRCS = main.c ft_strlen.c check_cmd.c print_error.c spaces_dop.c\
		ft_strcmp.c spaces.c signals.c check_cmd_dop.c check_cmd_dop2.c cd_dop.c\
		test_env.c ft_substr.c ft_strjoin.c signals_dop.c test_env_dop_2.c\
		ft_strlcpy.c ft_strdup.c ft_strncmp.c ft_memset.c test_env_dop_1.c\
		env.c export.c export_dop.c exit.c unset.c cd.c ft_putstr_fd.c ft_putendl_fd.c\
		ft_putchar_fd.c ft_isalnum.c readinput.c ft_strjoinchr.c ft_memcpy.c\
		\
		echo.c pwd.c pars_dollar.c pars_file.c \
		pars_zero.c pars_main.c pars_flags_alock.c pars_quotes_1.c \
		pars_quotes_2.c clean.c pars_dollar_dop.c \
		pars_file_dop.c pars_flag_alloc_dop.c ft_calloc.c ft_itoa.c ft_atoi.c\
		ft_isalpha.c ft_isdigit.c
		
		

OBJS = $(SRCS:%.c=%.o)

CC = cc
CFLAGS = -lncurses -lpthread -pthread -Wall -Wextra -Werror
CLIBFLAGS = 

HEADERS = minishell.h libft.h enums.h error_msgs.h

CL_BOLD	 = \e[1m
CL_DIM	= \e[2m
CL_UDLINE = \e[4m

NO_COLOR = \e[0m

BG_TEXT = \e[48;2;45;55;72m
BG_BLACK = \e[48;2;30;31;33m

FG_WHITE = $(NO_COLOR)\e[0;37m
FG_TEXT = $(NO_COLOR)\e[32m
FG_TEXT_DEL = $(NO_COLOR)\e[31m
FG_TEXT_PRIMARY = $(CL_BOLD)

LF = \e[1K\r$(NO_COLOR)
CRLF= \n$(LF)
.PHONY: all clean fclean re bonus

all : $(NAME)

clean :
	@$(RM) $(RMFLAGS) $(OBJS)
	@printf "$(FG_TEXT_DEL)Cleaning $(FG_TEXT_PRIMARY)$(NAME) Object files...\n"

fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)
	@printf "$(FG_TEXT_DEL)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n"

re : fclean all

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

%.o : %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ -lreadline
	@printf "$(LF)$(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)from $(FG_TEXT_PRIMARY)$<"

$(NAME) : $(HEADERS) $(OBJS) Makefile 
	@printf "$(LF)$(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ Object files$(FG_TEXT) !\n"
	@printf "$(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT) !\n"
	@$(CC) $(CFLAGS)  $(OBJS) -o $@ -lreadline
	@printf "$(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@$(FG_TEXT) !\n$(NO_COLOR)"