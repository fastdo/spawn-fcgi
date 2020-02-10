# Build
如果 ./configure 不存在，就运行 ./autogen.sh。<br/>运行./autogen.sh需要您安装autotools工具集，包括autoheader,autoconf,aclocal,automake,libtool等。

    ./configure [--prefix=你期望的绝对路径]
    make
    make install

# Programs
## spawn-fcgi
### 简介
基于[lighttpd/spawn-fcgi](https://github.com/lighttpd/spawn-fcgi)修改。
- fcgi进程崩溃时取消core dump文件生成，改为自动启动新fcgi进程。
- 自动记录fcgi进程的PID到.pid文件。
- 通过msgget()来接收spawn-manager传来的命令控制自身。

### 使用示例
可以先把相关程序所在路径加入PATH环境变量。

以下命令将创建4个`FCGI程序`的子进程，并且监听9001端口。

    spawn-fcgi -a 127.0.0.1 -p 9001 -F 4 -f FCGI程序的路径

## spawn-manager
### 简介
增加spawn-manager程序能控制fcgi进程启动和spawn-fcgi退出。

### 使用示例
可以先把相关程序所在路径加入PATH环境变量。

以下命令将退出监听9001的spawn-fcgi程序及所有子FCGI程序进程。

    spawn-manager exit 9001

以下命令将令监听在9001端口上的spawn-fcgi程序再产生一个FCGI子进程。

    spawn-manager new 9001

以下命令列出监听在9001端口上的spawn-fcgi程序产生的FCGI子进程。

    spawn-manager list 9001

