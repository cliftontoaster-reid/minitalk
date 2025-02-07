CCX = clang++
CC  = clang

SRC_DIR	=	src/
OBJ_DIR	?=	target
LFT_DIR	?=	../libft
LFT_VER	?= HEAD
_LIB_FT	=	$(LFT_DIR)/libft.a
INC_DIR	?=	../include

# CUnit configuration
CUNIT_VER = 2.1-3
CUNIT_TAR = CUnit-$(CUNIT_VER).tar.bz2
CUNIT_DIR = $(OBJ_DIR)/CUnit-$(CUNIT_VER)
CUNIT_INSTALL_DIR = $(OBJ_DIR)/cunit
CUNIT_LIB = $(CUNIT_INSTALL_DIR)/lib/libcunit.a


CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++17 -g -fsanitize=undefined -fsanitize=address \
			  -I$(CUNIT_INSTALL_DIR)/include -I/usr/include/cunit -I$(LFT_DIR) -I$(INC_DIR) -I./
LDFLAGS = -g -fsanitize=undefined -fsanitize=address \
	-L$(CUNIT_INSTALL_DIR)/lib -lcunit \
	-Wl,-rpath,$(CUNIT_INSTALL_DIR)/lib

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
	$(SRC_DIR)sig.cpp \

OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXT_OBJ ?= 

all: $(NAME)

$(NAME): $(CUNIT_LIB) $(_LIB_FT) $(OBJ)
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

$(CUNIT_LIB):
	mkdir -p $(OBJ_DIR) $(CACHE_DIR)
	echo "Downloading CUnit..."
	if [ ! -f $(CACHE_DIR)/$(CUNIT_TAR) ]; then \
		wget https://downloads.sourceforge.net/project/cunit/CUnit/$(CUNIT_VER)/$(CUNIT_TAR) -O $(OBJ_DIR)/$(CUNIT_TAR); \
	else \
		echo "Using cached CUnit archive"; \
	fi
	echo "Extracting CUnit..."
	cd $(OBJ_DIR) && tar -xjf $(CUNIT_TAR)
	echo "Configuring CUnit..."
	cd $(CUNIT_DIR) && autoreconf -fi && ./configure --prefix=$(abspath $(CUNIT_INSTALL_DIR))
	echo "Building CUnit..."
	$(MAKE) -C $(CUNIT_DIR)
	echo "Installing CUnit..."
	$(MAKE) -C $(CUNIT_DIR) install

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
