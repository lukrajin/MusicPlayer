
#include "stdafx.h"
#include "Messages.h"

Messages::messageContent Messages::GetMessage(int messageId)
{
	messageContent msgContent = {};
	CString filename = _T(".\\Messages.ini");

	CString chapter;
	chapter.Format(_T("Message%d"), messageId);

	TCHAR textBuff[100];
	TCHAR captionBuff[100];

	GetPrivateProfileString(chapter, _T("Text"), NULL, textBuff, sizeof(textBuff), filename);
	GetPrivateProfileString(chapter, _T("Caption"), NULL, captionBuff, sizeof(captionBuff), filename);

	msgContent.text = textBuff;
	msgContent.caption = captionBuff;


	return msgContent;
}