@echo off

:outer_function
	setlocal
	endlocal & set return=outer function call reached
	goto :eof