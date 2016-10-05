#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <err.h>
#include <libmsr.h>

#define STREQ(a, b) (!(strcmp((a), (b))))

static char *version = "0.1.0";
static int output = 1;
static char *format = "bits";
static char *device = "/dev/ttyUSB0";

int dump(void);

int main(int argc, char **argv)
{
	signed char opt;
	struct option options[] =
	{
		{ "output", required_argument, 0, 'o' },
		{ "format", required_argument, 0, 'f' },
		{ "device", required_argument, 0, 'd' },
		{ "version", no_argument, 0, 'v' },
		{ "help", no_argument, 0, 'h' },
		{ 0, 0, 0, 0 }
	};

	while ((opt = getopt_long(argc, argv, "o:f:d:hv", options, NULL)) != -1) {
		switch (opt) {
			case 'o':
				output = creat(optarg, 644);

				if (output < 1)	{
					printf("Fatal: Couldn't open '%s' for output.\n", optarg);
				}
				break;
			case 'f':
				format = optarg;

				if (!(STREQ(format, "bits") || STREQ(format, "hex")
					|| STREQ(format, "string"))) {
					printf("Fatal: Unrecognized format: '%s'\n", format);
					return 1;
				}
				break;
			case 'd':
				device = optarg;
				break;
			case 'v':
				printf("msr-dump %s (c) William Woodruff 2016\n", version);
				break;
			default:
				printf("Usage: %s [options]\n", argv[0]);
				printf("\n%s\n", "Options:\n"
					"  -o, --output <file>\n"
					"  -f, --format <bits|hex|string>\n"
					"  -d, --device <file>\n"
					"  -v, --version\n"
					"  -h, --help\n");
				return 1;
		}
	}

	return dump();
}

int dump(void)
{
	int msr_fd = -1;
	msr_tracks_t tracks;

	memset(&tracks, 0, sizeof(tracks));

	if (msr_serial_open(device, &msr_fd, MSR_BLOCKING, MSR_BAUD) < 0) {
		err(1, "Serial open of '%s' failed.", device);
		return 1;
	}

	msr_init(msr_fd);
	msr_set_hi_co(msr_fd);

	for (int i = 0; i < MSR_MAX_TRACKS; i++) {
		tracks.msr_tracks[i].msr_tk_len = MSR_MAX_TRACK_LEN;
	}

	msr_raw_read(msr_fd, &tracks);

	if (STREQ(format, "bits")) {
		msr_pretty_output_bits(output, tracks);
	}
	else if (STREQ(format, "hex")) {
		msr_pretty_output_hex(output, tracks);
	}
	else {
		msr_pretty_output_string(output, tracks);
	}

	msr_serial_close(msr_fd);

	return 0;
}
