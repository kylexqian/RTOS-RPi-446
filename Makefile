ignore_local_config:
	git update-index --assume-unchanged local_config

include local_config

submodules:
	@echo "Downloading sources. This may take a while..."
	git submodule init
	git submodule update

check_dependencies: ignore_local_config
	python3 scripts/check_dependencies.py

build_u-boot: submodules
	. scripts/build_u-boot.sh

setup: check_dependencies build_u-boot
	cd rtos_lib
	. config orange_pi
	# ToDo: setup tftp location

build:
	cd rtos_lib
	make -j
