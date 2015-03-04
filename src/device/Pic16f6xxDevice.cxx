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
 * $Id: Pic16f6xxDevice.cxx,v 1.1 2008-08-25 21:47:50 gaufille Exp $
 */
using namespace std;

#include <cstdio>
#include <stdexcept>
#include "PicDevice.h"
#include "Util.h"


Pic16f6xxDevice::Pic16f6xxDevice(char *name) : Pic16Device(name) {
}


Pic16f6xxDevice::~Pic16f6xxDevice() {
}


void Pic16f6xxDevice::bulk_erase(void) {
	try {
		this->set_program_mode();

		/* This clears the config word. XXX: TESTME */
		this->write_command(COMMAND_LOAD_CONFIG);
		this->io->shift_bits_out(0x7ffe, 16);
		this->io->usleep(1);
		for(int i=0; i<7; i++)
			this->write_command(COMMAND_INC_ADDRESS);
		this->write_command(COMMAND_BULK_ERASE_SETUP1);
		this->write_command(COMMAND_BULK_ERASE_SETUP2);
		this->write_command(COMMAND_BEGIN_PROG);
		this->io->usleep(this->erase_time + this->program_time);
		this->write_command(COMMAND_BULK_ERASE_SETUP1);
		this->write_command(COMMAND_BULK_ERASE_SETUP2);

		/* This should erase the ID & program memory */
		this->write_prog_data(0x3fff);
		this->write_command(COMMAND_ERASE_PROG_MEM);
		this->write_command(COMMAND_BEGIN_PROG);
		this->io->usleep(this->erase_time);

		if(this->flags & PIC_FEATURE_EEPROM) {
			/* This clears the data EEPROM */
			this->write_ee_data(0x3fff);
			this->write_command(COMMAND_ERASE_DATA_MEM);
			this->write_command(COMMAND_BEGIN_PROG);
			this->io->usleep(this->erase_time);
		}

		this->pic_off();
	} catch(std::exception& e) {
		this->pic_off();
		throw;
	}
}


void Pic16f6xxDevice::disable_codeprotect(void) {
	bulk_erase();
}
