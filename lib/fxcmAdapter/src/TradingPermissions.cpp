/*
Copyright (C) 2017 Mihai Vasilian
*/


#include "TradingPermissions.hpp"

namespace fxcm
{
	void TradingPermissions::Init()
	{
		m_instrument = "";
		m_canCreateMarketOpenOrder = PermissionDisabled;
		m_canChangeMarketOpenOrder = PermissionDisabled;
		m_canDeleteMarketOpenOrder = PermissionDisabled;
		m_canCreateMarketCloseOrder = PermissionDisabled;
		m_canChangeMarketCloseOrder = PermissionDisabled;
		m_canDeleteMarketCloseOrder = PermissionDisabled;
		m_canCreateEntryOrder = PermissionDisabled;
		m_canChangeEntryOrder = PermissionDisabled;
		m_canDeleteEntryOrder = PermissionDisabled;
		m_canCreateStopLimitOrder = PermissionDisabled;
		m_canChangeStopLimitOrder = PermissionDisabled;
		m_canDeleteStopLimitOrder = PermissionDisabled;
		m_canRequestQuote = PermissionDisabled;
		m_canAcceptQuote = PermissionDisabled;
		m_canDeleteQuote = PermissionDisabled;
		m_canCreateOCO = PermissionDisabled;
		m_canCreateOTO = PermissionDisabled;
		m_canJoinToNewContingencyGroup = PermissionDisabled;
		m_canJoinToExistingContingencyGroup = PermissionDisabled;
		m_canRemoveFromContingencyGroup = PermissionDisabled;
		m_canChangeOfferSubscription = PermissionDisabled;
		m_canCreateNetCloseOrder = PermissionDisabled;
		m_canChangeNetCloseOrder = PermissionDisabled;
		m_canDeleteNetCloseOrder = PermissionDisabled;
		m_canCreateNetStopLimitOrder = PermissionDisabled;
		m_canChangeNetStopLimitOrder = PermissionDisabled;
		m_canDeleteNetStopLimitOrder = PermissionDisabled;
		m_canUseDynamicTrailingForStop = PermissionDisabled;
		m_canUseDynamicTrailingForLimit = PermissionDisabled;
		m_canUseDynamicTrailingForEntryStop = PermissionDisabled;
		m_canUseDynamicTrailingForEntryLimit = PermissionDisabled;
		m_canUseFluctuateTrailingForStop = PermissionDisabled;
		m_canUseFluctuateTrailingForLimit = PermissionDisabled;
		m_canUseFluctuateTrailingForEntryStop = PermissionDisabled;
		m_canUseFluctuateTrailingForEntryLimit = PermissionDisabled;
	}

	TradingPermissions::TradingPermissions()
	{
		Init();
	}

	TradingPermissions::~TradingPermissions()
	{
	}

	TradingPermissions::TradingPermissions(const TradingPermissions& tp)
	{
		Init();
		*this = tp;
	}

