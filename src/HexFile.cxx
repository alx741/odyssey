/* Copyright (C) 2002-2003  Mark Andrew Aikens <marka@desert.cx>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: HexFile.cxx,v 1.4 2010-11-23 18:43:31 gaufille Exp $
 */
using namespace std;

#include <stdexcept>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include "HexFile.h"


HexFile *HexFile::load(char *filename) {
	FILE *fp;
	char buf[100];
	int i, len;

	fp = fopen(filename, "r");
	if(fp == NULL)
		throw runtime_error(strerror(errno));
	if(fgets(buf, sizeof(buf), fp) == NULL)
		throw runtime_error(strerror(errno));

	/* Detect the file type */
	if(sscanf(buf, ":%02X", &i) == 1) {	/* Intel hex */
		len = strlen(buf) - 12;	/* Don't count line prefix and \n char */
		if(i == len/2) {
			return new HexFile_ihx8(fp, HEXFILE_READ);
		} else if(i == len/4) {
			return new HexFile_ihx16(fp, HEXFILE_READ);
		}
	}
	fclose(fp);
	throw runtime_error("Unknown HEX file type.");
}


HexFile::HexFile(FILE *fp, hexfile_mode_t mode) {
	this->mode = mode;;
	this->fp = fp;
	rewind(fp);
}


HexFile::HexFile(char *filename, hexfile_mode_t mode) {
	this->mode = mode;
	this->fp = fopen(filename, (mode == HEXFILE_WRITE) ? "w+" : "r");
	if(this->fp == NULL)
		throw runtime_error(strerror(errno));
}


HexFile::~HexFile(void) {
	fclose(fp);
}
