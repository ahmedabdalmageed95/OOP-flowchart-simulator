#include "DEFS.h"

//this function is used to remove the conversion from 'double' to 'int' graphics library warning
//NOTE: It doesn't work in Visual Studio 2013 because there is already a round function in the STL
//If Visual Studio 2013 is used, this function should be removed
int round(double no)
{
	if(no-floor(no)>=0.5)
		return (int) no+1;
	else
		return (int) no;
}