	TradingPermissions& TradingPermissions::operator=(const TradingPermissions& tp)
	{
		if (this != &tp)
		{
			m_instrument = tp.m_instrument;
			m_canCreateMarketOpenOrder = tp.m_canCreateMarketOpenOrder;
			m_canChangeMarketOpenOrder = tp.m_canChangeMarketOpenOrder;
			m_canDeleteMarketOpenOrder = tp.m_canDeleteMarketOpenOrder;
			m_canCreateMarketCloseOrder = tp.m_canCreateMarketCloseOrder;
			m_canChangeMarketCloseOrder = tp.m_canChangeMarketCloseOrder;
			m_canDeleteMarketCloseOrder = tp.m_canDeleteMarketCloseOrder;
			m_canCreateEntryOrder = tp.m_canCreateEntryOrder;
			m_canChangeEntryOrder = tp.m_canChangeEntryOrder;
			m_canDeleteEntryOrder = tp.m_canDeleteEntryOrder;
			m_canCreateStopLimitOrder = tp.m_canCreateStopLimitOrder;
			m_canChangeStopLimitOrder = tp.m_canChangeStopLimitOrder;
			m_canDeleteStopLimitOrder = tp.m_canDeleteStopLimitOrder;
			m_canRequestQuote = tp.m_canRequestQuote;
			m_canAcceptQuote = tp.m_canAcceptQuote;
			m_canDeleteQuote = tp.m_canDeleteQuote;
			m_canCreateOCO = tp.m_canCreateOCO;
			m_canCreateOTO = tp.m_canCreateOTO;
			m_canJoinToNewContingencyGroup = tp.m_canJoinToNewContingencyGroup;
			m_canJoinToExistingContingencyGroup = tp.m_canJoinToExistingContingencyGroup;
			m_canRemoveFromContingencyGroup = tp.m_canRemoveFromContingencyGroup;
			m_canChangeOfferSubscription = tp.m_canChangeOfferSubscription;
			m_canCreateNetCloseOrder = tp.m_canCreateNetCloseOrder;
			m_canChangeNetCloseOrder = tp.m_canChangeNetCloseOrder;
			m_canDeleteNetCloseOrder = tp.m_canDeleteNetCloseOrder;
			m_canCreateNetStopLimitOrder = tp.m_canCreateNetStopLimitOrder;
			m_canChangeNetStopLimitOrder = tp.m_canChangeNetStopLimitOrder;
			m_canDeleteNetStopLimitOrder = tp.m_canDeleteNetStopLimitOrder;
			m_canUseDynamicTrailingForStop = tp.m_canUseDynamicTrailingForStop;
			m_canUseDynamicTrailingForLimit = tp.m_canUseDynamicTrailingForLimit;
			m_canUseDynamicTrailingForEntryStop = tp.m_canUseDynamicTrailingForEntryStop;
			m_canUseDynamicTrailingForEntryLimit = tp.m_canUseDynamicTrailingForEntryLimit;
			m_canUseFluctuateTrailingForStop = tp.m_canUseFluctuateTrailingForStop;
			m_canUseFluctuateTrailingForLimit = tp.m_canUseFluctuateTrailingForLimit;
			m_canUseFluctuateTrailingForEntryStop = tp.m_canUseFluctuateTrailingForEntryStop;
			m_canUseFluctuateTrailingForEntryLimit = tp.m_canUseFluctuateTrailingForEntryLimit;
		}
		return *this;
	}

	const char* TradingPermissions::GetInstrument() const
	{
		return m_instrument.c_str();
	}
	void TradingPermissions::SetInstrument(const char* instrument)
	{
		m_instrument = instrument;
	}

