ignore_local_config:
	git update-index --assume-unchanged local_config

include local_config

submodules:
	@echo "Downloading sources. This may take a while on first run..."
	git submodule init
	git submodule update
	git submodule update --rebase --remote `git submodule status | awk '{ print $$2 }'`
	@echo "Sources downloaded!"

check_dependencies: ignore_local_config
	python3 scripts/check_dependencies.py
	@echo "All dependencies met!"

build_u-boot: submodules
	# Configure for OrangePi using Kbuild
	#ToDo: Setup CROSS_COMPILER env var
	cd boot && \
	$(MAKE) distclean && \
	$(MAKE) orangepi_pc_defconfig && \
	$(MAKE) all
	@echo "U-Boot built!"
	
setup: check_dependencies build_u-boot
	cd rtos_lib && \
	./config orange_pi
	# ToDo: setup tftp location
	@echo "Setup complete!"

build: submodules
	cd rtos_lib && $(MAKE)
	@echo "Compilation and deploy complete!"
