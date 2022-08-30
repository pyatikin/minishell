NAME			= minishell

SRCS = main.c ft_strlen.c check_cmd.c print_error.c\
		ft_strcmp.c spaces.c miniparser.c signals.c\
		test_env.c ft_substr.c ft_strjoin.c ft_calloc.c\
		ft_strlcpy.c ft_strdup.c ft_strncmp.c ft_memset.c\
		env.c export.c

OBJS = $(SRCS:%.c=%.o)

CC = gcc
CFLAGS =
CLIBFLAGS = -lncurses -lpthread -pthread

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

%.o : %.c 
	@$(CC) $(CFLAGS) -c $< -o $@ -lreadline
	@printf "$(LF)$(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)from $(FG_TEXT_PRIMARY)$<"

$(NAME) : $(HEADERS) $(OBJS) Makefile
	@printf "$(LF)$(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ Object files$(FG_TEXT) !\n"
	@printf "$(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT) !\n"
	@$(CC) $(CFLAGS)  $(OBJS) -o $@ -lreadline
	@printf "$(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@$(FG_TEXT) !\n$(NO_COLOR)"