NAME = IRC
NAME_TEST = ircserv_test
CC = c++
RM = rm -rf
CFLAGS =  -std=c++98 -MD -Wall -Wextra -Werror

SRC = main Parsing

SRC_DIR = src/
OBJ_DIR = objects/

SRCS		= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC)))
SRCS_TEST	= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_TEST)))

OBJS		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
OBJS_TEST	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_TEST)))

all: $(NAME) 

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME) 

test: $(OBJS_TEST)
	@$(CC) $(CFLAGS) -o $(NAME_TEST) $(OBJS_TEST)
	@clear

re: fclean all
.PHONY: all clean fclean re