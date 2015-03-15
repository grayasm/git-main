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


#ifndef __MonitorIni_hpp__
#define __MonitorIni_hpp__



#include "string.hpp"
#include "iniserv.hpp"
#include "Currency.hpp"


class MonitorIni
{
public:
	MonitorIni();
	MonitorIni(const misc::string& inifile);
	~MonitorIni();
	MonitorIni(const MonitorIni&);
	MonitorIni& operator=(const MonitorIni&);
	
	void SetQuoteUpdateTimeout(double sec);
	double GetQuoteUpdateTimeout() const;

	bool GetKeepStrategyInProfit() const;
	void SetKeepStrategyInProfit(bool value);

	bool GetKeepStrategyInLoss() const;
	void SetKeepStrategyInLoss(bool value);

	bool GetDumpStrategyOutcome() const;
	void SetDumpStrategyOutcome(bool value);

	const misc::string& GetConnection() const;
	void SetConnection(const misc::string& value);

	const misc::string& GetMarketPlugin() const;
	void SetMarketPlugin(const misc::string& value);

	fx::Currency GetPriceGeneratorCurrency() const;
	void SetPriceGeneratorCurrency(const fx::Currency& currency);

	void SetPriceGeneratorTrendChance(int value);
	int GetPriceGeneratorTrendChance() const;

	void SetPriceGeneratorTrendFragmentation(int value);
	int GetPriceGeneratorTrendFragmentation() const;

	void SetPriceGeneratorVolatility(double value);
	double GetPriceGeneratorVolatility() const;

	//TODO: implement some canonical date variable/struct/class.
	const misc::string& GetDateFrom() const;
	void SetDateFrom(const misc::string& value);	// m.d.Y H:M:S

	const misc::string& GetDateTo() const;
	void SetDateTo(const misc::string& value);

	const misc::string& GetAuditFile() const;
	void SetAuditFile(const misc::string& filepath);

	bool SaveIni();

private:
	misc::iniserv		m_inisrv;
};


#endif // __MonitorIni_hpp__

