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
这个项目是Stanford网络课的lab，实现了Intenet的一些重要组件：IP路由器、IP/Ethernet网络接口(适配器)、TCP协议，形成了一个相对完整的网络协议栈，最终可以替换掉Linux kernel提供的TCPSocket，向web server发送请求并接收响应，也可以双向传输文件，吞吐量可以达到1.6Gbit/s
7. 可靠传输怎么实现的  
checksum：  
seq & ack：  
流量控制：接收方的接收窗口recv_win是滑动的，发送方根据header中的ackno & window size确定是否继续发送segments  
超时重传：自动重传请求(automatic repeat request)，直到收到接收方的ack

9. 重传怎么实现  
用queue记录所有已经发送但是还未被接收方ack的segment(outstanding segments)，如果超时则重传这些segment(从最早的开始)。**超时时间**(retransmission timeout, RTO)的设置不能太长或太短，构造sender时会设置RTO的初始值(1s)，通过实现一个定时器判断是否超过了RTO，如果接收窗口不为0，记录**连续重传次数**，RTO加倍(exponential backoff, 指数回退)，如果收到了接收方的ackno大于之前收到的ackno，重置RTO和重传次数。如果重传次数大于8次，发送空的RST包终止连接。

11. 遇到的困难  
完成了receiver和sender模块后，在做connection模块连接两者时，有几个test case总是过不了，用wireshark抓包发现一直在重传SYN包，可能是网络问题或者receiver的bug，分析了很久没有头绪，后来将所有模块全部替换仍然在重传，最后发现因为虚拟机环境virtualbox的问题，配置好VMware的环境就OK了，至今不知道什么问题，怀疑是virtualbox网络转发相关问题。

13. 有什么亮点  
利用已有的性能优化知识突破了吞吐量瓶颈。实现了从传输层、网络层到数据链路层相对完整的协议栈，可以用来替换kernel提供的模块进行通信，也可以和实际的server进行通信。

15. 如何替换内核提供的TCPSocket
实现的TCP协议栈都在user space，用户态的TCP协议需要做到Application(webget.cc)-TCP-in-IP-in-Ethernet，并进而和网卡直接交互，旁路掉内核提供的协议栈。

17. 

## Map
1. 地图具体怎么实现的？怎么解析XML的地理数据
2. 图怎么存储的？用的啥数据库
3. 地图项目的滚动？如果滚得特别快应该怎么办？一会快一会满怎么办？

## CMU
### malloc
1. 别人调用会发生什么？
 - 检查申请的size是否小于等于0；
 - 调整size大小使其满足8B对齐要求，包括元信息的开销，包含开销的最小的块asize是16B；
 - 在已有的分级链表中（共16条free list，0-16B，17-32B，...，257-512MB）查找合适的链表（不为空且size合适），在该级链表中寻找满足大小的块进行分配，如果不满足就找下一级，返回指针；
 - 如果已有分级链表中没有满足要求的块，向虚拟堆申请更大的内存`max(asize, CHUNKSIZE)`，申请失败返回null，否则放置该块。
 - 所有的放置过程：如果剩余空闲容量小于16B就全部分配，如果要求的asize>=112B，从后面划分，否则从前面划分，将剩余空闲容量重新插入空闲链表。  
   为什么这样做可以提高性能？因为开始时free list基本为空，有些极端的测试样例是小大小大小大小大小大小大小大的情况，如果都是从头分配，那么如果free时只释放大的，就会造成很多内存外碎片，不连续所以不能合并，下次申请大的就寄了。  
   如果按照我们的方法，大的内存块释放时可以合并，下次申请大的就ok，提高内存利用率。  
2. 为什么你的实现比别人快？链表怎么实现的
 - 搜索时间只花费在特定的链表上而非整个堆，内存利用率近似于最佳匹配
 - 相比于隐式链表，现在每块都有prev和next指针，降低了分配的时间复杂度。原来是O(N)，现在是O(free)
3. TCMalloc, glibc malloc, jemalloc实现
 - glibc使用的是ptmalloc2 tcmalloc是谷歌的 jemalloc是fb的



8. free怎么知道大小
9. 如果用裸指针，valgrind是如何检测内存泄露的？
10. 内存对齐为什么快？
11. 共4G内存，父进程有2G内存，fork之后内存会爆吗？没有遇到过fork很慢的情况吗？
12. malloc项目遇到的问题？
13. 速度和内存利用率之间怎么权衡的

### shell
1. 僵尸子进程怎么回收的？Linux中是Z标记还是D标记？为什么不能自己回收自己的资源呢？
2. 

### web代理
1. HTTP格式

 HTTP请求报文组成：  
   请求行：请求方法 URL 协议版本\r\n  
若干行请求头部：头部字段名:值\r\n 包括host user-agent connection  
   \r\n  
   请求数据
3. URL的解析过程

解析请求行获得域名和端口  
   请求头部原封不动转发，缺少的头部用默认值填充
5. 别人调用会发生什么
6. 条件变量和锁为什么不能分开用？
7. 多线程并发怎么实现的？读写锁底层怎么实现的？锁这个变量如何保证并发修改不出错的？
8. LRU缓存读写锁效率问题
9. IO多路复用
10. 
