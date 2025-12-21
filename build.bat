@echo off
setlocal

REM ==============================
REM MSYS2 / MinGW setup
REM ==============================
set MSYS2_DIR=%CD%\msys2
set PATH=%MSYS2_DIR%\mingw64\bin;%PATH%

REM ==============================
REM Compiler flags
REM ==============================
set CXX=g++
set CXXFLAGS=-std=c++17 -O2
set INCLUDES=-Iinclude -Iinclude/raylib -Iinclude/ffmpeg
set LIBS=-Llib -lraylib -lavformat -lavcodec -lavutil -lswresample -lswscale -lopengl32 -lgdi32 -lwinmm -lshell32 -luser32

REM ==============================
REM Output
REM ==============================
set OUT=build\TetrisGame.exe

REM ==============================
REM Source files
REM ==============================
set SOURCES=^
src\core\main.cpp ^
src\core\game.cpp ^
src\core\global.cpp ^
src\util\icon.cpp ^
src\util\game-utils.cpp ^
src\ui\cursor-effect.cpp ^
src\ui\custom-colors.cpp ^
src\ui\window-manager.cpp ^
src\theme\theme-manager.cpp ^
src\stats\stats-manager.cpp ^
src\menu\menu.cpp ^
src\menu\game-menu.cpp ^
src\grid\grid.cpp ^
src\font\font-manager.cpp ^
src\booster\booster.cpp ^
src\booster\booster-manager.cpp ^
src\blocks\block.cpp ^
src\blocks\blocks.cpp ^
src\blocks\position.cpp ^
src\audio\audio-manager.cpp ^
src\animation\animation-manager.cpp ^
src\animation\ball-animation.cpp ^
src\animation\dots-animation.cpp ^
src\animation\lines-animation.cpp ^
src\animation\particle-animation.cpp ^
src\animation\square-animation.cpp ^
src\intro-video\video-player.cpp ^
src\intro-video\intro-video.cpp ^
src\background-image\background-image.cpp

REM ==============================
REM Build
REM ==============================
echo === Building Tetris ===
%CXX% %CXXFLAGS% %INCLUDES% %SOURCES% %LIBS% -o %OUT%

if errorlevel 1 (
    echo Build failed
    pause
    exit /b 1
)

echo Build successful: %OUT%
echo ==============================
%OUT%
pause
