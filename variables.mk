TRUE := true
FALSE := false
TRUTHY := $(TRUE) 1
FALSY := $(FALSE) 0

_ := $(if $(filter $(TRUTHY),$(V) $(VERBOSE)),,@)
MAKE := make $(if $(filter $(TRUTHY),$(V) $(VERBOSE)),,--no-print-directory)

ifeq ($(OS),Windows_NT)
IS_WINDOWS ?= true
else
IS_WINDOWS ?= false
ifeq ($(shell uname -s),Darwin)
IS_MACOS ?= true
else
IS_MACOS ?= false
endif
endif

-include variables.local.mk
