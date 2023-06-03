#include <ncurses.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vered.h"

static char *read_file(const char *file_name);
static void write_file(const char *file_name, const char *src);

typedef struct {
	size_t start;
	size_t end;
} Line;

typedef struct {
	char *file;
	size_t file_size;
	uint32_t index;

	Line *lines;
	size_t lines_size;

	uint32_t cursor_x, cursor_y;
} Vered;

char *vered_run(const char *file_name)
{
	Vered *vered = malloc(sizeof(Vered));

	if (file_name == NULL) {
		vered->file_size = 32;
		vered->file = calloc(vered->file_size, sizeof(char));
	}
	else {
		vered->file = read_file(file_name);
		vered->file_size = strlen(vered->file + 1);
	}
	vered->index = 0;

	vered->cursor_x = 0;
	vered->cursor_y = 0;

	WINDOW *window = initscr();
	raw();
	cbreak();
	// noecho();
	keypad(window, true);

	int c;
	for (;;) {
		c = getch();

		if (c == KEY_UP)
			printw("up");

		refresh();
	}

	endwin();

	free(vered);

	return vered->file;
}

static char *read_file(const char *file_name)
{
	FILE *file = fopen(file_name, "r");
	if (file == NULL) {
		fprintf(stderr, "error: %s: Cannot open file\n", file_name);
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = malloc(file_size + 1);
	fread(buffer, sizeof(char), file_size, file);

	fclose(file);

	return buffer;
}

static void write_file(const char *file_name, const char *src)
{
	FILE *file = fopen(file_name, "w+");
	if (file == NULL) {
		fprintf(stderr, "error: %s: Cannot write to file\n", file_name);
		exit(EXIT_FAILURE);
	}

	fwrite(src, sizeof(char), strlen(src), file);

	fclose(file);
}
