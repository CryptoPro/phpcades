.DEFAULT_GOAL := build

TARGETS := \
	help \
	clean clean-build \
	build rebuild \
	docker-build docker

.PHONY: $(TARGETS)

help: ## Display this help screen
	@grep -E '^[a-z.A-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "$(CYAN)%-30s$(RESET) %s\n", $$1, $$2}'

clean: clean-build ## Clean project

clean-build:
	rm -fr build

build: ## Build shared library
	cmake -S . -B build
	cmake --build build -j$$(nproc)

rebuild: clean build ## Clean and rebuild the library from scratch

docker-build: ## Build docker image for phpcades
	docker build -t phpcades-build .

docker: docker-build ## Run sample in docker
	docker run phpcades-build php samples/test_extension.php

# =========================
# Printing out targets
# =========================
GREEN := \033[38;2;0;255;128m
CYAN  := \033[38;5;51m
RESET := \033[0m

define inject_start_hook
.PHONY: .print-start-$1
.print-start-$1:
	@printf "$(GREEN)>>> Running target: [%s]$(RESET)\n" "$1"

$1: .print-start-$1
endef
$(foreach t,$(TARGETS),$(eval $(call inject_start_hook,$t)))
