CONTIKI_PROJECT = coap-example-server
all: $(CONTIKI_PROJECT)

# Do not try to build on Sky because of code size limitation
PLATFORMS_EXCLUDE = sky z1

# Include the CoAP implementation
MODULES += os/net/app-layer/coap

# Include CoAP resources
MODULES_REL += ./resources

# Include the CoAP implementation
# MODULES += $(CONTIKI_NG_APP_LAYER_DIR)/coap

PROJECT_SOURCEFILES += data.c
PROJECT_SOURCEFILES += dataAggOptimizer.c
PROJECT_SOURCEFILES += serialize.c
PROJECT_SOURCEFILES += helpers.c
PROJECT_SOURCEFILES += rest.c

CONTIKI=../..
include $(CONTIKI)/Makefile.include
# WERROR=0
CFLAGS += -Wno-error

# -WERROR=
# Wunused-function=1
# Wunused-label=1
# Wunused-parameter=1
# Wunused-value=1
# Wunused-variable=1
