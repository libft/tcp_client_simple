
NAME := libft_tcp_client_simple

NAME_DYNAMIC := $(NAME).$(if $(filter $(TRUTHY),$(IS_WINDOWS)),dll,$(if $(filter $(TRUTHY),$(IS_MACOS)),dylib,so))
NAME_STATIC := $(NAME).$(if $(filter $(TRUTHY),$(IS_WINDOWS)),lib,a)

all: $(NAME_DYNAMIC) $(NAME_STATIC)
.PHONY: all

SOURCES := $(shell find $(SRC_DIR) -name "*.c")
OBJECTS_DYNAMIC := $(patsubst $(SRC_DIR)/%,%.dynamic.o,$(SOURCES))
OBJECTS_STATIC := $(patsubst $(SRC_DIR)/%,%.static.o,$(SOURCES))

CCLD := clang
CC := clang

$(NAME_DYNAMIC): $(OBJECTS_DYNAMIC)
	$_$(CCLD) -shared -o $@ $^
$(NAME_STATIC): $(OBJECTS_STATIC)
	$_$(AR) crs $@ $^

CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic -I$(SRC_DIR)/includes

%.dynamic.o: $(SRC_DIR)/%
	$_$(CC) -fPIC -c $(CFLAGS) -MMD -o $@ $<
%.static.o: $(SRC_DIR)/%
	$_$(CC) -c $(CFLAGS) -MMD -o $@ $<
