#include "stdafx.h"
#include "DebugWrapperDevicePropertyStore.h"

#include <propkey.h>
#include <functiondiscoverykeys_devpkey.h>

// example: L"{1}.TUSBAUDIO_ENUM\\VID_1397&PID_0508&KS\\9&34A5FE73&4&4"
DEFINE_PROPERTYKEY(PKEY_Device_DeviceIdHiddenKey1, 0xb3f8fa53, 0x0004, 0x438e, 0x90, 0x03, 0x51, 0xa4, 0x6e, 0x13, 0x9b, 0xfc, 2);

// example: L"oem24.inf:7a9b59c8209f0782:_Install_8.NTamd64:4.59.0.56775:TUSBAUDIO_ENUM\\VID_1397&PID_0508&KS"
DEFINE_PROPERTYKEY(PKEY_Device_DeviceIdHiddenKey2, 0x83DA6326, 0x97A6, 0x4088, 0x94, 0x53, 0xA1, 0x92, 0x3F, 0x57, 0x3B, 0x29, 3);


#define DEBUG_PRINT_HR(hr) if(FAILED(hr)) rslog::info_ts() << "  hr: " << HResultToStr(hr) << std::endl

DebugWrapperDevicePropertyStore::DebugWrapperDevicePropertyStore(IPropertyStore& realPropertyStore, const std::wstring& deviceId)
	: m_RealPropertyStore(realPropertyStore)
	, m_DeviceId(deviceId)
{
	m_RealPropertyStore.AddRef();
}

DebugWrapperDevicePropertyStore::~DebugWrapperDevicePropertyStore()
{
	m_RealPropertyStore.Release();
}

HRESULT STDMETHODCALLTYPE DebugWrapperDevicePropertyStore::GetCount(DWORD *cProps)
{
	rslog::info_ts() << m_DeviceId << " " __FUNCTION__ << std::endl;

	HRESULT hr = m_RealPropertyStore.GetCount(cProps);

	DEBUG_PRINT_HR(hr);
	
	if (SUCCEEDED(hr) && cProps)
	{
		rslog::info_ts() << "  *cProps: " << std::dec << *cProps << std::endl;
	}

	return hr;
}

HRESULT STDMETHODCALLTYPE DebugWrapperDevicePropertyStore::GetAt(DWORD iProp, PROPERTYKEY *pkey)
{
	// NOTE: this log entry gets too noisy on WASAPI devices...
	//rslog::info_ts() << m_DeviceId << " " __FUNCTION__ " - iProp: " << std::dec << iProp << std::endl;

	HRESULT hr = m_RealPropertyStore.GetAt(iProp, pkey);
	DEBUG_PRINT_HR(hr);

	return hr;
}

HRESULT STDMETHODCALLTYPE DebugWrapperDevicePropertyStore::GetValue(REFPROPERTYKEY key, PROPVARIANT *pv)
{
	//rslog::info_ts() << m_DeviceId << " " __FUNCTION__ " - key: " << key << std::endl;

	HRESULT hr = m_RealPropertyStore.GetValue(key, pv);
	DEBUG_PRINT_HR(hr);
	/*
	if (hr == S_OK)
	{
		if (pv->vt == VT_EMPTY)
		{
			rslog::info_ts() << "  unhandled key" << std::endl;
		}
		else if (key == PKEY_AudioEngine_DeviceFormat && pv->vt == VT_BLOB)
		{	
			rslog::info_ts() << *(WAVEFORMATEX*)pv->blob.pBlobData;
		}
		else if (key == PKEY_AudioEndpoint_FormFactor && pv->vt == VT_UI4)
		{
			rslog::info_ts() << "  form factor: " << std::dec << pv->uintVal << std::endl;
		}
		else if (key == PKEY_Device_FriendlyName)
		{
			if (pv->vt == VT_LPWSTR)
				rslog::info_ts() << "  friendly name: " << std::dec << pv->pwszVal << std::endl;
			else if (pv->vt == VT_LPSTR)
				rslog::info_ts() << "  friendly name: " << std::dec << pv->pszVal << std::endl;
		}
	}
	*/

	return hr;
}

HRESULT STDMETHODCALLTYPE DebugWrapperDevicePropertyStore::SetValue(REFPROPERTYKEY key, REFPROPVARIANT propvar)
{
	rslog::info_ts() << m_DeviceId << " " __FUNCTION__ " - key: " << key << std::endl;

	HRESULT hr = m_RealPropertyStore.SetValue(key, propvar);
	DEBUG_PRINT_HR(hr);

	return hr;
}

HRESULT STDMETHODCALLTYPE DebugWrapperDevicePropertyStore::Commit()
{
	rslog::info_ts() << m_DeviceId << " " __FUNCTION__ << std::endl;

	HRESULT hr = m_RealPropertyStore.Commit();
	DEBUG_PRINT_HR(hr);

	return hr;
}
