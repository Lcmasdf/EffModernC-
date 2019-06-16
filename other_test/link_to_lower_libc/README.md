# How to link to a old GLIC version function
------------
## Version 'GLIBC_2.14' not found
这个问题常见于linux上，编译好的工程放到另一个环境上跑不起来(即使统一了gcc的版本)。根本原因在于libc版本的不一致。

glibc从2.1开始引入了Symbol Versioning的机制，每个符号会对应一个版本号。例如：memcpy对应 memcpy@@GLIBC_2.14和GLIBC_2.2.5两个版本。
可以通过 ```nm /lib/x86_64-linux-gnu/libc.so.6``` 来查看。

两个版本的memcpy其中一个会被指定为默认的版本，当新的环境没有此版本的方法时，就会出现标题中所述的那种情况。

## Is there an option that switch the link version?
理所当然，我们会希望有一个编译/链接的选项，支持将所有的方法链接到gcc-xxx版本所对应的func-version上。