//
// Define the data structure that will be used to pass
// database requests from the IS2ODBC DLL to DbServer.
// DbServer will fill in the sqlResult field.
//
// Note: It would be much better to use a buffer whose
//			size was not hardcoded. This could be done
//			by using different amounts of memory for
//			commit vs. reserve, but that is beyond the
//			scope of this book.
struct DbRequest
{
	char sqlFilter[512];
	char sqlSort[512];
	char sqlResult[4096];
};

//
// Define names for shared kernel objects.
// This allows both the IS2ODBC DLL and 
// the DbServer to communicate.
// 
const LPCTSTR MUTEX_DB_REQUEST			= _T("IS2ODBC Mutex");
const LPCTSTR EVENT_START_PROCESSING	= _T("IS2ODBC Event Start Processing");
const LPCTSTR EVENT_DONE_PROCESSING		= _T("IS2ODBC Event Done Processing");
const LPCTSTR FILE_DB_REQUEST			= _T("IS2ODBC DbRequest Structure");
const LPCTSTR EVENT_SERVER_RUNNING		= _T("IS2ODBC Server Running");

