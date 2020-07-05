# 关于此仓库

这个仓库保存的是我对Linux下C语言Socket编程的学习、研究以及相关的实践的内容。

## 参考内容

- [GNU/Linux C Socket](https://www.gnu.org/software/libc/manual/html_node/Sockets.html)
- [pthread](https://www.man7.org/linux/man-pages/man3/pthread_create.3.html)

## 使用

仓库的根目录下有`basic`、`pthread`等子目录，通过`cd`进入后，用`gcc`编译里面的源代码然后执行。例如：

    $ cd basic
    $ gcc 01_socket_create.c
    $ ./a.out
    文件描述符的值是3

