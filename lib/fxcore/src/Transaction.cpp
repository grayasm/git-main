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

#include "Transaction.hpp"

//c
//c++
#include "algorithm.hpp"
//local
#include "math.hpp"

namespace fx
{
	Transaction::Transaction()
	{
	}

	Transaction::~Transaction()
	{
	}

	Transaction::Transaction(const Transaction& tc)
	{
		*this = tc;
	}

	Transaction& Transaction::operator=(const Transaction& tc)
	{
		if(this != &tc)
		{
			m_positions = tc.m_positions;
		}
		return *this;
	}

	const Transaction::Positions& Transaction::GetPositions() const
	{
		return m_positions; 
	}

	Transaction::PosIt Transaction::GetBegin() 
	{
		return m_positions.begin(); 
	}

	Transaction::PosIt Transaction::GetEnd() 
	{ 
		return m_positions.end(); 
	}

	Transaction::PosCIt Transaction::GetBegin() const 
	{ 
		return m_positions.begin(); 
	}

	Transaction::PosCIt Transaction::GetEnd() const 
	{ 
		return m_positions.end(); 
	}

	void Transaction::Add(const Position& position)
	{
		m_positions.push_back(position);
	}

	bool Transaction::IsEmpty() const
	{
		return m_positions.empty();
	}

	size_t Transaction::Size() const
	{
		return m_positions.size();
	}

	Transaction::Symbols Transaction::GetSymbols() const
	{
		Symbols symbols;
		for(PosCIt bit = m_positions.begin(); bit != m_positions.end(); ++bit)
		{
			const Position& pos = *bit;
			const misc::string& symbol = pos.GetCurrency().GetSymbol();
			if(misc::find(symbols.begin(), symbols.end(), symbol) == symbols.end())
			{
				symbols.push_back(symbol);
			}
		}
		return symbols;
	}

	double Transaction::GetMMR(const misc::string& symbol) const
	{
		double buyMMR(0);
		double sellMMR(0);	
		for(PosCIt bit = m_positions.begin(); bit != m_positions.end(); ++bit)
		{
			const Position& pos = *bit;
			if(pos.GetCurrency().GetSymbol() == symbol)
			{         
				if(pos.IsOpen())
				{
					double margin = pos.GetMMR();
					if(bit->IsBuy()) 
						buyMMR += margin;
					else 
						sellMMR += margin;
				}
			}
		}
		return (buyMMR > sellMMR ? buyMMR : sellMMR);
	}

	void Transaction::Close(const misc::string& symbol, const Price& rate)
	{
		for(PosIt bit = m_positions.begin(); bit != m_positions.end(); ++bit)
		{
			Position& pos = *bit;
			if(pos.GetCurrency().GetSymbol() == symbol &&
				pos.IsOpen())
			{
				pos.Close(rate);
			}
		}
	}

	double Transaction::GetGPL(const misc::string& symbol, const Price& rate) const
	{
		double profit(0.f);
		for(PosCIt bit = m_positions.begin(); bit != m_positions.end(); ++bit)
		{
			const Position& pos = *bit;
			if(pos.GetCurrency().GetSymbol() == symbol)
			{
				if(!pos.IsOpen())
					profit += pos.GetGPL();
				else
					profit += pos.GetGPL(rate);				
				profit -= pos.GetCommission();
				profit -= pos.GetInterest();
			}
		}
		return profit;
	}

	double Transaction::GetPL(const misc::string& symbol, const Price& rate) const
	{
		double pips(0.f);
		for(PosCIt bit = m_positions.begin(); bit != m_positions.end(); ++bit)
		{
			const Position& pos = *bit;
			if(pos.GetCurrency().GetSymbol() == symbol)
			{
				double totalPL(0);
				if(!pos.IsOpen())
					totalPL = pos.GetAmount() * pos.GetPL();
				else
					totalPL = pos.GetAmount() * pos.GetPL(rate);

				pips += totalPL;
			}
		}
		return pips;
	}

	Price Transaction::EstimateRate(const misc::string& symbol, double pips) const
	{
		/*
			-20 means a total Sell: 20K transaction
			220 means a total Buy: 220K transaction
			0 means a hedge transaction with no profit. 
			At the very best it will break even.
		*/

		double sumAmt(0);	
		double pipCost(0);
		double rate2pip(0);
		
		for(PosCIt bit = m_positions.begin(); bit != m_positions.end(); ++bit)
		{
			const Position& pos = *bit;
			if(pos.GetCurrency().GetSymbol() == symbol)
			{
				double s = pos.IsBuy() == true ? 1 : -1;
				sumAmt += s * pos.GetAmount();
				pipCost = pos.GetCurrency().GetPipCost();
				rate2pip = pos.GetCurrency().GetRate2Pip();
			}
		}
	    
		if( math::is_eq(sumAmt, 0) )
			return Price(0, 0); /* Hedged transaction. */     
	    
		double sumGPL = ::fabs(sumAmt) * pips * pipCost;
	    
	    
	   /*	Calculate a rate where the entire transaction will score the given number
			of pip in the direction given by the sum of all positions.
	    
		(cp - op0) * s0 * rate2pip * k0 * pipcost = GPL0;
		(cp - op2) * s2 * rate2pip * k2 * pipcost = GPL2;
		....
		(cp - opn) * sn * rate2pip * kn * pipcost = GPLn
		---------------------------------------------------
		
	    
		(cp - op0) * s0 * rate2pip * k0 * pipcost + (cp - op2) * s2 * rate2pip * k2 * pipcost = sum(GPL);
		sum(GPL) = GPL0 + GPL2;
		sum(GPL) = sum(Amt) * pips * pipcost;
		(cp - op0) * s0 * rate2pip * k0 + (cp - op2) * s2 * rate2pip * k2 = sum(GPL) / pipcost;    
	    
		f0 = s0 * rate2pip * k0;
		f2 = s2 * rate2pip * k2;
	    

		(cp - op0) * f0 + (cp - op2) * f2 = sum(GPL) / pipcost;
		cp * f0 - op0 * f0 + cp * f2 - op2 * f2 = sum(GPL) / pipcost;
		cp * f0 + cp * f2 = sum(GPL) / pipcost + op0 * f0 + op2 * f2;
		cp * (f0 + f2) = sum(GPL) / pipcost + op0 * f0 + op2 * f2;
	    
		M1 = sum(GPL) / pipcost + op0 * f0 + op2 * f2;
		M2 = f0 + f2;
	    
		cp = M1 / M2;
	   */
		double M1 = sumGPL / pipCost;
		double M2(0);
		for(PosCIt bit = m_positions.begin(); bit != m_positions.end(); ++bit)
		{
			const Position& pos = *bit;
			if(pos.GetCurrency().GetSymbol() == symbol)
			{
				double s = (pos.IsBuy() == true ? 1 : -1);
				double k = pos.GetAmount();
				double f = s * pos.GetCurrency().GetRate2Pip() * k;
				const Price& p_Open = pos.GetCurrency().GetPrice();
				double op = (pos.IsBuy() == true ? p_Open.GetBuy() : p_Open.GetSell());

				M1 += op * f;
				M2 += f;
			}
		}
	    
		double rate = M1 / M2;
		double spread(2); // something resonable;

		double q1 = (sumAmt > 0 ? rate + spread : rate);
		double q2 = (sumAmt > 0 ? rate : rate - spread);
		return Price(q1, q2);
	}


}  // namespace fx