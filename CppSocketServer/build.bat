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
echo [settings] > C:\Users\Administrator\.conan2\profiles\whmProfile
echo arch=x86_64 >> C:\Users\Administrator\.conan2\profiles\whmProfile
echo build_type=Debug >> C:\Users\Administrator\.conan2\profiles\whmProfile
echo os=Windows >> C:\Users\Administrator\.conan2\profiles\whmProfile
echo compiler=msvc >> C:\Users\Administrator\.conan2\profiles\whmProfile
echo compiler.cppstd=23 >> C:\Users\Administrator\.conan2\profiles\whmProfile
echo compiler.runtime=dynamic >> C:\Users\Administrator\.conan2\profiles\whmProfile
echo compiler.version=193 >> C:\Users\Administrator\.conan2\profiles\whmProfile
echo compiler.runtime_type=Debug >> C:\Users\Administrator\.conan2\profiles\whmProfile

conan install . --output-folder=build --build=missing --profile=whmProfile
cd build
@REM CMAKE_TOOLCHAIN_FILE 的主要作用是定义和配置工具链	 								
@REM 																	  CMAKE_PREFIX_PATH是要编译的文件所在的安装路径
cmake .. -G "Visual Studio 17 2022"  -DCMAKE_TOOLCHAIN_FILE=D:\project\cppProject\CppSocketServer\build\conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW  -Wno-dev

@REM cmake --build . --config Release -- /m
@REM cmake --build . --config Debug -- /m

@REM Release\xxx.exe
@REM start devenv build\CppSocketServer.sln


@REM 退出虚拟环境
deactivate