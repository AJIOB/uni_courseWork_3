#include "ExternalLib.h"

std::string getpass(const char* prompt, bool show_asterisk)
{
	const char BACKSPACE=8;
	const char RETURN=13;

	std::string password;
	unsigned char ch=0;

	std::cout <<prompt<< std::endl;

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
                password.resize(password.length()-1);
            }
		}
		else
		{
			password+=ch;
            if(show_asterisk)
				std::cout <<'*';
        }
	}
	std::cout << std::endl;
	return password;
}
