#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <err.h>
#include <libmsr.h>
#include <unistd.h>
#include <stdlib.h>

#define STREQ(a, b) (!(strcmp((a), (b))))
#define FATAL(format, ...) do { \
							fprintf(stderr, "Fatal: " format "\n", ##__VA_ARGS__); \
							exit(1); \
						} while(0)

static char *version = "0.0.1";
static char *coercivity = "high";
static char *device = "/dev/ttyUSB0";

void clone();

int main(int argc, char **argv)
{
	signed char opt;
	struct option options[] =
	{
		{ "coercivity", required_argument, 0, 'c' },
		{ "device", required_argument, 0, 'd' },
		{ "version", no_argument, 0, 'v' },
		{ "help", no_argument, 0, 'h' },
		{ 0, 0, 0, 0 }
	};

	while ((opt = getopt_long(argc, argv, "c:d:hv", options, NULL)) != -1) {
		switch (opt) {
			case 'c':
				coercivity = optarg;

				if (!(STREQ(coercivity, "high") || STREQ(coercivity, "low"))) {
					FATAL("Bad coercivity: '%s'.", coercivity);
				}
				break;
			case 'd':
				device = optarg;
				break;
			case 'v':
				printf("msr-clone %s (c) William Woodruff 2016\n", version);
				break;
			default:
				printf("Usage: %s [options]\n", argv[0]);
				printf("\n%s\n", "Options:\n"
					"  -c, --coercivity <high|low>\n"
					"  -o, --output <file>\n"
					"  -f, --format <raw|bits|hex|string>\n"
					"  -d, --device <file>\n"
					"  -v, --version\n"
					"  -h, --help\n");
				return 1;
		}
	}

	clone();

	return 0;
}

void clone()
{
	int ret;
	int msr_fd = -1;
	msr_tracks_t tracks = {0};

	if (msr_serial_open(device, &msr_fd, MSR_BLOCKING, MSR_BAUD) != 0) {
		FATAL("Serial open of '%s' failed.", device);
	}

	msr_init(msr_fd);

	if (STREQ(coercivity, "high")) {
		msr_set_hi_co(msr_fd);
	}
	else {
		msr_set_lo_co(msr_fd);
	}

	for (int i = 0; i < MSR_MAX_TRACKS; i++) {
		tracks.msr_tracks[i].msr_tk_len = MSR_MAX_TRACK_LEN;
	}

	printf("Scan the card to be cloned...\n");

	msr_raw_read(msr_fd, &tracks);

	printf("Scan the card to clone onto...\n");

	msr_raw_write(msr_fd, &tracks);

	msr_serial_close(msr_fd);
}
