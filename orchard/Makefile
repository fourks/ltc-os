##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

CH_USE_RT = TRUE
ifeq ($(CH_USE_RT),)
  CH_USE_RT=FALSE
endif

ifeq ($(LTC_HW_VERSION),PVT1C)
  # LTC board, PVT, 1, no patches 
  HWVER=0x00030100
  HWNAME=PVT1C
endif
ifeq ($(LTC_HW_VERSION),PVT1E)
  # LTC board, PVT, 1, rev E
  HWVER=0x0003010E
  HWNAME=PVT1E
endif
ifeq ($(HWVER),)
  $(error LTC_HW_VERSION is not set or not recognized.  Set LTC_HW_VERSION to one of: PVT1C, PVT1E)
endif
BUILDDIR=build-$(LTC_HW_VERSION)

# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -Os -ggdb -fomit-frame-pointer -falign-functions=16 -nostdlib -mfloat-abi=soft -mfp16-format=none -fsingle-precision-constant
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT = -std=gnu99
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti -fno-exceptions
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT =
endif

# Enable this if you want link time optimizations (LTO)
ifeq ($(USE_LTO),)
  USE_LTO = no
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
USE_VERBOSE_COMPILE = no
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

# If enabled, this option makes the build process faster by not compiling
# modules not used in the current configuration.
ifeq ($(USE_SMART_BUILD),)
  USE_SMART_BUILD = yes
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x80
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0xb8
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Define project name here
PROJECT = orchard

# Imported source files and paths
CHIBIOS = ..
# Startup files.
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_kl02x.mk
# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/KINETIS/KL02x/platform.mk
include $(CHIBIOS)/os/hal/boards/CHIBITRONICS_ESPLANADE/board.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
# RTOS files (optional).
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v6m.mk

QFPLIB = $(CHIBIOS)/ext/qfplib-20160419
include $(QFPLIB)/build.mk

# Define linker script file here
LDSCRIPT= $(STARTUPLD)/KL02P20.ld

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = main.c \
       esplanade_demod.c \
       orchard-vectors.c \
       esplanade_analog.c \
       esplanade_updater.c \
       esplanade_mac.c \
       esplanade_app.c \
       murmur3.c \
       flash.c \
       lptmr.c \
       $(STARTUPSRC) \
       $(PORTSRC) \
       $(KERNSRC) \
       $(HALSRC) \
       $(OSALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       printf.c \
       ws2812b.c \
       $(CHIBIOS)/os/hal/lib/streams/chprintf.c \
       $(CHIBIOS)/os/hal/lib/streams/memstreams.c \
       __aeabi.c \
       math.c \
       arduino-chibios.c \
       arduino-flash.c \
       arduino-i2c.c \
       arduino-io.c \
       arduino-irqs.c \
       arduino-math.c \
       arduino-pwm.c \
       arduino-time.c \
       arduino-tone.c \

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC =

# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC =

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC =

# List ASM source files here
ASMSRC += $(STARTUPASM) $(PORTASM) $(OSALASM) \
          svc_handler.s ws2812b_ll.s \
          thumb1_case.s \
          hardfault_handler.s memmanage_handler.s \
          usagefault_handler.s busfault_handler.s \
          syscalls-os.s \
          $(CHIBIOS)/os/hal/lib/streams/chprintf_fix_va.s \


INCDIR = $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) $(TESTINC) \
         $(CHIBIOS)/os/various \
         $(CHIBIOS)/os/hal/lib/streams \

#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

MCU  = cortex-m0

#TRGT = arm-elf-
#TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
LD   = $(TRGT)gcc
#LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar
OD   = $(TRGT)objdump
SZ   = $(TRGT)size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT =

# THUMB-specific options here
TOPT = -mthumb -DTHUMB -msoft-float

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes # -Wundef

# Define C++ warning options here
CPPWARN = -Wall -Wextra # -Wundef

#
# Compiler settings
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS = -DLTC_HW_VERSION=$(HWVER) -DLTC_HW_VERSION_$(HWNAME)

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = lib/libstdc++-armv6-m.a \
        lib/libaeabi-cortexm0.a \
        lib/libunaligned-funcs.a \
        lib/libcrtbegin.a \

#
# End of user defines
##############################################################################

RULESPATH = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC
include $(RULESPATH)/rules.mk

##############################################################################
# MISRA check rule, requires PCLint and the setup files, not provided.
#
#misra:
#	@lint-nt -v -w3 $(DEFS) pclint/co-gcc.lnt pclint/au-misra3.lnt pclint/waivers.lnt $(IINCDIR) $(CSRC) &> misra.txt

gitversion.h: $(CHIBIOS)/.git/HEAD $(CHIBIOS)/.git/index
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@

dsptables.h: dsptables
ifeq ($(USE_VERBOSE_COMPILE),yes)
	./dsptables
else
	@echo Generating DSP tables $@
	@./dsptables
endif

dsptables: dsptable_gen.c esplanade_demod.h
ifeq ($(USE_VERBOSE_COMPILE),yes)
	gcc -I. $(IINCDIR) -lm $< -lm -o $@
else
	@echo Building DSP table generator $@
	@gcc -I. $(IINCDIR) -lm $< -lm -o $@
endif

# Build a .symbol file, to enable OS/App debugging
POST_MAKE_ALL_RULE_HOOK: $(BUILDDIR)/$(PROJECT).symbol

PRE_MAKE_ALL_RULE_HOOK: dsptables.h gitversion.h

# Suppress a cryptic, harmless warning about copying mstack
%.symbol: %.elf
ifeq ($(USE_VERBOSE_COMPILE),yes)
	$(CP) --only-keep-debug $< $@ 2> /dev/null
else
	@echo Creating $@
	@$(CP) --only-keep-debug $< $@ 2> /dev/null
endif

# These must go down here, due to variable expansion.
# Add special command line parameters to certain files.
$(OBJDIR)/esplanade_demod.o : USE_COPT += -O3
$(OBJDIR)/esplanade_analog.o : USE_COPT += -O3
$(OBJDIR)/esplanade_mac.o : USE_COPT += -Os
$(OBJDIR)/esplanade_updater.o : USE_COPT += -Os

# Debug hook - enable printing Makefile variables
# by running e.g. "make print-OUTFILES"
print-%:
	@echo '$*=$($*)'
