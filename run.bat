echo off

REM Get cpp file name
REM set /p file_source=Enter your cpp file: 

REM Print current system status
REM echo Compiling cpp file into executable file

REM Call g++ to compile file source name
REM g++ -std=c++11 "%file_source%.cpp" -o "%file_source%.exe"
g++ -std=c++11 "main.cpp" -o "main.exe"

REM Check if compiling status is success
if %errorlevel% equ 0 (
  REM If success then we print compiling is success and run it
  echo Compiling success, Trying to run main.exe

  "main.exe"
) else (
  echo Compiling error, something went wrong
)

pause
