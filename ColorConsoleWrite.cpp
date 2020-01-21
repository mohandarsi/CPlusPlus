#include<Windows.h>
#include <iostream>

//Example to set the color to console

void ColoredWriteToStderr(const char* message, size_t len) {

	const HANDLE stderr_handle = GetStdHandle(STD_ERROR_HANDLE);

	// Gets the current text color.
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(stderr_handle, &buffer_info);
	const WORD old_color_attrs = buffer_info.wAttributes;

	fflush(stderr);

	SetConsoleTextAttribute(stderr_handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
	fwrite(message, len, 1, stderr);
	fflush(stderr);
	// Restores the text color.
	SetConsoleTextAttribute(stderr_handle, old_color_attrs);

}

int main()
{
	std::string log = "log me in RED";
	ColoredWriteToStderr(log.c_str(), log.length());
}
