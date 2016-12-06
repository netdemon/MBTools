
#include "stdafx.h"
#include "http.h"


//1、下载文件
BOOL Download(const CString& strFileURLInServer, //待下载文件的URL
	const CString & strFileLocalFullPath)//存放到本地的路径
{
	ASSERT(strFileURLInServer != "");
	ASSERT(strFileLocalFullPath != "");
	CInternetSession session;
	CHttpConnection* pHttpConnection = NULL;
	CHttpFile* pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;
	DWORD dwType;
	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //重试之间的等待延时
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //重试次数
	char* pszBuffer = NULL;
	try
	{
		AfxParseURL(strFileURLInServer, dwType, strServer, strObject, wPort);
		pHttpConnection = session.GetHttpConnection(strServer, wPort);
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject);
		if (pHttpFile->SendRequest() == FALSE)
			return false;
		DWORD dwStateCode;
		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if (dwStateCode == HTTP_STATUS_OK)
		{
			HANDLE hFile = CreateFile(strFileLocalFullPath, GENERIC_WRITE,
				FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
				NULL);  //创建本地文件
			if (hFile == INVALID_HANDLE_VALUE)
			{
				pHttpFile->Close();
				pHttpConnection->Close();
				session.Close();
				return false;
			}

			char szInfoBuffer[1000];  //返回消息
			DWORD dwFileSize = 0;   //文件长度
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
				(void*)szInfoBuffer, &dwInfoBufferSize, NULL);
			dwFileSize = atoi(szInfoBuffer);
			const int BUFFER_LENGTH = 1024 * 10;
			pszBuffer = new char[BUFFER_LENGTH];  //读取文件的缓冲
			DWORD dwWrite, dwTotalWrite;
			dwWrite = dwTotalWrite = 0;
			UINT nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH); //读取服务器上数据
			while (nRead > 0)
			{
				WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //写到本地文件
				dwTotalWrite += dwWrite;
				nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH);
			}
			delete[]pszBuffer;
			pszBuffer = NULL;
			CloseHandle(hFile);
		}
		else
		{
			delete[]pszBuffer;
			pszBuffer = NULL;
			if (pHttpFile != NULL)
			{
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}
			if (pHttpConnection != NULL)
			{
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}
			session.Close();
			return false;
		}
	}
	catch (...)
	{
		delete[]pszBuffer;
		pszBuffer = NULL;
		if (pHttpFile != NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		if (pHttpConnection != NULL)
		{
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		return false;
	}
	if (pHttpFile != NULL)
		pHttpFile->Close();
	if (pHttpConnection != NULL)
		pHttpConnection->Close();
	session.Close();
	return true;
}


//2、上传文件
/*
BOOL UploadFile(LPCTSTR strURL, //负责接收上传操作的页面的URL
	LPCTSTR strLocalFileName)  //待上传的本地文件路径
{
	ASSERT(strURL != NULL && strLocalFileName != NULL);
	BOOL bResult = FALSE;
	DWORD dwType = 0;
	CString strServer;
	CString strObject;
	INTERNET_PORT wPort;
	//= INTERNET_DEFAULT_HTTP_PORT;
	DWORD dwFileLength = 0;
	char * pFileBuff = NULL;
	CHttpConnection * pHC = NULL;
	CHttpFile * pHF = NULL;
	CInternetSession cis;
	bResult = AfxParseURL(strURL, dwType, strServer, strObject, wPort);
	if (!bResult)
		return FALSE;
	CFile file;
	try
	{
		if (!file.Open(strLocalFileName, CFile::shareDenyNone | CFile::modeRead))
			return FALSE;
		dwFileLength = file.GetLength();
		if (dwFileLength <= 0)
			return FALSE;
		pFileBuff = new char[dwFileLength];
		memset(pFileBuff, 0, sizeof(char) * dwFileLength);
		file.Read(pFileBuff, dwFileLength);
		const int nTimeOut = 5000;
		cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //联接超时设置
		cis.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);  //重试1次
		pHC = cis.GetHttpConnection(strServer, wPort);  //取得一个Http联接
		pHF = pHC->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject);
		if (!pHF->SendRequest(NULL, 0, pFileBuff, dwFileLength))
		{
			delete[]pFileBuff;
			pFileBuff = NULL;
			pHF->Close();
			pHC->Close();
			cis.Close();
			return FALSE;
		}
		DWORD dwStateCode = 0;
		pHF->QueryInfoStatusCode(dwStateCode);
		if (dwStateCode == HTTP_STATUS_OK)
			bResult = TRUE;
	}
	catch (CInternetException * pEx)
	{
		char sz[256] = "";
		pEx->GetErrorMessage(sz, 25);
		CString str;
		str.Format("InternetException occur!\r\n%s", sz);
		AfxMessageBox(str);
	}
	catch (CFileException& fe)
	{
		CString str;
		str.Format("FileException occur!\r\n%d", fe.m_lOsError);
		AfxMessageBox(str);
	}
	catch (...)
	{
		DWORD dwError = GetLastError();
		CString str;
		str.Format("Unknow Exception occur!\r\n%d", dwError);
		AfxMessageBox(str);
	}
	delete[]pFileBuff;
	pFileBuff = NULL;
	file.Close();
	pHF->Close();
	pHC->Close();
	cis.Close();
	return bResult;
}
*/

BOOL UploadFile(LPCTSTR strURL, LPCTSTR strLocalFileName)
{
	BOOL   nRet = FALSE;
	string          FilePath = _T("C:\\tmp\\logo.jpg");       //本地文件路径  
	string          ServerName = _T("mbt.20cn.com");          //服务器地址  
	string          ObjectName = _T("/cgi-bin/u.pl");         //服务器文件对象  
	string          HTTPBoundary = _T("---------------------------7db29f2140360");      //边界值:要求不严格  
	INTERNET_PORT   nPort = 80;                               //端口  
	nRet = Upload(FilePath, ServerName, ObjectName, HTTPBoundary, nPort);
	return nRet;
}

string MakeRequestHeaders(string &strBoundary)
{
	string strData;
	strData += _T("Content-Type: multipart/form-data; boundary=");//二进制文件传送Content-Type类型为: multipart/form-data
	strData += strBoundary;
	strData += "\r\n";
	return strData;
}
string MakePreFileData(string &strBoundary, string &strFileName, int iRecordID)
{
	//////////////////////////////////////////////////////////////////////////////////  
	string strData;

	strData += _T("--");
	strData += strBoundary;
	strData += _T("\r\n");
	strData += _T("Content-Disposition: form-data; name=\"file1\"; filename=\"");  //必备1:Path  
	strData += strFileName;
	strData += _T("\"");
	strData += _T("\r\n");
	strData += _T("Content-Type: image/jpeg");                                     //必备2:Type  
	strData += _T("\r\n\r\n");
	return strData;
}
string MakePostFileData(string &strBoundary)
{
	string strData;
	strData = _T("\r\n");
	strData += _T("--");
	strData += strBoundary;
	strData += _T("\r\n");
	strData += _T("Content-Disposition: form-data; name=\"submitted \"");
	strData += _T("\r\n\r\n");
	strData += _T("hello");
	strData += _T("\r\n");
	strData += _T("--");
	strData += strBoundary;
	strData += _T("--");
	strData += _T("\r\n");
	return strData;
}

//文件长度与文件内容   
BOOL GetFileInfo(FileInfo &BinaryInfo, string FilePath)
{
	BOOL   nRet = FALSE;
	HANDLE hFile;
	DWORD nBytesRead;
	hFile = CreateFile(FilePath.c_str(),
		GENERIC_READ,              // open for reading   
		FILE_SHARE_READ,           // share for reading   
		NULL,                      // no security   
		OPEN_EXISTING,             // existing file only   
		FILE_ATTRIBUTE_NORMAL,     // normal file   
		NULL);                     // no attr. template %  

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return nRet;
	}

	BinaryInfo.nFileLen = GetFileSize(hFile, &BinaryInfo.nFileHighLen);
	BinaryInfo.FileBuf = new char[BinaryInfo.nFileLen];
	if (!BinaryInfo.FileBuf)
	{
		CloseHandle(hFile);
		return nRet;
	}
	//memset(BinaryInfo.FileBuf, 0, sizeof(char) * dwFileLength);
	//memset(BinaryInfo.nFileLen,0, sizeof(char) * dwFileLength);
	BinaryInfo.FileBuf = { 0 };
	BinaryInfo.nFileLen = { 0 };

	if (!ReadFile(hFile, BinaryInfo.FileBuf, BinaryInfo.nFileLen, &nBytesRead, NULL))
	{
		CloseHandle(hFile);
		return nRet;
	}

	CloseHandle(hFile);
	nRet = TRUE;
	return nRet;
}

