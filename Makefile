SUBDIRS = $(wildcard */)

all: subdirs

subdirs:
	@for dir in $(SUBDIRS); do echo [MAKE] $$dir; make --no-print-directory -C $$dir; done

.PHONY: clean
clean:
	@for dir in $(SUBDIRS); do echo [MAKE] $$dir; make --no-print-directory -C $$dir clean; done
