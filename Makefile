# This currently builds some sample user space programs

PREFIX = /usr

CFLAGS = -Wall -g -std=c99 -pedantic -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lmsr

MSRDEMO = msr
MSRDEMOSRCS = msr.c
MSRDEMOOBJS = $(MSRDEMOSRCS:.c=.o)

MSRQUICKERASER = msr-quick-eraser
MSRQUICKERASEROBJS = msr-quick-eraser.o

MSRDUMP = msr-dump
MSRDUMPOBJS = msr-dump.o

MSRQUICKISODUMPER = msr-quick-iso-dumper
MSRQUICKISODUMPEROBJS = msr-quick-iso-dumper.o

MSRQUICKRAWDUMPER = msr-quick-raw-dumper
MSRQUICKRAWDUMPEROBJS = msr-quick-raw-dumper.o

MAKSTRIPEQUICKCLONE = makstripe-quick-clone
MAKSTRIPEQUICKCLONEOBJS = makstripe-quick-clone.o

MSRBARTDUMPER = msr-bart-dumper
MSRBARTDUMPEROBJS = msr-bart-dumper.o

FILEBITREVERSER = file-bit-reverser
FILEBITREVERSEROBJS = file-bit-reverser.o

FILEBITSHIFTER = file-bit-shifter
FILEBITSHIFTEROBJS = file-bit-shifter.o

FILEFIELDVISUALIZER = file-field-visualizer
FILEFIELDVISUALIZEROBJS = file-field-visualizer.o

all: $(MSRDEMO) $(MSRQUICKERASER) $(MSRDUMP) $(MSRQUICKISODUMPER) \
	$(MSRQUICKRAWDUMPER) $(MAKSTRIPEQUICKCLONE) $(MSRBARTDUMPER) \
	$(FILEBITREVERSER) $(FILEBITSHIFTER) $(FILEFIELDVISUALIZER)

$(MSRDEMO): $(MSRDEMOOBJS)
	$(CC) -o $(MSRDEMO) $(MSRDEMOOBJS) $(LDFLAGS)

$(MSRQUICKERASER): $(MSRQUICKERASEROBJS)
	$(CC) -o $(MSRQUICKERASER) $(MSRQUICKERASEROBJS) $(LDFLAGS)

$(MSRDUMP): $(MSRDUMPOBJS)
	$(CC) -o $(MSRDUMP) $(MSRDUMPOBJS) $(LDFLAGS)

$(MSRQUICKISODUMPER): $(MSRQUICKISODUMPEROBJS)
	$(CC) -o $(MSRQUICKISODUMPER) $(MSRQUICKISODUMPEROBJS) $(LDFLAGS)

$(MSRQUICKRAWDUMPER): $(MSRQUICKRAWDUMPEROBJS)
	$(CC) -o $(MSRQUICKRAWDUMPER) $(MSRQUICKRAWDUMPEROBJS) $(LDFLAGS)

$(MAKSTRIPEQUICKCLONE): $(MAKSTRIPEQUICKCLONEOBJS)
	$(CC) -o $(MAKSTRIPEQUICKCLONE) $(MAKSTRIPEQUICKCLONEOBJS) $(LDFLAGS)

$(MSRBARTDUMPER): $(MSRBARTDUMPEROBJS)
	$(CC) -o $(MSRBARTDUMPER) $(MSRBARTDUMPEROBJS) $(LDFLAGS)

$(FILEBITREVERSER): $(FILEBITREVERSEROBJS)
	$(CC) -o $(FILEBITREVERSER) $(FILEBITREVERSEROBJS) $(LDFLAGS)

$(FILEBITSHIFTER): $(FILEBITSHIFTEROBJS)
	$(CC) -o $(FILEBITSHIFTER) $(FILEBITSHIFTEROBJS) $(LDFLAGS)

$(FILEFIELDVISUALIZER): $(FILEFIELDVISUALIZEROBJS)
	$(CC) -o $(FILEFIELDVISUALIZER) $(FILEFIELDVISUALIZEROBJS) $(LDFLAGS) -lncurses

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

install:
	install -m755 -D $(MSRDEMO) $(PREFIX)/bin/$(MSRDEMO)
	install -m755 -D $(MSRQUICKERASER) $(PREFIX)/bin/$(MSRQUICKERASER)
	install -m755 -D $(MSRDUMP) $(PREFIX)/bin/$(MSRDUMP)
	install -m755 -D $(MSRQUICKISODUMPER) $(PREFIX)/bin/$(MSRQUICKISODUMPER)
	install -m755 -D $(MSRQUICKRAWDUMPER) $(PREFIX)/bin/$(MSRQUICKRAWDUMPER)
	install -m755 -D $(MAKSTRIPEQUICKCLONE) $(PREFIX)/bin/$(MAKSTRIPEQUICKCLONE)
	install -m755 -D $(MSRBARTDUMPER) $(PREFIX)/bin/$(MSRBARTDUMPER)
	install -m755 -D $(FILEBITREVERSER) $(PREFIX)/bin/$(FILEBITREVERSER)
	install -m755 -D $(FILEBITSHIFTER) $(PREFIX)/bin/$(FILEBITSHIFTER)

clean:
	rm -rf *.o *~
	rm -rf $(MSRDEMO) $(MSRQUICKERASER) $(MSRDUMP) $(MSRQUICKISODUMPER)
	rm -rf $(MSRQUICKRAWDUMPER) $(MAKSTRIPEQUICKCLONE) $(MSRBARTDUMPER)
	rm -rf $(FILEBITREVERSER) $(FILEBITSHIFTER) $(FILEFIELDVISUALIZER)
