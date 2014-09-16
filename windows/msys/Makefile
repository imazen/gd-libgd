
# Simple makefile for building and testing libgd under MSYS/MinGW on
# Windows


# The version
LIBVER=3.0.1

# Misc. config flags.
CDEFS=-DHAVE_ERRNO_H -DHAVE_ICONV -DHAVE_ICONV_H		\
-DHAVE_ICONV_T_DEF -DHAVE_INTTYPES_H -DHAVE_LIMITS_H -DHAVE_STDDEF_H	\
-DHAVE_STDINT_H -DHAVE_STDLIB_H -DHAVE_VISIBILITY -DICONV_CONST

# GnuWin32 libs should all be installed in one place.
#GNUDIR=/C/Qt/Qt5.3.1/Tools/mingw482_32/i686-w64-mingw32
#GNUINC=-I$(GNUDIR)/include
#GNULIB=-L$(GNUDIR)/lib
GNUDLL=$(GNUDIR)/bin/

# Various optional components.  Comment-out the ones you don't have
# and edit the paths and options as needed if you do.  The default
# assumes GnuWin32 packages installed in /c/Program Files/GnuWin32.
JPEG_D=-DHAVE_LIBJPEG
JPEG_L=-ljpeg
JPEG_I=-I"../gd-msys-dependencies/libjpeg/include"
JPEG_LIBDIR=-L"../gd-msys-dependencies/libjpeg/lib"
JPEG_DLLDIR=$(GNUDLL)

PNG_D=-DHAVE_LIBPNG
PNG_L=-lpng
PNG_I=				-I"../gd-msys-dependencies/libpng/include"
PNG_LIBDIR=			-L"../gd-msys-dependencies/libpng/lib"
PNG_DLLDIR=			#$(GNUDLL)

TIFF_D=-DHAVE_LIBTIFF
TIFF_L=-ltiff
TIFF_I=				-I"../gd-msys-dependencies/libtiff/include"
TIFF_LIBDIR=		-L"../gd-msys-dependencies/libtiff/lib"
TIFF_DLLDIR=		#$(GNUDLL)

LIBZ_D=-DHAVE_LIBZ
LIBZ_L=-lz
LIBZ_I=				#$(GNUINC)
LIBZ_LIBDIR=		-L"../gd-msys-dependencies/zlib/lib"
LIBZ_DLLDIR=		#$(GNUDLL)

# LIBXPM_D=-DHAVE_LIBXPM
# LIBXPM_L=-lxpm
# LIBXPM_I=			#$(GNUINC)
# LIBXPM_LIBDIR=		#$(GNULIB)

FREETYPE_D=-DHAVE_LIBFREETYPE -DHAVE_FT2BUILD_H
FREETYPE_L=-lfreetype
FREETYPE_I=-I"../gd-msys-dependencies/libfreetype/include" -I"../gd-msys-dependencies/libfreetype/include/freetype2"
FREETYPE_LIBDIR=	-L"../gd-msys-dependencies/libfreetype/lib"
FREETYPE_DLLDIR=	#$(GNUDLL)

# FONTCONFIG_D=-DHAVE_LIBFONTCONFIG
# FONTCONFIG_L=
# FONTCONFIG_I=
# FONTCONFIG_LIBDIR=

ALL_D=$(FREETYPE_D) $(JPEG_D) $(PNG_D) $(TIFF_D) $(LIBZ_D) $(LIBXPM_D)
ALL_L=$(FREETYPE_L) $(JPEG_L) $(PNG_L) $(TIFF_L) $(LIBZ_L) $(LIBXPM_L)-lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -liconv
ALL_I=$(FREETYPE_I) $(JPEG_I) $(PNG_I) $(TIFF_I) $(LIBZ_I) $(LIBXPM_I)
ALL_LIBDIR=$(FREETYPE_LIBDIR) $(JPEG_LIBDIR) $(PNG_LIBDIR) $(TIFF_LIBDIR) \
	$(LIBZ_LIBDIR) $(LIBXPM_LIBDIR)
ALL_DLLDIR=$(FREETYPE_DLLDIR) $(JPEG_DLLDIR) $(PNG_DLLDIR) $(TIFF_DLLDIR) \
	$(LIBZ_DLLDIR) $(LIBXPM_DLLDIR)

# We need libiconv for internationalization.  We default to static
# linking because that reduces the number of dependencies.  However,
# libiconv is released under the GNU GPL which may impose extra
# restrictions on redistribution.
#LIBICONV=-L"../gd-msys-dependencies/libiconv/libiconv.a"
#LIBICONV=-liconv


DEFS=$(CDEFS) $(ALL_D)
INCLUDES=$(ALL_I)

CC=gcc
CFLAGS=-g -O2 -I. -std=gnu99 -fvisibility=hidden -static-libgcc \
	-D_WIN32 -DBGDWIN32 $(DEFS) $(INCLUDES)

LD=gcc
LDFLAGS=-g -O2 -fvisibility=hidden -static-libgcc $(ALL_LIBDIR)
LIBS=$(ALL_L) $(LIBICONV)

ZIP=zip -j9
DIST=libgd-win.zip

# Get this list from c files in libgd_la_SOURCES in Makefile.mk
SRC=gd.c gd_color.c gd_color_map.c gd_transform.c gdfx.c			\
gd_security.c gd_gd.c gd_gd2.c gd_io.c gd_io_dp.c gd_gif_in.c		\
gd_gif_out.c gd_io_file.c gd_io_ss.c gd_jpeg.c gd_png.c gd_ss.c		\
gd_topal.c gd_wbmp.c gdcache.c gdfontg.c gdfontl.c gdfontmb.c		\
gdfonts.c gdfontt.c gdft.c gdhelpers.c gdkanji.c gdtables.c gdxpm.c	\
wbmp.c gd_filter.c gd_nnquant.c gd_rotate.c gd_matrix.c				\
gd_interpolation.c gd_crop.c webpimg.c gd_webp.c gd_tiff.c gd_tga.c	\
gd_bmp.c gd_xbm.c gd_color_match.c gd_version.c gd_filename.c

OBJ=$(SRC:.c=.o)

TARGETBASE=libgd
TARGET=$(TARGETBASE).dll
TARGET_A=$(TARGETBASE).a

all:
	(cd ../../src && mingw32-make -f ../windows/msys/Makefile $(TARGET))

# BUG: this sucks in all the DLLs in the lib installation directory,
# including those you may not need.
dist: all
	(cd ../.. && $(ZIP) $(DIST) src/*.dll src/*.a $$(for d in $(ALL_DLLDIR); do echo $$d/*.dll; done | sort -u) )


clean:
	del /q /f ..\..\$(DIST)
	(cd ../../src && del /q /f *.dll *.a $(OBJ))

check: all
	bash run_tests.sh "$(GNUDIR)/bin" "$(INCLUDES)"

$(TARGET): $(OBJ)
	gcc -shared -o $(TARGET) $(LDFLAGS) -Wl,--out-implib,$(TARGET_A) \
		$(OBJ) $(LIBS)










