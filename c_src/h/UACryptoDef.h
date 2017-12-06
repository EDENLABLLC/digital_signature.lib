#pragma once

#include "CommonTypes.h"

/**	\defgroup basetypes ������� ���� ����� */
/** @{ */

#define UAC_IN
#define UAC_OUT
#define UAC_INOUT

#define UAC_MAX_SERIAL_NUMBER_BYTES			32													///< ������������ ����� ��������� ������ � ������
typedef QWORD								UAC_TIME;											///< �����
typedef CHAR								UAC_TEXT_SIZE2[2+1];								///< ������������� ��� ������
typedef CHAR								CURRENCY_CODE[4+1];									///< ��� ������ ("UAH")
typedef CHAR								UAC_TEXT_SIZE64[64+1];								///< �-����� (����������� 0h)
typedef CHAR								UAC_TEXT_SIZE256[256+1];							///< �-����� ������� ����� (����������� 0h)
typedef CHAR								UAC_SERIAL_NUMBER[UAC_MAX_SERIAL_NUMBER_BYTES*2+1]; ///< �������� ����� � 16-������ ����
typedef UAC_TEXT_SIZE64						UAC_KEY_ID;											///< ������������� ����� � 16-������ ����
typedef BYTE								UAC_HASH_BLOCK[32];									///< ������������� ����� � 16-������ ����
typedef BYTE								UAC_DKE[64];
typedef const char *						CONST_PCHAR;
typedef CHAR								UAC_TOKEN_SN[16+1];
typedef CHAR								UAC_TEXT_SIZE10[10+1];

/** @} */

/**	\defgroup const ��������� */
/** @{ */

/** \defgroup Errors ���� ������
	@{
*/

/** \name ������� ���� ������
	@{
*/
/// ��� ������
#define UAC_SUCCESS							0
/// ����� ������
#define UAC_ERROR_GENERAL					100
/** @} */
/** \name ������ �������� ������
	@{
*/
/// ������� ���������
#define UAC_ERROR_NULL_PARAM				1
/// ������ �������� \see _UAC_BLOB
#define UAC_ERROR_EMPTY_PARAM				2
/// ������ ������ ������������ ��� ������ ������
#define UAC_ERROR_SMALL_BUFFER				3
/// ������ ������������� ������ ������ \see _UAC_BLOB
#define UAC_ERROR_ALLOCATE					5
/** @} */
/** \name ������ ������������ ������� ������
	@{
*/
/// �������� ��������������
#define UAC_ERROR_CRYPTO_CONTEXT			11
/// �������� �������� ����
#define UAC_ERROR_CRYPTO_PUBLICKEY			12
/// �������� ��������� ����
#define UAC_ERROR_CRYPTO_PRIVATEKEY			13
/// �������������� ��������� � ���������� ������
#define UAC_ERROR_CRYPTO_KEYPAIR			14
/// �������� ��������� �������� ����
#define UAC_ERROR_CRYPTO_POLYNOM			15
/// ��� �������
#define UAC_ERROR_CRYPTO_SIGNATURE			16
/// �������� ��������� ������� � ������������ (�� ��������������� ��������� ���)
#define UAC_ERROR_CRYPTO_DEADLOOP			17
/// ��� �������� ������������ ���������� ��������� ���������� ������
#define UAC_ERROR_CRYPTO_MAC				18

/** @} */
/** \name ����������� ������ ������������
	@{
*/
/// �������� ���-������ ������
#define UAC_ERROR_DIGEST     				21
/// �������������� ��������������� ��������� � ���������� ������
#define UAC_ERROR_KEYPAIR					22
/// �������� ������ ���������� � ������
#define UAC_ERROR_WRONG_PASSWORD			23
/// �������� ��� ���������� ��� ���������� �������
#define UAC_ERROR_CONTENT_TYPE				24
/// ������ �� ���������� �� �������� ������
#define UAC_ERROR_EMPTY_CERTREF				25
/** @} */
/** \name ������ ��������
	@{
*/
/// �������� ������ ������� ������
#define UAC_ERROR_FORMAT					30
/// �������� ������ �����������
#define UAC_ERROR_FORMAT_CERT				31
/// �������� ������ ������� �� ������������
#define UAC_ERROR_FORMAT_CERTREQUEST		32
/// �������� ������ OCSP �������
#define UAC_ERROR_FORMAT_OCSPREQUEST		33
/// �������� ������ OCSP ������
#define UAC_ERROR_FORMAT_OCSPRESPONSE		34
/// �������� ������ ����������� ������
#define UAC_ERROR_FORMAT_SIGNEDDATA			35
/// �������� ������ ������� ����� �������
#define UAC_ERROR_FORMAT_TSREQUEST			36
/// �������� ������ ������ ����� �������
#define UAC_ERROR_FORMAT_TSRESPONSE			37
/// �������� ������ �������� � ������������ �������
#define UAC_ERROR_FORMAT_ENVELOPE			38
/// �������� ������ ��������� ������ UAC
#define UAC_ERROR_FORMAT_TOKEN				39

