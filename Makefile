SNAME = server
CNAME = client

# Directories
SRCS_DIR = ./src
INCLUDES_DIR = ./include

# Modules
MODS = 

# Source files
SRCS = \

# Object files
SERVERC = $(SNAME).c
CLIENTC = $(CNAME).c
OBJS = $(SRCS:.c=.o) libft/libft.a

# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -std=gnu17
INCLUDES = -I$(INCLUDES_DIR) -I./libft

# Rules
all: $(SNAME) $(CNAME)

$(SNAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(SNAME) $(SERVERC) $(OBJS)
$(CNAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(CNAME) $(CLIENTC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	cd ./libft && make && cd ../

clean:
	cd ./libft && make clean && cd ../
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	cd ./libft && make fclean && cd ../
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
