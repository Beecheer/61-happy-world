#pragma once
#define BIN //BIN：二进制文件读写

#ifdef BIN //文件名选择
#define FILENAME "bus.bin"
#else 
#define FILENAME "bus.txt"
#endif