/** @} */

/** \name �������������� ����
	@{
*/
/// ��������� ������ �����������
#define UAC_ERROR_NODATA		     		40
/// ������ �����������
#define UAC_ERROR_NO_SIGNATURE	     		41
/// ��������������� ��������� �� ������
#define UAC_ERROR_NO_SIGNER     			42
/// ��������������� ���������� �� ������
#define UAC_ERROR_NO_RECIPIENT				43
/// �������� ������������� ��� ��� ������
#define UAC_ERROR_TOKEN_ID					44
/// �� ������ �������� ���� 
#define UAC_ERROR_NO_KEY					45
/// ������ ������/������ UAC_STREAM
#define UAC_ERROR_STREAM					50

/// ����������� ��� ������ �������� ����������
#define UAC_MAX_ERROR				0x80000000


/** @} */
/** @} */ // Errors

/** \defgroup ContentTypes ���� ������-�����������
	@{
*/
typedef DWORD UAC_CT;

/// �� ����������
#define UAC_CT_UNDEFINED					0
/** \name ������� ������, �������������� CMS-ContentType: iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) pkcs-9(9) smime(16) ct(1) ..
	@{
*/
/// ���������������� ������
#define UAC_CT_DATA							1
/// ����������� ������
#define UAC_CT_SIGNEDDATA					2
/// ������������� ������
#define UAC_CT_ENVELOPEDDATA				3
/// ���������� � ����� �������
#define UAC_CT_TSINFO						4
/** @} */

/** \name ������� ������� ������
	@{
*/
/// ���������� �����
#define UAC_CT_CERT							101
/// ������ �� ������������ PKCS-10 ��� �����������(PKCS-10)
#define UAC_CT_CERTREQUEST					102
/// OCSP ������ (������ �����������)
#define UAC_CT_OCSPREQUEST					103
/// OCSP ����� (������ �����������)
#define UAC_CT_OCSPRESPONSE					104
/// ������ ����� �������
#define UAC_CT_TSREQUEST					105
/// ����� ����� ������� / ����� �������
#define UAC_CT_TSRESPONSE					106
/// ������ ���������� ������������ (CRL)
#define UAC_CT_CRL							107
/// ���-������
#define UAC_CT_HASH							108
/** @} */
/** @} */

/** \defgroup UAC_KU ������������� �����
	@{
*/
/// ���: UAC_KU
typedef DWORD UAC_KU;
/// �������� (KeyUsage) \see UAC_KU_BASIC
#define UAC_KU_BASIC							0x0000FFFF
/// ����������� (ExtendedKeyUsage) \see UAC_KU_EXTENDED
#define UAC_KU_EXTENDED							0x00FF0000
/// �������������� \see UAC_KU_OPTIONS
#define UAC_KU_OPTIONS							0xFF000000
/** \name  ��������
	@{
*/
/// ����������� �������� �����
#define UAC_KU_DATA_SIGN						0x0080
/// ��������������
#define UAC_KU_NON_REPUDIATION					0x0040
/// ���������� � ����� ��������������� �����
#define UAC_KU_KEY_ENCIPHERMENT					0x0020
/// ���������� �����
#define UAC_KU_DATA_ENCIPHERMENT				0x0010
/// �������� ���� ��������������� � ���������� ���������� �����
#define UAC_KU_KEY_AGREEMENT					0x0008
/// ����������� �������� ����� � ����������
#define UAC_KU_CERT_SIGN						0x0004
/// ����������� �������� ����� � ������ ���������� �����������
#define UAC_KU_CRL_SIGN							0x0002
/// ���� �� �keyAgreement� �����������, �������� ���� ���� ����������������� ����� ��� ���������� �����
#define UAC_KU_ENCIPHER_ONLY					0x0001
/// ���� �� �keyAgreement� �����������, �������� ���� ���� ����������������� ����� ��� ������������� �����
#define UAC_KU_DECIPHER_ONLY					0x8000
/** @} */
/** \name  �����������
	@{
*/
/// OCSP ������
#define UAC_KU_OCSP								0x00010000
/// TSP ������
#define UAC_KU_TSP								0x00020000
/// ���������� �������
#define UAC_KU_STAMP							0x00040000
/** @} */
/** \name  ��������������
	@{
*/
/// ���������� �� � ����������
#define UAC_KU_NOT_QUALIFIED					0x01000000
/// ���������� �� �������� ���������
#define UAC_KU_HAS_LIMIT						0x02000000
/** @} */
/** @} */

