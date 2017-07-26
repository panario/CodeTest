//
//	shared library class Analysis
//
#include <iostream> 
#include <fstream>
#include <limits.h>

#ifdef __cplusplus
extern "C" 
{
#endif

class Analysis {

// enum for result code
// SUCCESS = 0
// negative value = error condition

private:


enum RESCODE {SUCCESS=0, EMPTYFILE=-1, INVALIDPARAM=-2, INPUTERROR=-3, OUTPUTERROR=-4, INVALIDINPUT=-5, RANGEERROR=-6};

public:
static int analyse(const char* input, const char* output);

private:
// file operations
static bool openInputFile(const char* input); 
static bool openOutputFile(const char* output); 
static void closeFiles();
static void write(const long data);

// integer overflow
static bool overflow(const long x, const long y);

};

#ifdef __cplusplus
}
#endif





