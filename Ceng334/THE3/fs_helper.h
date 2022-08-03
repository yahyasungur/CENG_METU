#ifndef __HW3_FS__
#define __HW3_FS__

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include "fat32.h"

typedef struct file_item {
	int long_file_name_count;
	FatFileLFN* long_file_name_list;
	FatFile83 msdos;
} file_item;

#pragma pack(push, 1)
typedef struct fat_item {
	unsigned int address: 28;
	unsigned int mask: 4;
} fat_item;
#pragma pack(pop)

void file_system_open(char* fsname);
int read_clusters(int fat_id, uint32_t cluster_num, void** data, int size);
int read_dir_tab(int cluster_num, file_item** directory);
uint32_t find_directory_cluster(char* dir, file_item **fileItem_return_parent,
int* dir_i_return, int* dirs_read_return, int is_dir);
void write_to_file_item(char* dir, file_item* fileItem, int create_dir);
void write_to_directory(uint32_t directory_cluster, file_item* fileItem_dir, int dir_size);

extern int filesystem_fd;
extern BPB_struct bpb;
extern fat_item** fat_table;
extern uint32_t cluster;
extern char* CWD;

#endif