#define UAC_KU_CA								UAC_KU_CERT_SIGN

/** \defgroup UAC_CRL_REASON ������� ������ �����������
	@{
*/
/// ���: UAC_CRL_REASON
typedef DWORD UAC_CRL_REASON;
/// ������� �� ���������
#define UAC_CRL_REASON_UNSPECIFIED				0
/// ������������� ���������� �����
#define UAC_CRL_REASON_KEY_COMPROMISE			1
/// ������������� ���������� ����� �������������� ������
#define UAC_CRL_REASON_CA_COMPROMISE			2
/// ���� ����� ��� �������� �����������
#define UAC_CRL_REASON_AFFILIATION_CHANGED		3
/// ���������� ����� ��������
#define UAC_CRL_REASON_SUPERSEDED				4
/// ���������� ��������
#define UAC_CRL_REASON_CESSATION_OF_OPERATION	5
/// ���������� ����� ���������
#define UAC_CRL_REASON_CERTIFICATE_HOLD			6
/// ���������� ����� ���������
#define UAC_CRL_REASON_REMOVE_FROM_CRL			8
/// ������������ ���������
#define UAC_CRL_REASON_PRIVILEGE_WITN_DRAWN		9
/** @} */

/** \defgroup UAC_TS_STATUS ������ ������ ������� ����� �������
	@{
*/
/// ���: UAC_TS_STATUS
typedef DWORD UAC_TS_STATUS;

/// �������� ���� ����������
#define UAC_TS_STATUS_GRANTED					0
/// �������� ���� ���������� � �������������
#define UAC_TS_STATUS_GRANTED_WITH_MODS			1
/// � ��������� �������� ���� ���� ���������
#define UAC_TS_STATUS_REJECTION					2
/// ����� ��������� �������� � ������ �� �����������������
#define UAC_TS_STATUS_WAITING					3
/** @} */

/** \defgroup UAC_TS_FAILURE ������� ������ ������� ����� �������
	������� ������ � �������� ����

	@{
*/
// ���: UAC_TS_FAILURE
typedef DWORD UAC_TS_FAILURE;

/// �������� �������� ��������� ��� �����, �� �� �����������
#define UAC_TS_FAILURE_BAD_ALG					0
/// ����� �����, �� �� �����������, ��� ������������
#define UAC_TS_FAILURE_BAD_REQUEST				1
/// ����� �����������
#define UAC_TS_FAILURE_BAD_DATA_FORMAT			5
/// ��������� ��������� ������ ���
#define UAC_TS_FAILURE_TIME_NOY_AVAILABLE		14
/// ������� ���������� �������� ���� ����, �� �� �����������
#define UAC_TS_FAILURE_UNACCEPTED_POLICY		15
/// ���������� ����, �� �� �����������
#define UAC_TS_FAILURE_UNACCEPTED_EXTENTION		16
/// ³������ ��������� ��������� ����������
#define UAC_TS_FAILURE_ADD_INFO_NOT_AVAILABLE	17
/// �������� �������
#define UAC_TS_FAILURE_SYSTEM_FAILURE			25
/** @} */

/** \defgroup UAC_CERT_STATUS ������ �����������
	@{
*/
/// ���: UAC_CERT_STATUS
typedef DWORD UAC_CERT_STATUS;
/// ���������� ������
#define UAC_CERT_STATUS_GOOD					0
/// ���������� ����������
#define UAC_CERT_STATUS_REVOKED					1
/// ������ ����������� ��������
#define UAC_CERT_STATUS_UNKNOWN					2
/** @} */

