.DEFAULT_GOAL := build

.PHONY: help
help: ## Display this help screen
	@grep -E '^[a-z.A-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean: clean-build ## Clean project

.PHONY: clean-build
clean-build:
	rm -fr build

.PHONY: build
build: ## Build shared library
	cmake -S . -B build
	cmake --build build -j$$(nproc)

.PHONY: rebuild
rebuild: clean build ## Clean and rebuild the library from scratch
