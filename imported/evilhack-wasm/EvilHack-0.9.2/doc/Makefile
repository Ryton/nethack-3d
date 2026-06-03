#
# This file is generated automatically.  Do not edit.
# Your changes will be lost.  See sys/unix/NewInstall.unx.
# Identify this file:
MAKEFILE_DOC=1

###
### Start hints/linux PRE
###
# (new segment at source line 6 )
# Linux hints file
# This hints file provides a single-user tty build for Linux, specifically
# for Ubuntu dapper.

# Typical install path for normal user (non-root)
PREFIX=$(wildcard ~)
HACKDIR=$(PREFIX)/games/$(GAME)dir

# Default install path (assumes running at root)
#PREFIX=/usr
#HACKDIR=$(PREFIX)/games/lib/$(GAME)dir

SHELLDIR = $(PREFIX)/games
INSTDIR = $(HACKDIR)
VARDIR = $(HACKDIR)/var

POSTINSTALL=cp -n sys/unix/sysconf $(INSTDIR)/sysconf; $(CHOWN) $(GAMEUID) $(INSTDIR)/sysconf; $(CHGRP) $(GAMEGRP) $(INSTDIR)/sysconf; chmod $(VARFILEPERM) $(INSTDIR)/sysconf; cp dat/serverseed $(INSTDIR)/serverseed; $(CHOWN) $(GAMEUID) $(INSTDIR)/serverseed; $(CHGRP) $(GAMEGRP) $(INSTDIR)/serverseed; chmod $(VARFILEPERM) $(INSTDIR)/serverseed;

CFLAGS=-g3 -O0 -I../include -DNOTPARMDECL -fno-common
CFLAGS+=-DDLB
CFLAGS+=-DCOMPRESS=\"/bin/gzip\" -DCOMPRESS_EXTENSION=\".gz\"
CFLAGS+=-Wno-unused-result -Wno-format-overflow
CFLAGS+=-DSYSCF -DSYSCF_FILE=\"$(HACKDIR)/sysconf\" -DSECURE
CFLAGS+=-DTIMED_DELAY
CFLAGS+=-DHACKDIR=\"$(HACKDIR)\"
CFLAGS+=-DVAR_PLAYGROUND=\"$(HACKDIR)/var\"
CFLAGS+=-DCONFIG_ERROR_SECURE=FALSE
CFLAGS+=-DCURSES_GRAPHICS
CFLAGS+=-DPANICLOG_FMT2
CFLAGS+=-DFCMASK=0644
CFLAGS+=-DTTY_TILES_ESCCODES
CFLAGS+=-DSCORE_ON_BOTL
CFLAGS+=-DREALTIME_ON_BOTL
CFLAGS+=-DDGAMELAUNCH
CFLAGS+=-DLIVELOG_ENABLE
CFLAGS+=-DDUMPLOG
CFLAGS+=-DDUMPHTML

#detection of clang vs gcc
CCISCLANG := $(shell echo `$(CC) --version` | grep clang)
ifneq "$(CCISCLANG)" ""
CLANGGTEQ18 := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 18)
ifeq "$(CLANGGTEQ18)" "1"
# clang-specific starts here
CFLAGS+=-Wno-deprecated-non-prototype
endif
# clang-specific ends here
else
# gcc-specific starts here
CFLAGS+=-Wno-old-style-definition -Wno-unused-result -Wno-format-overflow
# gcc-specific ends here
endif  # clang-specific or gcc-specific ends here

LINK=$(CC)
# Only needed for GLIBC stack trace:
LFLAGS=-rdynamic

WINSRC = $(WINTTYSRC) $(WINCURSESSRC)
WINOBJ = $(WINTTYOBJ) $(WINCURSESOBJ)
WINLIB = $(WINTTYLIB) $(WINCURSESLIB)

# if TTY_TILES_ESCCODES
WINSRC += tile.c
WINOBJ += tile.o

WINTTYLIB=-lncursesw -ltinfo

CHOWN=true
CHGRP=true

VARDIRPERM = 0755
VARFILEPERM = 0600
GAMEPERM = 0755
### End hints/linux PRE

###
### Start Makefile.doc
###
#      NetHack Documentation Makefile.
# NetHack 3.6  Makefile.doc    $NHDT-Date: 1581732920 2020/02/15 02:15:20 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.20 $
# Copyright (c) 2015 by Kenneth Lorber, Kensington, Maryland
# NetHack may be freely redistributed.  See license for details.

# Root of source tree:
NHSROOT=..

# for Atari
# SHELL=E:/GEMINI2/MUPFEL.TTP

MAKEDEFS = ../util/makedefs

#STRIPBS=
STRIPBS = ../util/stripbs

# Which version do we want to build?  (XXX These are not used anywhere.)
GUIDEBOOK = Guidebook		# regular ASCII file
#GUIDEBOOK = Guidebook.ps	# PostScript file
#GUIDEBOOK = Guidebook.dvi	# TeX device-independent file

# Some versions of col need -x to keep them from converting spaces to tabs;
# some versions of col don't do the conversion by default and don't
# recognize the option.  Sigh.
#COLCMD ?= col -bx
#COLCMD ?= col -b
COLCMD ?= $(STRIPBS)

# The command to use to generate a PostScript file
# PSCMD = ditroff | psdit
PSCMD = groff

#NROFF_SWITCHES = -c -tascii
NROFF_SWITCHES = -c -Tascii -wall -Wtab -Wrange -Wel -Wscale

