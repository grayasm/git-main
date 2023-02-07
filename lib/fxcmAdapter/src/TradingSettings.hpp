/*
Copyright (C) 2017 Mihai Vasilian
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