@ECHO OFF

IF NOT EXIST build MKDIR build
:: build
PUSHD build	 	
conan install ..
conan build ..

