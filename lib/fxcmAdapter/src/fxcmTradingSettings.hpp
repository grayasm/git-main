/*
  Copyright (C) 2014 Mihai Vasilian

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


#ifndef __fxcmTradingSettings_hpp__
#define __fxcmTradingSettings_hpp__


// c
#include <stdlib.h> // NULL undefined in io2gtable.h(101)
// c++
#include <map>
// fxcm
#include "ForexConnect.h"

// local
#include "autoptr.hpp"
#include "stream.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "event.hpp"
#include "critical_section.hpp"
#include "fxcmIniParams.hpp"



namespace fxcm
{
	struct SymbolSettings
	{
		int	m_condDistStopForTrade;
		int	m_condDistLimitForTrade;
		int	m_condDistEntryStop;
		int	m_condDistEntryLimit;
		int	m_minQuantity;
		int	m_maxQuantity;
		int	m_baseUnitSize;
		O2GMarketStatus	m_marketStatus;
		double m_MMR;
		double m_MMR2;
		double m_EMR;
		double m_LMR;
		bool m_ThreeLM;
	};

	struct GeneralSettings
	{
		int m_minTrailingStep;
		int m_maxTrailingStep;
	};


	class TradingSettings
	{
	public:
		typedef misc::autoptr<TradingSettings>		Ptr;

	public:
		TradingSettings();
		~TradingSettings();
		TradingSettings(const TradingSettings& tc);
		TradingSettings& operator=(const TradingSettings& tc);

		bool CheckTradingSettings(
			const fxcm::IniParams& iniParams,
			IO2GSession* session,
			misc::vector<misc::string>& symbols);
		void Clear();

		const SymbolSettings& GetTradingSettings(const misc::string& symbol) const;
		const GeneralSettings& GetTradingSettings() const;

	private:
		void Init();
		void Destroy();

	private:
		std::map<misc::string, SymbolSettings>	m_symSettingsMap;
		GeneralSettings							m_genSettings;
	};

} // namespace


#endif // __fxcmTradingSettings_hpp__