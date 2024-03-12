@ECHO ON

set BASEDIR=%~dp0
PUSHD %BASEDIR%

RMDIR /Q /S build
@REM 创建虚拟环境
python -m venv .venv
@REM 使用虚拟环境
call .\.venv\Scripts\activate

python.exe -m pip install --upgrade pip
@REM 虚拟环境安装conan
pip install conan
conan install . --output-folder=build --build=missing
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=.\conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW
cmake --build . --config Release
cmake --build . --config Debug
@REM Release\xxx.exe

@REM 退出虚拟环境
deactivate