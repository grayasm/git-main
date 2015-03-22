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


#include "Deserializer.hpp"
#include "strconv.hpp"
#include "strtok.hpp"


namespace fx
{
	Deserializer::Deserializer(const misc::string& file)
	{
		m_file = file;
		m_out = 0;
		m_plugin = 0;
	}

	Deserializer::~Deserializer()
	{
	}

	void Deserializer::Deserialize()
	{
		Reset();
		m_out = new misc::ifstream(m_file.c_str());
		if(!m_out->is_open())
			return;


		misc::string sline;
		std::string stdline;	

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);			
			
			// identify the strategy
			if(id == "S")
			{
				misc::string sname(elems[1]); misc::trim(sname);

				// Fixed Grid Hedge
				if(sname == "hfg")
				{
					fx::StrategyHedgeFixGrid::Ptr hfgs = new fx::StrategyHedgeFixGrid();
					Deserialize(*hfgs);
					m_data.push_back(hfgs);
				}
				else if(sname == "2hfg")
				{
					fx::Strategy2HedgeFixGrid::Ptr h2fgs = new fx::Strategy2HedgeFixGrid();
					Deserialize(*h2fgs);
					m_data.push_back(h2fgs);
				}
				else if(sname == "1fg")
				{
					fx::StrategyFixGrid::Ptr fgs = new fx::StrategyFixGrid();
					Deserialize(*fgs);
					m_data.push_back(fgs);
				}
				else if(sname == "2fg")
				{
					fx::Strategy2FixGrid::Ptr _2fgs = new fx::Strategy2FixGrid();
					Deserialize(*_2fgs);
					m_data.push_back(_2fgs);
				}
				else
				{
					throw misc::exception("Unknown strategy.");
				}
			}
			else
			{
				throw misc::exception("Unrecognized token.");
			}
		}

		m_out->close();
		delete m_out;
		m_out = 0;
	}

	void Deserializer::SetPlugin(fx::MarketPlugin::Ptr plugin)
	{
		m_plugin = plugin;
	}

	const misc::vector<fx::StrategyBase::Ptr>& Deserializer::GetData() const
	{
		return m_data;

	}
	
	void Deserializer::Reset()
	{
		m_data.clear();
	}

	void Deserializer::Deserialize(fx::Transaction& t, size_t size)
	{
		for(size_t i = 0; i < size; ++i)
		{
			fx::Position p;
			Deserialize(p);
			t.Add(p);
		}
	}

	void Deserializer::Deserialize(fx::Position& p)
	{
		
		misc::string sline;
		std::string  stdline;

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);
			if(id != "P")
				throw misc::exception("Unexpected token.");

			if(elems.size() < 14)
				throw misc::exception("Position has minimum 14 elements");

			misc::string sOrderID	= elems[1];	misc::trim(sOrderID);
			misc::string sTradeID	= elems[2];	misc::trim(sTradeID);
			misc::string sOpen		= elems[3];	misc::trim(sOpen);
			misc::string symbol		= elems[4];	misc::trim(symbol);
			misc::string sBuy		= elems[5]; misc::trim(sBuy);
			misc::string sSell		= elems[6]; misc::trim(sSell);
			misc::string sMargin	= elems[7]; misc::trim(sMargin);
			misc::string sPipCost	= elems[8]; misc::trim(sPipCost);
			misc::string sRate2Pip	= elems[9]; misc::trim(sRate2Pip);
			misc::string sIsBuy		= elems[10]; misc::trim(sIsBuy);
			misc::string sAmount	= elems[11]; misc::trim(sAmount);
			misc::string sCommission= elems[12]; misc::trim(sCommission);
			misc::string sInterest	= elems[13]; misc::trim(sInterest);

			bool bOpen = (sOpen == "open");
			double dBuy = 0; misc::to_value(sBuy, dBuy);
			double dSell = 0; misc::to_value(sSell, dSell);
			double dMargin = 0; misc::to_value(sMargin, dMargin);
			double dPipCost = 0; misc::to_value(sPipCost, dPipCost);
			double dRate2Pip = 0; misc::to_value(sRate2Pip, dRate2Pip);
			bool bIsBuy = (sIsBuy == "buy");
			int iAmount = 0; misc::to_value(sAmount, iAmount);
			double dCommission = 0; misc::to_value(sCommission, dCommission);
			double dInterest = 0; misc::to_value(sInterest, dInterest);

			fx::Price open_p(dBuy, dSell);
			fx::Currency curr(symbol, open_p, dMargin, dPipCost, dRate2Pip);
			p = fx::Position(sOrderID, sTradeID, curr, bIsBuy, (double)iAmount, dCommission, dInterest);

			if(bOpen)
				return;

			misc::string sBuyC		= elems[14]; misc::trim(sBuyC);
			misc::string sSellC		= elems[15]; misc::trim(sSellC);

			double dBuyC = 0; misc::to_value(sBuyC, dBuyC);
			double dSellC = 0; misc::to_value(sSellC, dSellC);

			fx::Price close_p(dBuyC, dSellC);
			p.Close(close_p);

			return;
		}
		throw misc::exception("Enf of file");
	}

	void Deserializer::Deserialize(fx::StrategyHedgeFixGrid& fgs)
	{
		fx::Position ep;
		bool wait = false;
		double dh = 0;
		double dg = 0;
		double ha = 0;
		double de = 0;
		double maxn = 0;
		double maxp = 0;
		MarketPlugin::Ptr plugin;
		// private
		fx::Transaction		mct;
		fx::Price			menter;
		fx::Price			mrate;
		fx::Price			mprev_rate;
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				mgrid;
		bool				mblocked = true;


		// begin deserialization
		Deserialize(ep);
		
		misc::string sline;
		std::string  stdline;
		bool bsuccess = false;

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);
			if(id == "wait")
			{
				misc::string swait(elems[1]); misc::trim(swait);
				wait = (swait == "true");
			}
			else if(id == "dh")
			{
				misc::string sdh(elems[1]); misc::trim(sdh); misc::to_value(sdh, dh);
			}
			else if(id == "dg")
			{
				misc::string sdg(elems[1]); misc::trim(sdg); misc::to_value(sdg, dg);
			}
			else if(id == "ha")
			{
				misc::string sha(elems[1]); misc::trim(sha); misc::to_value(sha, ha);
			}
			else if(id == "de")
			{
				misc::string sde(elems[1]); misc::trim(sde); misc::to_value(sde, de);
			}
			else if(id == "maxn")
			{
				misc::string smaxn(elems[1]); misc::trim(smaxn); misc::to_value(smaxn, maxn);
			}
			else if(id == "maxp")
			{
				misc::string smaxp(elems[1]); misc::trim(smaxp); misc::to_value(smaxp, maxp);
			}
			else if(id == "plugin")
			{
				misc::string smplugin(elems[1]); misc::trim(smplugin);
				if(m_plugin.IsNull())
					throw misc::exception("Null plugin.");
				if(m_plugin->GetID() != smplugin)
					throw misc::exception("Plugin does not match.");

				plugin = m_plugin;
			}
			else if(id == "T")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);				
				Deserialize(mct, tsize);
			}
			else if(id == "enter")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				menter = fx::Price(dbuy, dsell);
			}
			else if(id == "rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mrate = fx::Price(dbuy, dsell);
			}
			else if(id == "prev_rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mprev_rate = fx::Price(dbuy, dsell);
			}
			else if(id == "grid")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);
				Deserialize(mgrid, tsize);
			}
			else if(id == "blocked")
			{
				misc::string sblocked(elems[1]); misc::trim(sblocked);
				mblocked = (sblocked == "true");
				bsuccess = true;
				break;
			}
		}

		if(!bsuccess)
			throw misc::exception("Enf of file");		

		// initialize strategy
		fgs = fx::StrategyHedgeFixGrid(ep, wait, dh, dg, ha, de, maxn, maxp, plugin);
		fgs.m_ct = mct;
		fgs.m_enter = menter;
		fgs.m_rate = mrate;
		fgs.m_prev_rate = mprev_rate;
		fgs.m_grid = mgrid;		
		for(size_t i = 0; i < fgs.m_grid.size(); ++i)
		{
			fx::FixGridPositionStub::Ptr ptr = mgrid[i];
			ptr->m_plugin = plugin;
			ptr->m_ct = &(fgs.m_ct);
		}
		fgs.m_blocked = mblocked;

		// done!
	}

	void Deserializer::Deserialize(fx::StrategyHedgeFixGrid::Grid& grid, size_t size)
	{
		for(size_t i = 0; i < size; ++i)
		{
			fx::FixGridPositionStub ps;
			Deserialize(ps);
			grid.push_back(new fx::FixGridPositionStub(ps));
		}
	}

	void Deserializer::Deserialize(FixGridPositionStub& ps)
	{
		fx::Position gp;
		double de(0);
		MarketPlugin::Ptr plugin = 0;
		fx::Transaction* ct = 0;
		fx::Transaction	mgt;
		fx::Price mrate;
		

		
		misc::string sline;
		std::string  stdline;
		bool bsuccess = false;

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);
			if(id != "fgps")
				throw misc::exception("Unexpected token.");

			break;
		}

		Deserialize(gp);

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);
			
			if(id == "de")
			{
				misc::string sde(elems[1]); misc::trim(sde); misc::to_value(sde, de);
			}
			else if(id == "T")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);				
				Deserialize(mgt, tsize);
			}
			else if(id == "rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mrate = fx::Price(dbuy, dsell);
				bsuccess = true;
				break;
			}
		}

		if(!bsuccess)
			throw misc::exception("Enf of file");

		// initialize position stub
		ps = fx::FixGridPositionStub(gp, de, plugin, ct);
		ps.m_gt = mgt;
		ps.m_rate = mrate;

		//! done
	}

	void Deserializer::Deserialize(fx::Strategy2HedgeFixGrid& h2fgs)
	{
		fx::Position ep;
		bool wait = false;
		double dh = 0;
		double dg = 0;
		double ha = 0;
		double de = 0;
		double maxn = 0;
		double maxp = 0;
		MarketPlugin::Ptr plugin;
		// private
		fx::Transaction		mct;
		fx::Price			menter;
		fx::Price			mrate;
		fx::Price			mprev_rate;
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				mgrid;
		bool				mblocked = true;


		// begin deserialization
		Deserialize(ep);

		misc::string sline;
		std::string  stdline;
		bool bsuccess = false;

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);
			if(id == "wait")
			{
				misc::string swait(elems[1]); misc::trim(swait);
				wait = (swait == "true");
			}
			else if(id == "dh")
			{
				misc::string sdh(elems[1]); misc::trim(sdh); misc::to_value(sdh, dh);
			}
			else if(id == "dg")
			{
				misc::string sdg(elems[1]); misc::trim(sdg); misc::to_value(sdg, dg);
			}
			else if(id == "ha")
			{
				misc::string sha(elems[1]); misc::trim(sha); misc::to_value(sha, ha);
			}
			else if(id == "de")
			{
				misc::string sde(elems[1]); misc::trim(sde); misc::to_value(sde, de);
			}
			else if(id == "maxn")
			{
				misc::string smaxn(elems[1]); misc::trim(smaxn); misc::to_value(smaxn, maxn);
			}
			else if(id == "maxp")
			{
				misc::string smaxp(elems[1]); misc::trim(smaxp); misc::to_value(smaxp, maxp);
			}
			else if(id == "plugin")
			{
				misc::string smplugin(elems[1]); misc::trim(smplugin);
				if(m_plugin.IsNull())
					throw misc::exception("Null plugin.");
				if(m_plugin->GetID() != smplugin)
					throw misc::exception("Plugin does not match.");

				plugin = m_plugin;
			}
			else if(id == "T")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);				
				Deserialize(mct, tsize);
			}
			else if(id == "enter")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				menter = fx::Price(dbuy, dsell);
			}
			else if(id == "rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mrate = fx::Price(dbuy, dsell);
			}
			else if(id == "prev_rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mprev_rate = fx::Price(dbuy, dsell);
			}
			else if(id == "grid")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);
				Deserialize(mgrid, tsize);
			}
			else if(id == "blocked")
			{
				misc::string sblocked(elems[1]); misc::trim(sblocked);
				mblocked = (sblocked == "true");
				bsuccess = true;
				break;
			}
		}

		if(!bsuccess)
			throw misc::exception("Enf of file");		

		// initialize strategy
		h2fgs = fx::Strategy2HedgeFixGrid(ep, wait, dh, dg, ha, de, maxn, maxp, plugin);
		h2fgs.m_ct = mct;
		h2fgs.m_enter = menter;
		h2fgs.m_rate = mrate;
		h2fgs.m_prev_rate = mprev_rate;
		h2fgs.m_grid = mgrid;		
		for(size_t i = 0; i < h2fgs.m_grid.size(); ++i)
		{
			fx::FixGridPositionStub::Ptr ptr = mgrid[i];
			ptr->m_plugin = plugin;
			ptr->m_ct = &(h2fgs.m_ct);
		}
		h2fgs.m_blocked = mblocked;

		// done!
	}

	void Deserializer::Deserialize(fx::StrategyFixGrid& fgs)
	{
		fx::Position ep;
		bool wait = false;
		double dg = 0;
		double pa = 0;
		double de = 0;
		double maxn = 0;
		double maxp = 0;
		MarketPlugin::Ptr plugin;
		// private
		fx::Transaction		mct;
		fx::Price			mrate;
		fx::Price			mprev_rate;
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				mgrid;
		bool				mblocked = true;


		// begin deserialization
		Deserialize(ep);

		misc::string sline;
		std::string  stdline;
		bool bsuccess = false;

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);
			if(id == "wait")
			{
				misc::string swait(elems[1]); misc::trim(swait);
				wait = (swait == "true");
			}
			else if(id == "dg")
			{
				misc::string sdg(elems[1]); misc::trim(sdg); misc::to_value(sdg, dg);
			}
			else if(id == "pa")
			{
				misc::string sha(elems[1]); misc::trim(sha); misc::to_value(sha, pa);
			}
			else if(id == "de")
			{
				misc::string sde(elems[1]); misc::trim(sde); misc::to_value(sde, de);
			}
			else if(id == "maxn")
			{
				misc::string smaxn(elems[1]); misc::trim(smaxn); misc::to_value(smaxn, maxn);
			}
			else if(id == "maxp")
			{
				misc::string smaxp(elems[1]); misc::trim(smaxp); misc::to_value(smaxp, maxp);
			}
			else if(id == "plugin")
			{
				misc::string smplugin(elems[1]); misc::trim(smplugin);
				if(m_plugin.IsNull())
					throw misc::exception("Null plugin.");
				if(m_plugin->GetID() != smplugin)
					throw misc::exception("Plugin does not match.");

				plugin = m_plugin;
			}
			else if(id == "T")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);				
				Deserialize(mct, tsize);
			}
			else if(id == "rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mrate = fx::Price(dbuy, dsell);
			}
			else if(id == "prev_rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mprev_rate = fx::Price(dbuy, dsell);
			}
			else if(id == "grid")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);
				Deserialize(mgrid, tsize);
			}
			else if(id == "blocked")
			{
				misc::string sblocked(elems[1]); misc::trim(sblocked);
				mblocked = (sblocked == "true");
				bsuccess = true;
				break;
			}
		}

		if(!bsuccess)
			throw misc::exception("Enf of file");		

		// initialize strategy
		fgs = fx::StrategyFixGrid(ep, wait, dg, pa, de, maxn, maxp, plugin);
		fgs.m_ct = mct;
		fgs.m_rate = mrate;
		fgs.m_prev_rate = mprev_rate;
		fgs.m_grid = mgrid;		
		for(size_t i = 0; i < fgs.m_grid.size(); ++i)
		{
			fx::FixGridPositionStub::Ptr ptr = mgrid[i];
			ptr->m_plugin = plugin;
			ptr->m_ct = &(fgs.m_ct);
		}
		fgs.m_blocked = mblocked;

		// done!
	}

	void Deserializer::Deserialize(fx::Strategy2FixGrid& _2fgs)
	{
		fx::Position ep;
		bool wait = false;
		double dbg = 0;
		double dg = 0;
		double pa = 0;
		double de = 0;
		double maxn = 0;
		double maxp = 0;
		MarketPlugin::Ptr plugin;
		// private
		fx::Transaction		mct;
		fx::Price			menter;
		fx::Price			mrate;
		fx::Price			mprev_rate;
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				mgrid;
		bool				mblocked = true;


		// begin deserialization
		Deserialize(ep);

		misc::string sline;
		std::string  stdline;
		bool bsuccess = false;

		while(!m_out->eof())
		{
			std::getline(*m_out, stdline);
			sline = stdline.c_str();

			misc::trim(sline);
			if(sline.empty())
				continue;

			misc::strtok tokenizer(sline, ";");
			const misc::strtok::Tokens& elems = tokenizer.tokens();
			misc::string id(elems[0]);
			misc::trim(id);
			if(id == "wait")
			{
				misc::string swait(elems[1]); misc::trim(swait);
				wait = (swait == "true");
			}
			else if(id == "dbg")
			{
				misc::string sdbg(elems[1]); misc::trim(sdbg); misc::to_value(sdbg, dbg);
			}
			else if(id == "dg")
			{
				misc::string sdg(elems[1]); misc::trim(sdg); misc::to_value(sdg, dg);
			}
			else if(id == "pa")
			{
				misc::string spa(elems[1]); misc::trim(spa); misc::to_value(spa, pa);
			}
			else if(id == "de")
			{
				misc::string sde(elems[1]); misc::trim(sde); misc::to_value(sde, de);
			}
			else if(id == "maxn")
			{
				misc::string smaxn(elems[1]); misc::trim(smaxn); misc::to_value(smaxn, maxn);
			}
			else if(id == "maxp")
			{
				misc::string smaxp(elems[1]); misc::trim(smaxp); misc::to_value(smaxp, maxp);
			}
			else if(id == "plugin")
			{
				misc::string smplugin(elems[1]); misc::trim(smplugin);
				if(m_plugin.IsNull())
					throw misc::exception("Null plugin.");
				if(m_plugin->GetID() != smplugin)
					throw misc::exception("Plugin does not match.");

				plugin = m_plugin;
			}
			else if(id == "T")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);				
				Deserialize(mct, tsize);
			}
			else if(id == "rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mrate = fx::Price(dbuy, dsell);
			}
			else if(id == "prev_rate")
			{
				misc::string sBuy = elems[1]; misc::trim(sBuy);
				misc::string sSell = elems[2]; misc::trim(sSell);
				double dbuy; misc::to_value(sBuy, dbuy);
				double dsell; misc::to_value(sSell, dsell);
				mprev_rate = fx::Price(dbuy, dsell);
			}
			else if(id == "grid")
			{
				size_t tsize = 0;
				misc::to_value(elems[1], tsize);
				Deserialize(mgrid, tsize);
			}
			else if(id == "blocked")
			{
				misc::string sblocked(elems[1]); misc::trim(sblocked);
				mblocked = (sblocked == "true");
				bsuccess = true;
				break;
			}
		}

		if(!bsuccess)
			throw misc::exception("Enf of file");		

		// initialize strategy
		_2fgs = fx::Strategy2FixGrid(ep, wait, dbg, dg, pa, de, maxn, maxp, plugin);
		_2fgs.m_ct = mct;
		_2fgs.m_rate = mrate;
		_2fgs.m_prev_rate = mprev_rate;
		_2fgs.m_grid = mgrid;		
		for(size_t i = 0; i < _2fgs.m_grid.size(); ++i)
		{
			fx::FixGridPositionStub::Ptr ptr = mgrid[i];
			ptr->m_plugin = plugin;
			ptr->m_ct = &(_2fgs.m_ct);
		}
		_2fgs.m_blocked = mblocked;

		// done!
	}
	
}; // namespace