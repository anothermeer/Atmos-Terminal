::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAnk
::fBw5plQjdG8=
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSDk=
::cBs/ulQjdF+5
::ZR41oxFsdFKZSDk=
::eBoioBt6dFKZSDk=
::cRo6pxp7LAbNWATEpCI=
::egkzugNsPRvcWATEpCI=
::dAsiuh18IRvcCxnZtBJQ
::cRYluBh/LU+EWAnk
::YxY4rhs+aU+JeA==
::cxY6rQJ7JhzQF1fEqQJQ
::ZQ05rAF9IBncCkqN+0xwdVs0
::ZQ05rAF9IAHYFVzEqQJQ
::eg0/rx1wNQPfEVWB+kM9LVsJDGQ=
::fBEirQZwNQPfEVWB+kM9LVsJDGQ=
::cRolqwZ3JBvQF1fEqQJQ
::dhA7uBVwLU+EWDk=
::YQ03rBFzNR3SWATElA==
::dhAmsQZ3MwfNWATElA==
::ZQ0/vhVqMQ3MEVWAtB9wSA==
::Zg8zqx1/OA3MEVWAtB9wSA==
::dhA7pRFwIByZRRnk
::Zh4grVQjdCyDJGyX8VAjFBpQQQ2MAE+/Fb4I5/jHzv6KrV4iYOctdYbV27jAJfgWig==
::YB416Ek+ZG8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
rem startup
title Atmos Terminal
cls

:welcome
echo Welcome to [93mAtmos Terminal[0m !
echo Type [7mcmd.help[0m to get the list of avalible commands.
echo.

:cmdAgain
title Atmos Terminal
set /p cmd="admin > "

rem [4;7;96mbasic commands[0m

rem basic commands
if %cmd%==cmd.help goto help
if %cmd%==cmd.exit goto CMDexit
if %cmd%==cmd.cs goto ClearScreen
if %cmd%==cmd.restart goto CMDrestart
if %cmd%==cmd.talk goto talk
if %cmd%==cmd.ver goto CMDver
if %cmd%==cmd.sysver goto CMDsysver
if %cmd%==cmd.run goto runAPP
rem directory commands
if %cmd%==cmd.ls goto CMDDIRls
if %cmd%==cmd.lspath goto CMDDIRlspath
if %cmd%==cmd.cd goto CMDDIRcd
if %cmd%==cmd.mdir goto CMDDIRmkdir
rem internet command
if %cmd%==cmd.ipc goto INTERNETipc
if %cmd%==cmd.ipca goto INTERNETipca

echo invalid command.
echo.
goto cmdAgain

:help
echo.
echo Atmos Terminal v1.3.162
echo List of avalible commands :
echo.
echo [7;96mfunctional commands[0m
echo cmd.help    - Shows this list
echo cmd.cs      - Clear the terminal
echo cmd.exit    - Exit the terminal
echo cmd.restart - Restart the terminal
echo cmd.ver     - Print the version of the terminal
echo cmd.sysver  - Print the version of the system
echo cmd.talk    - Print the text
echo cmd.run     - Run the app you inserted
echo.
echo [7;96mfile system commands[0m
echo cmd.ls      - Print the contents of the directory
echo cmd.lspath  - Prints the path of current directory
echo cmd.cd      - Change directory
echo cmd.mdir    - Make directory
echo.
echo [7;96mnetworking commands[0m
echo cmd.ipc     - Show all the network satus
echo cmd.ipca    - Show detailed network satus
echo.
goto cmdAgain

:ClearScreen
cls
echo.
goto cmdAgain

:CMDrestart
cls
cls
goto welcome

:talk
title Atmos Terminal - talk
set /p talktext="Talk: "
echo %talktext%
echo.
goto cmdAgain

:CMDver
echo Atmos Terminal v1.3.162
echo.
goto cmdAgain

:CMDsysver
systeminfo | findstr /B /C:"OS Name" /B /C:"OS Version"
echo.
goto cmdAgain

:CMDDIRls
dir
echo.
goto cmdAgain

:CMDDIRlspath
echo.
echo Current directory :
echo %CD%
echo.
goto cmdAgain

:runAPP
echo Please enter full path of the program.
set /p runapp="RUN: "
start %runapp%
echo.
goto cmdAgain

:CMDDIRcd
echo current dir
echo %CD%
set /p cdto="CD: "
cd %cdto%
echo.
goto cmdAgain

:CMDDIRmkdir
echo current dir
echo %CD%
set /p mkdir="Directory Name: "
mkdir %mkdir%
echo cmdAgain

:INTERNETipc
ipconfig
echo.
goto cmdAgain

:INTERNETipca
ipconfig /all
echo.
goto cmdAgain


:CMDexit
echo exiting... Please Wait
timeout /t 01 /NOBREAK > NUL