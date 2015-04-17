/*
  Copyright (C) 2015 Mihai Vasilian

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



#ifndef __StrategyJNemRenko_hpp__
#define __StrategyJNemRenko_hpp__


namespace fx
{
	class StrategyJNemRenko : public StrategyBase
	{
	public:
		StrategyJNemRenko(
			bool UPtrend,			// true if trend is up, false otherwise.
			//ema,
			double pa,				// position amount
			//renko
			);
		StrategyJNemRenko(const StrategyJNemRenko& tc);
		~StrategyJNemRenko();
		// --- virtual table ---
		void AcceptVisitor(StrategyVisitor& visitor);
		bool Update(const fx::Price& price);
		double GetPL() const;
		double GetGPL() const;
		bool ReInit();
		// --- end of virtual ---

		misc::string ToString() const;

	private:

	};
} // namespace
#endif // __StrategyJNemRenko_hpp__