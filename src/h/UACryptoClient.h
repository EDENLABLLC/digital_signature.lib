#pragma once

#ifdef LINUX

#define UAC_API(type) type

#else

#define CALLING_CONVENTION __stdcall

#ifdef __BORLANDC__
#ifdef BUILD_CL
#define UAC_API(type) type __declspec( dllexport ) CALLING_CONVENTION
#else
#define UAC_API(type) type __declspec( dllimport ) CALLING_CONVENTION
#endif
#else
#define UAC_API(type) type CALLING_CONVENTION
#endif

#endif

#include "UACryptoDef.h"
#include "cryptoki.h"

#if defined( __cplusplus)
extern "C" {
#endif
/** \addtogroup client_func �������������� ������� �������
	@{ */
/** \name ��������� �� �������  */
/**
	\brief �������� ��������� � ��������� ������
	\return ��������� �� ������ ���������
*/
UAC_API(const char*)	GetLastErrorMessage();
/**
	\brief ���������� ��������� � ��������� ������
	\param[in] message ��������� �� ������ ��������� (�� 1999 ��������) ��� NULL
	\return ::UAC_SUCCESS
*/
UAC_API(DWORD)			SetLastErrorMessage(const char* message);
/**
	\brief �������� ���������� ���������� ���� ������
	\param[in] code ��� ������
	\return ��������� �� ������ c ���������� ������������ ���� ������
*/
UAC_API(const char*)	GetErrorCodeDescription(int code);

/** \name ���-�������  */
/**
	\brief ���������� ���-������ �� ������
	\param[in] pData ������
	\param[in] pCert ����������, ���������� ��������� ����, ��� NULL
	\param[out] pHash ����� ��� ����
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_HashCreate(
	UAC_IN PUAC_BLOB		pData,
	UAC_IN PUAC_BLOB		pCert,
	UAC_OUT PUAC_BLOB	 	pHash );

/**
	\brief �������� ���-������� �� ������
	\param[in] pData ������
	\param[in] pCert ����������, ���������� ��������� ����, ��� NULL
	\param[in] pHash ��������� �������� ����
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_HashVerify(
	UAC_IN PUAC_BLOB		pData,
	UAC_IN PUAC_BLOB		pCert,
	UAC_IN PUAC_BLOB	 	pHash );

/** \name �����������  */
/**
	\brief �������� ���������� � �����������
	\param[in] pCert		����������
	\param[out] pCertInfo	����� ��� ���������� �����������
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CertLoad (
	UAC_IN PUAC_BLOB pCert,
	UAC_OUT PUAC_CERT_INFO pCertInfo );
/**
	\brief �������� ������� �����������
	\param[in] pUserCert	����������� ����������
	\param[out] pIssuerCert	����������� ��������
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CertVerify (
	UAC_IN PUAC_BLOB pUserCert,
	UAC_IN PUAC_BLOB pIssuerCert );
/**
	\brief �������� ������������ ����������� � ������ �� ����������
	� ������ �������������� ���������� ::UAC_ERROR_NO_SIGNER
	\param[in] pCert		����������
	\param[in] pCertRef		������ �� ����������
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CertMatch (
	UAC_IN PUAC_CERT_REF	pCertRef,
	UAC_IN PUAC_BLOB		pCert );

/**
	\brief �������� ������ �� ����������
	\param[in] pCert		����������
	\param[out] pSubjectRef	��������� ��� ������ �� ����������
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CertSubjectRef (
	UAC_IN PUAC_BLOB pCert,
	UAC_OUT PUAC_CERT_REF pSubjectRef );
/**
	\brief �������� ������ �� ���������� ��������
	\param[in] pCert		�������� ����������
	\param[out] pIssuerRef	��������� ��� ������ �� ���������� ��������
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CertIssuerRef (
	UAC_IN PUAC_BLOB pCert,
	UAC_OUT PUAC_CERT_REF pIssuerRef );

/**
	\brief �������� ������������ ������������ ����������� � ���������� �����
	� ������ �������������� ��������������� ���������� ::UAC_ERROR_KEYPAIR
	\param[in] pKeys		���� ������ (���������� � ���������� ��� ������� � ���������� �����)
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_KeyPairVerify (
	UAC_IN PUAC_KEYPAIR pKeys );

/** \name �������� ������������  */
/**
	\brief ��������� ������. �������� ��������� ����������. ������������ ��������������� ������ �� ������������ ������.
	\param[in] pRequestInfo	���������� ��������� ��������� �����������
	\param[in] pParam		��������� ��������� �����
	\param[out] pPrivateKey	����� ��� ���������� � ��������� ������
	\param[out] pRequest	����� ��� ������ �� ������������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CertRequestCreate (
	UAC_IN PUAC_CERT_REQUEST_INFO	pRequestInfo,
	UAC_IN PUAC_BLOB				pParam,
	UAC_OUT PUAC_PRIVATE_KEY		pPrivateKey,
	UAC_OUT	PUAC_BLOB				pRequest );
/**
	\brief ������������ ��������������� ������ �� ����� �������������� �����������
	\param[in] pRequest		������ �� ������������ PKCS#10
	\param[in] pRequestInfo	����������������� ��������� ������
	\param[in] pKeys		���������� � ���� �������������� �����������
	\param[out] pRequestSigned	����� ��� ����������� ������ �� ������������
*/
UAC_API(DWORD) UAC_CertRequestSign (
	UAC_IN PUAC_BLOB pRequest,
	UAC_IN PUAC_CERT_REQUEST_INFO pRequestInfo,
	UAC_IN PUAC_KEYPAIR pKeys,
	UAC_OUT PUAC_BLOB pRequestSigned );
/** \name ������ ���������� ������������ (CRL)  */
/**
	\brief �������� ���������� � ������ ���������� ������������ (CRL)
	\param[in] pCrl			CRL
	\param[in] pCrlInfo		��������� ��� ���������� � CRL

*/
UAC_API(DWORD) UAC_CrlLoad (
	UAC_IN	PUAC_BLOB pCrl,
	UAC_OUT PUAC_CRL_INFO pCrlInfo );
/**
	\brief �������� ������� ������ ���������� ������������ (CRL)
	\param[in] pCrl			CRL
	\param[in] pIssuerCert	���������� ���
*/
UAC_API(DWORD) UAC_CrlVerify (
	UAC_IN PUAC_BLOB pCrl,
	UAC_IN PUAC_BLOB pIssuerCert );

/** \name ������� � ������������ ������� (SignedData)  */
/**
	\brief ������������ �������� � ������������ �������
	\param[in] pData			���� ������
	\param[in] pSigners			������ � ������� �����������
	\param[in] pTimeStamps		������ � ������� ������� ��� ������ ��� ������� ���������� ��� NULL
	\param[in] dwSignersCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_STORE_CONTENT
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID
		::UAC_OPTION_INCLUDE_SIGNED_TIME
		::UAC_OPTION_FORCE_SIGN_ATTRS

	\param[out] pSignedData		����� ��� ����������� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_SignedDataCreate (
	UAC_IN PUAC_BLOB			pData,
	UAC_IN PUAC_KEYPAIR			pSigners,
	UAC_IN PUAC_BLOB			pTimeStamps,
	UAC_IN DWORD				dwSignersCount,
	UAC_IN DWORD				dwOptions,
	UAC_OUT PUAC_BLOB			pSignedData );

/**
	\brief ������������ �������� � ������������ ������� + ���������� � ������� ���������
	\param[in] pData			���� ������
	\param[in] pSigners			������ � ������� �����������
	\param[in] pTimeStamps		������ � ������� ������� ��� ������ ��� ������� ���������� ��� NULL
	\param[in] pAttributes		������ � ����������, ���������������� ������������, ��� NULL
	\param[in] dwSignersCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_STORE_CONTENT
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID
		::UAC_OPTION_INCLUDE_SIGNED_TIME
		::UAC_OPTION_FORCE_SIGN_ATTRS

	\param[out] pSignedData		����� ��� ����������� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_SignedDataCreate2 (
	UAC_IN PUAC_BLOB			pData,
	UAC_IN PUAC_KEYPAIR			pSigners,
	UAC_IN PUAC_BLOB			pTimeStamps,
	UAC_IN PUAC_SIGNATURE_ATTR  pAttributes,
	UAC_IN DWORD				dwSignersCount,
	UAC_IN DWORD				dwOptions,
	UAC_OUT PUAC_BLOB			pSignedData );

/**
	\brief ������������ ������� ������ �� ������ + ���������� � ���������
	\param[in] pDataInput		����� ������������� ������
	\param[in] pSigners			������ � ������� �����������
	\param[in] pTimeStamps		������ � ������� ������� ��� ������ ��� ������� ���������� ��� NULL
	\param[in] pAttributes		������ � ����������, ���������������� ������������, ��� NULL
	\param[in] dwSignersCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID
		::UAC_OPTION_INCLUDE_SIGNED_TIME

	\param[out] pSignedData		����� ��� �������
	������ ������� ������������� ������� SignedData ��� ���������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_SignatureCreate ( 
	UAC_IN PUAC_STREAM			pDataInput,
	UAC_IN PUAC_KEYPAIR			pSigners,
	UAC_IN PUAC_BLOB			pTimeStamps,
	UAC_IN PUAC_SIGNATURE_ATTR  pAttributes,
	UAC_IN DWORD				dwSignersCount,
	UAC_IN DWORD				dwOptions,
	UAC_OUT PUAC_BLOB	 		pSignature );

/**
	\brief ���������� ����� �������� � ������� � ������������ �������
	\param[in] pSignedData		�������� ������� � ������������ �������
	\param[in] pExternalData	���� ������� ������ ��� NULL, ���� ������ ��������� � ��������
	\param[in] pSigners			������ � ������� �����������
	\param[in] pTimeStamps		������ � ������� ������� ��� ������ ��� ������� ���������� ��� NULL
	\param[in] dwSignersCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID
		::UAC_OPTION_INCLUDE_SIGNED_TIME
		::UAC_OPTION_FORCE_SIGN_ATTRS

	\param[out] pNewSignedData	����� ��� ������ ��������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_SignedDataAppend (
	UAC_IN PUAC_BLOB			pSignedData,
	UAC_IN PUAC_BLOB			pExternalData,
	UAC_IN PUAC_KEYPAIR			pSigners,
	UAC_IN PUAC_BLOB			pTimeStamps,
	UAC_IN DWORD				dwSignersCount,
	UAC_IN DWORD				dwOptions,
	UAC_OUT PUAC_BLOB			pNewSignedData );

/**
	\brief �������� ���������� � �������� ����������� ������
	\param[in] pSignedData		������� � ������������ �������
	\param[out] pData			����� ��� ������ �� �������� ��� NULL
	\param[out] pInfo			��������� ��� ���������� � �������� ��� NULL
	\note ���� �� ���� �� ���������� pData ��� pInfo ������ ���� ���������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_SignedDataLoad (
	UAC_IN	PUAC_BLOB pSignedData,
	UAC_OUT PUAC_BLOB pData,
	UAC_OUT PUAC_SIGNED_DATA_INFO pInfo );

/**
	\brief �������� ������� ������ ��� ����������� ����������
	\param[in] pSignedData		������� � ������������ �������
	\param[in] pSignerCert		���������� ����������
	\param[in] pExternalData	������� ������ ��� NULL
*/
UAC_API(DWORD) UAC_SignedDataVerify (
	UAC_IN PUAC_BLOB pSignedData,
	UAC_IN PUAC_BLOB pSignerCert,
	UAC_IN PUAC_BLOB pExternalData);

/**
	\brief �������� ������� ������ �� ������ ��� ����������� ����������
	\param[in] pSignedData		������� � ������������ �������
	\param[in] pSignerCert		���������� ����������
	\param[in] pDataInput		����� ����������� ������
*/
UAC_API(DWORD) UAC_SignatureVerify (
	UAC_IN PUAC_BLOB pSignature,
	UAC_IN PUAC_BLOB pSignerCert,
	UAC_IN PUAC_STREAM pDataInput);

/**
	\brief ���������� ����������� � ������� � ������������ �������
	\param[in] pSignedData		������� � ������������ �������
	\param[in] pCert			����������� ����������
	\param[out] pNewSignedData	����� ��� ������ ��������
*/

UAC_API(DWORD) UAC_SignedDataAddCert (
	UAC_IN PUAC_BLOB pSignedData,
	UAC_IN PUAC_BLOB pCert,
	UAC_IN PUAC_BLOB pNewSignedData );

/**
	\brief ���������� ����������� �� ������� �� �������� � ������������ �������
	\param[in] pSignedData		������� � ������������ �������
	\param[in] dwIndex			������ ����������� � �������� (� ����)
	\param[out] pCert			����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_SignedDataGetCert (
	UAC_IN PUAC_BLOB		pSignedData,
	UAC_IN DWORD			dwIndex,
	UAC_OUT PUAC_BLOB		pCert );
/**
	\brief ���������� ����������� �� ��������� ������ �� �������� � ������������ �������
	\param[in] pSignedData		������� � ������������ �������
	\param[in] pCertRef			������ �� ����������
	\param[out] pCert			����� ��� ������������ �����������
*/

UAC_API(DWORD) UAC_SignedDataFindCert (
	UAC_IN PUAC_BLOB		pSignedData,
	UAC_IN PUAC_CERT_REF	pCertRef,
	UAC_OUT PUAC_BLOB		pCert );
/**
	\brief ���������� ����� ������� ������ �� �������� � ������������ �������
	\param[in] pSignedData		������� � ������������ �������
	\param[in] dwSignerIndex	������ ���������� � �������� (� ����)
	\param[out] pTs 			����� ��� ����� �������
*/

UAC_API(DWORD) UAC_SignedDataGetTs (
	UAC_IN PUAC_BLOB	pSignedData,
	UAC_IN DWORD		dwSignerIndex,
	UAC_OUT PUAC_BLOB	pTs );

/** \name �������� ������� ����������� (OCSP)  */
/**
	\brief ������������ ������� �� �������� ������� �����������
	\param[in] pTargetCert		����������, ������������ ��������
	\param[in] pSignerKeys		����� ���������� ������� ��� NULL, ���� ������ �� �����������
	\param[in] dwOptions		�����
	\par ��������� �����:
		::UAC_OPTION_INCLUDE_VERSION		- ������� ������ �������\n
		::UAC_OPTION_INCLUDE_NONCE			- �������� ������������� �������

	\param[out] pOcspRequest	����� ��� ������������ �������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_OcspRequestCreate (
	UAC_IN PUAC_BLOB			pTargetCert,
	UAC_IN PUAC_KEYPAIR			pSignerKeys,
	UAC_IN DWORD				dwOptions,
	UAC_OUT PUAC_BLOB			pOcspRequest );

/**
	\brief ������������ ������� �� �������� ������� �����������
	�� ������ �� ���������� � ����������� ��������
	\param[in] pTargetCertRef	������ �� ����������, ������������ ��������
		\note ��������� ������ � ������ ::UAC_OPTION_IDENT_BY_SERIAL_NUMBER, ����� ������ ������ ::UAC_ERROR_NODATA
	\param[in] pTargetIssuerCert ���������� �������� ������������ �����������
	\param[in] pSignerKeys		����� ���������� ������� ��� NULL, ���� ������ �� �����������
	\param[in] dwOptions		�����
	\par ��������� �����:
		::UAC_OPTION_INCLUDE_VERSION		- ������� ������ �������\n
		::UAC_OPTION_INCLUDE_NONCE			- �������� ������������� �������

	\param[out] pOcspRequest	����� ��� ������������ �������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_OcspRequestCreateByIssuer (
	UAC_IN PUAC_CERT_REF		pTargetCertRef,
	UAC_IN PUAC_BLOB			pTargetIssuerCert,
	UAC_IN PUAC_KEYPAIR			pSignerKeys,
	UAC_IN DWORD				dwOptions,
	UAC_OUT PUAC_BLOB			pOcspRequest );

/**
	\brief ���������� ����������� � ������ �� �������� ������� �����������
	\param[in] pRequest			������ �� �������� ������� �����������
	\param[in] pCert			����������� ����������
	\param[out] pNewRequest	    ����� ��� ������ �������
*/
UAC_API(DWORD) UAC_OcspRequestAddCert (
	UAC_IN PUAC_BLOB		pRequest,
	UAC_IN PUAC_BLOB		pCert,
	UAC_IN PUAC_BLOB		pNewRequest );
/**
	\brief �������� ���������� �� ������ �� ������ ������� �����������
	\param[in] pResponse		�����
	\param[out] pResponseInfo	��������� ���������� �� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_OcspResponseLoad (
	UAC_IN	PUAC_BLOB pResponse,
	UAC_OUT PUAC_OCSP_RESPONSE_INFO pResponseInfo );
/**
	\brief �������� ������� ������ �� ������ ������� �����������
	\param[in] pResponse		�����
	\param[in] pSignerCert		���������� ����������
*/
UAC_API(DWORD) UAC_OcspResponseVerify (
	UAC_IN PUAC_BLOB pResponse,
	UAC_IN PUAC_BLOB pSignerCert );

/**
	\brief ���������� ����������� � ����� �� ������ ������� �����������
	\param[in] pResponse		�����
	\param[in] pCert			����������� ����������
	\param[out] pNewResponse	����� ��� ������ ������
*/
UAC_API(DWORD) UAC_OcspResponseAddCert (
	UAC_IN PUAC_BLOB	pResponse,
	UAC_IN PUAC_BLOB	pCert,
	UAC_IN PUAC_BLOB	pNewResponse );

/**
	\brief ���������� ����������� �� ������� �� ������ �� ������ ������� �����������
	\param[in] pResponse		�����
	\param[in] dwIndex			������ ����������� (� ����)
	\param[out] pCert			����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_OcspResponseGetCert (
	UAC_IN PUAC_BLOB	pResponse,
	UAC_IN DWORD		dwIndex,
	UAC_OUT PUAC_BLOB	pCert );

/**
	\brief ���������� ����������� �� ��������� ������ �� ������ �� ������ ������� �����������
	\param[in] pResponse		�����
	\param[in] pCertRef			������ �� ����������
	\param[out] pCert			����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_OcspResponseFindCert (
	UAC_IN PUAC_BLOB		pResponse,
	UAC_IN PUAC_CERT_REF	pCertRef,
	UAC_OUT PUAC_BLOB		pCert );

/** \name ����� ������� (TSP)  */
/**
	\brief ������������ ������� �� �������� ����� �������
	\param[in] pHash			�������� ���-������ ������
	\param[in] nonce			������������� �������
	\param[in] dwOptions		�����
	��������� �����:
		::UAC_OPTION_QUERY_CERT				��������� ���������� ������� ����� ������� � ������
	\param[out] pTsRequest		����� ��� �������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TsRequestCreate (
	UAC_IN PUAC_BLOB			pHash,
	UAC_IN UAC_SERIAL_NUMBER	nonce,
	UAC_IN DWORD				dwOptions,
	UAC_OUT PUAC_BLOB			pTsRequest );
/**
	\brief �������� ���������� �� ������ c ������ �������
	\param[in] pTsResponse		�����
	\param[out] pTsInfo	        ��������� ��� ���������� �� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TsResponseLoad (
	UAC_IN	PUAC_BLOB pTsResponse,
	UAC_OUT PUAC_TIME_STAMP_INFO pTsInfo );

/**
	\brief �������� ������� ������ c ������ �������
	\param[in] pResponse		�����
	\param[in] pSignerCert		���������� ����������
*/

UAC_API(DWORD) UAC_TsResponseVerify (
	UAC_IN PUAC_BLOB pResponse,
	UAC_IN PUAC_BLOB pSignerCert );

/**
	\brief �������� ������������ ���� ��������� c ������ �������
	\param[in] pHash			�������� ���-������ ������
	\param[out] pTsInfo	        ���������� �� ������
*/

UAC_API(DWORD) UAC_TsVerifyHash (
	UAC_IN PUAC_BLOB pHash,
	UAC_IN PUAC_TIME_STAMP_INFO pTsInfo );

/**
	\brief ���������� ����������� � ����� c ������ �������
	\param[in] pResponse		�����
	\param[in] pCert			����������� ����������
	\param[out] pNewResponse	����� ��� ������ ������
*/

UAC_API(DWORD) UAC_TsResponseAddCert (
	UAC_IN PUAC_BLOB pResponse,
	UAC_IN PUAC_BLOB pCert,
	UAC_IN PUAC_BLOB pNewResponse );

/**
	\brief ���������� ����������� �� ������� �� ������ c ������ �������
	\param[in] pResponse		�����
	\param[in] dwIndex			������ ����������� (� ����)
	\param[out] pCert			����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_TsResponseGetCert (
	UAC_IN PUAC_BLOB	pResponse,
	UAC_IN DWORD		dwIndex,
	UAC_OUT PUAC_BLOB	pCert );
/**
	\brief ���������� ����������� �� ��������� ������ �� ������ c ������ �������
	\param[in] pResponse		�����
	\param[in] pCertRef			������ �� ����������
	\param[out] pCert			����� ��� ������������ �����������
*/

UAC_API(DWORD) UAC_TsResponseFindCert (
	UAC_IN PUAC_BLOB		pResponse,
	UAC_IN PUAC_CERT_REF	pCertRef,
	UAC_OUT PUAC_BLOB		pCert );

/** \name ������� � �������������� ������� (Envelope, EnvelopedData)  */
/**
	\brief ������������ �������� � �������������� �������
	\param[in] pData			���� ������
	\param[in] pOriginatorKey	����� �����������
	\param[in] pRecipientCerts	������ � ������������� �����������
	\param[in] dwRecipientCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID

	\param[out] pExternalData	����� ��� �������� �������������� ��������� ��� NULL
	\param[out] pEnvelope		����� ��� ��������

	\return ��� ������ ��� ::UAC_SUCCESS
*/

UAC_API(DWORD) UAC_EnvelopeCreate (
	UAC_IN PUAC_BLOB			pData,
	UAC_IN PUAC_KEYPAIR			pOriginatorKey,
	UAC_IN PUAC_BLOB			pRecipientCerts,
	UAC_IN DWORD				dwRecipientCount,
	UAC_IN DWORD				dwOptions,
	UAC_IN PUAC_BLOB			pExternalData,
	UAC_OUT PUAC_BLOB			pEnvelope );

/**
	\brief ������������ �������� � �������������� ������� � ��������� ��� ����������
	\param[in] pData			���� ������
	\param[in] pOriginatorKey	����� �����������
	\param[in] pRecipientCerts	������ � ������������� �����������
	\param[in] dwRecipientCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID

	\param[out] pExternalData	����� ��� �������� �������������� ��������� ��� NULL
	\param[in]  pDke			��� ��� ����������� ��� NULL

	\param[out] pEnvelope		����� ��� ��������

	\return ��� ������ ��� ::UAC_SUCCESS
*/

UAC_API(DWORD) UAC_EnvelopeCreateDke (
	UAC_IN PUAC_BLOB			pData,
	UAC_IN PUAC_KEYPAIR			pOriginatorKey,
	UAC_IN PUAC_BLOB			pRecipientCerts,
	UAC_IN DWORD				dwRecipientCount,
	UAC_IN DWORD				dwOptions,
	UAC_IN PUAC_BLOB			pExternalData,
	UAC_IN PUAC_BLOB			pDke,
	UAC_OUT PUAC_BLOB			pEnvelope );

/**
	\brief ������������ �������� � �������������� ������� � ��������� ��������� ����������
	\param[in] pData			���� ������
	\param[in] pOriginatorKey	����� �����������
	\param[in] pRecipientCerts	������ � ������������� �����������
	\param[in] dwRecipientCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID

	\param[out] pExternalData	����� ��� �������� �������������� ��������� ��� NULL
	\param[in]  cypherOid		��������� ������������� ��������� ����������� (��� NULL == Gost28147 Mode2)

	\param[out] pEnvelope		����� ��� ��������

	\return ��� ������ ��� ::UAC_SUCCESS
*/

UAC_API(DWORD) UAC_EnvelopeCreateEx (
	UAC_IN PUAC_BLOB			pData,
	UAC_IN PUAC_KEYPAIR			pOriginatorKey,
	UAC_IN PUAC_BLOB			pRecipientCerts,
	UAC_IN DWORD				dwRecipientCount,
	UAC_IN DWORD				dwOptions,
	UAC_IN PUAC_BLOB			pExternalData,
	UAC_IN CONST_PCHAR			cypherOid,
	UAC_OUT PUAC_BLOB			pEnvelope );


/**
	\brief ������������ �������� � �������������� ������� � ��������� ��������� ����������
	\param[in] pOriginatorKey	����� �����������
	\param[in] pRecipientCerts	������ � ������������� �����������
	\param[in] dwRecipientCount	���������� �����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_EXTERNAL_ENVELOPE
		::UAC_OPTION_INCLUDE_CERT
		::UAC_OPTION_IDENT_BY_SERIAL_NUMBER
		::UAC_OPTION_IDENT_BY_KEY_ID
	\param[in] pDataInput		������� ����� �������� ������
	\param[in] pDataOutput		�������� ����� ������������� ������
	\param[in]  cypherOid		��������� ������������� ��������� ����������� (��� NULL == Gost28147 Mode2)
	\param[in]  pDke			��������� ��������� ����������� ��� NULL
	\param[out] pEnvelope		����� ��� ��������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_EnvelopeCreateStream (
	UAC_IN PUAC_KEYPAIR			pOriginatorKey,
	UAC_IN PUAC_BLOB			pRecipientCerts,
	UAC_IN DWORD				dwRecipientCount,
	UAC_IN DWORD				dwOptions,
	UAC_IN PUAC_STREAM			pDataInput,
	UAC_IN PUAC_STREAM			pDataOutput,
	UAC_IN CONST_PCHAR			cypherOid,
	UAC_IN PUAC_BLOB			pDke,
	UAC_OUT PUAC_BLOB			pEnvelope );

/**
	\brief �������� ���������� � �������� � �������������� �������
	\param[in] pEnvelope		�������
	\param[out] pInfo	        ��������� ��� ���������� � ��������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_EnvelopeLoad (
	UAC_IN	PUAC_BLOB pEnvelope,
	UAC_OUT PUAC_ENVELOPE_INFO pInfo );

/**
	\brief ������������� ������ �� ��������
	\param[in] pEnvelope		�������
	\param[in] pOriginatorCert	���������� ����������� (��� NULL, ��� ������������ �����)
	\param[in] pRecipientKeys	�����  ����������
	\param[in] pExternalData    ������� ������������� ��������� ��� NULL
	\param[out] pPlainData		����� ��� ������������� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_EnvelopeDecrypt (
	UAC_IN	PUAC_BLOB			pEnvelope,
	UAC_IN	PUAC_BLOB			pOriginatorCert,
	UAC_IN	PUAC_KEYPAIR		pRecipientKeys,
	UAC_IN	PUAC_BLOB			pExternalData,
	UAC_OUT PUAC_BLOB			pPlainData );

/**
	\brief ������������� ������ �� ������ �� ����� �� ��������
	\param[in] pEnvelope		�������
	\param[in] pOriginatorCert	���������� ����������� (��� NULL, ��� ������������ �����)
	\param[in] pRecipientKeys	�����  ����������
	\param[in] dwOptions		���������/������
	\par ��������� �����:
		::UAC_OPTION_EXTERNAL_ENVELOPE
	\param[in] pDataInput		������� ����� � ������������� ����������
	\param[out] pDataOutput		����� ��� ������������� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_EnvelopeDecryptStream (
	UAC_IN	PUAC_BLOB			pEnvelope,
	UAC_IN	PUAC_BLOB			pOriginatorCert,
	UAC_IN	PUAC_KEYPAIR		pRecipientKeys,
	UAC_IN  DWORD				dwOptions,
	UAC_IN	PUAC_STREAM			pDataInput,
	UAC_OUT PUAC_STREAM			pDataOutput );
/**
	\brief ���������� ����������� � ������� � �������������� �������
	\param[in] pEnvelope		�������
	\param[in] pCert			����������� ����������
	\param[out] pNewEnvelope	����� ��� ������ ��������
*/
UAC_API(DWORD) UAC_EnvelopeAddCert (
	UAC_IN PUAC_BLOB pEnvelope,
	UAC_IN PUAC_BLOB pCert,
	UAC_IN PUAC_BLOB pNewEnvelope );

/**
	\brief ���������� ����������� �� ������� �� �������� � �������������� �������
	\param[in] pEnvelope		�������
	\param[in] dwIndex			������ ����������� (� ����)
	\param[out] pCert			����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_EnvelopeGetCert (
	UAC_IN PUAC_BLOB	pEnvelope,
	UAC_IN DWORD		dwIndex,
	UAC_OUT PUAC_BLOB	pCert );

/**
	\brief ���������� ����������� �� ��������� ������ �� �������� � �������������� �������
	\param[in] pEnvelope		�������
	\param[in] pCertRef			������ �� ����������
	\param[out] pCert			����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_EnvelopeFindCert (
	UAC_IN PUAC_BLOB		pEnvelope,
	UAC_IN PUAC_CERT_REF	pCertRef,
	UAC_OUT PUAC_BLOB		pCert );

/** \name ���������� �����������  */
/**
	\brief �������� ����� ���������� ����4145-2002
	\param[in] pParamInfo		���������
	\param[out] pParam			����� ��� ����� ����������
*/

UAC_API(DWORD) UAC_DstuParamCreate(
	UAC_IN	PUAC_DSTU_PARAMS		pParamInfo,
	UAC_OUT	PUAC_BLOB				pParam );

/**
/**
	\brief ���������� / ���������� �������������� � ���������� � ������
	\param[in] pOldKey	        �������� ��������� � ������
	\param[in,out] pNewKey		����� ��������� � ������ (�������� ����� ������)
	\param[in] pCert	        ���������� ����� ��� ���������� ��������������
								��� NULL ��� ��� ����������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_ResetKeyId (
	UAC_IN	PUAC_PRIVATE_KEY	pOldKey,
	UAC_INOUT PUAC_PRIVATE_KEY	pNewKey,
	UAC_IN	PUAC_BLOB			pCert
	);

	\brief ����� ������ (�������) � ������
	\param[in] pOldKey	        ������� ��������� ������� � ������
	\param[in,out] pNewKey		����� ��������� ������� � ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_PasswordChange (
	UAC_IN		PUAC_PRIVATE_KEY	pOldKey,
	UAC_INOUT	PUAC_PRIVATE_KEY	pNewKey );

/**
	\brief ���������� ������ ���������� �������
	\param[out] pBuf		����� ��� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_Random ( UAC_OUT PUAC_BLOB pBuf );

/**
	\brief ��������� ������ � 16-������ ����
	\param[out] number		���� ��� ������
	\param[in] bytes	    �������� ������ � ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_RandomNumber (
	UAC_OUT	UAC_SERIAL_NUMBER	number,
	UAC_IN	DWORD				bytes );

/** \name ���������� ������� ������ � ������������ � �������� ��������  */
/**
	\brief �������� ������� ������-����������
	\param[in] contentType	��� ���������� (UAC_CT_*)
	\param[in] pData		����������� ���������
	\param[out] pSignerCert	����������� ����������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_Verify (
	UAC_IN UAC_CT		contentType,
	UAC_IN PUAC_BLOB	pData,
	UAC_IN PUAC_BLOB	pSignerCert );
/**
	\brief ���������� ����������� �� ����������
	\param[in] contentType	��� ���������� (UAC_CT_*)
	\param[in] pContent		�������� ���������
	\param[in] dwIndex		������ ����������� (� ����)
	\param[out] pCert		����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_GetCert (
	UAC_IN UAC_CT		contentType,
	UAC_IN PUAC_BLOB	pContent,
	UAC_IN DWORD		dwIndex,
	UAC_OUT PUAC_BLOB	pCert );
/**
	\brief ���������� ����������� � ���������
	\param[in] contentType	��� ���������� (UAC_CT_*)
	\param[in] pContent		�������� ���������
	\param[in] pCert		����������� ����������
	\param[out] pNewContent	����� ��� ������ ����������
*/
UAC_API(DWORD) UAC_AddCert (
	UAC_IN UAC_CT		contentType,
	UAC_IN PUAC_BLOB	pContent,
	UAC_IN PUAC_BLOB	pCert,
	UAC_IN PUAC_BLOB	pNewContent );
/**
	\brief ���������� ����������� �� ��������� ������ �� ����������
	\param[in] contentType	��� ���������� (UAC_CT_*)
	\param[in] pContent		�������� ���������
	\param[in] pCertRef		������ �� ����������
	\param[out] pCert		����� ��� ������������ �����������
*/
UAC_API(DWORD) UAC_FindCert (
	UAC_IN UAC_CT			contentType,
	UAC_IN PUAC_BLOB		pContent,
	UAC_IN PUAC_CERT_REF	pCertRef,
	UAC_OUT PUAC_BLOB		pCert );

/**
	\brief ���������� CMS-��� ��������� (UAC_CT_DATA, UAC_CT_SIGNEDDATA ��� UAC_CT_ENVELOPEDDATA)
	\param[in] pData		�������� ��������
	\param[out] pType		����� ��� CMS-����
*/

UAC_API(DWORD) UAC_GetCmsType (
	UAC_IN PUAC_BLOB			pData,
	UAC_OUT PDWORD				pType	);

/**
	\brief ������� CMS-��� �� ��������� (UAC_CT_SIGNEDDATA ��� UAC_CT_ENVELOPEDDATA)
	\param[in,out] pData		�������� ��� ���������
	\param[out] pType		����� ��� CMS-����
*/

UAC_API(DWORD) UAC_RemoveCmsType (
	UAC_IN UAC_OUT PUAC_BLOB	pData,
	UAC_OUT PDWORD				pType	);

/**
	\brief �������� CMS-��� � ��������, ���� ��� ���������� (UAC_CT_DATA, UAC_CT_SIGNEDDATA ��� UAC_CT_ENVELOPEDDATA)
	\param[in] pData	�������� ��������
	\param[in] type		CMS-���
	\param[out] pTypedData	����� ��� ����������
*/
UAC_API(DWORD) UAC_AddCmsType (
	UAC_IN UAC_OUT PUAC_BLOB	pData,
	UAC_IN DWORD				type,
	UAC_OUT PUAC_BLOB			pTypedData	);

/** \name ���-�������  */
/**
	\brief ���������� ���-������ �� CMS-������
	������� ���������� � CMS-���� ����� �����������
	\param[in] pData ������
	\param[in] pCert ����������, ���������� ��������� ����, ��� NULL
	\param[out] pHash ����� ��� ����
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CmsHashCreate (
	UAC_IN PUAC_BLOB		pData,
	UAC_IN PUAC_BLOB		pCert,
	UAC_OUT PUAC_BLOB	 	pHash );

/**
	\brief �������� ���-������� �� CMS-������
	������� ���������� � CMS-���� ����� �����������
	\param[in] pData ������
	\param[in] pCert ����������, ���������� ��������� ����, ��� NULL
	\param[in] pHash ��������� �������� ����
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CmsHashVerify (
	UAC_IN PUAC_BLOB		pData,
	UAC_IN PUAC_BLOB		pCert,
	UAC_IN PUAC_BLOB	 	pHash );

/**
	\brief �������� CMS-�������� �� ������
	\param[in] pDataInput ������� �����
	\param[out] pCms ����� ��� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_CmsLoadStream (
	UAC_IN	PUAC_STREAM			pDataInput,
	UAC_OUT	PUAC_BLOB			pCms);

/** \name ������� ��������� ��������� �������� �������� ����������� */
/**
	\brief ��������� ������� ����� ����������� � ������ ������
	\param[in] kf		�������� ��������� ������� ���������� � ������ ������

	-	::kfCntNew	- ������ ����������� ������ - �������,
					- ������ ����������� ������ - ������ (cnt),
	-	::kfPk8New	- ������ ����������� ������ - �������,
					- ������ ����������� ������ - PKCS#8,
	-	::kfCntAlways - ������ ���� ����������� ������ - ������ (cnt),
	-	::kfPk8Always - ������ ���� ����������� ������ - PKCS#8.

	\return ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_SetKeyFormat ( KeyFormat kf ) ;

/** \name ������� ������ � ������������ PFX � ������������ ������� */
/**
	\brief	������� ������ ���������� PFX
			���������� ������ � ������������ ��������� PFX
	\param[in] pPfx			������������ ��������� PFX ��� NULL
	\param[in] password		������ � ����������
	\param[in] fileType		��� ������������ �����
	\param[in] pFileData	���������� ������������ �����
	\param[out] pNewPfx		����� ���������

	\par ����������� ���� ������:
		::UAC_ERROR_CONTENT_TYPE - ��� ����� �� ��������������
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_PfxAddFile (
	UAC_IN PUAC_BLOB		pPfx,
	UAC_IN CONST_PCHAR		password,
	BagSet					fileType,
	UAC_IN PUAC_BLOB		pFileData,
	UAC_OUT PUAC_BLOB	 	pNewPfx ) ;

/**
	\brief	�������� ������ �� ���������� PFX
	\param[in] pPfx			��������� PFX
	\param[in] password		������ � ����������
	\param[in] fileType		��� ������������ �����
	\param[in] fileIndex	������ (0..) ����� ������� ����
	\param[in] pFilesCount	��������� �� ������� ������ ��� NULL
	\param[in] pFileData	����� ��� ������������ �����

	\par ����������� ���� ������:
		::UAC_ERROR_CONTENT_TYPE		- ��� ����� �� �������������� \n
		::UAC_ERROR_NODATA			- ���� ���� ���� fileType � �������� fileIndex �����������\n
		* � ���� ������, � FilesCount ������������ ���������� ������ ������� ����

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_PfxGetFile (
	UAC_IN PUAC_BLOB		pPfx,
	UAC_IN CONST_PCHAR		password,
	BagSet					fileType,
	DWORD					fileIndex,
	PDWORD					pFilesCount,
	UAC_OUT PUAC_BLOB		pFileData ) ;

/**
	\brief	�������� ���������� � ������� � ���������� PFX
	\param[in] pPfx			��������� PFX
	\param[in] password		������ � ����������

	\par ����������� ���� ������:
		::UAC_ERROR_WRONG_PASSWORD

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_PfxVerify (
	UAC_IN PUAC_BLOB		pPfx,
	UAC_IN CONST_PCHAR		password ) ;

/** \name ������� ������ � ����������� �������� ������� (*.tok) */

/**
	\brief	����������� ��������� ������ � ����� PKCS#11
	� ��������� ��� ���������� ��������������
	\param[in] pathName		���� � ��������� ������
	\param[out] pTokenId	������ ��� �������������� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/

UAC_API(DWORD) UAC_TokenMount(
	UAC_IN CONST_PCHAR pathName,
	UAC_OUT PUAC_TOKEN pTokenId );
/**
	\brief	��������� �������������� ����� PKCS#11 � �������� �������� �������� �����
	��� ������ � ��������� PKCS#11

	������� �������������� � �� ���������� �������� PKCS#11

	\param[in] pTokenId		������������� ������
	\param[out] pSlot		������ ��� �������������� �����

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenGetSlot(
	UAC_IN	PUAC_TOKEN	pTokenId,
	UAC_OUT PQWORD		pSlot );
/**
	\brief	����������� �������������� ������ ��� ����� PKCS#11
	
	������� �������������� � �� ���������� �������� PKCS#11

	\param[in,out] pTokenId	������ ��� �������������� ������. 
							���� provider_name ������ ��������� �������� ��� ����������
	\param[in] slot			������������� �����

	\note ���� pTokenId->provider_name �������� ������ �-������ ��� ������� �����, 
	�� ������������ �������� ����� UAC (provider_name="UAC_TOK")

	\return ��� ������ ��� ::UAC_SUCCESS
*/

UAC_API(DWORD) UAC_TokenWithSlot(
	UAC_OUT PUAC_TOKEN	pTokenId,
	UAC_IN  QWORD		slot );
/**
	\brief	���������� ���� ������ PKCS#11, ��������� � �������� �������
	\param[in] pathName		���� � ��������� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenUmountPath(
	UAC_IN CONST_PCHAR		 pathName );
/**
	\brief	���������� �������� ����������� ��������� ������
	\param[in] pTokenId		������������� ������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenUmount(
	UAC_IN PUAC_TOKEN pTokenId );

/**
	\brief	�������� ������� ��������� ������
	\param[in] pathName		���� � ������ ��������� ������
	\param[in] pwd			������ ������ � ������������ � ������
	\param[in] pwdLen		����� ������
	\param[in] sn			�������� ����� ������ ������ (��� NULL) 

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenFormat(
	UAC_IN CONST_PCHAR		pathName,
	UAC_IN CONST_PCHAR		pwd, 
	UAC_IN DWORD			pwdLen,
	UAC_INOUT UAC_TOKEN_SN	sn  );

/**
	\brief	�������� ��������� ������ � �������� ����� � �����������, ��������� ������
	\param[in] tokenPathName	���� � ������ ��������� ������
	\param[in] keys				�����, ���������� � ������ ��� ������ ������
	\param[in] sn				�������� ����� ������ ������ (��� NULL) 

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenCreate(
	UAC_IN CONST_PCHAR		tokenPathName,
	UAC_IN PUAC_KEYPAIR		keys,
	UAC_INOUT UAC_TOKEN_SN	sn );
/**
	\brief	�������� ��������������� ����������� � �������� �����
	\param[in] pTokenId		������������� ������
	\param[in] pwd			������ ������� � ������
	\param[in] pwdLen		����� ������ ������� � ������
	\param[in] pCert		����������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenAddCert (
	UAC_IN PUAC_TOKEN		pTokenId,
	UAC_IN CONST_PCHAR		pwd, 
	UAC_IN DWORD			pwdLen,
	UAC_IN PUAC_BLOB		pCert );

/**
	\brief	������ ����������� �� ��������� ������
	\param[in] pTokenId		������������� ������
	\param[in] dwIndex		������ ���������� ����������� ( 0 - ���������� ����� ������ )
	\param[in] pCert		����� ��� �����������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenGetCert (
	UAC_IN	PUAC_TOKEN		pTokenId,
	UAC_IN	DWORD			dwIndex,
	UAC_OUT PUAC_BLOB		pCert );

/**
	\brief	����� � ������ ����������� �� ��������� ������ �� ������ �� ����������
	\param[in] pTokenId		������������� ������
	\param[in] pCertRef		������ �� ����������
	\param[in] pCert		����� ��� �����������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenFindCert (
	UAC_IN	PUAC_TOKEN		pTokenId,
	UAC_IN	PUAC_CERT_REF	pCertRef,
	UAC_OUT PUAC_BLOB		pCert );
/**
	\brief	���������� ��������� UAC_PRIVATE_KEY ��������������� ������ � �������
	��� ������ � ��������� UAC_* � UAC_Key*. 
	������� ��������� � UAC_PRIVATE_KEY ������ �� ����������� ����������� ����.
	
	\param[in] pTokenId		������������� ������
	\param[in] pwd			������ � ������
	\param[in] pKey			��������� UAC_PRIVATE_KEY ��� ������ � �������� UAC_*

	\note � �������� ��������� pKey ����� ������������
	����� ���� "privateKeyData" ��������� UAC_KEYPAIR.
	� ���� ������ ��������� ���� ����������� "cert" �� ����� -
	�� �������, ������� ������� ��������� UAC_KEYPAIR
	����� ������������� ��������� ���������� �� ������.

	\return ��� ������ ��� ::UAC_SUCCESS
*/

UAC_API(DWORD) UAC_TokenAsKey(
	UAC_IN	PUAC_TOKEN			pTokenId,
	UAC_IN	CONST_PCHAR			pwd,
	UAC_OUT PUAC_PRIVATE_KEY	pKey );

/**
	\brief	������ �������������� ������ UAC_TOKEN �� ��������� UAC_PRIVATE_KEY.
	������������� ����� ��� ������ � ��������� UAC_Token*.

	\param[in] pKey			��������� UAC_PRIVATE_KEY 
	\param[in] pTokenId		���� ��� �������������� ������

	\note ���� pTokenId==NULL, �� ����� ������������� �������� pKey �� �������
	�������������� ������. � ���� ������ ������� ���������:
	::UAC_ERROR_FORMAT, ���� pKey �� �������� ������������� ������,
	::UAC_ERROR_NULL_PARAM,   ���� pKey �������� ������������� ������.
	
	\note ������� �� ���������� �������� ���������� ����������� �������������� ������

	\return 
		::UAC_ERROR_FORMAT - ���� pKey �� �������� ������������� ������
		��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenOfKey(
	UAC_IN  PUAC_PRIVATE_KEY	pKey,
	UAC_OUT	PUAC_TOKEN			pTokenId );


/**
	\brief	������������ ������������ ����������
	������� ������������� ������� � ��������� ������������ �������� �������.

	������� ������ ���������� �� ������ ������ ������� UAC_Token* � ������� PKCS#11:
	� ���� ������, ��������� ������������ ����� ��������� ��� ������ ��������� � ��������� ��������.
	� ��������� ������, ���� mountOnStartup!=0, �� ����� ����������� ��������� �������� ������� �� ����� ����������.


	��� ������ ������������� ���������� PKCS#11

	\param[in] tokenDir		���� � �������� �� �������� ������������� ����������� ������
							��-��������� "."
	\param[in] tokenExt		���������� ����� ��������� ������ ��� ������������
							��-��������� ".tok"
	\param[in] mountOnStartup ��������� ������������
							0 = �� ���������


	\return ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenAutoMount(
	UAC_IN	CONST_PCHAR		tokenDir,
	UAC_IN	CONST_PCHAR		tokenExt,
	UAC_IN	DWORD			mountOnStartup );

/**
	\brief	��������� ������ ������������ ������� ��������� ����������
	
	������������� ����� ��� ������ � �������� UAC_Token*

	\param[out] pTokens		������ ��� ��������������� ��������� ������� 
							��� NULL - ��� ������� ���������� �������
	\param[in,out] pTokenCount	���� ��� ���������� ��������� �������
	\param[in] providerName	��� ���������� Pkcs#11 
	\param[in] onlyWithToken =true, ���� ���������� ������ ����� � ������������� ��������

	\note � ������� ������ �������� 2 ����������: 
	::UAC_PROVIDER - �������� ������ UAC
	::EFT_PROVIDER - ����� Efit
	
	\note ������� �� ���������� �������� ���������� ����������� �������������� ������

	\return 
		��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_TokenEnum(
	UAC_OUT	PUAC_TOKEN		pTokens,
	UAC_OUT	PDWORD			pTokenCount,
	UAC_IN	CONST_PCHAR		providerName,
	UAC_IN	bool			onlyWithToken );

/**
	\brief	����� ������� ��������� ���������� � �������� �������� �������
	\param[out] tokenBuf	���� ��� �������������� ���������� ������
	\param[in] providerName	��� ���������� Pkcs#11 
	\param[in] sn			�������� ����� �������� ������

	\return 
	::UAC_ERROR_NODATA, ���� ����� �� ������
	::UAC_SUCCESS, ���� ����� ������ 
	��� ��� ������
*/
UAC_API(DWORD) UAC_TokenFind(
	UAC_OUT	PUAC_TOKEN		tokenBuf,
	UAC_IN	CONST_PCHAR		providerName,
	UAC_IN  UAC_TOKEN_SN	sn);

/**
	\brief	������ ���������� � ����� � ������������ ������ 
	\param[in]	token		������������� ������
	\param[out] slotInfo	���� ��� ���������� � ����� Pkcs#11 (��� NULL)
	\param[out] tokenInfo	���� ��� ���������� � ������ (��� NULL)

	\note ���� slotInfo==NULL � tokenInfo==NULL, �� ������� �� ���������� ��������� 
	� ������ � ���� ��������� ������������ ������� �������������� UAC_TOKEN.

	\return 
	::UAC_SUCCESS ��� ��� ������
*/
UAC_API(DWORD) UAC_TokenInfo(
	UAC_IN	PUAC_TOKEN			token,
	UAC_OUT CK_SLOT_INFO_PTR	slotInfo,
	UAC_OUT CK_TOKEN_INFO_PTR	tokenInfo );

/** \name ������� ������ � ����������� ����������� ������ ����� ������ �� UAC_PRIVATE_KEY  */

/**
	\brief	����� ��������� ������� ����� �� ������� �/��� ������ ��� ����������� 
	\param[in] pKey			������ ������� �����, ����������� �� �����
	\param[in] dwIndex		��������� ������ ���������� ����� 
	(��� ::UAC_CURRENT_KEY_INDEX - ������� �������� ���� � pKey)
	\param[out] pCert		����� ��� ����������� ��� NULL, ���� ���������� �� ����� 

	\return UAC_ERROR_NO_KEY, ���� ���� �� ������.
	��� ������ ��� ::UAC_SUCCESS
	pCert - ������, ���� ���������� ��� ��������� ����� �����������.

*/
UAC_API(DWORD) UAC_KeySelect (
	UAC_INOUT PUAC_PRIVATE_KEY	pKey,
	UAC_IN	DWORD			dwIndex,
	UAC_IN	QWORD			keyType,
	UAC_OUT PUAC_BLOB		pCert );

/**
	\brief	����� ��������� ������� ����� �� ����������� �����

	\param[in] pKey			������ ������� �����, ����������� �� �����
	\param[in] pCert		���������� �������� �����
	
	\note ����� ����� ������������ �� �������������� �����. 

	\note ������� ����������� � ������ �� �����������.

	\return UAC_ERROR_NO_KEY, ���� ���� �� ������.
	��� ������ ��� ::UAC_SUCCESS

*/
UAC_API(DWORD) UAC_KeySelectByCert (
	UAC_INOUT PUAC_PRIVATE_KEY	pKey,
	UAC_IN  PUAC_BLOB			pCert );

/**
	\brief	������ ����������� � �����
	\param[in] pKey			������ ������� �����, ����������� �� �����
	\param[in] pCert		������������ ����������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_KeyAddCert (
	UAC_IN PUAC_PRIVATE_KEY	pKey,
	UAC_IN PUAC_BLOB		pCert );

/**
	\brief	������ ����������� �� ������
	\param[in] pKey			������ ������� �����, ����������� �� �����
	\param[in] dwIndex		��������� ������ ���������� ����������� ��� ::UAC_CURRENT_KEY_INDEX
	\param[in] pCert		����� ��� �����������

	���� dwIndex == ::UAC_CURRENT_KEY_INDEX,
	�� ����� �������� ����������, ��������������� �������� ���������� ����� (���������� �������� UAC_KeySelect);
	���� ���� �� ������, ������� ������ ������ UAC_ERROR_NO_KEY.
	
	���� ���������� �� ������, ������� ������ ������ UAC_ERROR_NODATA.

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_KeyGetCert (
	UAC_IN PUAC_PRIVATE_KEY	pKey,
	UAC_IN	DWORD			dwIndex,
	UAC_OUT PUAC_BLOB		pCert );

/**
	\brief	����� � ������ ����������� �� ������ �� ������ �� ����������
	\param[in] pKey			������ ������� �����, ����������� �� �����
	\param[in] pCertRef		������ �� ����������
	\param[in] pCert		����� ��� �����������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_KeyFindCert (
	UAC_IN PUAC_PRIVATE_KEY	pKey,
	UAC_IN	PUAC_CERT_REF	pCertRef,
	UAC_OUT PUAC_BLOB		pCert );


/**
	\brief	�������� ����������� �� ������ 
	\param[in] pKey			������ ������� �����, ����������� �� �����
	\param[in] pCert		���������� 

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_KeyDelCert (
	UAC_IN PUAC_PRIVATE_KEY	pKey,
	UAC_IN	PUAC_BLOB		pCert );
/**
	\brief	�������� ��������� ������� ����� � ����������� �� ������ 
	\param[in] pKey			������ ������� �����, ����������� �� �����

	���� ���� �� ������, ������� ������ ������ UAC_ERROR_NO_KEY.
	
	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_KeyDel (
	UAC_IN PUAC_PRIVATE_KEY	pKey );

/**
	\brief	��������� callback-������� ��������� ������ ��� ������������� UAC_BLOB
	\param[in] pAllocate	callback-������� ��������� ������ ��� ������������� UAC_BLOB ��� NULL

	\return ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_SetBlobAllocator (
	UAC_IN PUAC_ALLOCATE_DYNAMIC_BLOB pAllocate );


UAC_API(DWORD) UAC_Import1 (
	UAC_IN PUAC_BLOB inkey,
    UAC_IN CONST_PCHAR password, 
	UAC_OUT PUAC_BLOB key1,
	UAC_OUT PUAC_BLOB key2
    );

UAC_API(DWORD) UAC_TokenPasswordChange (
	UAC_IN PUAC_TOKEN		pTokenId,
	UAC_IN PUAC_BLOB		oldPwd,
	UAC_IN PUAC_BLOB		newPwd );

/**@}*/
/**@}*/

#if defined( __cplusplus)
}
#endif








