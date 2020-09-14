INSTANCES_DIR=~/instances/
GPUSAT_ORIG=~/GPUSAT_orig/build/gpusat
GPUSAT_NEW=~/GPUSAT/build/gpusat

#INSTANCES=$(shell find ~/instances/counting-benchmarks/basic/application -name "*.cnf.bz2")
INSTANCES=$(shell ls -d /home/vroland/instances/cachet/DQMR/* --sort=size -r | grep ".wcnf")
SHELL=/bin/bash
CHECK_DIR=/tmp/check
CHECK_ARGS ?=

space :=
space +=

$(info args: $(CHECK_ARGS))
.SECONDEXPANSION:
run/%: /$$(subst $$(space),/,$$(wordlist 3,1000,$$(subst /, ,$$*))) $(if $(CHECK_ARGS),,guard)
	echo "$(notdir $@)"
	$(GPUSAT_NEW) $(CHECK_ARGS) < $< 2> $(CHECK_DIR)/$(subst $<,,$*)/$(notdir $*) || echo 'failed!'

tree/%: %
	CHECK_ARGS='--dataStructure tree $(if $(subst .wcnf,,$(suffix $*)),,--weighted)' $(MAKE) run/new/tree/$*
	CHECK_ARGS='--dataStructure tree $(if $(subst .wcnf,,$(suffix $*)),,--weighted)' $(MAKE) run/orig/tree/$*
array/%: %
	CHECK_ARGS='--dataStructure array $(if $(subst .wcnf,,$(suffix $*)),,--weighted)' $(MAKE) run/new/array/$*
	CHECK_ARGS='--dataStructure array $(if $(subst .wcnf,,$(suffix $*)),,--weighted)' $(MAKE) run/orig/array/$*

check_dirs:
	mkdir -p $(CHECK_DIR)/new/tree
	mkdir -p $(CHECK_DIR)/new/array
	mkdir -p $(CHECK_DIR)/orig/tree
	mkdir -p $(CHECK_DIR)/orig/array

check: check_dirs $(foreach instance,$(INSTANCES),tree/$(instance) array/$(instance))
	echo "all checked."

build:
	make -C build
.PHONY: check_dirs check build
