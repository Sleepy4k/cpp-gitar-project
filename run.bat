echo off

REM Call g++ to compile file source name
g++ -std=c++11 "main.cpp" -o "main"

REM Check if compiling status is success
if %errorlevel% equ 0 (
  REM If success then we print compiling is success and run it
  echo Compiling success, Trying to run main.exe

  REM Run main
  "./main"
) else (
  echo Compiling error, something went wrong
)

pause
