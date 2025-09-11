@ECHO ON

set BASEDIR=%~dp0
PUSHD %BASEDIR%

IF EXIST build (
  RMDIR /Q /S build 2>nul
  IF ERRORLEVEL 1 (
    echo 无法删除build目录，可能正在使用中。尝试继续...
  )
)
mkdir build 2>nul

REM 不使用虚拟环境，直接使用系统Python
python.exe -m pip install --upgrade pip
python.exe -m pip install conan
set CONAN_PROFILE_PATH=
if exist "%USERPROFILE%\.conan\profiles\" (
    set CONAN_PROFILE_PATH=%USERPROFILE%\.conan\profiles\whmProfile
) else if exist "%USERPROFILE%\.conan2\profiles\" (
    set CONAN_PROFILE_PATH=%USERPROFILE%\.conan2\profiles\whmProfile
) else if exist "C:\.conan\profiles\" (
    set CONAN_PROFILE_PATH=C:\.conan\profiles\whmProfile
) else if exist "C:\.conan2\profiles\" (
    set CONAN_PROFILE_PATH=C:\.conan2\profiles\whmProfile
) else (
    mkdir "%USERPROFILE%\.conan\profiles" 2>nul
    set CONAN_PROFILE_PATH=%USERPROFILE%\.conan\profiles\whmProfile
)


(
echo [settings]
echo arch=x86_64
echo build_type=Debug
echo os=Windows
echo compiler=msvc
echo compiler.cppstd=23
echo compiler.runtime=dynamic
echo compiler.version=193
echo compiler.runtime_type=Debug
echo.
echo [options]
echo *:shared=True
echo boost/*:shared=True
echo boost/*:with_stacktrace_backtrace=True
echo boost/*:without_cobalt=True
echo boost/*:without_contract=True
echo boost/*:without_coroutine=True
echo boost/*:without_fiber=True
echo boost/*:without_graph=True
echo boost/*:without_graph_parallel=True
echo boost/*:without_iostreams=True
echo boost/*:without_json=True
echo boost/*:without_log=True
echo boost/*:without_math=True
echo boost/*:without_mpi=True
echo boost/*:without_nowide=True
echo boost/*:without_process=True
echo boost/*:without_program_options=True
echo boost/*:without_python=True
echo boost/*:without_serialization=True
echo boost/*:without_stacktrace=True
echo boost/*:without_test=True
echo boost/*:without_timer=True
echo boost/*:without_type_erasure=True
echo boost/*:without_url=True
echo boost/*:without_wave=True
echo boost/*:zstd=False
) > "%CONAN_PROFILE_PATH%"

conan install . --output-folder=build --build=missing --profile=whmProfile
cd build
@REM CMAKE_TOOLCHAIN_FILE 的主要作用是定义和配置工具链	 								
@REM 																	  CMAKE_PREFIX_PATH是要编译的文件所在的安装路径
cmake .. -G "Visual Studio 17 2022"  -DCMAKE_TOOLCHAIN_FILE=D:\project\cppProject\CppSocketServer\build\conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW  -Wno-dev

@REM cmake --build . --config Release -- /m
@REM cmake --build . --config Debug -- /m

@REM Release\xxx.exe
@REM start devenv build\CppSocketServer.sln
