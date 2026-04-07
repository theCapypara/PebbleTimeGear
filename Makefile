SOURCES = $(shell find src) $(shell find resources) package.json package-lock.json
PLATFORMS = aplite basalt chalk diorite emery flint gabbro

.PHONY: all emulators enable-qv disable-qv

build/PebbleTimeGear.pbw: $(SOURCES)
	pebble build

all: build/PebbleTimeGear.pbw

emulators: all
	# we need to sleep due to some issues when running them at the exact same time
	sleeptime=0; \
	for plat in $(PLATFORMS); do \
      sleep 0.$$sleeptime && pebble install --emulator $$plat; \
      sleeptime=$(($sleeptime + 1)); \
    done

enable-qv:
	for plat in $(PLATFORMS); do \
      PEBBLE_EMULATOR=$$plat pebble emu-set-timeline-quick-view on; \
    done

disable-qv:
	for plat in $(PLATFORMS); do \
      PEBBLE_EMULATOR=$$plat pebble emu-set-timeline-quick-view off; \
    done
