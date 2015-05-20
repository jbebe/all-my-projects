:: turn off command visibility

@echo off

:: main 'function'

:main
	
	:: %RANDOM%
	:: %TIME%
	:: %DATE%
	:: if we need rescan on variables
	:: setlocal EnableDelayedExpansion
	setlocal
	
	::  ______________________________
	:: /         NUMBERS             /
	:: ``````````````````````````````
	
	:: basic math
	set /a a=5*2
	set /a a/=5
	set /a a+=10
	set /a a = 5
	set /a b = a = 6
	echo %b% %a%
	
	::  ______________________________
	:: /         STRINGS             /
	:: ``````````````````````````````
	
	:: strlen
	set c=Hello
	call :strlen %c%
	echo string length: %return%
	
	:: substring 0-8
	set c=Large Penis
	call :substr "%c%" 0 8
	echo substring: %return%
	
	:: indexof character
	call :indexof "LOREM IPSUM DOLOR SIT AMET" SUM
	echo indexof: %return%
	
	::  ______________________________
	:: /         INCLUDE             /
	:: ``````````````````````````````
	
	:: shortcut for call
	set Array=%CD%\array.bat
	:: usage
	call Array :outer_function
	echo %return%
	
	::  ______________________________
	:: /         Arrays              /
	:: ``````````````````````````````
	
	:: initiate with array length por ejemplo
	set /a array=4
	:: set array
	for /l %%i in (0,1,%array%) do (
		set /a array[%%i]=2*%%i
	)
	:: get array
	for /l %%i in (0,1,%array%) do (
		echo !array[%%i]!
	)
	:: join array to string
	call :join array ","
	echo %return%
	
	:: split string to array
	set string=1,2,3,4,5,6,7,8
	
	:common_loop
		call :strlen string
		set /a size_of_string=%return%
		call :indexof string ","
		if %return% neq -1 (
			set /a i=%return%
			call :substr string 0 %i%
			echo %return%
			call :substr string %i% size_of_string
			set string=%return%
			goto :common_loop
		)
	
	endlocal
	goto :eof
	
:: *--------------------------------ALGORITHMS---------------------------------*

:: string manipulations	

:strlen
	setlocal EnableDelayedExpansion
	set temp=%~1~
	set counter=0
	:strlen_loop
	if !temp:~%counter%! neq ~ (
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
		if "!string:~%%i,%search_length%!" equ "%search%" (
			endlocal & set return=%%i
			goto :eof
		)
	)
	endlocal & set return=-1
	goto :eof
	

	
:: arrays
	
:map
:: call :map array(name/size) function
	goto :eof
	
:join 
	setlocal
	set array_name=%1
	set /a array_size=!%1!
	set separator=%~2
	set output=
	set /a i=0
	:join_loop
		if %i% leq %array_size% (
			set output=%output%!%array_name%[%i%]!%separator%
			set /a i+=1
			goto :join_loop
		)
	endlocal & set return=%output:~0,-1%
	goto :eof