/** \defgroup UAC_OCSP_STATUS ��� ������ � ������� �����������
	@{
*/
/// ���: UAC_OCSP_STATUS
typedef DWORD UAC_OCSP_STATUS;
/// �������� ����������� ������
#define UAC_OCSP_STATUS_SUCCESSFUL				0
/// ����������� ��� ������������ �����
#define UAC_OCSP_STATUS_MAILFORMED_REQUEST		1
/// �������� �������
#define UAC_OCSP_STATUS_INTERNAL_ERROR			2
/// ����� ��������� �������� � ������ �� �����������������
#define UAC_OCSP_STATUS_TRY_LATER				3
/// OCSP-c����� �������� ���� ������� ������
#define UAC_OCSP_STATUS_SIG_REQUIRED			5
/// ����� �� ���������������� �����������
#define UAC_OCSP_STATUS_UNAUTHORIZED			6
/** @} */

/** \defgroup UAC_OPTION ��������� �������
	@{
*/
/// ���: UAC_OPTION
typedef DWORD UAC_OPTION;

/// ���������������� ���������� �� ��������� ������ � ������ ����� ��������
#define UAC_OPTION_IDENT_BY_SERIAL_NUMBER	0x00000001
/// ���������������� ���������� �� �������������� �����
#define UAC_OPTION_IDENT_BY_KEY_ID			0x00000002
/// ���������������� ���������� �� ������ �����
/** \note ������������ ������ ��� ������������ � ������� �� OCSP ������ */
#define UAC_OPTION_IDENT_BY_NAME			0x00000200
/// ������ ������������ ����������� ������ ������������ ���������
#define UAC_OPTION_FORCE_SIGN_ATTRS			0x00000004
/// �������� � ������� ���������� ����������
#define UAC_OPTION_INCLUDE_CERT				0x00000008
/// �������� � ������� ���������
#define UAC_OPTION_STORE_CONTENT			0x00000010
/// ��������� ����� ������ ��������
#define UAC_OPTION_INCLUDE_VERSION			0x00000020
/// ��������� ��������� ������������� � ������
#define UAC_OPTION_INCLUDE_NONCE			0x00000040
/// ������� ����� �������
#define UAC_OPTION_INCLUDE_SIGNED_TIME		0x00000080
/// ��������� ���������� � ������
#define UAC_OPTION_QUERY_CERT				0x00000100
/// ���������/��������� ������� ������ � �������� �������
#define UAC_OPTION_EXTERNAL_ENVELOPE		0x00004000
/// ���������� ��� ��������
#define UAC_RESET_CONTENT_TYPE(options, contentType)	(((options)&=0xFFF0FFFF)|=(contentType) << 16)
/// �������� ������������� ��� ��������
#define UAC_GET_CONTENT_TYPE(options)		(((options) & 0x000F0000)>>16)
/// ��������� ��-���������
#define UAC_OPTIONS_DEFAULT (UAC_OPTION_IDENT_BY_SERIAL_NUMBER | UAC_OPTION_FORCE_SIGN_ATTRS | UAC_OPTION_INCLUDE_NONCE | UAC_OPTION_INCLUDE_SIGNED_TIME | UAC_OPTION_INCLUDE_CERT | UAC_OPTION_STORE_CONTENT)

/** \name  �������� ������� ���������
	\see UAC_SIGNATURE_ATTR
	@{
*/
///< ����� �������	OPERATION_INDEX - ������ �������� ��� ����������
#define UAC_OPTION_OPERATION_ATTR			0x00100000
///< ����� �������	STATUS_INDEX - ������ ���������� �������� ��� ����������.
#define UAC_OPTION_STATUS_ATTR				0x00200000
///< ����� �������	PREVSIGN_DIGEST - ��� ����������� ������������ �������� � �������
#define UAC_OPTION_PREVSIGN_ATTR			0x00400000
/** @} */

/** @} */

/** @} */ // group const

#pragma pack (push,1)
/** \defgroup STRUCT ��������� ������� ������
	@{
*/

