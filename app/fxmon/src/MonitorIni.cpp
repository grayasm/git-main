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

#include "MonitorIni.hpp"
#include "strtok.hpp"
#include "stream.hpp"
#include "strconv.hpp"


misc::string g_section("monitor");
misc::string g_quoteUpdateTimeout("quoteUpdateTimeout");
misc::string g_keepStrategyInProfit("keepStrategyInProfit");
misc::string g_keepStrategyInLoss("keepStrategyInLoss");
misc::string g_dumpStrategyOutcome("dumpStrategyOutcome");
misc::string g_connection("connection");
misc::string g_marketPlugin("marketPlugin");
//connection=Demo
//connection=Real
//connection=PriceGenerator
misc::string g_priceGeneratorCurrency("priceGeneratorCurrency");
misc::string g_priceGeneratorTrendChance("priceGeneratorTrendChance");
misc::string g_priceGeneratorTrendFragmentation("priceGeneratorTrendFragmentation");
misc::string g_priceGeneratorVolatility("priceGeneratorVolatility");
//connection=HistoryPrices
misc::string g_dateFrom("dateFrom");
misc::string g_dateTo("dateTo");
//dateFrom=8.11.2014 00:00:00
//dateTo  =8.11.2014 01:00:00
misc::string g_auditFile("auditFile");



MonitorIni::MonitorIni()
{
}

MonitorIni::MonitorIni(const misc::string& inifile)	
{
	misc::iniserv iniReader(inifile);

	misc::string emptys("");

	m_iniFile = inifile;
	m_section = g_section;
	m_quoteUpdateTimeout = iniReader.get(m_section, g_quoteUpdateTimeout, double(0));
	m_keepStrategyInProfit = iniReader.get(m_section, g_keepStrategyInProfit, false);
	m_keepStrategyInLoss = iniReader.get(m_section, g_keepStrategyInLoss, false);
	m_dumpStrategyOutcome = iniReader.get(m_section, g_dumpStrategyOutcome, true);
	m_connection = iniReader.get(m_section, g_connection, emptys);
	m_marketPlugin = iniReader.get(m_section, g_marketPlugin, emptys);
	m_priceGeneratorCurrency = iniReader.get(m_section, g_priceGeneratorCurrency, emptys);
	m_priceGeneratorTrendChance = iniReader.get(m_section, g_priceGeneratorTrendChance, int(0));
	m_priceGeneratorTrendFragmentation = iniReader.get(m_section, g_priceGeneratorTrendFragmentation, int(0));
	m_priceGeneratorVolatility = iniReader.get(m_section, g_priceGeneratorVolatility, double(0));
	m_dateFrom = iniReader.get(m_section, g_dateFrom, emptys);
	m_dateTo = iniReader.get(m_section, g_dateTo, emptys);
	m_auditFile = iniReader.get(m_section, g_auditFile, emptys);
}

MonitorIni::~MonitorIni()
{	
}

MonitorIni::MonitorIni(const MonitorIni& tc)
{
	*this = tc;
}

MonitorIni& MonitorIni::operator=(const MonitorIni& tc)
{
	if(this != &tc)
	{
		m_section = tc.m_section;
		m_quoteUpdateTimeout = tc.m_quoteUpdateTimeout;
		m_keepStrategyInProfit = tc.m_keepStrategyInProfit;
		m_keepStrategyInLoss = tc.m_keepStrategyInLoss;
		m_dumpStrategyOutcome = tc.m_dumpStrategyOutcome;
		m_connection = tc.m_connection;
		m_marketPlugin = tc.m_marketPlugin;
		m_priceGeneratorCurrency = tc.m_priceGeneratorCurrency;
		m_priceGeneratorTrendChance = tc.m_priceGeneratorTrendChance;
		m_priceGeneratorTrendFragmentation = tc.m_priceGeneratorTrendFragmentation;
		m_priceGeneratorVolatility = tc.m_priceGeneratorVolatility;
		m_dateFrom = tc.m_dateFrom;
		m_dateTo = tc.m_dateTo;
		m_auditFile = tc.m_auditFile;
	}
	return *this;
}

void MonitorIni::SetQuoteUpdateTimeout(double sec)
{
	m_quoteUpdateTimeout = sec;
}

double MonitorIni::GetQuoteUpdateTimeout() const
{
	return m_quoteUpdateTimeout;
}

bool MonitorIni::GetKeepStrategyInProfit() const
{
	return m_keepStrategyInProfit;
}

void MonitorIni::SetKeepStrategyInProfit(bool value)
{
	m_keepStrategyInProfit = value;
}

bool MonitorIni::GetKeepStrategyInLoss() const
{
	return m_keepStrategyInLoss;
}

void MonitorIni::SetKeepStrategyInLoss(bool value)
{
	m_keepStrategyInLoss = value;
}

bool MonitorIni::GetDumpStrategyOutcome() const
{
	return m_dumpStrategyOutcome;
}

