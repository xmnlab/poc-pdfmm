# path
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

ARGS:=

# build flags
BUILD_TYPE:=release


.PHONY: clean-optional
clean-optional:
	bash ./scripts/optclean.sh
	mkdir -p build


.ONESHELL:
.PHONY: build
build: clean-optional
	set -ex
	meson setup \
		--prefix ${CONDA_PREFIX} \
		--libdir ${CONDA_PREFIX}/lib \
		--includedir ${CONDA_PREFIX}/include \
		--includedir ${CONDA_PREFIX}/include/pdfmm \
		--buildtype=${BUILD_TYPE} \
		--native-file meson.native ${ARGS} \
		build .
	meson compile -C build

.ONESHELL:
.PHONY: build-with-tests
build-with-tests:
	set -ex
	$(MAKE) build ARGS="-Ddev=enabled -Db_coverage=true -Db_sanitize=address"

.ONESHELL:
.PHONY: install
install:
	meson install -C build


# TESTS
# =====

.ONESHELL:
.PHONY: run-tests
run-tests:
	set -ex
	meson test -C build -v

.ONESHELL:
.PHONY: code-coverage
code-coverage:
	set -ex
	ninja coverage -C build