	O2GPermissionStatus TradingPermissions::CanCreateMarketOpenOrder() const
	{
		return m_canCreateMarketOpenOrder;
	}
	void TradingPermissions::SetCanCreateMarketOpenOrder(O2GPermissionStatus ps)
	{
		m_canCreateMarketOpenOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanChangeMarketOpenOrder() const
	{
		return m_canChangeMarketOpenOrder;
	}
	void TradingPermissions::SetCanChangeMarketOpenOrder(O2GPermissionStatus ps)
	{
		m_canChangeMarketOpenOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanDeleteMarketOpenOrder() const
	{
		return m_canDeleteMarketOpenOrder;
	}
	void TradingPermissions::SetCanDeleteMarketOpenOrder(O2GPermissionStatus ps)
	{
		m_canDeleteMarketOpenOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanCreateMarketCloseOrder() const
	{
		return m_canCreateMarketCloseOrder;
	}
	void TradingPermissions::SetCanCreateMarketCloseOrder(O2GPermissionStatus ps)
	{
		m_canCreateMarketCloseOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanChangeMarketCloseOrder() const
	{
		return m_canChangeMarketCloseOrder;
	}
	void TradingPermissions::SetCanChangeMarketCloseOrder(O2GPermissionStatus ps)
	{
		m_canChangeMarketCloseOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanDeleteMarketCloseOrder() const
	{
		return m_canDeleteMarketCloseOrder;
	}
	void TradingPermissions::SetCanDeleteMarketCloseOrder(O2GPermissionStatus ps)
	{
		m_canDeleteMarketCloseOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanCreateEntryOrder() const
	{
		return m_canCreateEntryOrder;
	}
	void TradingPermissions::SetCanCreateEntryOrder(O2GPermissionStatus ps)
	{
		m_canCreateEntryOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanChangeEntryOrder() const
	{
		return m_canChangeEntryOrder;
	}
	void TradingPermissions::SetCanChangeEntryOrder(O2GPermissionStatus ps)
	{
		m_canChangeEntryOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanDeleteEntryOrder() const
	{
		return m_canDeleteEntryOrder;
	}
	void TradingPermissions::SetCanDeleteEntryOrder(O2GPermissionStatus ps)
	{
		m_canDeleteEntryOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanCreateStopLimitOrder() const
	{
		return m_canCreateStopLimitOrder;
	}
	void TradingPermissions::SetCanCreateStopLimitOrder(O2GPermissionStatus ps)
	{
		m_canCreateStopLimitOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanChangeStopLimitOrder() const
	{
		return m_canChangeStopLimitOrder;
	}
	void TradingPermissions::SetCanChangeStopLimitOrder(O2GPermissionStatus ps)
	{
		m_canChangeStopLimitOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanDeleteStopLimitOrder() const
	{
		return m_canDeleteStopLimitOrder;
	}
	void TradingPermissions::SetCanDeleteStopLimitOrder(O2GPermissionStatus ps)
	{
		m_canDeleteStopLimitOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanRequestQuote() const
	{
		return m_canRequestQuote;
	}
	void TradingPermissions::SetCanRequestQuote(O2GPermissionStatus ps)
	{
		m_canRequestQuote = ps;
	}

	O2GPermissionStatus TradingPermissions::CanAcceptQuote() const
	{
		return m_canAcceptQuote;
	}
	void TradingPermissions::SetCanAcceptQuote(O2GPermissionStatus ps)
	{
		m_canAcceptQuote = ps;
	}

	O2GPermissionStatus TradingPermissions::CanDeleteQuote() const
	{
		return m_canDeleteQuote;
	}
	void TradingPermissions::SetCanDeleteQuote(O2GPermissionStatus ps)
	{
		m_canDeleteQuote = ps;
	}

	O2GPermissionStatus TradingPermissions::CanCreateOCO() const
	{
		return m_canCreateOCO;
	}
	void TradingPermissions::SetCanCreateOCO(O2GPermissionStatus ps)
	{
		m_canCreateOCO = ps;
	}

	O2GPermissionStatus TradingPermissions::CanCreateOTO() const
	{
		return m_canCreateOTO;
	}
	void TradingPermissions::SetCanCreateOTO(O2GPermissionStatus ps)
	{
		m_canCreateOTO = ps;
	}

	O2GPermissionStatus TradingPermissions::CanJoinToNewContingencyGroup() const
	{
		return m_canJoinToNewContingencyGroup;
	}
	void TradingPermissions::SetCanJoinToNewContingencyGroup(O2GPermissionStatus ps)
	{
		m_canJoinToNewContingencyGroup = ps;
	}

	O2GPermissionStatus TradingPermissions::CanJoinToExistingContingencyGroup() const
	{
		return m_canJoinToExistingContingencyGroup;
	}
	void TradingPermissions::SetCanJoinToExistingContingencyGroup(O2GPermissionStatus ps)
	{
		m_canJoinToExistingContingencyGroup = ps;
	}

	O2GPermissionStatus TradingPermissions::CanRemoveFromContingencyGroup() const
	{
		return m_canRemoveFromContingencyGroup;
	}
	void TradingPermissions::SetCanRemoveFromContingencyGroup(O2GPermissionStatus ps)
	{
		m_canRemoveFromContingencyGroup = ps;
	}

	O2GPermissionStatus TradingPermissions::CanChangeOfferSubscription() const
	{
		return m_canChangeOfferSubscription;
	}
	void TradingPermissions::SetCanChangeOfferSubscription(O2GPermissionStatus ps)
	{
		m_canChangeOfferSubscription = ps;
	}

	O2GPermissionStatus TradingPermissions::CanCreateNetCloseOrder() const
	{
		return m_canCreateNetCloseOrder;
	}
	void TradingPermissions::SetCanCreateNetCloseOrder(O2GPermissionStatus ps)
	{
		m_canCreateNetCloseOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanChangeNetCloseOrder() const
	{
		return m_canChangeNetCloseOrder;
	}
	void TradingPermissions::SetCanChangeNetCloseOrder(O2GPermissionStatus ps)
	{
		m_canChangeNetCloseOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanDeleteNetCloseOrder() const
	{
		return m_canDeleteNetCloseOrder;
	}
	void TradingPermissions::SetCanDeleteNetCloseOrder(O2GPermissionStatus ps)
	{
		m_canDeleteNetCloseOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanCreateNetStopLimitOrder() const
	{
		return m_canCreateNetStopLimitOrder;
	}
	void TradingPermissions::SetCanCreateNetStopLimitOrder(O2GPermissionStatus ps)
	{
		m_canCreateNetStopLimitOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanChangeNetStopLimitOrder() const
	{
		return m_canChangeNetStopLimitOrder;
	}
	void TradingPermissions::SetCanChangeNetStopLimitOrder(O2GPermissionStatus ps)
	{
		m_canChangeNetStopLimitOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanDeleteNetStopLimitOrder() const
	{
		return m_canDeleteNetStopLimitOrder;
	}
	void TradingPermissions::SetCanDeleteNetStopLimitOrder(O2GPermissionStatus ps)
	{
		m_canDeleteNetStopLimitOrder = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseDynamicTrailingForStop() const
	{
		return m_canUseDynamicTrailingForStop;
	}
	void TradingPermissions::SetCanUseDynamicTrailingForStop(O2GPermissionStatus ps)
	{
		m_canUseDynamicTrailingForStop = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseDynamicTrailingForLimit() const
	{
		return m_canUseDynamicTrailingForLimit;
	}
	void TradingPermissions::SetCanUseDynamicTrailingForLimit(O2GPermissionStatus ps)
	{
		m_canUseDynamicTrailingForLimit = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseDynamicTrailingForEntryStop() const
	{
		return m_canUseDynamicTrailingForEntryStop;
	}
	void TradingPermissions::SetCanUseDynamicTrailingForEntryStop(O2GPermissionStatus ps)
	{
		m_canUseDynamicTrailingForEntryStop = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseDynamicTrailingForEntryLimit() const
	{
		return m_canUseDynamicTrailingForEntryLimit;
	}
	void TradingPermissions::SetCanUseDynamicTrailingForEntryLimit(O2GPermissionStatus ps)
	{
		m_canUseDynamicTrailingForEntryLimit = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseFluctuateTrailingForStop() const
	{
		return m_canUseFluctuateTrailingForStop;
	}
	void TradingPermissions::SetCanUseFluctuateTrailingForStop(O2GPermissionStatus ps)
	{
		m_canUseFluctuateTrailingForStop = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseFluctuateTrailingForLimit() const
	{
		return m_canUseFluctuateTrailingForLimit;
	}
	void TradingPermissions::SetCanUseFluctuateTrailingForLimit(O2GPermissionStatus ps)
	{
		m_canUseFluctuateTrailingForLimit = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseFluctuateTrailingForEntryStop() const
	{
		return m_canUseFluctuateTrailingForEntryStop;
	}
	void TradingPermissions::SetCanUseFluctuateTrailingForEntryStop(O2GPermissionStatus ps)
	{
		m_canUseFluctuateTrailingForEntryStop = ps;
	}

	O2GPermissionStatus TradingPermissions::CanUseFluctuateTrailingForEntryLimit() const
	{
		return m_canUseFluctuateTrailingForEntryLimit;
	}
	void TradingPermissions::SetCanUseFluctuateTrailingForEntryLimit(O2GPermissionStatus ps)
	{
		m_canUseFluctuateTrailingForEntryLimit = ps;
	}	
} // namespace