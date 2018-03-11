/*
	Copyright (C) 2018 Mihai Vasilian

	This program is free software; you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation; either version 2 of the License, or (at your
	option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program. If not, see http://www.gnu.org/licenses/.

	contact: grayasm@gmail.com
*/

#ifndef __HistoryFxcmliveReader_hpp__
#define __HistoryFxcmliveReader_hpp__

#include "vector.hpp"
#include "string.hpp"
#include "Offer.hpp"

class HistoryFxcmliveReader
{
public:
	HistoryFxcmliveReader(const misc::string& instrument);
	~HistoryFxcmliveReader();
	HistoryFxcmliveReader(const HistoryFxcmliveReader&) = delete;
	HistoryFxcmliveReader& operator=(const HistoryFxcmliveReader&) = delete;

	// return all recorded offers in receiving order; false if at the end;
	bool GetOffer(fx::Offer& offer);


private:
	void ParseFile(const misc::string& filePath,
		misc::vector<fx::Offer>& result);

private:
	misc::string	m_instrument;
	misc::vector<misc::string>	m_offerFileVec;
	int	m_ofvPos;
	misc::vector<fx::Offer>	m_offersVec;
	int	m_ovPos;
};

#endif // __HistoryFxcmliveReader_hpp__
