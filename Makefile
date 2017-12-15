all: lib src                  # Build lib src and tests.

targets:                      # Show a listing of targets.
	@echo Targets available:
	@echo ---------------------------------------------------------------------------
	@cat Makefile \
		|grep -e '^[a-zA-Z-]*:'               \
		|sed -e 's/[:#]/|/g' -e 's/\[/|[/g'   \
		|awk -F\| '{ printf("%12s -%-35s%s\n", $$1, $$3, $$4); }'

lib:                          # Build the project-shared library.
	make -C lib all

src: lib                      # Build source. [implies lib]
	make -C src all

docs: Doxyfile                # Generate documentation
	doxygen

tags:                         # Generate ctags file.
	find -iname \*.[ch] |xargs ctags -T

clean:                        # Clean everything, including tags.
	make -C lib clean
	make -C src clean
	rm -f tags

mrclean: clean                # Clean more. [implies clean]
	make -C lib mrclean
	make -C src mrclean

.PHONY: all targets lib src docs tags clean mrclean
