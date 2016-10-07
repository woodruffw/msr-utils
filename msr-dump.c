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

static char *version = "0.2.0";
static char *coercivity = "high";
static int output = 1;
static char *format = "bits";
static char *device = "/dev/ttyUSB0";

int dump(void);

int main(int argc, char **argv)
{
	signed char opt;
	struct option options[] =
	{
		{ "coercivity", required_argument, 0, 'c' },
		{ "output", required_argument, 0, 'o' },
		{ "format", required_argument, 0, 'f' },
		{ "device", required_argument, 0, 'd' },
		{ "version", no_argument, 0, 'v' },
		{ "help", no_argument, 0, 'h' },
		{ 0, 0, 0, 0 }
	};

	while ((opt = getopt_long(argc, argv, "c:o:f:d:hv", options, NULL)) != -1) {
		switch (opt) {
			case 'c':
				coercivity = optarg;

				if (!(STREQ(coercivity, "high") || STREQ(coercivity, "low"))) {
					FATAL("Bad coercivity: '%s'.", coercivity);
				}
				break;
			case 'o':
				output = creat(optarg, 644);

				if (output < 1)	{
					FATAL("Couldn't open '%s' for output.", optarg);
				}
				break;
			case 'f':
				format = optarg;

				if (!(STREQ(format, "raw") || STREQ(format, "bits")
					|| STREQ(format, "hex") || STREQ(format, "string"))) {
					FATAL("Bad format: '%s'.", format);
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
					"  -c, --coercivity <high|low>\n"
					"  -o, --output <file>\n"
					"  -f, --format <raw|bits|hex|string>\n"
					"  -d, --device <file>\n"
					"  -v, --version\n"
					"  -h, --help\n");
				return 1;
		}
	}

	dump();

	close(output);

	return 0;
}

int dump(void)
{
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

	msr_raw_read(msr_fd, &tracks);

	if (STREQ(format, "raw")) {
		for (int tn = 0; tn < MSR_MAX_TRACKS; tn++) {
			write(output, tracks.msr_tracks[tn].msr_tk_data,
					tracks.msr_tracks[tn].msr_tk_len);
		}
	}
	else if (STREQ(format, "bits")) {
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