/**
    \brief ���� �������� ������ ������������� �������
    \li ��� �������, ���������� ��������  ::PUAC_BLOB:
    \par
    � ������, ���� �������� ������������ � ::PUAC_BLOB==NULL, ���������� ������ ::UAC_ERROR_NULL_PARAM
    \par
    � ������, ���� �������� �������������� � ::PUAC_BLOB==NULL, �������, ��� �� �� ������.

    \li ��� �������, �������� ������ �� UAC_IN ::PUAC_BLOB:
    \par
    � ������ UAC_BLOB::data==NULL ���������� ������ ::UAC_ERROR_NULL_PARAM
    \par
    � ������ UAC_BLOB::dataLen==0 ���������� ������ ::UAC_ERROR_EMPTY_PARAM .

    \li ��� �������, ������������ ������ � UAC_OUT ::PUAC_BLOB:
    \par
    � ������, ���� UAC_BLOB::data==NULL, ���������� ::UAC_SUCCESS
    � ���������� ������ ������������ ������ � ���� UAC_BLOB::dataLen.
    ��� ���� �������� ������ �� ����������.
    \par
    � ������, ���� UAC_BLOB::data!=NULL � ������ ������ UAC_BLOB::dataLen ������������ ��� ���������� ������,
    ���������� ������ ::UAC_ERROR_SMALL_BUFFER .
*/
typedef struct _UAC_BLOB
{
	PVOID	data;				///< ��������� �� ����� ������
	DWORD	dataLen;			///< ���������� ���� ������ � ������
} UAC_BLOB, *PUAC_BLOB;

/// ���������� � ��������� �����
typedef struct _UAC_SUBJECT_INFO
{
	UAC_TEXT_SIZE64 commonName;						///< ����� ���
	UAC_TEXT_SIZE2	countryName;					///< ������ ="UA"
	UAC_TEXT_SIZE64 surname;						///< �������
	UAC_TEXT_SIZE64 givenName;						///< ���
	UAC_TEXT_SIZE64 organizationName;				///< �����������
	UAC_TEXT_SIZE64 serialNumber;					///< �������� ����� ���������
	UAC_TEXT_SIZE64 stateOrProvinceName;			///< �������
	UAC_TEXT_SIZE64 localityName;					///< �����
	UAC_TEXT_SIZE64 organizationalUnitName;			///< �����
	UAC_TEXT_SIZE64 title;							///< ��������
	UAC_TEXT_SIZE10 edrpou;							///< ��� ������
	UAC_TEXT_SIZE10	drfo;							///< ��� ���� ��� ���
	
	
} UAC_SUBJECT_INFO, *PUAC_SUBJECT_INFO, UAC_ISSUER_INFO, *PUAC_ISSUER_INFO;

/// ������ �� ���������� �����
typedef struct _UAC_CERT_REF
{
	UAC_KEY_ID			subjectKeyIdentifier;		///< ������������� �����
	UAC_SERIAL_NUMBER	serialNumber;				///< �������� ����� �����������
	UAC_TEXT_SIZE64		issuerCommonName;			///< ����� ��� �������� ����������� (������ � �������� ������� �����������)
	UAC_TEXT_SIZE64		subjectCommonName;			///< ����� ��� ��������� �����������
	DWORD				options;					///< �������� ������������� = ::UAC_OPTION_IDENT_BY_SERIAL_NUMBER | ::UAC_OPTION_IDENT_BY_KEY_ID | ::UAC_OPTION_IDENT_BY_NAME
	UAC_TEXT_SIZE64		issuerSecondaryName;		///< ��� ���������� - �������� ����� �������� (������ � �������� ������� �����������)
	UAC_TEXT_SIZE64		subjectSecondaryName;		///< ��� ���������� - �������� ����� �������� (������ � ����� ������ ��������� �����������)
	
} UAC_CERT_REF, *PUAC_CERT_REF;

/// ���������� � �������� �������
typedef struct _UAC_SIGNATURE_INFO
{
	UAC_CERT_REF		signerRef;					///< ������ �� ���������� ����������
	UAC_TIME			signingTime;				///< ����� ������� ��� 0
} UAC_SIGNATURE_INFO, *PUAC_SIGNATURE_INFO;

/// ���������� �� ��������� �������� �������
typedef struct _UAC_SIGNATURE_ATTR
{
	DWORD				options;					///< �������� ������� ��������� (::UAC_OPTION_OPERATION_ATTR, ::UAC_OPTION_STATUS_ATTR,	::UAC_OPTION_PREVSIGN_ATTR)

	DWORD				operationIndex;				///< �������� �������� ��������		OPERATION_INDEX - ������ �������� ��� ����������
	UAC_TEXT_SIZE64		operationInfo;				///< ��������� �������� ��������	OPERATION_INDEX - ��������� �������� �������� ��� ����������
	DWORD				statusIndex;				///< �������� �������� ��������		STATUS_INDEX - ������ ���������� �������� ��� ����������.
	UAC_TEXT_SIZE64		statusInfo;					///< ��������� �������� ��������	STATUS_INFO  - ��������� �������� ���������� �������� ��� ����������.
	UAC_HASH_BLOCK		prevSignDigest;				///< �������� ��������				PREVSIGN_DIGEST - ��� ����������� ������������ �������� � �������
} UAC_SIGNATURE_ATTR, *PUAC_SIGNATURE_ATTR;

