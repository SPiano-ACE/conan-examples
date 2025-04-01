# conan-examples
conan交叉编译例程

# 交叉编译基本概念
交叉编译是一种在特定的硬件平台和操作系统环境下，为另一个不同的硬件平台和操作系统环境生成可执行代码的编译方式。

通常情况下，软件开发是在目标运行的平台上进行编译，即编译环境和运行环境一致。但交叉编译打破了这一常规，它允许开发者在一个平台（称为主机平台）(BUILD_PLATFORM)上编写和编译代码，而生成的可执行文件将在另一个不同的平台（称为目标平台）(HOST_PLATFORM)上运行。

为何需要交叉编译?

* 硬件资源限制：目标平台可能资源有限，如嵌入式系统、物联网设备等，这些设备可能没有足够的计算能力和存储空间来支持完整的编译过程。通过在资源丰富的主机平台上进行交叉编译，可以更高效地完成代码编译。
* 开发效率考量：在开发过程中，使用功能强大的主机平台进行编译可以显著提高编译速度。例如，在高性能的桌面计算机上为资源受限的嵌入式设备进行代码编译，比在嵌入式设备本身进行编译要快得多。
* 跨平台开发需求：当开发者需要为多个不同的目标平台开发软件时，交叉编译可以让他们在一个统一的开发环境中进行代码编写和编译，减少了开发的复杂性和成本。

什么是conan?

* 它适用于包括 Windows、Linux、OSX、FreeBSD 等在内的所有操作系统，并且能够针对任何平台进行开发，包括桌面端、服务器端以及针对移动设备（Android 和 iOS）的跨平台构建，还有嵌入式和裸机设备。它能与诸如 Docker、MinGW、WSL 等其他工具以及诸如 CMake、MSBuild、Makefiles、Meson、SCons 等所有构建系统集成。它甚至还能与任何专有构建系统集成。

* 它与 JFrog Artifactory 实现了原生集成，包括免费的 Artifactory Community Edition 版本用于 Conan，使得开发人员能够在自己的服务器上托管自己的私有包。Conan 由一支由全职维护人员组成的完整团队开发，他们为从小型企业到大型企业的众多用户提供支持，并且还有一个活跃且出色的社区。

* 不仅不同版本的二进制文件存在差异，而且不同的构建配置也存在差异，包括不同的架构、编译器、编译器版本、运行时环境、C++ 标准库等等。当某个配置下的二进制文件不可用时，可以按需从源代码构建它们。Conan 在每个平台上都能使用相同的命令和流程来创建、上传和下载二进制文件，这在开发和持续集成中节省了大量的时间。

# 安装conan
推荐使用pip安装
```shell
pip install conan
```
生成本机默认编译环境配置文件
```shell
conan profile detect
```
第一次生成的配置文件如下:
```txt
detect_api: Found apple-clang 16.0
detect_api: apple-clang>=13, using the major as version

Detected profile:
[settings]
arch=armv8
build_type=Release
compiler=apple-clang
compiler.cppstd=gnu17
compiler.libcxx=libc++
compiler.version=16
os=Macos

WARN: This profile is a guess of your environment, please check it.
WARN: Defaulted to cppstd='gnu17' for apple-clang.
WARN: The output of this command is not guaranteed to be stable and can change in future Conan versions.
WARN: Use your own profile files for stability.
Saving detected profile to /Users/busybox/.conan2/profiles/default
```

# 仓库目录结构
```txt
├── profiles conan目标平台配置文件
├── src 例程源码目录
├── CMakeLists.txt
├── conanfile.py conan依赖描述文件
├── README.md

```

# 编译指南
## 编译MacOS应用
### arm64架构
```bash
rm -rf build
# -pr:b=default 表示编译环境使用的配置文件
# -pr:h=./profiles/macos-arm64 表示目标平台使用的配置文件
conan install . --build=missing --output-folder=build -pr:b=default -pr:h=./profiles/macos-arm64

cd build
source ./conanbuild.sh
cmake .. -D HOST_PLATFORM=macos-arm64 -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake
cmake --build . -j --config Release
```
### x86_64架构
```bash
rm -rf build
conan install . --build=missing --output-folder=build -pr:b=default -pr:h=./profiles/macos-x86_64

cd build
source ./conanbuild.sh
cmake .. -D HOST_PLATFORM=macos-x86_64 -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake
cmake --build . -j --config Release
```

## 编译Linux应用
Linux系统下交叉编译需要配置不同架构的源, 请将/etc/apt/sources.list 替换为如下内容（这里以Ubuntu22.04为例）
```bash
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy main restricted
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy-updates main restricted
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy universe
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy-updates universe
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy multiverse
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy-updates multiverse
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy-backports main restricted universe multiverse
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy-security main restricted
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy-security universe
deb [arch=arm64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ jammy-security multiverse

deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy universe
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates universe
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy multiverse
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates multiverse
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security main restricted
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security universe
deb [arch=amd64] https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-security multiverse
```
然后执行如下命令启动多架构支持 
```bash
sudo dpkg --add-architecture arm64 # 添加arm64架构支持
sudo dpkg --add-architecture amd64 # 添加amd64架构支持
sudo apt update
```
安装交叉编译工具链
```bash
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
sudo apt install gcc-x86-64-linux-gnu g++-x86-64-linux-gnu
```

