// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#include <afxdisp.h>
// CSlicerCacheLevel wrapper class

class CSlicerCacheLevel : public COleDispatchDriver
{
public:
	CSlicerCacheLevel(){} // Calls COleDispatchDriver default constructor
	CSlicerCacheLevel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSlicerCacheLevel(const CSlicerCacheLevel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// SlicerCacheLevel methods
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_SlicerItems()
	{
		LPDISPATCH result;
		InvokeHelper(0xba1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Ordinal()
	{
		long result;
		InvokeHelper(0xba5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_CrossFilterType()
	{
		long result;
		InvokeHelper(0xba2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_CrossFilterType(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xba2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SortItems()
	{
		long result;
		InvokeHelper(0xba3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SortItems(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xba3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_VisibleSlicerItemsList()
	{
		VARIANT result;
		InvokeHelper(0xba0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}

	// SlicerCacheLevel properties
public:

};
