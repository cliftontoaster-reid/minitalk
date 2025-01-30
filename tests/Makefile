CCX = clang++
CC  = clang

SRC_DIR	=	src/
OBJ_DIR	?=	target
LFT_DIR	?=	../libft
LFT_VER	?= HEAD
_LIB_FT	=	$(LFT_DIR)/libft.a
INC_DIR	?=	../include

CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++17 -g -fsanitize=undefined -fsanitize=address \
			 -I/usr/include/cunit -I$(LFT_DIR) -I$(INC_DIR)
LDFLAGS = -g -fsanitize=undefined -fsanitize=address -lcunit

# Check if mold linker exists
MOLD_LINKER := $(shell command -v mold 2> /dev/null)
# Check if lld linker exists
LLD_LINKER := $(shell command -v ld.lld 2> /dev/null)

# Use mold as linker if available, otherwise use lld, otherwise use default
ifneq ($(MOLD_LINKER),)
	LDFLAGS += -fuse-ld=mold
else ifneq ($(LLD_LINKER),)
	LDFLAGS += -fuse-ld=lld
endif

NAME = swapush

SRC	=	\
	$(SRC_DIR)minitalk.cpp \

OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXT_OBJ ?= 

all: $(NAME)

$(NAME): $(_LIB_FT) $(OBJ)
	@$(CCX) $(LDFLAGS) -o $@ $(OBJ) $(EXT_OBJ) \
        -Wl,--whole-archive $(_LIB_FT) -Wl,--no-whole-archive
ifneq ($(MOLD_LINKER),)
	@echo "Linking $@ using the mold linker"
else ifneq ($(LLD_LINKER),)
	@echo "Linking $@ using the lld linker"
else
	@echo "Linking $@ using the default linker"
endif

$(_LIB_FT):
	@if [ ! -d $(LFT_DIR) ]; then git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); fi
	@cd $(LFT_DIR) && git checkout $(LFT_VER) && cd ..
	$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CCX) $(CFLAGS) -c -o $@ $<
	@echo "Compiled $<"

clean:
	rm -rf $(OBJ_DIR)
nclean: clean
	rm -f $(NAME)
fclean: nclean
	rm -rf$(LFT_DIR)

re: fclean all
qre: nclean all

.PHONY: all clean nclean fclean re qre 
