@echo off

rem Allow unicode characters
chcp 65001 >nul 2>nul

setlocal enabledelayedexpansion

set OUTPUT=snake.exe
set SOURCES=

for /r %%i in (*.c) do (
  set SOURCES=!SOURCES! "%%i"
)

echo 🔧 Building.

gcc -Wall -Wextra -pedantic -I./src -std=c18 %SOURCES% -o %OUTPUT%


if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

echo Build successful!