如果编译环境为服务器端或者在docker容器中，为了编译QT，请安装图行库依赖
```bash
sudo apt install libgl-dev:arm64 libgl1-mesa-dev:arm64 libx11-dev:arm64 libx11-xcb-dev:arm64 libfontenc-dev:arm64 libice-dev:arm64 libsm-dev:arm64 libxau-dev:arm64 libxaw7-dev:arm64 libxcomposite-dev:arm64 libxcursor-dev:arm64 libxdamage-dev:arm64 libxfixes-dev:arm64 libxi-dev:arm64 libxinerama-dev:arm64 libxkbfile-dev:arm64 libxmuu-dev:arm64 libxrandr-dev:arm64 libxrender-dev:arm64 libxres-dev:arm64 libxss-dev:arm64 libxtst-dev:arm64 libxv-dev:arm64 libxxf86vm-dev:arm64 libxcb-glx0-dev:arm64 libxcb-render0-dev:arm64 libxcb-render-util0-dev:arm64 libxcb-xkb-dev:arm64 libxcb-icccm4-dev:arm64 libxcb-image0-dev:arm64 libxcb-keysyms1-dev:arm64 libxcb-randr0-dev:arm64 libxcb-shape0-dev:arm64 libxcb-sync-dev:arm64 libxcb-xfixes0-dev:arm64 libxcb-xinerama0-dev:arm64 libxcb-dri3-dev:arm64 uuid-dev:arm64 libxcb-cursor-dev:arm64 libxcb-dri2-0-dev:arm64 libxcb-dri3-dev:arm64 libxcb-present-dev:arm64 libxcb-composite0-dev:arm64 libxcb-ewmh-dev:arm64 libxcb-res0-dev:arm64 libxcb-util-dev:arm64 libxcb-util0-dev:arm64
sudo apt install libgl-dev:amd64 libgl1-mesa-dev:amd64 libx11-dev:amd64 libx11-xcb-dev:amd64 libfontenc-dev:amd64 libice-dev:amd64 libsm-dev:amd64 libxau-dev:amd64 libxaw7-dev:amd64 libxcomposite-dev:amd64 libxcursor-dev:amd64 libxdamage-dev:amd64 libxfixes-dev:amd64 libxi-dev:amd64 libxinerama-dev:amd64 libxkbfile-dev:amd64 libxmuu-dev:amd64 libxrandr-dev:amd64 libxrender-dev:amd64 libxres-dev:amd64 libxss-dev:amd64 libxtst-dev:amd64 libxv-dev:amd64 libxxf86vm-dev:amd64 libxcb-glx0-dev:amd64 libxcb-render0-dev:amd64 libxcb-render-util0-dev:amd64 libxcb-xkb-dev:amd64 libxcb-icccm4-dev:amd64 libxcb-image0-dev:amd64 libxcb-keysyms1-dev:amd64 libxcb-randr0-dev:amd64 libxcb-shape0-dev:amd64 libxcb-sync-dev:amd64 libxcb-xfixes0-dev:amd64 libxcb-xinerama0-dev:amd64 libxcb-dri3-dev:amd64 uuid-dev:amd64 libxcb-cursor-dev:amd64 libxcb-dri2-0-dev:amd64 libxcb-dri3-dev:amd64 libxcb-present-dev:amd64 libxcb-composite0-dev:amd64 libxcb-ewmh-dev:amd64 libxcb-res0-dev:amd64 libxcb-util-dev:amd64 libxcb-util0-dev:amd64
```
### arm64架构
```bash
rm -rf build
conan install . --build=missing --output-folder=build -pr:b=default -pr:h=./profiles/linux-arm64

cd build
source ./conanbuild.sh
cmake .. -D HOST_PLATFORM=linux-arm64 -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake
cmake --build . -j --config Release
```
### x86_64架构
```bash
rm -rf build
conan install . --build=missing --output-folder=build -pr:b=default -pr:h=./profiles/linux-x86_64

cd build
source ./conanbuild.sh
cmake .. -D HOST_PLATFORM=linux-x86_64 -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake
cmake --build . -j --config Release
```

## 编译Windows应用
请先安装 Visual Studio 2022 并勾选 C++ 桌面开发。
```bash
rm build
conan install . --build=missing --output-folder=build -pr:b=default -pr:h=./profiles/windows-x86_64

cd build
./conanbuild.bat
cmake .. -G "Visual Studio 17 2022" -D HOST_PLATFORM=windows-x86_64 -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake -D CMAKE_POLICY_DEFAULT_CMP0091=NEW
cmake --build . -j --config Release
```