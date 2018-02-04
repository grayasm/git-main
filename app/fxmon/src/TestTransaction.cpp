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

#include "TestTransaction.hpp"
#include "GetOffersPrices.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "strconv.hpp"
#include "Offer.hpp"
#include "Position.hpp"
#include "Transaction.hpp"


void OpenPosition(const fxcm::Offer& offer, int lots, bool buy, fx::Position& result);
void ClosePosition(const fxcm::Offer& offer, fx::Position& curpos);


void TestTransaction()
{
	misc::string instr("EUR/USD");
	OffersReader oreader(instr);
	fxcm::Offer offer;
	fx::Price price;
	fx::Transaction tr;
	double closedPL = 0;
	double closedGPL = 0;

	fx::Price maxprice(0, 0);
	double PL2Enter = -50;		// price - maxprice = it's a retrace
	double trLimit = 70;		// profit on entire transaction
	double trStop = -500;		// loss on entire transaction
	int iAmount = 1;			// lots in k
	double price2pip = 1 / 0.0001;



	while (true)
	{
		if (!oreader.GetOffer(offer))
			break;
		
		price = fx::Price(offer.GetAsk(), offer.GetBid());
		if (price.GetBuy() > maxprice.GetBuy() &&
			price.GetSell() > maxprice.GetSell())
			maxprice = price;		

		misc::time tnow = offer.GetTime();
		bool canOpen = (tnow.hour_() > 8 && tnow.hour_() < 22);
		
		if (!canOpen)
		{
			if (tr.Size() > 0)
			{
				tr.Close(instr, price);
				closedPL  += tr.GetPL(instr, price);
				closedGPL += tr.GetGPL(instr, price);
				
				misc::cout << "EndofDay: " << 
					"Pos=" << tr.Size() << " closedPL=" << closedPL <<
					" closedGPL=" << closedGPL << std::endl;

				tr = fx::Transaction();
			}

			continue;
		}

		// must calculate anything on tr?
		if (!tr.IsEmpty())
		{
			double curPL = tr.GetPL(instr, price);
			if (curPL > trLimit) // close in profit
			{
				tr.Close(instr, price);
				closedPL += curPL;
				closedGPL += tr.GetGPL(instr, price);
				misc::cout << "Prof: " << "Pos=" << tr.Size()
					<< " trPL=" << curPL
					<< " closedPL=" << closedPL 
					<< " closedGPL=" << closedGPL << std::endl;
				tr = fx::Transaction();
				maxprice = price;
				continue;
			}

			if (curPL < trStop) // close in loss
			{
				tr.Close(instr, price);
				closedPL += curPL;
				closedGPL += tr.GetGPL(instr, price);
				misc::cout << "Loss: Pos=" << tr.Size()
					<< " trPL=" << curPL
					<< " closedPL=" << closedPL
					<< " closedGPL=" << closedGPL << std::endl;
				tr = fx::Transaction();
				maxprice = price;
				continue;
			}

			if (tr.GetPositions().back().GetPL(price) < PL2Enter)
			{
				fx::Position pos;
				OpenPosition(offer, iAmount, true, pos);
				tr.Add(pos);
				continue;
			}

			// anything else?
			continue;
		}


		if (tr.IsEmpty()) // calculate first position
		{
			double diffPL = (price.GetBuy() - maxprice.GetBuy())*price2pip;
			if (diffPL < PL2Enter)
			{
				fx::Position pos;
				OpenPosition(offer, iAmount, true, pos);
				tr.Add(pos);
			}

			continue;
		}
	}
}


void OpenPosition(const fxcm::Offer& offer, int lots, bool buy, fx::Position& result)
{
	static int orderID = 0;
	static int tradeID = 0;
	
	fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
	fx::Currency currency(
		offer.GetInstrument(),
		price,
		2.5,		// margin= EUR/USD: 2.5 let's say
		0.08,		// pipCost,
		1/0.0001);	// rate2pip

	result = fx::Position(
		misc::from_value(orderID++),
		misc::from_value(tradeID++),
		currency,
		buy,
		lots,	// K lots
		0,		// commission
		0);		// interest

	misc::cout << "Open position" << std::endl;

}

void ClosePosition(const fxcm::Offer& offer, fx::Position& curpos)
{
	fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
	curpos.Close(price);
}