# Not appropriate for creating Guidebook.txt.
# GUIDECMD = cat Guidebook.txt
#
# Single page. Might need adjustment to .pl value
# GUIDECMD= $(GUIDE_PREFORMAT) | perl -pe 's/^(.mt)$$/.pl 4720v\n.in 0\n.po 8\n.ll 64m\n$$1/' | nroff -c -Tascii | $(COLCMD)
#
GUIDECMD = $(GUIDE_PREFORMAT) | nroff $(NROFF_SWITCHES) | $(COLCMD)
ONEPAGECMD = $(ONEPAGE_PREFORMAT) | nroff $(NROFF_SWITCHES) | $(COLCMD) \
	| sed -e '/EOF--EOF/,12345D'

# Only generate output for the current configuration:
NHGREP = $(MAKEDEFS) --grep --input - --output -
# Generate output for all configurations:
#NHGREP = $(MAKEDEFS) --grep --input - --output - --grep-define ALLDOCS
# Fallback:
#NHGREP = cat

GUIDE_PREFORMAT = cat Guidebook.mn | $(NHGREP) | tbl tmac.n -
# for Guidebook.dat, unpaginated version of Guidebook.txt
ONEPAGE_PREFORMAT = cat Gbk-1pg-pfx.mn Guidebook.mn Gbk-1pg-sfx.mn \
	| $(NHGREP) | tbl tmac.n -

# the basic guidebook
Guidebook:	Guidebook.mn tmac.n tmac.nh $(MAKEDEFS) $(STRIPBS)
	-$(GUIDECMD) > Guidebook

# Fancier output for those with ditroff, psdit and a PostScript printer.
Guidebook.ps:	Guidebook.mn tmac.n tmac.nh
	$(GUIDE_PREFORMAT) | $(PSCMD) > Guidebook.ps

# Guidebook.tex is the same as Guidebook.mn but formatted with LaTeX.
# - The invocation command for LaTeX may vary in different installations.
# - To print Guidebook.dvi you need to use a suitable dvi-driver.
# - LaTeX needs to be run twice; second pass uses Guidebook.aux made by first.
Guidebook.dvi:	Guidebook.tex
	latex Guidebook.tex
	latex Guidebook.tex

../util/makedefs:
	( cd .. ; $(MAKE) makedefs )
../util/stripbs:
	( cd .. ; $(MAKE) stripbs )

GAME	= evilhack
MANDIR	= /usr/man/man6
MANEXT	= 6

# manual installation for most BSD-style systems
GAMEMANCREATE = cat evilhack.6 | $(NHGREP) >
LEVMANCREATE = cat lev_comp.6 | $(NHGREP) >
DGNMANCREATE = cat dgn_comp.6 | $(NHGREP) >
RCVRMANCREATE = cat recover.6 | $(NHGREP) >
DLBMANCREATE = cat dlb.6 | $(NHGREP) >
MDMANCREATE = cat makedefs.6 | $(NHGREP) >
# manual installation for most SYSV-style systems
# GAMEMANCREATE = cat evilhack.6 | $(NHGREP) | nroff -man - >
# LEVMANCREATE = cat lev_comp.6 | $(NHGREP) | nroff -man - >
# DGNMANCREATE = cat dgn_comp.6 | $(NHGREP) | nroff -man - >
# RCVRMANCREATE = cat recover.6 | $(NHGREP) | nroff -man - >
# DLBMANCREATE = cat dlb.6 | $(NHGREP) | nroff -man - >
# MDMANCREATE = cat makedefs.6 | $(NHGREP) | nroff -man - >

manpages:
	-$(GAMEMANCREATE) $(MANDIR)/$(GAME).$(MANEXT)
	-$(LEVMANCREATE) $(MANDIR)/lev_comp.$(MANEXT)
	-$(DGNMANCREATE) $(MANDIR)/dgn_comp.$(MANEXT)
	-$(RCVRMANCREATE) $(MANDIR)/recover.$(MANEXT)
	-$(DLBMANCREATE) $(MANDIR)/dlb.$(MANEXT)
	-$(MDMANCREATE) $(MANDIR)/makedefs.$(MANEXT)

# manual creation for distribution
DISTRIB = Guidebook.txt evilhack.txt lev_comp.txt dgn_comp.txt recover.txt \
	dlb.txt makedefs.txt

distrib: $(DISTRIB)
	@echo "Plain text documentation is up to date."

Guidebook.txt	: Gbk-1pg-pfx.mn Gbk-1pg-sfx.mn Guidebook.mn tmac.n tmac.nh
	$(ONEPAGECMD) > Guidebook.txt
Guidebook.dat	: Gbk-1pg-pfx.mn Gbk-1pg-sfx.mn Guidebook.mn tmac.n tmac.nh
	$(ONEPAGECMD) > Guidebook.dat

MAN2TXT = $(NHGREP) | nroff -man - | $(COLCMD)
evilhack.txt	: evilhack.6
	cat evilhack.6 | $(MAN2TXT) > evilhack.txt
lev_comp.txt	: lev_comp.6
	cat lev_comp.6 | $(MAN2TXT) > lev_comp.txt
dgn_comp.txt	: dgn_comp.6
	cat dgn_comp.6 | $(MAN2TXT) > dgn_comp.txt
recover.txt	: recover.6
	cat recover.6 | $(MAN2TXT) > recover.txt
dlb.txt		: dlb.6
	cat dlb.6 | $(MAN2TXT) > dlb.txt
makedefs.txt		: makedefs.6
	cat makedefs.6 | $(MAN2TXT) > makedefs.txt

clean:
	-rm -f Guidebook.aux Guidebook.log

spotless: clean
	-rm -f Guidebook Guidebook.dat Guidebook.ps Guidebook.dvi

maintainer-clean: spotless
	-rm -f $(DISTRIB)
#	-rm -f Makefile
### End Makefile.doc

###
### Start hints/linux POST
###
### End hints/linux POST
