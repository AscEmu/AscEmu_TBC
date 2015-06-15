@ECHO OFF
TITLE WhyDB's Installation Tool
COLOR 0A

:TOP
CLS
ECHO.
ECHO          ษออออออออออออออออออออออออออออออออป
ECHO          บ                                บ
ECHO          บ      Welcome to the WhyDB      บ
ECHO          บ        Installation Tool       บ
ECHO          บ                                บ
ECHO          ศออออออออออออออออออออออออออออออออผ
ECHO.
ECHO            ##############################
ECHO            #    http://www.whydb.org    #
ECHO            ##############################
ECHO.
ECHO    Please enter your MySQL Info...
ECHO.
SET /p host= MySQL Server Address (e.g. localhost): 
ECHO.
SET /p user= MySQL Username: 
SET /p pass= MySQL Password: 
ECHO.
SET /p world_db= World Database: 

SET port=3306
SET dumppath=.\dump\
SET mysqlpath=.\mysql\
SET devsql=.\development\ascent_world
SET changsql=.\development\changesets


:Begin
CLS
SET v=""
ECHO.
ECHO  oooooo   oooooo     oooo oooo                    oooooooooo.   oooooooooo.  
ECHO   `888.    `888.     .8'   888                     888    `Y8b   888    `Y8b 
ECHO    `888.   .8888.   .8'    888 .oo.   oooo    ooo  888      888  888     888 
ECHO     `888  .8'`888. .8'     888P"Y88b   `88.  .8'   888      888  888oooo888' 
ECHO      `888.8'  `888.8'      888   888    `88..8'    888      888  888    `88b 
ECHO       `888'    `888'       888   888     `888'     888     d88'  888    .88P 
ECHO        `8'      `8'       o888o o888o     .8'     o888bood8P'   o888bood8P'  
ECHO                                       .o..8'                                 
ECHO    http://www.whydb.org               `Y8P' 
ECHO.
ECHO    I - Import World Database, NOTE! Whole db will be overwritten!
ECHO    W - Backup World Database.
ECHO    C - Backup Character Database.
ECHO.
ECHO    D - Dump your table.
ECHO    S - Change your settings
ECHO.
ECHO    X - Exit this tool
ECHO.
SET /p v= 		Enter a char: 
IF %v%==* GOTO error
IF %v%==i GOTO import
IF %v%==I GOTO import
IF %v%==w GOTO dumpworld
IF %v%==W GOTO dumpworld
IF %v%==c GOTO dumpchar
IF %v%==C GOTO dumpchar
IF %v%==d GOTO dumpever
IF %v%==D GOTO dumpever
IF %v%==s GOTO top
IF %v%==S GOTO top
IF %v%==x GOTO exit
IF %v%==X GOTO exit
IF %v%=="" GOTO exit
GOTO error

:import
CLS
ECHO First Lets Create database (or overwrite old) !!
ECHO.
ECHO DROP database IF EXISTS `%world_db%`; > %devsql%\databaseclean.sql
ECHO CREATE database IF NOT EXISTS `%world_db%`; >> %devsql%\databaseclean.sql
%mysqlpath%\mysql --host=%host% --user=%user% --password=%pass% --port=%port% < %devsql%\databaseclean.sql
@DEL %devsql%\databaseclean.sql
ECHO Database %world_db% successfully created !
ECHO.
ECHO Importing files now...
ECHO.
FOR %%C IN (%devsql%\*.sql) DO (
	ECHO Importing: %%~nxC
	%mysqlpath%\mysql --host=%host% --user=%user% --password=%pass% --port=%port% %world_db% < "%%~fC"
	ECHO Successfully imported %%~nxC
)
ECHO Done.
ECHO.
ECHO.
ECHO You don't have to import any changesets or updates now!
ECHO.
ECHO.
PAUSE
GOTO exit

:dumpworld
CLS
IF NOT EXIST "%dumppath%" MKDIR %dumppath%
ECHO %world_db% Database Export started...

FOR %%a IN ("%devsql%\*.sql") DO SET /A Count+=1
setlocal enabledelayedexpansion
FOR %%C IN (%devsql%\*.sql) DO (
	SET /A Count2+=1
	ECHO Dumping [!Count2!/%Count%] %%~nC
	%mysqlpath%\mysqldump --host=%host% --user=%user% --password=%pass% --port=%port% %world_db% %%~nC > %dumppath%\%%~nxC
)
endlocal 

ECHO  Finished ... %world_db% exported to %dumppath% folder...
PAUSE
GOTO begin

:dumpchar
CLS
SET sqlname=char-%DATE:~0,3% - %DATE:~4,2%-%DATE:~7,2%-%DATE:~10,4%--%TIME:~0,2%-%TIME:~3,2%
SET /p chardb=   Enter name of your character DB:
ECHO.
IF NOT EXIST "%dumppath%" MKDIR %dumppath%
ECHO Dumping %sqlname%.sql to %dumppath%
%mysqlpath%\mysqldump -u%user% -p%pass% --result-file="%dumppath%\%sqlname%.sql" %chardb%
ECHO Done.
PAUSE
GOTO begin

:changeset
CLS
ECHO   Please Write down number of changeset (not the number of rev!!!)
ECHO   Or type in "a" to import all changesets
ECHO.
ECHO.
set /p ch=      Number: 
ECHO.
IF %ch%==a GOTO changesetall
ECHO      Importing...
IF NOT EXIST "%changsql%\changeset_%ch%.sql" GOTO error2
ECHO.
%mysqlpath%\mysql --host=%host% --user=%user% --password=%pass% --port=%port% %world_db% < %changsql%\changeset_%ch%.sql
ECHO.
ECHO      File changeset_%ch%.sql imported sucesfully!
ECHO.
PAUSE
GOTO begin

:changesetall
CLS
ECHO.
ECHO import: Changesets
for %%C in (development\changesets\*.sql) do (
	ECHO import: %%~nxC
	%mysqlpath%\mysql --host=%host% --user=%user% --password=%pass% --port=%port% %world_db% < "%%~fC"
)
ECHO Changesets imported sucesfully!
ECHO.
PAUSE   
GOTO begin

:dumpever
CLS
ECHO.
ECHO          Type there name of table, which you want to dump
ECHO.
SET z=""
SET /p z=           Name: 
IF %z%=="" GOTO error
ECHO              Processing....
ECHO.
IF NOT EXIST "%dumppath%" MKDIR %dumppath%

%mysqlpath%\mysqldump --host=%host% --user=%user% --password=%pass% --add-drop-table %world_db% "%z%" > "%dumppath%\%z%.sql"

ECHO              Dump table %z% from database %world_db% is successful !
ECHO.
SET y=""
SET /p y=          Dump another table (Y/N)?: 
IF %y%==y GOTO dumpever
IF %y%==Y GOTO dumpever
IF %y%==n GOTO begin
IF %y%==N GOTO begin
ELSE GOTO dumpever

:error
ECHO	Please enter a correct character.
ECHO.
PAUSE
GOTO begin

:error2
ECHO	Changeset with this number not found.
ECHO.
PAUSE
GOTO begin

:exit