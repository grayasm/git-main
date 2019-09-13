/*
	Copyright (C) 2017 Mihai Vasilian

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com
*/

#ifndef __TradingSettings_hpp__
#define __TradingSettings_hpp__

#include "string.hpp"
#include <O2GEnum.h>


namespace fxcm
{
	class TradingSettings
	{
		void Init();
	public:
		TradingSettings();
		~TradingSettings();
		TradingSettings(const TradingSettings& tc);
		TradingSettings& operator=(const TradingSettings& tc);

		const stl::string& GetInstrument() const;
		void SetInstrument(const stl::string& instrument);

		int GetCondDistStopForTrade() const;
		void SetCondDistStopForTrade(int val);		
		
		int GetCondDistLimitForTrade() const;
		void SetCondDistLimitForTrade(int val);
		
		int GetCondDistEntryStop() const;
		void SetCondDistEntryStop(int val);
		
		int GetCondDistEntryLimit() const;
		void SetCondDistEntryLimit(int val);

		int GetMinQuantity() const;
		void SetMinQuantity(int val);

		int GetMaxQuantity() const;
		void SetMaxQuantity(int val);

		int	GetBaseUnitSize() const;
		void SetBaseUnitSize(int val);

		O2GMarketStatus GetMarketStatus() const;
		void SetMarketStatus(O2GMarketStatus ms);

		int GetMinTrailingStep() const;
		void SetMinTrailingStep(int val);

		int GetMaxTrailingStep() const;
		void SetMaxTrailingStep(int val);

		double GetMMR() const;
		void SetMMR(double val);

		double GetMMR2() const;
		void SetMMR2(double val);

		double GetEMR() const;
		void SetEMR(double val);

		double GetLMR() const;
		void SetLMR(double val);

	private:
		stl::string	m_instrument;
		int				m_condDistStopForTrade;
		int				m_condDistLimitForTrade;
		int				m_condDistEntryStop;
		int				m_condDistEntryLimit;
		int				m_minQuantity;
		int				m_maxQuantity;
		int				m_baseUnitSize;
		O2GMarketStatus		m_marketStatus;
		int				m_minTrailingStep;
		int				m_maxTrailingStep;
		double			m_mmr;
		double			m_mmr2;
		double			m_emr;
		double			m_lmr;
	};
} // namespace

#endif // __TradingSettings_hpp__