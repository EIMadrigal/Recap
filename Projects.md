性能分析和优化
## CS144
1. 性能瓶颈突破过程  
项目的最低要求是100Mbit/s，虽然第一个版本可以达到1.1Gbit/s左右，但是官方说自己的吞吐量可以达到1.7Gbit/s，所以为了提升性能，要利用CSAPP中的性能优化相关知识挑战。  
首先，profiling寻找性能瓶颈。修改编译参数，将-g改为-Og -pg，使得生成程序可以用gprof进行剖析；将对benchmark的分析结果重定向到文本，观察耗时操作；  
其次，发现了ByteStream的write/pop_output/peek_output操作占据了大概80%的时间，ByteStream的容器是`deque<char>`，以`write`方法为例，入参是`string& data`，`write`时将`data`中的字符拷贝到`deque`中，存储方式是**基于内存拷贝的**，比较慢；  
因此，希望将buffer的对象的存储方式改为**基于内存所有权转移**，通过`move(string&)`将左值引用转为右值引用，进而调用移动构造函数`BufferList(string &&str)`，将`data`变为一个shared object，通过引用计数以及指针偏移控制访问，避免拷贝`data`，从而提升性能。另外，对于`pop_output/peek_output`，以前是用`for`循环真的从`deque`中pop字符，改为shared后直接移动指针偏移量即可，再次提高了性能。  
移动构造函数的参数是右值引用即只接受右值，`move`是将左值强制转换为右值，让右值引用可以指向，等同于`static_cast<T&&>(lvalue)`
3. 项目的测试过程  
根据课程提供的测试用例；将Linux Kernel中的`TCPSocket`替换为自己实现的`CS144TCPSocket`，和真正的webserver通信；遇到Bug时通过构造一些小case，打断点观察相应变量的变化，或者通过wireshark抓包
5. 项目整体介绍，包括目的、功能、实用价值  
这个项目是Stanford网络课的lab，实现了Intenet的一些重要组件：IP路由器、IP/Ethernet网络接口(适配器)、TCP协议，形成了一个相对完整的网络协议栈，最终可以替换掉Linux kernel提供的TCPSocket，向web server发送请求并接收响应，也可以双向传输文件。
7. 可靠传输怎么实现的
8. 重传怎么实现
9. 遇到的困难
10. 有什么亮点

## Map
1. 地图具体怎么实现的？怎么解析XML的地理数据
2. 图怎么存储的？用的啥数据库
3. 地图项目的滚动？如果滚得特别快应该怎么办？一会快一会满怎么办？

## CMU
### malloc
1. 别人调用会发生什么
2. 为什么你的实现比别人快
3. TCMalloc, glibc malloc, jemalloc实现
4. 链表怎么实现的
5. free怎么知道大小
6. 如果用裸指针，valgrind是如何检测内存泄露的？
7. 内存对齐为什么快？
8. 共4G内存，父进程有2G内存，fork之后内存会爆吗？没有遇到过fork很慢的情况吗？
9. malloc项目遇到的问题？
10. 速度和内存利用率之间怎么权衡的

### shell
1. 僵尸子进程怎么回收的？Linux中是Z标记还是D标记？为什么不能自己回收自己的资源呢？
2. 

### web代理
1. HTTP格式
2. URL的解析过程
3. 别人调用会发生什么
4. 条件变量和锁为什么不能分开用？
5. 多线程并发怎么实现的？读写锁底层怎么实现的？锁这个变量如何保证并发修改不出错的？
6. LRU缓存读写锁效率问题
7. IO多路复用
8. 
