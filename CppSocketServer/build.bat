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
@REM conan默认配置文件
conan profile detect
conan install . --output-folder=build --build=missing
cd build
@REM CMAKE_TOOLCHAIN_FILE 的主要作用是定义和配置工具链	 								
@REM 																	  CMAKE_PREFIX_PATH是要编译的文件所在的安装路径
cmake .. -G "Visual Studio 17 2022"  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_PREFIX_PATH=build 

cmake --build . --config Release
cmake --build . --config Debug
@REM Release\xxx.exe

@REM 退出虚拟环境
deactivate