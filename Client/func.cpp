#include "pch.h"
#include "func.h"

void FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{
			_pOutBuff[i++] = '\0'; // 마지막에 NULL문자를 넣어준다.
			break;
		}

		_pOutBuff[i++] = c;
	}
}