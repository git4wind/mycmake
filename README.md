# mycmake
win10+vscode+msys64/mingw64

====2023年6月3日00:25:34
win10系统64位,vscode 和 MSYS2 ,并MSYS2中安装 gcc g++ gdb开发环境, cmake,make,
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
将C:\msys64\mingw64\bin 添加到系统path中;

https://code.visualstudio.com/docs/cpp/config-mingw
https://az764295.vo.msecnd.net/stable/b3e4e68a0bc097f0ae7907b217c1119af9e03435/VSCodeUserSetup-x64-1.78.2.exe
即可实现超速下载 :将地址中的/stable前换成vscode.cdn.azure.cn
MSYS2中mingw-w64-x86_64-cmake的命令:  cmake -G Ninja //默认
-G Ninja
-G "MSYS Makefiles"
-G "MinGW Makefiles"  //配合make 命令使用;
