@echo off

echo Building...

gcc -Wall -Wextra -pedantic -std=c18 source/main.c


if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

echo Build successful!