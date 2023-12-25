CFLAGS = -Wall

all:
	@echo "Compiling..."
	cc $(CFLAGS) main.c mt.c init.c struct.h -o app
	@echo "Done. Type: ./app to run."

clear:
	@rm app
	@echo "Deleted all temp files."