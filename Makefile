NAME		= pipex

CC			= gcc
ifdef DEBUG
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g 
else
CFLAGS		= -Wall -Wextra -Werror
endif
LIBFT		= libft
SRC_DIR		= src/
OBJ_DIR		= obj/

HEADER_DIR	= includes/
HEADER_SRC	= pipex.h
HEADERS		= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

SRC_DIR		= src/
SRC_FILE	= children.c command.c free_error.c pipex.c

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF =	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m

all: $(NAME)

$(NAME):	$(OBJ) $(OBJF)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)
			@echo "$(CYAN_B)- pipex is compiled -"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADER)| $(OBJF)
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)$(SRC_DIR)
		@touch $(OBJF)

clean:
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT)
		@rm -f $(OBJF)
		@echo "$(CYAN)- Object files are cleaned -"

fclean: clean
		@rm -f $(NAME)
		@make fclean -C $(LIBFT)
		@echo "$(CYAN)- Executable files are cleaned -"

re:	fclean all

.PHONY: all clean fclean re