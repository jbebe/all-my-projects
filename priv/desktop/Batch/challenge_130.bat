@echo off
:main
	setlocal
	set input=%1
	
	call :strlen %input%
	set /a input_length=%return%
	
	call :indexof %input% d
	set /a pos_of_d=%return%
	
	call :substr %input% 0 %pos_of_d%
	set /a roll=%return%
	
	set /a pos_of_d+=1
	
	call :substr %input% %pos_of_d% %input_length%
	set /a sides=%return%
	
	for /l %%i in (0,1,%roll%) do (
		echo %RANDOM%
		rem ping -n 2 127.0.0.1>nul
	)
	echo %RANDOM%
	endlocal
	goto :eof

:strlen
	setlocal EnableDelayedExpansion
	set temp=%~1~
	set counter=0
	:strlen_loop
	if !temp:~%counter%! NEQ ~ (
		set /a counter+=1
		goto :strlen_loop
	)
	endlocal & set return=%counter%
	goto :eof
	
:substr
	setlocal EnableDelayedExpansion
	set string=%~1
	set from=%2
	set to=%3
	
	call :strlen "%string%"
	set /a length=%return%
	set /a to -= from
	
	set output=!string:~%from%,%to%!
	
	endlocal & set return=%output%
	goto :eof

:indexof
	setlocal EnableDelayedExpansion
	
	set string=%~1
	call :strlen "%string%"
	set /a string_length=%return%
	
	set search=%~2
	call :strlen "%search%"
	set /a search_length=%return%
	
	set /a i_length=%string_length%-%search_length%
	
	for /l %%i in (0,1,%i_length%) do (
		if "!string:~%%i,%search_length%!"=="%search%" (
			endlocal & set return=%%i
			goto :eof
		)
	)
	endlocal & set return=-1
	goto :eof
	
:random
	setlocal
	set /a from=%1
	set /a to=%2
	set /a rnd=%RANDOM%
	set /a out=%rnd%-(%to%*(%rnd%/%to%))
	endlocal & set return=%RANDOM%
	goto :eof