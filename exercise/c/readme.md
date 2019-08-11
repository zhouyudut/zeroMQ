**epoll** zmq_poll可以实现类似epoll的功能，但感觉很繁琐 </br>
**inporc** 主从线程通信，主线程与工作者线程绑定套接字进行通信</br>
**multiReqRsp** 通过中间件进行通信，router、dealer</br>
**pair** 工作线程通信，使用pair进行一对一通信</br>
**PubSub** ZMQ_SUB、ZMQ_PUB通信模式</br>
**sendMore** 消息封包，多个消息片段</br>
**sync** 进程间同步，使用REQ、REP同步SUB、PUB，但是效果并不好，有两个问题，一个是上一次执行完的进程并没有完全退出，还有需要更确定的保证订阅发布的进程是否构建了连接</br>
**task** 管道模型</br>
**version** 获取zmq版本号，目前版本号为4.3.3</br>
**XSubXPub** 桥接，将内网和外网相连接，但是没成功，可能环境不对</br>
