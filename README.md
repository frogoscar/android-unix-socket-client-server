# android-unix-socket-client-server
In Android, using NDK, create Client-Server for testing Unix-Socket (there are two clients, the first has same UID with the server), test shows that only the client whose UID is the same with the server can communicate with the server.
在Android中,使用NDK(JNI), 创建Client-Server模式, 以测试Unix Socket, 有一个Server, 两个Client, 第一个Client和Server的UID是一样的. 测试表明, 只有UID和Server一样的Client才能和Server通信.
