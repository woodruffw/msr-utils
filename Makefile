PREFIX = /usr

CFLAGS = -Wall -g -std=c99 -pedantic -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lmsr

MSRDUMP = msr-dump
MSRDUMPOBJS = msr-dump.o

MSRCLONE = msr-clone
MSRCLONEOBJS = msr-clone.o

all: $(MSRDUMP) $(MSRCLONE)

$(MSRDUMP): $(MSRDUMPOBJS)
	$(CC) -o $(MSRDUMP) $(MSRDUMPOBJS) $(LDFLAGS)

$(MSRCLONE): $(MSRCLONEOBJS)
	$(CC) -o $(MSRCLONE) $(MSRCLONEOBJS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

install:
	install -m755 -D $(MSRDUMP) $(PREFIX)/bin/$(MSRDUMP)
	install -m755 -D $(MSRCLONE) $(PREFIX)/bin/$(MSRCLONE)

clean:
	rm -rf *.o *~
	rm -rf $(MSRDUMP) $(MSRCLONE)
