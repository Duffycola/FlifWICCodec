#include "decode_metadata_reader.h"
#include "uuid.h"

DecodeMetadataQueryReader::DecodeMetadataQueryReader(UINT width, UINT height, UINT frame_delay)
	: width_(width), height_(height), frame_delay_(frame_delay)
{

}

DecodeMetadataQueryReader::~DecodeMetadataQueryReader()
{
}

HRESULT DecodeMetadataQueryReader::QueryInterface(REFIID riid, void ** ppvObject)
{
	TRACE2("(%s, %p)\n", debugstr_guid(riid), ppvObject);
	if (ppvObject == nullptr)
		return E_INVALIDARG;
	*ppvObject = nullptr;

	if (!IsEqualGUID(riid, IID_IUnknown) &&
		!IsEqualGUID(riid, IID_IWICMetadataQueryReader))
		return E_NOINTERFACE;
	this->AddRef();
	*ppvObject = static_cast<IWICMetadataQueryReader*>(this);
	return S_OK;
}


HRESULT DecodeMetadataQueryReader::GetLocation(UINT cchMaxLength, WCHAR * wzNamespace, UINT * pcchActualLength)
{
	TRACE3("(%d, %p, %p)\n", cchMaxLength, wzNamespace, pcchActualLength);
	return WINCODEC_ERR_PROPERTYNOTSUPPORTED;
}

HRESULT DecodeMetadataQueryReader::GetMetadataByName(LPCWSTR wzName, PROPVARIANT * pvarValue)
{
	TRACE2("(%p, %p)\n", wzName, pvarValue);
	if (wzName == nullptr)
		return E_INVALIDARG;

	if (pvarValue == nullptr)
		return E_INVALIDARG;

	// Fake Gif Information
	if (_wcsicmp(L"/logscrdesc/Width", wzName) == 0)
	{
		pvarValue->uiVal = width_;
		pvarValue->vt = VT_UI2;
		return S_OK;
	}
	else if (_wcsicmp(L"/logscrdesc/Height", wzName) == 0)
	{
		pvarValue->uiVal = height_;
		pvarValue->vt = VT_UI2;
		return S_OK;
	}
	else if (_wcsicmp(L"/logscrdesc/PixelAspectRatio", wzName) == 0)
	{
		pvarValue->bVal = 0;
		pvarValue->vt = VT_UI1;
		return S_OK;
	}
	else if (_wcsicmp(L"/logscrdesc/GlobalColorTableFlag", wzName) == 0)
	{
		//return WINCODEC_ERR_PROPERTYNOTFOUND;
	}
	else if (_wcsicmp(L"/logscrdesc/BackgroundColorIndex", wzName) == 0)
	{
		//return WINCODEC_ERR_PROPERTYNOTFOUND;
	}
	else if (_wcsicmp(L"/imgdesc/Left", wzName) == 0)
	{
		pvarValue->uiVal = 0;
		pvarValue->vt = VT_UI2;
		return S_OK;
	}
	else if (_wcsicmp(L"/imgdesc/Top", wzName) == 0)
	{
		pvarValue->uiVal = 0;
		pvarValue->vt = VT_UI2;
		return S_OK;
	}
	else if (_wcsicmp(L"/imgdesc/Width", wzName) == 0)
	{
		pvarValue->uiVal = width_;
		pvarValue->vt = VT_UI2;
		return S_OK;
	}
	else if (_wcsicmp(L"/imgdesc/Height", wzName) == 0)
	{
		pvarValue->uiVal = height_;
		pvarValue->vt = VT_UI2;
		return S_OK;
	}
	else if (_wcsicmp(L"/grctlext/Disposal", wzName) == 0)
	{
		//Clear befor draw new frame
		pvarValue->bVal = 2;
		pvarValue->vt = VT_UI1;
		return S_OK;
	}
	else if (_wcsicmp(L"/grctlext/Delay", wzName) == 0)
	{
		// Delay in 10th ms
		pvarValue->uiVal = frame_delay_ / 10;
		pvarValue->vt = VT_UI2;
		return S_OK;
	}
	return WINCODEC_ERR_PROPERTYNOTFOUND;
}

HRESULT DecodeMetadataQueryReader::GetEnumerator(IEnumString ** ppIEnumString)
{
	TRACE1("(%p)\n", ppIEnumString);
	return WINCODEC_ERR_PROPERTYNOTSUPPORTED;
}

HRESULT DecodeMetadataQueryReader::GetContainerFormat(GUID * pguidContainerFormat)
{
	TRACE1("(%p)\n", pguidContainerFormat);
	if (pguidContainerFormat == nullptr)
		return E_INVALIDARG;
	*pguidContainerFormat = GUID_ContainerFormatFLIF;
	return S_OK;
}


