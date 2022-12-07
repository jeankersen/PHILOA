NAME		= philo

SRC			= src
INC			= include
OBJ			= obj
CFILES		= main.c fct.c
HFILES		= philo.h
OFILES		= $(CFILES:.c=.o)
SRCS		= $(addprefix $(SRC)/, $(CFILES))
OBJS		= $(addprefix $(OBJ)/, $(OFILES))
HEADERS		= $(addprefix $(INC)/, $(HFILES))

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -rf

$(OBJ)/%.o:	$(SRC)/%.c
			$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME):	$(OBJ) $(OBJS)
			$(CC) $(OBJS) -lpthread  -o $(NAME)

$(OBJ):
			@mkdir -p $(OBJ)

all:		$(NAME)

clean:
			fclean
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

norme:
			norminette $(SRCS) $(HEADERS)

.PHONY:		all clean fclean re norme visual
