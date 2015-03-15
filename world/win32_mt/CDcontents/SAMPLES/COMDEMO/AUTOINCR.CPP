/*
 * AutoIncr.cpp : Implementation of CComDemoApp and DLL registration.
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 17
 *
 * Implements a FreeThreaded COM Object CAutoIncr
 */


#include "stdafx.h"
#include "ComDemo.h"
#include "AutoIncr.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CAutoIncr::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAutoIncr,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// User Functions start here

CAutoIncr::CAutoIncr()
{
	// Initialize Counters
	m_iValue1 = 0;
	m_iValue2 = 0;
}

STDMETHODIMP CAutoIncr::get_SlowCounter(WORD* pValue)
{
	Sleep(15000); // simulate work being done.
	if (pValue)
	{	// Return value and increase for next time
		*pValue = m_iValue1++;
		return S_OK;
	}
	return E_POINTER;
}

STDMETHODIMP CAutoIncr::get_FastCounter(WORD* pValue)
{
	Sleep(2000); // simulate work being done.
	if (pValue)
	{	// Return value and increase for next time
		*pValue = m_iValue2++;
		return S_OK;
	}
	return E_POINTER;
}

STDMETHODIMP CAutoIncr::get__NewEnum(IUnknown** retval)
{
	if (retval == NULL)
		return E_POINTER;
	*retval = NULL;
	typedef CComObject<CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT,
		_Copy<VARIANT> > > enumvar;
	HRESULT hRes = S_OK;
	enumvar* p = new enumvar;
	if (p == NULL)
		hRes = E_OUTOFMEMORY;
	else 
	{
		hRes = p->FinalConstruct();
		if (hRes == S_OK)
		{
			hRes = p->Init(&m_var[0], &m_var[4], NULL, AtlFlagCopy);
			if (hRes == S_OK)
				hRes = p->QueryInterface(IID_IUnknown, (void**)retval);
		}
	}
	if (hRes != S_OK)
		delete p;
	return hRes;
}
