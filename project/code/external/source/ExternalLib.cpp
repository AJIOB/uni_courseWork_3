#include "../headers/ExternalLib.h"

std::string getpass(const char* prompt, bool show_asterisk)
{
	const char BACKSPACE=8;
	const char RETURN=13;

	std::string password;
	unsigned char ch=0;

	std::cout <<prompt<< std::endl;
	
	std::cin >> password;
	Stream::Clear();
	/*
	DWORD con_mode;
	DWORD dwRead;

	HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode( hIn, &con_mode );
	SetConsoleMode( hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

	while(ReadConsoleA( hIn, &ch, 1, &dwRead, NULL) && ch !=RETURN)
    {
		if(ch==BACKSPACE)
        {
			if(password.length()!=0)
            {
				if(show_asterisk)
				{
					std::cout <<"\b \b";
				}
                password.resize(cl_password.length()-1);
            }
		}
		else
		{
			password+=ch;
            if(show_asterisk)
				std::cout <<'*';
        }
	}
	std::cout << std::endl;*/
	return password;
}

BOOL CtrlHandler( DWORD fdwCtrlType )
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		//printf( "Ctrl-C event\n\n" );
		
		Beep(750, 300);
		throw CtrlCException();
		return (TRUE);

		// CTRL-CLOSE: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		Beep(600, 200);
		printf("Ctrl-Close event\n\n");
		return (TRUE);

		// Pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		Beep(900, 200);
		printf("Ctrl-Break event\n\n");
		return FALSE;

	case CTRL_LOGOFF_EVENT:
		Beep(1000, 200);
		printf("Ctrl-Logoff event\n\n");
		return FALSE;

	case CTRL_SHUTDOWN_EVENT:
		Beep(750, 500);
		printf("Ctrl-Shutdown event\n\n");
		return FALSE;

	default:
		return FALSE;
	} 
} 