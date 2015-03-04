#
#             (c) 2009 Pierre Gaufillet <pierre.gaufillet@magic.fr> 
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
#
# $Id: Makefile.am,v 1.7 2009-08-22 12:51:41 gaufille Exp $
#

AUTOMAKE_OPTIONS=nostdinc subdir-objects
AM_CPPFLAGS=-DDATADIR="\"$(pkgdatadir)\"" -DSYSCONFDIR="\"$(sysconfdir)\"" -I.
AM_CXXFLAGS=-Wall -Wundef -Wpointer-arith -Wcast-qual -Wcast-align \
	-Wwrite-strings -Werror

noinst_LIBRARIES=libcommon.a
bin_PROGRAMS=odyssey

libcommon_a_SOURCES=ConfigFile.cxx ConfigFile.h \
	Util.cxx Util.h DataBuffer.cxx DataBuffer.h \
	HexFile.cxx HexFile.h HexFile_ihx16.cxx HexFile_ihx8.cxx \
	ParallelPort.cxx ParallelPort.h IO.cxx IO.h \
	Device.cxx Device.h device/PicDevice.h device/PicDevice.cxx \
	device/Pic16Device.cxx device/Pic16f8xxDevice.cxx \
	device/Pic16f81xDevice.cxx \
	device/Pic16f7xDevice.cxx device/Pic18Device.cxx \
	device/Pic12f6xxDevice.cxx\
	device/Pic16f6xxDevice.cxx device/Pic16f6xxADevice.cxx \
	device/Pic16f87xADevice.cxx device/Pic18f2xx0Device.cxx
EXTRA_libcommon_a_SOURCES=DirectPPIO.cxx DirectPPIO.h \
	LinuxPPDevIO.cxx LinuxPPDevIO.h

libcommon_a_LIBADD=
if ENABLE_LINUX_PPDEV
libcommon_a_LIBADD+=LinuxPPDevIO.o
endif
if ENABLE_DIRECTIO
libcommon_a_LIBADD+=DirectPPIO.o
endif

odyssey_SOURCES=main.cxx
odyssey_LDADD=libcommon.a
