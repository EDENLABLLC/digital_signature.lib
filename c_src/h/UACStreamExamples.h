#include "UACryptoDef.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


/**
	\struct UAC_STREAM
	��������� ������ UAC_STREAM

	�������� �������:
	UAC_STREAM.read( PVOID ctx, PVOID* pbuf, unsigned* psize )
	
	1) ��� ������:
		- ctx == UAC_STREAM.context
		- pbuf != NULL
		- psize != NULL

	2) ���� *pbuf == NULL (������� �����), �� ���������� 
		- ������ �������� � (*pbuf) ����� ������ ������ � ���������, ����������� ������;
		- �� ������ ������������ �������� �������� *psize;
		- ����� ���������� � ����� ������ ����� ���������� ���� >0;

	3) ���� *pbuf != NULL (����������� �����), �� ���������� 
		- ������ ���������� � (*pbuf) ���� (*psize) ��������� ����, 
			���� ��� ���������� ����� �� ������, ���� �� ������ ��� (*psize).

	4) �� ���� ������� (�������, �����������) ���������� 
		- ������ �������� � (*psize) ���������� ������������ ����;
		- ������ �������� � (*psize) �������� 0 ����� ���������� ������.
		- ������ ������� �������� ������� UAC_SUCCESS (0), 
			���� ������ ������� ��������� ��� ��������� ����� ������
		- ������ ������� ��� ������, ���� ��������� ������ ������ ������.
			��� ������ ������ ���� UAC_ERROR_STREAM 
			���� ������ ��� ����������, ������� ��� ::UAC_MAX_ERROR
			


	�������� �������:
	UAC_STREAM.write( PVOID ctx, PVOID buf, unsigned size )

	1) ��� ������:
		- ctx == UAC_STREAM.context
		- ���� size>0, �� buf != NULL � �������� (size) ���� ������.
		- ���� size==0, �� �������� �� ���������.

	2) ���������� 
		- ������ �������� (size) ���� �� ������ (buf) � �����
		- ������ ������� �������� ������� UAC_SUCCESS (0), 
			���� ������ ������� ��������� ��� ��������� ����� ������
		- ������ ������� ��� ������, ���� ��������� ������ ������ ������.
			��� ������ ������ ���� UAC_ERROR_STREAM 
			���� ������ ��� ����������, ������� ��� ::UAC_MAX_ERROR

*/

#define INFILE_BUFSIZE 4096

/**
	���������� ������ ������ �� ����� � ����������� UAC_STREAM 
*/
class infile_uacstream
{
public:
    infile_uacstream( const char* file_name, std::ios_base::openmode file_options = std::ios_base::in)
		: file_stream_( file_name, file_options )
	{
		uac_stream_.context = this;
		uac_stream_.read = &read;
		uac_stream_.write = NULL;
	}
	PUAC_STREAM stream() { return &uac_stream_; }
	
protected:	
	static DWORD read( PVOID ctx, PVOID* pbuf, unsigned* psize ) { 
		return ((infile_uacstream*)ctx)->doread( pbuf, psize );
	}

	DWORD doread( PVOID* pbuf, unsigned* psize ) { 
		if (pbuf==NULL || psize==NULL)
			return UAC_ERROR_STREAM; // ������� �������� UAC_STREAM.read

		if (*pbuf==NULL) { // ������� �����
			file_stream_.read( buf_, sizeof(buf_) );
			*pbuf = buf_;
		} else { // ����������� �����
			file_stream_.read( (char*)(*pbuf), *psize );
		}
		*psize = file_stream_.gcount();
		return UAC_SUCCESS;
	}

	UAC_STREAM 	uac_stream_;
	ifstream	file_stream_;
	char 		buf_[INFILE_BUFSIZE];
};

/**
	���������� ������ ������ � ���� � ����������� UAC_STREAM 
*/
class outfile_uacstream
{
public:
    outfile_uacstream( const char* file_name, std::ios_base::openmode file_options = std::ios_base::out )
		: file_stream_( file_name, file_options )
	{
		uac_stream_.context = this;
		uac_stream_.read = NULL;
		uac_stream_.write = &write;
	}
	PUAC_STREAM stream() { return &uac_stream_; }

protected:		
	static DWORD write( PVOID ctx, PVOID buf, unsigned size ) { 
		return ((outfile_uacstream*)ctx)->dowrite( buf, size );
	}
	DWORD dowrite( PVOID buf, unsigned size ) 
	{ 
		file_stream_.write( (const char*)buf, size );
		return file_stream_.fail() ? UAC_ERROR_STREAM : 0;
	}
	UAC_STREAM 	uac_stream_;
	ofstream	file_stream_;

};


/**
	���������� ������ ������ �� ������ � ������ � ����������� UAC_STREAM 
*/
class inmem_uacstream
{
public:
	inmem_uacstream( const void* static_data, size_t data_size, unsigned chunk_size=INFILE_BUFSIZE ) 
	{
		static_data_ = static_data;
		data_size_ = data_size;
		chunk_size_ = chunk_size;
		offset_ = 0;
		uac_stream_.context = this;
		uac_stream_.read = &read;
		uac_stream_.write = NULL;
	}
	PUAC_STREAM stream() { return &uac_stream_; }
	
protected:	
	static DWORD read( PVOID ctx, PVOID* pbuf, unsigned* psize ) { 
		return ((inmem_uacstream*)ctx)->doread( pbuf, psize );
	}

	unsigned has_bytes( unsigned required_bytes )
	{
		unsigned bytes = required_bytes;
		if (size_t(bytes) > data_size_ - offset_)
			bytes = unsigned(data_size_ - offset_);
		return bytes;
	}

	DWORD doread( PVOID* pbuf, unsigned* psize ) { 
		if (pbuf==NULL || psize==NULL)
			return UAC_ERROR_STREAM; // ������� �������� UAC_STREAM.read
		unsigned bytes;
		if (*pbuf==NULL) { // ������� �����
			bytes = has_bytes( chunk_size_ );
			if (bytes > 0) {
				*pbuf = ((char*)static_data_)+offset_;
				offset_ += bytes;
			}
		} else { // ����������� �����
			bytes = has_bytes( *psize );
			if (bytes > 0) {
				memcpy( *pbuf, ((const char*)static_data_)+offset_, bytes );
				offset_ += bytes;
			}
			*psize = bytes;			
		}
		*psize = bytes;			
		return UAC_SUCCESS;
	}

protected:
	UAC_STREAM 	uac_stream_;
	const void *static_data_;
	size_t		data_size_;
	size_t		offset_;
	unsigned	chunk_size_;

};

/**
	���������� ������ ������ � ������ std::string � ����������� UAC_STREAM 
*/
class outstr_uacstream
{
public:
	outstr_uacstream() 
	{
		uac_stream_.context = this;
		uac_stream_.read = NULL;
		uac_stream_.write = &write;
	}
	PUAC_STREAM stream() { return &uac_stream_; }
	string		value() { return string_stream_.str(); }
protected:		
	static DWORD write( PVOID ctx, PVOID buf, unsigned size ) { 
		return ((outstr_uacstream*)ctx)->dowrite( buf, size );
	}
	DWORD dowrite( PVOID buf, unsigned size ) 
	{ 
		string_stream_.write( (const char*)buf, size );
		return string_stream_.fail() ? UAC_ERROR_STREAM : 0;
	}
	UAC_STREAM 		uac_stream_;
	ostringstream	string_stream_;

};