/// ����� �������� �����������
typedef struct _UAC_CERT_VALIDITY
{
	UAC_TIME notBefore;								///< ������ �������� �����������
	UAC_TIME notAfter;								///< ����� �������� �����������
} UAC_CERT_VALIDITY, *PUAC_CERT_VALIDITY;

/// ���������� � ����������� �����
typedef struct _UAC_CERT_INFO
{
	UAC_SERIAL_NUMBER	serialNumber;				///< �������� �����
	UAC_ISSUER_INFO		issuer;						///< ���������� �� �������� �����������
	UAC_SUBJECT_INFO	subject;					///< ���������� � ��������� �����������
	UAC_CERT_VALIDITY	validity;					///< ����� �������� �����������
	UAC_KEY_ID			authorityKeyIdentifier;		///< ������������� ����� �������� �����������
	UAC_KEY_ID			subjectKeyIdentifier;		///< ������������� ����� ��������� �����������
	UAC_KU				keyUsage;					///< ������ ������������� �����

	CURRENCY_CODE		currencyCode;				///< "UAH", ���� ���� ���. �����������
	DWORD				amount;						///< ����������� <= (amount * 10^exponent) currencyCode
	DWORD				exponent;					///< ����������� <= (amount * 10^exponent) currencyCode

	//	��� ������������ ���
	UAC_TEXT_SIZE256	crlDistributionPoints;		///< ����� ���������������� CRL
	UAC_TEXT_SIZE256	crlDeltaDistributionPoints;	///< ����� ���������������� ��������� CRL
	UAC_TEXT_SIZE256	accessCaRepository;			///< ����� ������� � ���
	UAC_TEXT_SIZE256	accessTSP;					///< ����� ������� � ������� ����� �������
	UAC_TEXT_SIZE256	accessOCSP;					///< ����� ������� � ������� OCSP
	UAC_TEXT_SIZE256	accessCaIssuers;			

	DWORD				pathLen;
	UAC_TEXT_SIZE64		keyTypeOid;					///< ��������� ������������� ��������� �����
} UAC_CERT_INFO, *PUAC_CERT_INFO;

/// ���������� � ������� �� ������������
typedef struct _UAC_CERT_REQUEST_INFO
{
	UAC_SUBJECT_INFO	subject;					///< �������� ��������� ������������ (������ ���� ������� ��� ���)
	UAC_KU				keyUsage;					///< ������ ������������� �����
	UAC_KEY_ID			subjectKeyIdentifier;		///< ������������� ����� �����������

	UAC_SIGNATURE_INFO	signature;					///< �������
} UAC_CERT_REQUEST_INFO, *PUAC_CERT_REQUEST_INFO;

/// ���������� �� ���������� ����������� (CRL)
typedef struct _UAC_CRL_ENTRY
{
	UAC_SERIAL_NUMBER	serialNumber;				///< �������� ����� �����������
	UAC_TIME			revocationDate;				///< ����� ������ �����������
	UAC_CRL_REASON		crlReason;					///< ������� ������
	UAC_TIME			invalidityDate;				///< �����, � �������� ���� �������� ���� ����������
	UAC_KEY_ID			subjectKeyIdentifier;		///< ������������� ����� �����������

} UAC_CRL_ENTRY, *PUAC_CRL_ENTRY;

/// ���������� � ������ ���������� ������������ (CRL)
typedef struct _UAC_CRL_INFO
{
	UAC_TIME			thisUpdate;					///< ����� ���������� ����������
	UAC_TIME			nextUpdate;					///< ����� ���������� ����������
	PUAC_CRL_ENTRY		revokedCertificates;		///< ������ ���������� ������������
	DWORD				dwRevokedCertificatesLength;///< ���������� ���������� ������������
	UAC_SERIAL_NUMBER	serialNumber;				///< �������� ����� ������
	UAC_SERIAL_NUMBER	baseSerialNumber;			///< �������� ����� �������� ������
	UAC_TEXT_SIZE64		crlDistributionPoints;		///< ����� ���������������� CRL

	UAC_ISSUER_INFO		issuer;						///< ���������� �� �������� CRL
	UAC_KEY_ID			authorityKeyIdentifier;		///< ������������� ����� �������� CRL
} UAC_CRL_INFO, *PUAC_CRL_INFO;

