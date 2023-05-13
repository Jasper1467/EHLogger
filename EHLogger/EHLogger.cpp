#include "include/EHLogger.h"

int main()
{
	const CEHLogger Logger;
	Logger.Log(CEHLogger::TYPE_ERROR, "Error test\n");
	Logger.Log(CEHLogger::TYPE_INFO, "Info test\n");
	Logger.Log(CEHLogger::TYPE_WARNING, "Warning test\n");
}