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
# $Id: Makefile.am,v 1.1 2009-08-22 12:51:41 gaufille Exp $
#

dist_man_MANS=odyssey.1 pic.conf.5
dist_doc_DATA=odyssey-man.html pic.conf-man.html

odyssey-man.html: odyssey.1
	man2html $< > $@

pic.conf-man.html: pic.conf.5
	man2html $< > $@
