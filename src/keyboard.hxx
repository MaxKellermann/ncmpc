/* ncmpc (Ncurses MPD Client)
 * (c) 2004-2018 The Music Player Daemon Project
 * Project homepage: http://musicpd.org
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <boost/asio/posix/stream_descriptor.hpp>

#include <curses.h>

namespace boost { namespace asio { class io_service; }}

class UserInput {
	boost::asio::posix::stream_descriptor d;
	WINDOW &w;

public:
	UserInput(boost::asio::io_service &io_service, WINDOW &_w);

private:
	void AsyncWait() {
		d.async_read_some(boost::asio::null_buffers(),
				  std::bind(&UserInput::OnReadable, this,
					    std::placeholders::_1));
	}

	void OnReadable(const boost::system::error_code &error);
};

void
keyboard_unread(boost::asio::io_service &io_service, int key);

#endif