/*
* 本地路径 服务器地址 服务器路径 数据分割信息 端口
* 通过以上传入信息 将二进制数据传入web服务器
*
*/
BOOL Upload(string& FilePath, string& ServerName, string& ObjectName, string& HTTPBoundary, INTERNET_PORT &nPort)
{
	BOOL      nRet = FALSE;
	HINTERNET hInternet;                //by   InternetOpen  
	HINTERNET hHttpSession;             //by   InternetConnect  
	HINTERNET hHttpRequest;             //by   HttpOpenRequest  
	int       iRecordID = 1;
	DWORD     dwTotalLen;               //数据包的总长度  
										//准备工作  
	int    startp = FilePath.rfind('\\');
	int    namelen = FilePath.length() - startp - 1;
	string FileName = FilePath.substr(startp+1);

	string strHeaders = MakeRequestHeaders(HTTPBoundary);
	string PreFileData = MakePreFileData(HTTPBoundary, FileName, iRecordID);
	string PostFileData = MakePostFileData(HTTPBoundary);
	////////////////////////////////////////////////////////////////////////// 
	//AfxMessageBox(strHeaders.c_str());
	//AfxMessageBox(PreFileData.c_str());
	//AfxMessageBox(PostFileData.c_str());
	//AfxMessageBox(FileName.c_str());


	//1:getFileInfo  
	FileInfo localJpg;
	if (!GetFileInfo(localJpg, FilePath))
	{
		return FALSE;
	}
	//AfxMessageBox(msg);
	dwTotalLen = localJpg.nFileLen + PreFileData.length() + PostFileData.length();
	//2:init www  
	hInternet = InternetOpen(_T("lpszAgent"),
		INTERNET_OPEN_TYPE_DIRECT,
		NULL,
		NULL,
		0);

	if (!hInternet)
	{
		return nRet;
	}

	hHttpSession = InternetConnect(hInternet,
		ServerName.c_str(),
		INTERNET_DEFAULT_HTTP_PORT,
		NULL,
		NULL,
		INTERNET_SERVICE_HTTP,
		INTERNET_FLAG_RELOAD, 0);

	if (hHttpSession == NULL)
	{
		InternetCloseHandle(hInternet);
		return nRet;
	}
	//3:Opening a Request  
	hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"),
		ObjectName.c_str(),
		HTTP_VERSIONA,
		NULL, NULL, INTERNET_FLAG_MAKE_PERSISTENT, 1);
	if (hInternet == NULL)
	{
		InternetCloseHandle(hHttpSession);
		InternetCloseHandle(hInternet);
		return nRet;
	}
	//4:HttpAddRequestHeaders  
	if (!HttpAddRequestHeaders(hHttpRequest, strHeaders.c_str(), strHeaders.length(), HTTP_ADDREQ_FLAG_ADD))
	{
		goto END;
	}

	//5:HttpSendRequestEx  
	INTERNET_BUFFERSA buffer;
	memset(&buffer, 0, sizeof(buffer));
	buffer.dwStructSize = sizeof(buffer);
	buffer.dwBufferTotal = dwTotalLen;
	if (!HttpSendRequestEx(hHttpRequest, &buffer, NULL, HSR_SYNC | HSR_INITIATE, 1))
	{
		goto END;
	}

	//6:_A_send http头  
	DWORD dwNumberOfBytesWritten;
	if (!InternetWriteFile(hHttpRequest, PreFileData.c_str(), PreFileData.length(), &dwNumberOfBytesWritten))
	{
		goto END;
	}
	if (dwNumberOfBytesWritten != PreFileData.length())
	{
		goto END;
	}

	//6:_B_send filedata  
	if (!InternetWriteFile(hHttpRequest, localJpg.FileBuf, localJpg.nFileLen, &dwNumberOfBytesWritten))
	{
		goto END;
	}

	if (dwNumberOfBytesWritten != localJpg.nFileLen)
	{
		goto END;
	}
	//6:_C_send Http尾  
	if (!InternetWriteFile(hHttpRequest, PostFileData.c_str(), PostFileData.length(), &dwNumberOfBytesWritten))
	{
		goto END;
	}

	if (dwNumberOfBytesWritten != PostFileData.length())
	{
		goto END;
	}
	//7:完成提交 必不可少  
	HttpEndRequest(hHttpRequest, NULL, HSR_SYNC, 1);
END:
	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hInternet);
	return nRet;
}
