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
	m_inisrv = misc::iniserv(inifile);
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
		m_inisrv = tc.m_inisrv;
	}
	return *this;
}

void MonitorIni::SetQuoteUpdateTimeout(double sec)
{
	m_inisrv.set(g_section, g_quoteUpdateTimeout, sec);
}

double MonitorIni::GetQuoteUpdateTimeout() const
{
	double defval = 0;
	return m_inisrv.get(g_section, g_quoteUpdateTimeout, defval);
}

bool MonitorIni::GetKeepStrategyInProfit() const
{
	bool defval = false; // conservative
	return m_inisrv.get(g_section, g_keepStrategyInProfit, defval);
}

void MonitorIni::SetKeepStrategyInProfit(bool value)
{
	m_inisrv.set(g_section, g_keepStrategyInProfit, value);
}

bool MonitorIni::GetKeepStrategyInLoss() const
{
	bool defval = false;	// safety
	return m_inisrv.get(g_section, g_keepStrategyInLoss, defval);
}

void MonitorIni::SetKeepStrategyInLoss(bool value)
{
	m_inisrv.set(g_section, g_keepStrategyInLoss, value);
}

bool MonitorIni::GetDumpStrategyOutcome() const
{
	bool defval = true;		// safety
	return m_inisrv.get(g_section, g_dumpStrategyOutcome, defval);
}

void MonitorIni::SetDumpStrategyOutcome(bool value)
{
	m_inisrv.set(g_section, g_dumpStrategyOutcome, value);
}

const misc::string& MonitorIni::GetConnection() const
{
	misc::string defval("");
	return m_inisrv.get(g_section, g_connection, defval);
}

void MonitorIni::SetConnection(const misc::string& value)
{
	m_inisrv.set(g_section, g_connection, value);
}

const misc::string& MonitorIni::GetMarketPlugin() const
{
	misc::string defval("");
	return m_inisrv.get(g_section, g_marketPlugin, defval);
}

void MonitorIni::SetMarketPlugin(const misc::string& value)
{
	m_inisrv.set(g_section, g_marketPlugin, value);
}

fx::Currency MonitorIni::GetPriceGeneratorCurrency() const
{
	misc::string defval("");
	misc::string sline = m_inisrv.get(g_section, g_priceGeneratorCurrency, defval);

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

	m_inisrv.set(g_section, g_priceGeneratorCurrency, sline);
}

void MonitorIni::SetPriceGeneratorTrendChance(int value)
{
	m_inisrv.set(g_section, g_priceGeneratorTrendChance, value);
}

int MonitorIni::GetPriceGeneratorTrendChance() const
{
	int defval=0;
	return m_inisrv.get(g_section, g_priceGeneratorTrendChance, defval);
}

void MonitorIni::SetPriceGeneratorTrendFragmentation(int value)
{
	m_inisrv.set(g_section, g_priceGeneratorTrendFragmentation, value);
}

int MonitorIni::GetPriceGeneratorTrendFragmentation() const
{
	int defval=0;
	return m_inisrv.get(g_section, g_priceGeneratorTrendFragmentation, defval);
}

void MonitorIni::SetPriceGeneratorVolatility(double value)
{
	m_inisrv.set(g_section, g_priceGeneratorVolatility, value);
}

double MonitorIni::GetPriceGeneratorVolatility() const
{
	double defval = 0;
	return m_inisrv.get(g_section, g_priceGeneratorVolatility, defval);
}

const misc::string& MonitorIni::GetDateFrom() const
{
	misc::string defval("");
	return m_inisrv.get(g_section, g_dateFrom, defval);
}

void MonitorIni::SetDateFrom(const misc::string& value)
{
	m_inisrv.set(g_section, g_dateFrom, value);
}

const misc::string& MonitorIni::GetDateTo() const
{
	misc::string defval("");
	return m_inisrv.get(g_section, g_dateTo, defval);
}

void MonitorIni::SetDateTo(const misc::string& value)
{
	m_inisrv.set(g_section, g_dateTo, value);
}

const misc::string& MonitorIni::GetAuditFile() const
{
	misc::string defval("");
	return m_inisrv.get(g_section, g_auditFile, defval);
}

void MonitorIni::SetAuditFile(const misc::string& filepath)
{
	m_inisrv.set(g_section, g_auditFile, filepath);
}


bool MonitorIni::SaveIni()
{
	return m_inisrv.write();
}
