@echo off

:: -----------------------------------------------------------------------------------
:: |           _                         _______                  _             _    |
:: |      /\  | |                       |__   __|                (_)           | |   |
:: |     /  \ | |_ _ __ ___   ___  ___     | | ___ _ __ _ __ ___  _ _ __   __ _| |   |
:: |    / /\ \| __| '_ ` _ \ / _ \/ __|    | |/ _ \ '__| '_ ` _ \| | '_ \ / _` | |   |
:: |   / ____ \ |_| | | | | | (_) \__ \    | |  __/ |  | | | | | | | | | | (_| | |   |
:: |  /_/    \_\__|_| |_| |_|\___/|___/    |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_|   |
:: |                                                                                 |
:: -----------------------------------------------------------------------------------

::                         V E R S I O N   1 . 7 . 4 

::     Local Vars : 
::           GlobalParam1  =  Command line 2nd option
::           termver       =  Terminal version
::           username      =  Current user name
::           cmd           =  The command placeholder

::     Known Issues : 
::           command cmd.Gsnake  --  Crash when start
::           runtime cli         --  Crash if run two word at one time

::     Common Commands :
::           wait 200ms  -  ping /n 1 /w 200 localhost > nul


::     Pending commands to add :
::           cmdadmin.actvwtmrkoff =  bcdedit /set TESTSIGNING OFF


::      W A R N I N G : You are looking into the source code of atmos terminal.
::                      You are editing the source code and you know what you are doing.
::                           ! ! !    EDIT   IT   CAREFULLY    !!!



:: C  O  D  E    S  T  A  R  T  S    H  E  R  E

echo initializing...
rem startup init
echo setlocal
SETLOCAL ENABLEDELAYEDEXPANSION
ping /n 1 /w 200 localhost > nul
echo set screen size
mode 117, 39
ping /n 1 /w 200 localhost > nul
echo set title
title Atmos Terminal
ping /n 1 /w 200 localhost > nul
echo set variables
set GlobalParam1=%1
set termver=v1.7.4
ping /n 1 /w 200 localhost > nul
::if %GlabalParam1%=="" goto continue
:globalparam
::echo parameter = %GlobalParam1%
goto welcome
:continue
ping /n 1 /w 200 localhost > nul
cls

:welcome
timeout /t 1 /nobreak > nul
cls
ping /n 1 /w 200 localhost > nul
echo Welcome to [93mAtmos Terminal[0m !
echo Type [7mcmd.help[0m to get the list of avalible commands.
echo.

:cmdAgain
title Atmos Terminal
set /p cmd="%username% > "

:: cli cmd config

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
rem os commands
if %cmd%==cmd.shutdown goto OSshutdown
if %cmd%==cmd.restart goto OSrestart
if %cmd%==cmd.sleep goto OSsleep
rem directory commands
if %cmd%==cmd.ls goto CMDDIRls
if %cmd%==cmd.lspath goto CMDDIRlspath
if %cmd%==cmd.cd goto CMDDIRcd
if %cmd%==cmd.mdir goto CMDDIRmkdir
rem administrator command
if %cmd%==cmdadmin.takeowner goto ADMINCMDTAKEOWN
rem internet command
if %cmd%==cmd.ipc goto INTERNETipc
if %cmd%==cmd.ipca goto INTERNETipca
rem game command
if %cmd%==cmd.Gsnake goto GAMEsnake
rem funny triggers
if %cmd%==huh goto TEXThuh
if %cmd%==what goto TEXTwhat
rem Admin Test command
::if %cmd%==cmd.admintest.
if %cmd%==cmd.admintest.sysinf goto TESTsysinf
if %cmd%==cmd.admintest.sysinfall goto TESTsysinfall
if %cmd%==cmd.admintest.glovar goto TESTglovar

:: invalid cmd prevention (error output)
echo invalid command.
echo.
goto cmdAgain

:: help menu
:help
echo.
echo Atmos Terminal %termver%
echo List of avalible commands :
echo.
echo [7;96m Functional commands [0m
echo cmd.help           - Shows this list
echo cmd.cs             - Clear the terminal
echo cmd.exit           - Exit the terminal
echo cmd.restart        - Restart the terminal
echo cmd.ver            - Print the version of the terminal
echo cmd.sysver         - Print the version of the system
echo cmd.talk           - Print the text
echo cmd.run            - Run the app you inserted
echo.
echo [7;96m System commands [0m
echo os.shutdown        - shutdown the computer
echo os.restart         - restart the computer
echo os.sleep           - hibernate the computer aka sleep
echo.
echo [7;96m Administration commands [0m
echo cmdadmin.takeowner - give the folder or file's permission to yourself
echo.
echo [7;96m File system commands [0m
echo cmd.ls             - Print the contents of the directory
echo cmd.lspath         - Prints the path of current directory
echo cmd.cd             - Change directory
echo cmd.mdir           - Make directory
echo.
echo [7;96m Networking commands [0m
echo cmd.ipc            - Show all the network satus
echo cmd.ipca           - Show detailed network satus
echo cmd.ipcres         - remove your IP address
echo cmd.ipcget         - get your new IP address
echo cmd.ipreget        - basicly run both ipcres and ipcget
echo.
echo [7;96m Game commands [0m
echo cmd.Gsnake  - Launch the game Snake
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
echo Atmos Terminal %termver%
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
::echo Please enter full path of the program.
set runparam=%1
start %runparam%
::set /p runapp="RUN: "
::start %runapp%
echo.
goto cmdAgain

:CMDDIRcd
echo current dir : %CD%
echo type exitcd to exit
set /p cdto="CD: "
if %cdto%==exitcd goto cmdAgain else cd /d %cdto%
echo.
goto cmdAgain

:CMDDIRmkdir
echo current dir
echo %CD%
set /p mkdir="Directory Name: "
mkdir %mkdir%
goto cmdAgain

:INTERNETipc
ipconfig
echo.
goto cmdAgain

:INTERNETipca
ipconfig /all
echo.
goto cmdAgain

:INTERNETipc.reset
ipconfig /release
echo.
goto cmdAgain

:INTERNETipc.renew
ipconfig /renew
echo.
goto cmdAgain

:INTERNETipc.reget
ipconfig /release
echo.
echo please wait 2 seconds for reget IP
timeout /t 2 /nobreak > NUL
echo.
ipconfig /renew
echo.
echo Complete.
echo.
goto cmdAgain

:OSshutdown
choice /c:Yn /m "Y to shutdown, n to cancel"
if %errorlevel% EQU 1 goto OSCMDshutdown else goto cmdAgain
if %errorlevel% EQU 2 goto OScancel else goto cmdAgain

:OSCMDshutdown
shutdown /s /t 00

:OSrestart
choice /c:Yn /m "Y to shutdown, n to cancel"
if %errorlevel% EQU 1 goto OSCMDrestart else goto cmdAgain
if %errorlevel% EQU 2 goto OScancel else goto cmdAgain

:OSCMDrestart
shutdown /r /t 00

:OSsleep
choice /c:Yn /m "Y to shutdown, n to cancel"
if %errorlevel% EQU 1 goto OSCMDsleep else goto cmdAgain
if %errorlevel% EQU 2 goto OScancel else goto cmdAgain

:OSCMDsleep
shutdown /h /t 00

:OScancel
echo command aborted.
echo.
goto cmdAgain

:ADMINCMDTAKEOWN
set /p takeowndir="directory path> "
choice /c Yn /n /m "do you want access to sub folder? (Y/n)> "
if %ERRORLEVEL%==1 set subfol=y
if %ERRORLEVEL%==2 set subfol=n
goto atofwd

:atofwd
if %subfol%==y takeown /f "%takeowndir%" /r /d y
if %subfol%==n takeown /f "%takeowndir%"
echo command executed.
echo.
goto cmdAgain





::funny things

:TEXThuh
echo huh?
echo.
goto cmdAgain

:TEXTwhat
echo what what?
echo.
goto cmdAgain

::funny things end
rem                                                                                        :)
:: test playgroud

:TESTsysinf
systeminfo | findstr /B /C:"OS Name" /B /C:"OS Version" /B /C:"Total Physical Memory" /B /C:"Available Physical Memory" /B /C:"System Locale"
echo.
goto cmdAgain

:TESTsysinfall
systeminfo
echo.
goto cmdAgain

:TESTsysclock




:TESTglovar
echo GlobalParam1 : %GlabalParam1%%
echo.
goto cmdAgain





:: test playground end

:GAMEsnakeremind
cls
echo warning


:GAMEsnake
rem snake game by thelowsunoverthemoon at github
rem ---------------------------------------------------------------------------------------


@echo off
IF not "%1" == "" (
    GOTO :%1
)
TITLE Atmos Terminal - Snake by thelowsunoverthemoon
MODE 30, 22
FOR /F %%A in ('ECHO prompt $E^| cmd') DO SET "ESC=%%A"
(CHCP 65001)>NUL

SET "mov[W]=y]-=1"
SET "mov[A]=x]-=1"
SET "mov[S]=y]+=1"
SET "mov[D]=x]+=1"
SET "snake[bou]=.0;0."
SET "skin[1]=%ESC%[38;2;105;78;148m▒$%ESC%[38;2;184;20;184m▓"
SET "skin[2]=%ESC%[38;2;235;180;52m♣$%ESC%[38;2;209;109;38m♥"
SET "skin[3]=%ESC%[38;2;212;38;61m◙$%ESC%[38;2;222;100;116m◘"
SET /A "map[width]=30", "map[height]=15", "char[0][x]=d[x]=3","char[0][y]=d[y]=3","snake[mass]=1","pel[x]=0","snake[speed]=16"

CALL :MAKEMAP %map[width]% %map[height]%

SET "exit=ECHO %ESC%[1;1H%disp[kill]%%ESC%[38;2;255;255;255m%ESC%[%map[height]%;1H%ESC%[3BOuch...Press W to Continue&(COPY NUL "%~dpn0.quit")>NUL&EXIT"
DEL "%~dpn0.quit" 2>NUL
ECHO %ESC%[?25l%ESC%[38;2;255;255;255mChoose your skin&FOR /L %%Q in (1, 1, 3) DO (
    ECHO %ESC%[B%ESC%[38;2;255;255;255m[%%Q] !skin[%%Q]:$=!!skin[%%Q]:$=!!skin[%%Q]:$=!
)
(CHOICE /C 123 /N)>NUL
FOR /F "tokens=1-2 delims=$" %%A in ("!skin[%errorlevel%]!") DO (
    SET "snake[cha][1]=%%A"&SET "snake[cha][2]=%%B"
)
SET "snake[disp]=%ESC%[%char[0][y]%;%char[0][x]%H%ESC%[38;2;184;20;184m%snake[cha][2]%"

:START
SETLOCAL
"%~F0" CONTROL >"%temp%\%~n0_signal.txt" | "%~F0" GAME <"%temp%\%~n0_signal.txt"
ENDLOCAL
GOTO :START

:GAME
FOR /L %%# in () DO (
    SET /P "input="
    SET /A "frames+=1"
    IF !pel[x]! EQU 0 (
        SET /A "pel[x]=!RANDOM! * ((%map[width]% - 1) - 2 + 1) / 32768 + 2", "pel[y]=!RANDOM! * ((%map[height]% - 1) - 2 + 1) / 32768 + 2"
        SET "pel[disp]=%ESC%[!pel[y]!;!pel[x]!H%ESC%[38;2;50;168;82m■"
    )
    IF defined input (
        FOR %%A in (!input!) DO (
            IF not "!input[cur]!" == "!mov[%%A]!" (
                SET "input[new]=1"
            )
            SET "input[cur]=!mov[%%A]!"
        )
    )
    (SET /A "1/((((~(0-(frames %% snake[speed]))>>31)&1)&((~((frames %% snake[speed])-0)>>31)&1))|input[new])" 2>NUL) && (
        SET /A "d[x]=char[0][x]","d[y]=char[0][y]","d[!input[cur]!","input[new]=0"
        IF !d[x]! LSS %map[width]% ( IF !d[x]! GTR 1 (
            IF !d[y]! LSS %map[height]% ( IF !d[y]! GTR 1 (
                SET "snake[disp]="
                SET /A "d[shift][x]=char[0][x]=d[x]","d[shift][y]=char[0][y]=d[y]"
                IF "!pel[x]!;!pel[y]!" == "!d[x]!;!d[y]!" (
                    SET /A "pel[x]=0","snake[mass]+=1"
                )
                IF !snake[mass]! NEQ 1 (
                    FOR %%Q in (".!d[x]!;!d[y]!.") DO (
                        IF not "!snake[bou]!" == "!snake[bou]:%%~Q=!" (
                            %exit%
                        )
                    )
                )
                SET "snake[bou]="
                FOR /L %%M in (1, 1, !snake[mass]!) DO (
                    SET "snake[bou]=!snake[bou]!.!char[%%M][x]!;!char[%%M][y]!"
                    SET /A "d[save][x]=char[%%M][x]","d[save][y]=char[%%M][y]", "char[%%M][x]=d[shift][x]","char[%%M][y]=d[shift][y]", "d[shift][x]=d[save][x]","d[shift][y]=d[save][y]","d[disp]=%%M %% 2"
                    IF !d[disp]! EQU 0 (
                        SET "snake[disp]=!snake[disp]!%ESC%[!char[%%M][y]!;!char[%%M][x]!H%ESC%[38;2;105;78;148m%snake[cha][1]%"
                    ) else (
                        SET "snake[disp]=!snake[disp]!%ESC%[!char[%%M][y]!;!char[%%M][x]!H%ESC%[38;2;184;20;184m%snake[cha][2]%"
                    )
                )
                SET "snake[bou]=!snake[bou]!."
            ) else (%exit%)) else (%exit%)
        ) else (%exit%)) else (%exit%)
    )
    ECHO %ESC%[2J%ESC%[1;1H%disp[map]%!pel[disp]!!snake[disp]!%ESC%[38;2;255;255;255m%ESC%[%map[height]%;1H%ESC%[BScore : !snake[mass]!%ESC%[1G%ESC%[BUse WASD to move
)

:MAKEMAP <width> <height>
SETLOCAL
SET "disp[border]="
FOR /L %%W in (1, 1, %1) DO (
    SET "disp[border]=!disp[border]!█"
)
SET /A  "width[adj]=%1 - 2","height[adj]=%2 - 1"
SET "disp[map]=%disp[border]%#%ESC%[B%ESC%[%1D%disp[border]%"
FOR /L %%H in (2, 1, %height[adj]%) DO (
    SET "disp[map]=!disp[map]:#=%ESC%[B%ESC%[%1D█%ESC%[%width[adj]%C█#!"
)
SET "disp[map]=%disp[map]:#=%"
ENDLOCAL&SET "disp[map]=%ESC%[38;2;148;194;224m%disp[map]%"&SET "disp[kill]=%ESC%[38;2;41;100;138m%disp[map]:█=X%"
GOTO :EOF

:CONTROL
FOR /L %%C in () do (
    FOR /F "tokens=*" %%A in ('CHOICE /C:WASD /N') DO (
        IF exist "%~dpn0.quit" (
            DEL "%~dpn0.quit"
            EXIT
        )
        <NUL SET /P ".=%%A"
    )
)
mode con:cols=80 lines=100
GOTO cmdAgain


rem ---------------------------------------------------------------------------------------

:


:CMDexit
echo exiting... Please Wait
endlocal
timeout /t 01 /NOBREAK > NUL
