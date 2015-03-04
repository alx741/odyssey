/* Copyright (C) 2007-2008  Renato Barbosa Santiago <rbsanti@iconect.com.br>
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
 * $Id: Pic16f6xxADevice.cxx,v 1.1 2008-08-25 21:47:50 gaufille Exp $
 */
using namespace std;

#include <stdio.h>
#include <stdexcept>
#include "PicDevice.h"
#include "Util.h"


Pic16f6xxADevice::Pic16f6xxADevice(char *name) : Pic16Device(name) {
}


Pic16f6xxADevice::~Pic16f6xxADevice() {
}

void Pic16f6xxADevice::set_program_mode(void) {
	/* Power up the PIC and put it in program/verify mode */
	this->io->set_lvp(false);		/* Disable LVP */
	this->io->set_clk(false);		/* Set RB6 low */
	this->io->set_data(false);		/* Set RB7 low */
	this->io->set_vpp(true);		/* Raise Vpp while RB6(Clock) & RB7(Data) are low */
	this->io->usleep(5);			/* Tppdp in programming specs*/
	this->io->set_pwr(true);
	this->io->usleep(5);			/* Thld0 in programming specs*/
}

bool Pic16f6xxADevice::program_cycle(uint32_t data, uint32_t mask) {
	this->write_prog_data(data);
	this->write_command(COMMAND_BEGIN_PROG_ONLY);
	this->io->usleep(this->program_time);
	if(this->flags & PIC_REQUIRE_EPROG)
		this->write_command(COMMAND_END_PROG);

	if((read_prog_data() & mask) == (data & mask)) return true;
	return false;
}

void Pic16f6xxADevice::bulk_erase(void) {
	try {
		/* Bulk Erase Program Memory */
		/*   Set PC to config memory (to erase ID locations) */
		/*   Do a "Load Data All 1's" command. */
		/*   Do a "Bulk Erase Program Memory" command. */
		/*   Wait erase_time to complete bulk erase. */
		this->set_program_mode();

		/* Set PC to start of configuration memory (0x2000) */
		this->write_command(COMMAND_LOAD_CONFIG);
		this->io->shift_bits_out(0x3ffe, 16); /* Dummy write of all 1's */

		this->write_command(COMMAND_LOAD_PROG_DATA);
;		this->io->shift_bits_out(0x3FFF, 16, 1);
		this->io->usleep(1);
		this->write_command(COMMAND_ERASE_PROG_MEM);
		this->io->usleep(this->erase_time);

		if(this->flags & PIC_FEATURE_EEPROM) {
			/* Bulk Erase Data Memory */
			/*   Do a "Bulk Erase Data Memory" command. */
			/*   Wait erase_time to complete bulk erase. */
			this->write_command(COMMAND_ERASE_DATA_MEM);
			this->io->usleep(this->erase_time);
		}
		this->pic_off();
	} catch(std::exception& e) {
		this->pic_off();
		throw;
	}
}

void Pic16f6xxADevice::program(DataBuffer& buf) {
	this->bulk_erase();
	Pic16Device::program(buf);
}

void Pic16f6xxADevice::disable_codeprotect(void) {
	// Don't Need. this->bulk_erase() do all needed work.
}
