#pragma once
#define BIN 1 //BIN：二进制文件读写

#if BIN //文件名选择
#define FILENAME "bus.bin"
#else 
#define FILENAME "bus.txt"
#endif