void MonitorIni::SetDumpStrategyOutcome(bool value)
{
	m_dumpStrategyOutcome = value;
}

const misc::string& MonitorIni::GetConnection() const
{
	return m_connection;
}

void MonitorIni::SetConnection(const misc::string& value)
{
	m_connection = value;
}

const misc::string& MonitorIni::GetMarketPlugin() const
{
	return m_marketPlugin;
}

void MonitorIni::SetMarketPlugin(const misc::string& value)
{
	m_marketPlugin = value;
}

fx::Currency MonitorIni::GetPriceGeneratorCurrency() const
{
	misc::string sline = m_priceGeneratorCurrency;

	misc::strtok tokenizer(sline, ";");
	if(tokenizer.count() < 6)
	{
		misc::cout << "\nMonitor \"currency\" parameter is not recognized";
		return fx::Currency();
	}

	const misc::strtok::Tokens& elems = tokenizer.tokens();
	misc::string symbol = elems[0];
	misc::trim(symbol);
	double buy = 0; misc::to_value(elems[1], buy);
	double sell= 0; misc::to_value(elems[2], sell);
	double margin = 0; misc::to_value(elems[3], margin);
	double pipcost= 0; misc::to_value(elems[4], pipcost);
	double rate2pip=0; misc::to_value(elems[5], rate2pip);

	return fx::Currency(symbol, fx::Price(buy, sell), margin, pipcost, rate2pip);
}

void MonitorIni::SetPriceGeneratorCurrency(const fx::Currency& currency)
{
	misc::string sline;
	sline += currency.GetSymbol(); sline += " ; ";	
	sline += misc::from_value(currency.GetPrice().GetBuy(), 5); sline += " ; ";
	sline += misc::from_value(currency.GetPrice().GetSell(), 5); sline += " ; ";

	sline += misc::from_value(currency.GetMargin(), 1); sline += " ; ";
	sline += misc::from_value(currency.GetPipCost(), 3); sline += " ; ";
	sline += misc::from_value(currency.GetRate2Pip(), 1); sline += " ; ";

	m_priceGeneratorCurrency = sline;
}

void MonitorIni::SetPriceGeneratorTrendChance(int value)
{
	m_priceGeneratorTrendChance = value;
}

int MonitorIni::GetPriceGeneratorTrendChance() const
{
	return m_priceGeneratorTrendChance;
}

void MonitorIni::SetPriceGeneratorTrendFragmentation(int value)
{
	m_priceGeneratorTrendFragmentation = value;
}

int MonitorIni::GetPriceGeneratorTrendFragmentation() const
{
	return m_priceGeneratorTrendFragmentation;
}

void MonitorIni::SetPriceGeneratorVolatility(double value)
{
	m_priceGeneratorVolatility = value;
}

double MonitorIni::GetPriceGeneratorVolatility() const
{
	return m_priceGeneratorVolatility;
}

const misc::string& MonitorIni::GetDateFrom() const
{
	return m_dateFrom;
}

void MonitorIni::SetDateFrom(const misc::string& value)
{
	m_dateFrom = value;
}

const misc::string& MonitorIni::GetDateTo() const
{
	return m_dateTo;
}

void MonitorIni::SetDateTo(const misc::string& value)
{
	m_dateTo = value;
}

const misc::string& MonitorIni::GetAuditFile() const
{
	return m_auditFile;
}

void MonitorIni::SetAuditFile(const misc::string& filepath)
{
	m_auditFile = filepath;
}


bool MonitorIni::SaveIni()
{
	misc::iniserv iniWriter(m_iniFile);

	iniWriter.set(m_section, g_quoteUpdateTimeout, m_quoteUpdateTimeout);
	iniWriter.set(m_section, g_keepStrategyInProfit, m_keepStrategyInProfit);
	iniWriter.set(m_section, g_keepStrategyInLoss, m_keepStrategyInLoss);
	iniWriter.set(m_section, g_dumpStrategyOutcome, m_dumpStrategyOutcome);
	iniWriter.set(m_section, g_connection, m_connection);
	iniWriter.set(m_section, g_marketPlugin, m_marketPlugin);
	iniWriter.set(m_section, g_priceGeneratorCurrency, m_priceGeneratorCurrency);
	iniWriter.set(m_section, g_priceGeneratorTrendChance, m_priceGeneratorTrendChance);
	iniWriter.set(m_section, g_priceGeneratorTrendFragmentation, m_priceGeneratorTrendFragmentation);
	iniWriter.set(m_section, g_priceGeneratorVolatility, m_priceGeneratorVolatility);
	iniWriter.set(m_section, g_dateFrom, m_dateFrom);
	iniWriter.set(m_section, g_dateTo, m_dateTo);
	iniWriter.set(m_section, g_auditFile, m_auditFile);
	
	return iniWriter.write();
}
