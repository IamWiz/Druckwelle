@echo off
rmdir /S /Q lib
rmdir /S /Q inc

mkdir lib
mkdir inc
mkdir bin

:: CPPLinq
xcopy /E /Y 3rdparty\cpplinq\*.* inc

:: POSIX
xcopy /E /Y 3rdparty\POSIX\*.h inc

:: OpenCV 3.0
xcopy /E /Y 3rdparty\opencv\include inc
xcopy /E /Y 3rdparty\opencv\lib lib
xcopy /E /Y 3rdparty\opencv\bin\*.dll bin

:: zlib (contained in GDAL)
xcopy /E /Y 3rdparty\zlib\include\*.* inc
xcopy /E /Y 3rdparty\zlib\lib\*.* lib
xcopy /E /Y 3rdparty\zlib\bin\*.dll bin

:: libpng (contained in GDAL)
xcopy /E /Y 3rdparty\libpng\include\*.* inc
xcopy /E /Y 3rdparty\libpng\lib\*.* lib
xcopy /E /Y 3rdparty\libpng\bin\*.dll bin

:: FANNN
xcopy /E /Y 3rdparty\fann\include\*.* inc
xcopy /E /Y 3rdparty\fann\lib\*.* lib
xcopy /E /Y 3rdparty\fann\bin\*.dll bin

:: GDAL
xcopy /E /Y 3rdparty\GDAL\include inc
xcopy /E /Y 3rdparty\GDAL\lib lib
xcopy /E /Y 3rdparty\GDAL\bin\*.dll bin

:: libmicrohttpd
xcopy /E /Y 3rdparty\libmicrohttpd\include inc
xcopy /E /Y 3rdparty\libmicrohttpd\lib lib
xcopy /E /Y 3rdparty\libmicrohttpd\bin\*.dll bin

:: rapidjson
mkdir inc\rapidjson
xcopy /E /Y 3rdparty\rapidjson\include inc\rapidjson

:: gsl
xcopy /E /Y 3rdparty\gsl\include inc
xcopy /E /Y 3rdparty\gsl\lib lib

:: stb
xcopy /E /Y 3rdparty\stb inc

:: GTEngine
xcopy /E /Y 3rdparty\GeometricTools\GTEngine\Include inc
xcopy /E /Y 3rdparty\GeometricTools\lib lib





mkdir bin\Debug
mkdir bin\Release
xcopy /Y bin\*.* bin\Debug
xcopy /Y bin\*.* bin\Release