/// ���������� �� ������ ������� ����� �������
typedef struct _UAC_TIME_STAMP_INFO
{
	UAC_SERIAL_NUMBER	nonce;						///< ��������� ������������� �������
	UAC_HASH_BLOCK		hash;						///< �������� ��� ������

/// \name ���� ������
	UAC_TS_STATUS		status;						///< ������ ������ ������� ����� �������
	UAC_TS_FAILURE		failureInfo;				///< ������� ������ ������� ����� �������
	UAC_TIME			genTime;					///< ����� �������� �����
	UAC_SERIAL_NUMBER	serialNumber;				///< �������� ����� �����
	DWORD				dwCertCount;				///< ���������� ������������ �������������� � ������
	UAC_SIGNATURE_INFO	signature;					///< ������� ������
} UAC_TIME_STAMP_INFO, *PUAC_TIME_STAMP_INFO;

/// ������ �� ���������� ��� ��������� ��� �������
typedef struct _UAC_OCSP_REF_INFO
{
	UAC_SERIAL_NUMBER	certificateSerialNumber;	///< �������� ����� �����������
	UAC_HASH_BLOCK		issuerNameHash;				///< ���-������ ����� ��������
	UAC_HASH_BLOCK		issuerKeyHash;				///< ������������� ����� ��������
	UAC_SERIAL_NUMBER	nonce;						///< ��������� ������������� �������
} UAC_OCSP_REF_INFO;

/// ���������� ��� ������� ������� �����������
typedef struct _UAC_OCSP_REQUEST_INFO
{
	UAC_OCSP_REF_INFO	ref;						///< ������ �� ������� ����������
	DWORD				dwCertCount;				///< ���������� ������������ �������������� � ������
	UAC_SIGNATURE_INFO	signature;					///< �������
} UAC_OCSP_REQUEST_INFO, *PUAC_OCSP_REQUEST_INFO;

/// ����� � ������� �����������
typedef struct _UAC_OCSP_RESPONSE_INFO
{
	UAC_OCSP_REF_INFO	ref;						///< ������ �� ������� ����������
	UAC_OCSP_STATUS		responseStatus;				///< ������ ������ ������� OCSP
	UAC_CERT_STATUS		certStatus;					///< ������ �������� �����������
	UAC_TIME			thisUpdate;					///< ����� ���������� ���������� ���������� � �������
	UAC_TIME			producedAt;					///< ����� �������� ������
	UAC_TIME			revocationTime;				///< ����� ������ �����������
	UAC_CRL_REASON		revocationReason;			///< ������� ������ �����������

	DWORD				dwCertCount;				///< ���������� ������������ �������������� � ������
	UAC_SIGNATURE_INFO	signature;					///< �������
} UAC_OCSP_RESPONSE_INFO, *PUAC_OCSP_RESPONSE_INFO;

/// ���������� ��� ������� � ���������� �����
typedef struct _UAC_PRIVATE_KEY_DATA
{
	UAC_BLOB			pkcs8Buf;					///< ����� � �������� �����������
	PCHAR				password;					///< ������ ������� / ������ ������� ��������������
	PCHAR				password2;					///< NULL (��� ���������� �������) / ������ ������� ��������������
	UAC_HASH_BLOCK		adminKey;					///< NULL (��� ���������� �������) / ���� ������� ���� ���������������
} UAC_PRIVATE_KEY, *PUAC_PRIVATE_KEY;

/// ���� ������: ���������� ��������� ����� � ��������� ���� ������������
typedef struct _UAC_KEYPAIR
{
	UAC_BLOB			certData;					///< ����������
	UAC_PRIVATE_KEY		privateKeyData;				///< ���������� ��� ������� � �����
} UAC_KEYPAIR, *PUAC_KEYPAIR;

/// ���������� � �������� � ������������ �������
typedef struct _UAC_SIGNED_DATA_INFO
{
	PUAC_SIGNATURE_INFO pSignatures;				///< ������ �������� [dwSignatureCount]
	DWORD				dwSignatureCount;			///< ���������� ��������
	DWORD				dwContentType;				///< ��� ����������� ������ (������ CMS)
	DWORD				dwDataLength;				///< ����� ����������� ������ (0, ���� ��������� �� ���������� � ��������)
	DWORD				dwCertCount;				///< ���������� ������������ ����������� � �������
	PUAC_SIGNATURE_ATTR pAttributes;				///< ������ ��������� �������� [dwSignatureCount]
	DWORD				dwAttributeCount;			///< ���������� �������� (��� ���������)
} UAC_SIGNED_DATA_INFO, *PUAC_SIGNED_DATA_INFO;

