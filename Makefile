check_dependencies:
	python3 scripts/check_dependencies.py

build_u-boot:
	. scripts/build_u-boot.sh

setup: check_dependencies build_u-boot
	cd rtos_lib
	. config orange_pi
	# ToDo: setup tftp location

build:
	cd rtos_lib
	make -j
