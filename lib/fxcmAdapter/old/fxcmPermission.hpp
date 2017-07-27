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

#ifndef __fxcmPermission_hpp__
#define __fxcmPermission_hpp__

#include <stdlib.h>
// fxcm
#include "ForexConnect.h"
// local
#include "string.hpp"
#include "vector.hpp"
// c
// c++
#include <map>






namespace fxcm
{
	struct SymbolPermission
	{
		// rights for a specific instrument
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
	};

	struct GeneralPermission
	{
		// general rights
		O2GPermissionStatus m_canUseDynamicTrailingForStop;
		O2GPermissionStatus m_canUseDynamicTrailingForLimit;
		O2GPermissionStatus m_canUseDynamicTrailingForEntryStop;
		O2GPermissionStatus m_canUseDynamicTrailingForEntryLimit;
		O2GPermissionStatus m_canUseFluctuateTrailingForStop;
		O2GPermissionStatus m_canUseFluctuateTrailingForLimit;
		O2GPermissionStatus m_canUseFluctuateTrailingForEntryStop;
		O2GPermissionStatus m_canUseFluctuateTrailingForEntryLimit;
	};

	
	class Permission
	{
	public:
		typedef misc::autoptr<Permission>		Ptr;


	public:
		Permission();
		~Permission();
		Permission(const Permission& tc);
		Permission& operator=(const Permission& tc);

		bool LoadPermissions(
			const misc::vector<misc::string>& symbols,
			IO2GSession* session);
		void Clear();

		const SymbolPermission& GetPermission(const misc::string& symbol) const;
		const GeneralPermission& GetPermission() const;

	private:
		void Init();
		void Destroy();

	private:
		std::map<misc::string, SymbolPermission>	m_symPermissionsMap;
		GeneralPermission							m_generalPermissions;
	};

} // namespace fxcm

#endif // __fxcmPermission_hpp__

