#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vered.h"

int main(int argc, char **argv)
{
	if (argc > 2) {
		fprintf(stderr, "error: Cannot edit more than one file at a time\n");
		return 1;
	}

	char *file;
	if (argc < 2)
		file = vered_run(NULL);
	else
		file = vered_run(argv[1]);

	free(file);

	return 0;
}
