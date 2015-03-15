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

#include "fxcmPermission.hpp"
#include "stream.hpp"

namespace fxcm
{
	Permission::Permission()
	{
		Init();
	}

	Permission::~Permission()
	{
		Destroy();
	}

	Permission::Permission(const Permission& tc)
	{
		Init();
		*this = tc;
	}

	Permission& Permission::operator=(const Permission& tc)
	{
		if(this != &tc)
		{
			m_symPermissionsMap = tc.m_symPermissionsMap;
			m_generalPermissions = tc.m_generalPermissions;
		}
		return *this;
	}

	bool Permission::LoadPermissions(
		const misc::vector<misc::string>& symbols,
		IO2GSession* session)
	{
		if(symbols.empty())
			throw misc::exception("Invalid symbols");
		if(session == NULL)
			throw misc::exception("Invalid session");

		O2G2Ptr<IO2GLoginRules> loginRules = session->getLoginRules();
		if(!loginRules)
		{
			misc::cout << "\n\tCannot get login rules";
			return false;
		}

		O2G2Ptr<IO2GPermissionChecker> checker = loginRules->getPermissionChecker();
		if(!checker)
		{
			misc::cout << "\n\tCannot get permission checker";
			return false;
		}

		for(size_t i=0; i < symbols.size(); ++i)
		{
			const char* symbol = symbols[i].c_str();

			SymbolPermission symbolPermission;

			symbolPermission.m_canCreateMarketOpenOrder = checker->canCreateMarketOpenOrder(symbol);
			symbolPermission.m_canChangeMarketOpenOrder = checker->canChangeMarketOpenOrder(symbol);
			symbolPermission.m_canDeleteMarketOpenOrder = checker->canDeleteMarketOpenOrder(symbol);
			symbolPermission.m_canCreateMarketCloseOrder = checker->canCreateMarketCloseOrder(symbol);
			symbolPermission.m_canChangeMarketCloseOrder = checker->canChangeMarketCloseOrder(symbol);
			symbolPermission.m_canDeleteMarketCloseOrder = checker->canDeleteMarketCloseOrder(symbol);
			symbolPermission.m_canCreateEntryOrder = checker->canCreateEntryOrder(symbol);
			symbolPermission.m_canChangeEntryOrder = checker->canChangeEntryOrder(symbol);
			symbolPermission.m_canDeleteEntryOrder = checker->canDeleteEntryOrder(symbol);
			symbolPermission.m_canCreateStopLimitOrder = checker->canCreateStopLimitOrder(symbol);
			symbolPermission.m_canChangeStopLimitOrder = checker->canChangeStopLimitOrder(symbol);
			symbolPermission.m_canDeleteStopLimitOrder = checker->canDeleteStopLimitOrder(symbol);
			symbolPermission.m_canRequestQuote = checker->canRequestQuote(symbol);
			symbolPermission.m_canAcceptQuote = checker->canAcceptQuote(symbol);
			symbolPermission.m_canDeleteQuote = checker->canDeleteQuote(symbol);
			symbolPermission.m_canCreateOCO = checker->canCreateOCO(symbol);
			symbolPermission.m_canCreateOTO = checker->canCreateOTO(symbol);
			symbolPermission.m_canJoinToNewContingencyGroup = checker->canJoinToNewContingencyGroup(symbol);
			symbolPermission.m_canJoinToExistingContingencyGroup = checker->canJoinToExistingContingencyGroup(symbol);
			symbolPermission.m_canRemoveFromContingencyGroup = checker->canRemoveFromContingencyGroup(symbol);
			symbolPermission.m_canChangeOfferSubscription = checker->canChangeOfferSubscription(symbol);
			symbolPermission.m_canCreateNetCloseOrder = checker->canCreateNetCloseOrder(symbol);
			symbolPermission.m_canChangeNetCloseOrder = checker->canChangeNetCloseOrder(symbol);
			symbolPermission.m_canDeleteNetCloseOrder = checker->canDeleteNetCloseOrder(symbol);
			symbolPermission.m_canCreateNetStopLimitOrder = checker->canCreateNetStopLimitOrder(symbol);
			symbolPermission.m_canChangeNetStopLimitOrder = checker->canChangeNetStopLimitOrder(symbol);
			symbolPermission.m_canDeleteNetStopLimitOrder = checker->canDeleteNetStopLimitOrder(symbol);

			m_symPermissionsMap[symbol] = symbolPermission;
		}

		m_generalPermissions.m_canUseDynamicTrailingForStop = checker->canUseDynamicTrailingForStop();
		m_generalPermissions.m_canUseDynamicTrailingForLimit = checker->canUseDynamicTrailingForLimit();
		m_generalPermissions.m_canUseDynamicTrailingForEntryStop = checker->canUseDynamicTrailingForEntryStop();
		m_generalPermissions.m_canUseDynamicTrailingForEntryLimit = checker->canUseDynamicTrailingForEntryLimit();
		m_generalPermissions.m_canUseFluctuateTrailingForStop = checker->canUseFluctuateTrailingForStop();
		m_generalPermissions.m_canUseFluctuateTrailingForLimit = checker->canUseFluctuateTrailingForLimit();
		m_generalPermissions.m_canUseFluctuateTrailingForEntryStop = checker->canUseFluctuateTrailingForEntryStop();
		m_generalPermissions.m_canUseFluctuateTrailingForEntryLimit = checker->canUseFluctuateTrailingForEntryLimit();

		return true;
	}

	void Permission::Clear()
	{
		Init();
	}

	const SymbolPermission& Permission::GetPermission(const misc::string& symbol) const
	{
		std::map<misc::string, SymbolPermission>::const_iterator it = m_symPermissionsMap.find(symbol);
		if(it == m_symPermissionsMap.end())
			throw misc::exception("Symbol not found");
		return it->second;
	}

	const GeneralPermission& Permission::GetPermission() const
	{
		if(m_symPermissionsMap.empty())
			throw misc::exception("Invalid permission");
		return m_generalPermissions;
	}

	void Permission::Init()
	{
		m_symPermissionsMap.clear();
		m_generalPermissions.m_canUseDynamicTrailingForStop = PermissionDisabled;
		m_generalPermissions.m_canUseDynamicTrailingForLimit = PermissionDisabled;
		m_generalPermissions.m_canUseDynamicTrailingForEntryStop = PermissionDisabled;
		m_generalPermissions.m_canUseDynamicTrailingForEntryLimit = PermissionDisabled;
		m_generalPermissions.m_canUseFluctuateTrailingForStop = PermissionDisabled;
		m_generalPermissions.m_canUseFluctuateTrailingForLimit = PermissionDisabled;
		m_generalPermissions.m_canUseFluctuateTrailingForEntryStop = PermissionDisabled;
		m_generalPermissions.m_canUseFluctuateTrailingForEntryLimit = PermissionDisabled;
	}

	void Permission::Destroy()
	{
	}

} // namespace fxcm