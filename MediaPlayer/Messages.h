#include "stdafx.h"

class Messages
{
	struct messageContent {
		CString text;
		CString caption;
	};
public:
	messageContent GetMessage(int messageId);
	
};