#include "pch.h"
#include "func.h"

bool WScanf(wchar_t* _pOutBuff, FILE* _pFile)
{
	int i = 0;

	while (true)
	{
		char c = getc(_pFile);

		if (feof(_pFile))
		{
			return false;
		}

		if (c == '\n')
		{
			_pOutBuff[i++] = '\0'; // 마지막에 NULL문자를 넣어준다.
			break;
		}

		_pOutBuff[i++] = c;
	}

	return true;
}

bool FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;

	while (true)
	{
		char c = getc(_pFile);

		if (feof(_pFile))
		{
			return false;
		}

		if (c == '\n')
		{
			_pOutBuff[i++] = '\0'; // 마지막에 NULL문자를 넣어준다.
			break;
		}

		_pOutBuff[i++] = c;
	}

	return true;
}