/// ���������� � �������� ������ ����� ����� ����������
typedef struct _UAC_EXCHANGE_INFO
{
	UAC_CERT_REF		originatorRef;				///< ������ �� ���������� �����������
	UAC_CERT_REF		recipientRef;				///< ������ �� ���������� ����������
} UAC_EXCHANGE_INFO, *PUAC_EXCHANGE_INFO;

/// ���������� � �������� ������������ ������
typedef struct _UAC_ENVELOPE_INFO
{
	PUAC_EXCHANGE_INFO	pExchanges;					///< ������ ����������� (� ����������� �� ������������)
	DWORD				dwExchangeCount;			///< ���������� �����������
	DWORD				dwContentType;				///< ��� ������������� ������ (������ CMS)
	DWORD				dwDataLength;				///< ����� ������������� ������ (0, ���� ��������� �� ���������� � ��������)
	DWORD				dwCertCount;				///< ���������� ������������ ����������� � �������
} UAC_ENVELOPE_INFO, * PUAC_ENVELOPE_INFO;

/// ��������� ���������� �������� ������� ����4145 � ����������� ����34311
typedef struct _UAC_DSTU_PARAMS
{
	DWORD				id;							///< ������������� ����������� ���������� ����4145-2002 � �������������� ������
	UAC_DKE				dke;						///< ��� ��� ���-�������
} UAC_DSTU_PARAMS, * PUAC_DSTU_PARAMS;

/// ������������� ����� ������������� ��������� ������ - ��� ������������� � �������� ���������� � ������
typedef char TokenTypeTag[8];
typedef TokenTypeTag * PUAC_TOKEN_PROVIDER_NAME;

typedef struct _UAC_TOKEN {
	TokenTypeTag	provider_name;						///< �������� ��� ���������� ������ pkcs#11 
	QWORD			slotid;								///< �������������� ����� (Pkcs#11)
	QWORD			key_handle;							///< ������������� ���������� ����� ��� 0 (Pkcs#11)
} UAC_TOKEN, * PUAC_TOKEN;

enum KeyFormat
{
	kfCntNew = 0,
	kfPk8New = 1,
	kfCntAlways = 2,
	kfPk8Always = 3
};

enum BagSet {
	bsKeyBag = 1,
	bsShroudedKeyBag = 2,
	bsCertBag = 3,
	bsCrlBag = 4,
	bsSecretBag,
	bsSafeContentsBag
};

typedef PVOID (CALLBACK_CONVENTION * PUAC_ALLOCATE_DYNAMIC_BLOB)( PUAC_BLOB pBlob, DWORD bytes );
typedef DWORD (*PUAC_STREAM_READ)( PVOID context, PVOID* pbuf, unsigned* psize );
typedef DWORD (*PUAC_STREAM_WRITE)( PVOID context, PVOID buf, unsigned size );


typedef struct _UAC_STREAM {
	PVOID	context;		///< ��������� - �������� ���������� ������� {read, write}
	PUAC_STREAM_READ read;	///< ��������� �� ������� ������ ������ 
	PUAC_STREAM_WRITE write;///< ��������� �� ������� ������ ������
} UAC_STREAM, *PUAC_STREAM;

#define UAC_PROVIDER "UAC_TOK"
#define EFT_PROVIDER "EFT_TOK"

#define GOST28147_OFB_OID	"1.2.804.2.1.1.1.1.1.1.2"
#define GOST28147_CFB_OID	"1.2.804.2.1.1.1.1.1.1.3"
#define AES_128_CBC_PAD_OID		"2.16.840.1.101.3.4.1.2"
#define AES_192_CBC_PAD_OID		"2.16.840.1.101.3.4.1.22"
#define AES_256_CBC_PAD_OID		"2.16.840.1.101.3.4.1.42"


#define UAC_CURRENT_KEY_INDEX	0xffffffff
#define UAC_MAX_BLOB_SIZE		0xffffff00
#define UAC_DYNAMIC_BLOB_LEN	0xffffffff
/**@}*/

#pragma pack (pop)


