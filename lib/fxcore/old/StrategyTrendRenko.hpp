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


#ifndef __StrategyTrendRenko_hpp__
#define __StrategyTrendRenko_hpp__



namespace fx
{
	/*
	 *	
	 */
	class StrategyTrendRenko : public StrategyBase
	{
	public:
		typedef misc::autoptr<StrategyTrendRenko> Ptr;
		friend class Serializer;
		friend class Deserializer;

		StrategyTrendRenko();
		~StrategyTrendRenko();
		StrategyTrendRenko(const StrategyTrendRenko& tc);
		StrategyTrendRenko& operator=(const StrategyTrendRenko& tc);

		StrategyTrendRenko(
			const fx::Position& ep,		// entry position - full data as valid
			bool wait,					// wait for condition or enter immediately
			double rs					// renko brick size
			);


		// --- virtual table ---
		void AcceptVisitor(StrategyVisitor& visitor);
		bool Update(const Price& rate);
		double GetPL() const;
		double GetGPL() const;
		bool ReInit();
		// --- end of virtual ---


	};

} // namespace

#endif // __StrategyTrendRenko_hpp__
