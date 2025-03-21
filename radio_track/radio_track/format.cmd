:: (c) Copyright Dmitriy Shikhov 2017

@IF NOT DEFINED CLANG_FORMAT SET CLANG_FORMAT=clang-format.exe

@%CLANG_FORMAT% --version
@IF ERRORLEVEL 1 ECHO Error. Set CLANG_FORMAT or add path in PATH & GOTO :EOF

@CALL :FormatFilesInDirectory %CD%\source
@CALL :FormatFilesInDirectory %CD%\tests\source
@GOTO :EOF

:FormatFilesInDirectory
@SET DIRECTORY=%1
@ECHO.
@ECHO Processing directory "%DIRECTORY%"
@ECHO.
@PUSHD %DIRECTORY%
@FOR /F "tokens=*" %%F IN ('DIR /B/S/A-D *.cpp *.hpp *.h') DO @ECHO Processing file "%%F" & @%CLANG_FORMAT% -i -style=file %%F
@POPD
