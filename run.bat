echo off

REM Get cpp file name
set /p file_source=Enter your cpp file: 

REM Print current system status
echo Compiling cpp file into executable file

REM Call g++ to compile file source name
g++ -std=c++11 "%file_source%.cpp" -o "%file_source%.exe"

REM Check if compiling status is success
if %errorlevel% equ 0 (
  REM If success then we print compiling is success and run it
  echo Compiling success, Trying to run %file_source%.exe

  "%file_source%.exe"
) else (
  echo Compiling error, something went wrong
)

pause
