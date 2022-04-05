BASE_PATH := .
include variables.mk
include variables_$(if $(filter $(TRUTHY),$(IS_WINDOWS)),windows,posix).mk

all: | builddir
	$_$(MAKE) -C builddir all
clean:
	$_rm -rf builddir
fclean: clean
re: fclean all
.PHONY: all clean fclean re

builddir:
ifeq ($(BUILDDIR_PATH),)
	$_$(MAKE) BUILDDIR_PATH=./builddir builddir_skip_if_already_exists
else
	$_[ ! -d $(BUILDDIR_PATH) ] || (echo "Directory already exists: $(BUILDDIR_PATH)" && false)
	$_[ ! -f $(BUILDDIR_PATH) ] || (echo "File already exists: $(BUILDDIR_PATH)" && false)
	$_rm -rf tmp
	$_mkdir -p tmp
	$_printf "SRC_DIR := %s\n" "$(shell cd src && pwd)" | cat - variables.mk variables_$(if $(filter $(TRUTHY),$(IS_WINDOWS)),windows,posix).mk builddir_template.mk > tmp/Makefile
	$_find . -name "*.local.mk" | xargs | xargs -I {} cp {} tmp
	$_echo "*" > tmp/.gitignore
	$_mv tmp $(BUILDDIR_PATH)
endif
builddir_skip_if_already_exists:
	$_[ -d $(BUILDDIR_PATH) ] || [ -f $(BUILDDIR_PATH) ] || $(MAKE) builddir
.PHONY: builddir builddir_skip_if_already_exists
