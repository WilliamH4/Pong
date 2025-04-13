@echo off
echo === Compiling ===
C:\msys64\ucrt64\bin\g++.exe -I C:/raylib/include main.cpp -o game.exe -L C:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel% neq 0 (
    echo Build failed.
    pause
    exit /b %errorlevel%
)

echo === Running ===
game.exe


