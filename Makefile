ignore_local_config:
	git update-index --assume-unchanged local_config

include local_config

submodules:
	@echo "Downloading sources. This may take a while on first run..."
	git submodule init
	git submodule update
	git submodule update --rebase --remote `git submodule status | awk '{ print $$2 }'`
	cd rtos_lib && git update-index --assume-unchanged user_entry/user.c
	@echo "Sources downloaded!"

check_dependencies: ignore_local_config
	python3 scripts/check_dependencies.py
	@echo "All dependencies met!"

build_u-boot: submodules
	cd boot && \
	$(MAKE) distclean && \
	$(MAKE) orangepi_pc_defconfig && \
	$(MAKE) all
	@echo "U-Boot built!"
	
setup: check_dependencies build_u-boot
	cd rtos_lib && \
	./config orange_pi
	@echo "Setup complete!"

clean:
	cd entry_point && rm *.o

deep_clean: clean
	cd boot && $(MAKE) clean
	cd rtos_lib && $(MAKE) clean

build: submodules clean
	cd rtos_lib && $(MAKE)
	@echo "Compilation and deploy complete!"
