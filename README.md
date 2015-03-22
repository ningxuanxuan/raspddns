# raspddns


##项目说明
本项目是一个用c语言实现的在linux下通过dnspos 提供的api实现的一个动态域名解析工具，目标是在raspberry pi 下稳定运行
----
##工程依赖：  
1.libcurl  
2.libxml2  
这两个库可能会依赖libiconv, openssl, zlib, openssh等，推荐使用包管理器安装以上依赖的lib  
redhat 系列使用 sudo yum install libcurl-devel libxml2-devel 来安装  
raspberry pi 及 debian 系列使用 sudo apt-get install libcurl-dev libxml2-dev 来安装  

----
##编译方法：  
  gcc -o raspddns ddns.c request.c -lcurl -lxml2 -I /usr/include/libxml2  
