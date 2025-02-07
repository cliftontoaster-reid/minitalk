CC = clang

SRC_DIR	=	src/
OBJ_DIR	=	target/
INC_DIR	=	include/
LFT_DIR	=	libft/
LFT_VER	=	e9f828b6741b1061a21729b6d44a5c0989c24474
_LIB_FT	=	$(LFT_DIR)libft.a

CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=gnu17 -g -O3 \
				-I$(INC_DIR) -I$(LFT_DIR)include -I$(LFT_DIR) -fsanitize=undefined -fsanitize=address
LDFLAGS = -g -fsanitize=undefined -fsanitize=address -I/usr/include -I/usr/local/include

MOLD_LINKER := $(shell command -v mold 2> /dev/null)
LLD_LINKER  := $(shell command -v ld.lld 2> /dev/null)

ifneq ($(MOLD_LINKER),)
	LDFLAGS += -fuse-ld=mold -L$(LFT_DIR) -lft
else ifneq ($(LLD_LINKER),)
	LDFLAGS += -fuse-ld=lld -L$(LFT_DIR) -lft
else
	INC_LBFT = -Wl,--whole-archive $(_LIB_FT) -Wl,--no-whole-archive
endif

NAME_CLIENT = client
NAME_SERVER = server

SRC_SHARED = \
	$(SRC_DIR)shared/sig.c \
	$(SRC_DIR)shared/brand.c \

SRC_CLIENT = \
	$(SRC_DIR)client/error.c \
	$(SRC_DIR)client/validator.c \

SRC_SERVER = \

OBJ_SHARED = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRC_SHARED))
OBJ_CLIENT = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRC_CLIENT))
OBJ_SERVER = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRC_SERVER))

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(_LIB_FT) $(OBJ_SHARED) $(OBJ_CLIENT) $(SRC_DIR)$(NAME_CLIENT).c
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ_SHARED) $(OBJ_CLIENT) $(SRC_DIR)$(NAME_CLIENT).c \
		$(INC_LBFT)
ifneq ($(MOLD_LINKER),)
	@echo "Linking $@ using the mold linker"
else ifneq ($(LLD_LINKER),)
	@echo "Linking $@ using the lld linker"
else
	@echo "Linking $@ using the default linker"
endif

$(NAME_SERVER): $(_LIB_FT) $(OBJ_SHARED) $(OBJ_SERVER) $(SRC_DIR)$(NAME_SERVER).c
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ_SHARED) $(OBJ_SERVER) $(SRC_DIR)$(NAME_SERVER).c \
		$(INC_LBFT)
ifneq ($(MOLD_LINKER),)
	@echo "Linking $@ using the mold linker"
else ifneq ($(LLD_LINKER),)
	@echo "Linking $@ using the lld linker"
else
	@echo "Linking $@ using the default linker"
endif

$(_LIB_FT):
	@if [ ! -d $(LFT_DIR) ]; then git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); fi
	@cd libft && git checkout $(LFT_VER) && cd ..
	$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compiled $<"

shared: $(OBJ_DIR)/shared.a

$(OBJ_DIR)/shared.a: $(_LIB_FT) $(OBJ_SHARED)
	ar rcs $(OBJ_DIR)/shared.a $(OBJ_SHARED)

test: shared
	@$(MAKE) -C tests OBJ_DIR=$(abspath $(OBJ_DIR))/tests LFT_DIR=$(abspath $(LFT_DIR)) INC_DIR=$(abspath $(INC_DIR)) \
		EXT_OBJ=$(abspath $(OBJ_DIR)/shared.a) LFT_VER=$(LFT_VER)
	@./tests/swapush

clean:
	rm -rf $(OBJ_DIR)

nclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

fclean: nclean
	rm -rf $(LFT_DIR)

re: fclean all
qre: nclean all

.PHONY: all clean nclean fclean re qre shared test
