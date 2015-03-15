/*
 * AutoIncr.h : Declaration of the CAutoIncr
 *
 * Sample code for "Multitasking in Win32"
 * This is from Chapter 17
 *
 * Implements a FreeThreaded COM Object
 */


#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// ComDemo

class CAutoIncr : 
	public CComDualImpl<IAutoIncr, &IID_IAutoIncr, &LIBID_COMDEMOLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CAutoIncr,&CLSID_CAutoIncr>
{
public:
	CAutoIncr();

BEGIN_COM_MAP(CAutoIncr)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAutoIncr)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CAutoIncr) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation.  The default is to support it

DECLARE_REGISTRY(CAutoIncr, _T("ComDemo.AutoIncr.1"), _T("ComDemo.AutoIncr"), IDS_AUTOINCR_DESC, THREADFLAGS_BOTH)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAutoIncr
public:
	STDMETHOD(get_SlowCounter)(WORD* pValue);
	STDMETHOD(get_FastCounter)(WORD* pValue);
	STDMETHOD(get__NewEnum)(IUnknown** retval);

protected:
	WORD m_iValue1;
	WORD m_iValue2;

	CComVariant m_var[4];
};
