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

#ifndef __TradingPermissions_hpp__
#define __TradingPermissions_hpp__


#include <O2GEnum.h>
#include <string.hpp>

namespace fxcm
{
	class TradingPermissions
	{
		void Init();
	public:
		TradingPermissions();
		~TradingPermissions();
		TradingPermissions(const TradingPermissions& tp);
		TradingPermissions& operator=(const TradingPermissions& tp);

		const char* GetInstrument() const;
		void SetInstrument(const char* instrument);

		O2GPermissionStatus CanCreateMarketOpenOrder() const;
		void SetCanCreateMarketOpenOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanChangeMarketOpenOrder() const;
		void SetCanChangeMarketOpenOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanDeleteMarketOpenOrder() const;
		void SetCanDeleteMarketOpenOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanCreateMarketCloseOrder() const;
		void SetCanCreateMarketCloseOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanChangeMarketCloseOrder() const;
		void SetCanChangeMarketCloseOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanDeleteMarketCloseOrder() const;
		void SetCanDeleteMarketCloseOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanCreateEntryOrder() const;
		void SetCanCreateEntryOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanChangeEntryOrder() const;
		void SetCanChangeEntryOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanDeleteEntryOrder() const;
		void SetCanDeleteEntryOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanCreateStopLimitOrder() const;
		void SetCanCreateStopLimitOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanChangeStopLimitOrder() const;
		void SetCanChangeStopLimitOrder(O2GPermissionStatus ps);
		
		O2GPermissionStatus CanDeleteStopLimitOrder() const;
		void SetCanDeleteStopLimitOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanRequestQuote() const;
		void SetCanRequestQuote(O2GPermissionStatus ps);

		O2GPermissionStatus CanAcceptQuote() const;
		void SetCanAcceptQuote(O2GPermissionStatus ps);

		O2GPermissionStatus CanDeleteQuote() const;
		void SetCanDeleteQuote(O2GPermissionStatus ps);

		O2GPermissionStatus CanCreateOCO() const;
		void SetCanCreateOCO(O2GPermissionStatus ps);

		O2GPermissionStatus CanCreateOTO() const;
		void SetCanCreateOTO(O2GPermissionStatus ps);

		O2GPermissionStatus CanJoinToNewContingencyGroup() const;
		void SetCanJoinToNewContingencyGroup(O2GPermissionStatus ps);

		O2GPermissionStatus CanJoinToExistingContingencyGroup() const;
		void SetCanJoinToExistingContingencyGroup(O2GPermissionStatus ps);

		O2GPermissionStatus CanRemoveFromContingencyGroup() const;
		void SetCanRemoveFromContingencyGroup(O2GPermissionStatus ps);

		O2GPermissionStatus CanChangeOfferSubscription() const;
		void SetCanChangeOfferSubscription(O2GPermissionStatus ps);

		O2GPermissionStatus CanCreateNetCloseOrder() const;
		void SetCanCreateNetCloseOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanChangeNetCloseOrder() const;
		void SetCanChangeNetCloseOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanDeleteNetCloseOrder() const;
		void SetCanDeleteNetCloseOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanCreateNetStopLimitOrder() const;
		void SetCanCreateNetStopLimitOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanChangeNetStopLimitOrder() const;
		void SetCanChangeNetStopLimitOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanDeleteNetStopLimitOrder() const;
		void SetCanDeleteNetStopLimitOrder(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseDynamicTrailingForStop() const;
		void SetCanUseDynamicTrailingForStop(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseDynamicTrailingForLimit() const;
		void SetCanUseDynamicTrailingForLimit(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseDynamicTrailingForEntryStop() const;
		void SetCanUseDynamicTrailingForEntryStop(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseDynamicTrailingForEntryLimit() const;
		void SetCanUseDynamicTrailingForEntryLimit(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseFluctuateTrailingForStop() const;
		void SetCanUseFluctuateTrailingForStop(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseFluctuateTrailingForLimit() const;
		void SetCanUseFluctuateTrailingForLimit(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseFluctuateTrailingForEntryStop() const;
		void SetCanUseFluctuateTrailingForEntryStop(O2GPermissionStatus ps);

		O2GPermissionStatus CanUseFluctuateTrailingForEntryLimit() const;
		void SetCanUseFluctuateTrailingForEntryLimit(O2GPermissionStatus ps);

	private:
		misc::string		m_instrument;
		O2GPermissionStatus m_canCreateMarketOpenOrder;
		O2GPermissionStatus m_canChangeMarketOpenOrder;
		O2GPermissionStatus m_canDeleteMarketOpenOrder;
		O2GPermissionStatus m_canCreateMarketCloseOrder;
		O2GPermissionStatus m_canChangeMarketCloseOrder;
		O2GPermissionStatus m_canDeleteMarketCloseOrder;
		O2GPermissionStatus m_canCreateEntryOrder;
		O2GPermissionStatus m_canChangeEntryOrder;
		O2GPermissionStatus m_canDeleteEntryOrder;
		O2GPermissionStatus m_canCreateStopLimitOrder;
		O2GPermissionStatus m_canChangeStopLimitOrder;
		O2GPermissionStatus m_canDeleteStopLimitOrder;
		O2GPermissionStatus m_canRequestQuote;
		O2GPermissionStatus m_canAcceptQuote;
		O2GPermissionStatus m_canDeleteQuote;
		O2GPermissionStatus m_canCreateOCO;
		O2GPermissionStatus m_canCreateOTO;
		O2GPermissionStatus m_canJoinToNewContingencyGroup;
		O2GPermissionStatus m_canJoinToExistingContingencyGroup;
		O2GPermissionStatus m_canRemoveFromContingencyGroup;
		O2GPermissionStatus m_canChangeOfferSubscription;
		O2GPermissionStatus m_canCreateNetCloseOrder;
		O2GPermissionStatus m_canChangeNetCloseOrder;
		O2GPermissionStatus m_canDeleteNetCloseOrder;
		O2GPermissionStatus m_canCreateNetStopLimitOrder;
		O2GPermissionStatus m_canChangeNetStopLimitOrder;
		O2GPermissionStatus m_canDeleteNetStopLimitOrder;
		O2GPermissionStatus m_canUseDynamicTrailingForStop;
		O2GPermissionStatus m_canUseDynamicTrailingForLimit;
		O2GPermissionStatus m_canUseDynamicTrailingForEntryStop;
		O2GPermissionStatus m_canUseDynamicTrailingForEntryLimit;
		O2GPermissionStatus m_canUseFluctuateTrailingForStop;
		O2GPermissionStatus m_canUseFluctuateTrailingForLimit;
		O2GPermissionStatus m_canUseFluctuateTrailingForEntryStop;
		O2GPermissionStatus m_canUseFluctuateTrailingForEntryLimit;
	};
} // namespace


#endif // __TradingPermissions_hpp__
