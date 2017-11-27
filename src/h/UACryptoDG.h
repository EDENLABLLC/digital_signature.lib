#pragma once

#include "UACrypto.h"


/**	\addtogroup basetypes ������� ���� ����� */
/** @{ */
typedef CHAR								UAC_DATE_BCD[8+1];									///< ���������� ���� � ������� BCD
/** @} */

#pragma pack (push,1)

/** \addtogroup STRUCT_DG ��������� ������� ������ ������ DG
	@{
*/

/// ���������� � �������� � ���������������� ������� ������ DG
typedef struct _UAC_DG_REGISTRATION_INFO
{
	UAC_SIGNATURE_INFO	signature;						///< ���������� � ������� � ����������
	DWORD				textLength;						///< ����� ��������� ������
	UAC_DATE_BCD		date;							///< ���� ���������. ������������ � BCD ���������
	UAC_TEXT_SIZE256	text;							///< ��������� ������ ���������� � ������� �������� ���, � ��������� ���������
	DWORD				applicationCode;				///< 32/33
} UAC_DG_REGISTRATION_INFO, *PUAC_DG_REGISTRATION_INFO;
/**@}*/

#pragma pack (pop)


#if defined( __cplusplus)
extern "C" {
#endif
/** \addtogroup func �������������� �������
	@{ */
/** \name ������� ������ DG  */

/**
	\brief �������� ���������� � �������� � ���������������� ������� ������ DG
	\param[in] pSignedData		������� � ������������ �������
	\param[out] pData			�������������� ����� ��� ���� text �� �������� ��� NULL
	\param[out] pInfo			��������� ��� ���������� � �������� ��� NULL
	
	\note ���� �� ���� �� ���������� pData ��� pInfo ������ ���� ���������

	\return ��� ������ ��� ::UAC_SUCCESS
*/
UAC_API(DWORD) UAC_DgRegistrationLoad (
	UAC_IN	PUAC_BLOB pSignedData,
	UAC_OUT PUAC_BLOB pData,
	UAC_OUT PUAC_DG_REGISTRATION_INFO pInfo );

/**
	\brief �������� ������� ������ ��� ����������� ����������
	\param[in] pSignedData		������� � ������������ �������
	\param[in] pSignerCert		���������� ����������
*/
UAC_API(DWORD) UAC_DgRegistrationVerify (
	UAC_IN PUAC_BLOB pSignedData,
	UAC_IN PUAC_BLOB pSignerCert);

/**@}*/

#if defined( __cplusplus)
}
#endif

