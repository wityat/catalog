#include <string.h>
void strrem( char* _pSourceStr, const char* _pDelStr )
{
    char* pTmpStr;

    pTmpStr = strstr( _pSourceStr, _pDelStr );

    strcpy( pTmpStr, pTmpStr + strlen( _pDelStr ) );
};