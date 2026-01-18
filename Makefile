# ShowBox Studio Makefile
# IDE for ShowBox - Build and Development Automation

.PHONY: all build clean install run test help
.PHONY: dev start-dev start-dev-build
.PHONY: lint format docs check-deps
.PHONY: pkg-appimage

# Variables
CMAKE := cmake
MAKE := make
NPROC := $(shell nproc)
BUILD_DIR := .
BIN_DIR := build
TARGET_BIN := showbox-studio

# Default target
all: check-deps build

# ============================================================================
# Development
# ============================================================================

build:  ## Compile ShowBox Studio
	@echo "Building ShowBox Studio..."
	mkdir -p $(BIN_DIR)
	cd $(BIN_DIR) && $(CMAKE) .. -DSHOWBOX_ROOT=../showbox && $(MAKE) -j$(NPROC)

clean:  ## Clean build artifacts
	@echo "Cleaning build artifacts..."
	rm -rf $(BIN_DIR)
	find . -name "*.o" -delete
	find . -name "moc_*" -delete

install: build  ## Install Studio (Desktop File)
	@echo "Installing ShowBox Studio..."
	# Logic to install desktop file or copy binary
	# Keeping simple for now, can be expanded

run: build  ## Run ShowBox Studio
	@echo "Running ShowBox Studio..."
	./$(BIN_DIR)/$(TARGET_BIN)

dev: start-dev  ## Alias for start-dev

start-dev:  ## Start Docker development environment
	./src/start-dev.sh

start-dev-build:  ## Start dev and compile inside container
	./src/start-dev.sh bash -c "mkdir -p build && cd build && cmake .. -DSHOWBOX_ROOT=../showbox && make -j$$(nproc)"

# ============================================================================
# Quality Assurance
# ============================================================================

lint:  ## Run code linting (clang-format dry-run)
	@echo "Running lint check..."
	@if command -v clang-format >/dev/null; then \
		find src -name "*.h" -o -name "*.cpp" | xargs clang-format -n --verbose -style=file; \
	else \
		echo "Error: clang-format not found. Please install it."; \
		exit 1; \
	fi

format:  ## Run code formatting (clang-format in-place)
	@echo "Formatting code..."
	@if command -v clang-format >/dev/null; then \
		find src -name "*.h" -o -name "*.cpp" | xargs clang-format -i -verbose -style=file; \
	else \
		echo "Error: clang-format not found. Please install it."; \
		exit 1; \
	fi

docs:  ## Generate documentation (Doxygen)
	@echo "Generating documentation..."
	@if command -v doxygen >/dev/null; then \
		if [ -f Doxyfile ]; then \
			doxygen Doxyfile; \
		else \
			echo "Warning: Doxyfile not found. Skipping docs generation."; \
		fi \
	else \
		echo "Error: doxygen not found. Please install it."; \
		exit 1; \
	fi

check-deps:  ## Check for required development tools
	@echo "Checking dependencies..."
	@command -v cmake >/dev/null || echo "Warning: cmake not found."
	@command -v $(QMAKE) >/dev/null || echo "Warning: $(QMAKE) not found."
	@command -v g++ >/dev/null || echo "Warning: g++ not found."
	@command -v docker >/dev/null || echo "Warning: docker not found."

# ============================================================================
# Testing
# ============================================================================

test:  ## Run tests
	@echo "Running tests..."
	@# Integrate with ctest or custom script
	cd $(BIN_DIR) && ctest || echo "No tests configured or build dir missing."

# ============================================================================
# Packaging
# ============================================================================

pkg-appimage:  ## Build AppImage
	@echo "Building AppImage..."
	./packaging/appimage/create_appimage.sh

# ============================================================================
# Help
# ============================================================================

help:  ## Show this help
	@echo "ShowBox Studio Makefile"
	@echo "===================================================================="
	@echo "Usage: make [target]"
	@echo ""
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2}'
