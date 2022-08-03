#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stddef.h>
#include <iostream>
#include "fat32.h"
#include "fs_helper.h"
#include <unistd.h>
#include <errno.h>

using namespace std;

string months_of_year[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void print_name(void* str, int start, int len){
	for (int i = start; i < len; i++) {
		uint16_t c = ((uint16_t*) str)[i];
		if (c == 0xFFFF)
			continue;
		printf("%c", c);
	}
}

void ls_command(char* dir, int pp){
	uint32_t directory_cluster = find_directory_cluster(dir, 0, 0, 0, 1);

	file_item* fileItem = 0;
	int dirs_read = read_dir_tab(directory_cluster, &fileItem);
	if (!pp) {
		for (int i = 0; i < dirs_read; i++) {
			if (fileItem[i].long_file_name_count == 0) {
				if (fileItem[i].msdos.filename[0] == 0x2E) {
					printf(".");
					if (fileItem[i].msdos.filename[1] != ' ')
						printf(".");
				} else {
					print_name(fileItem[i].msdos.filename, 1, 8);
					print_name(fileItem[i].msdos.extension, 0, 3);
				}
			} else {
				for (int j = fileItem[i].long_file_name_count - 1; j >= 0; j--) {
					print_name(fileItem[i].long_file_name_list[j].name1, 0, 5);
					print_name(fileItem[i].long_file_name_list[j].name2, 0, 6);
					print_name(fileItem[i].long_file_name_list[j].name3, 0, 2);
				}
			}
			printf(" ");
		}
		printf("\n");
	} else {
		for (int i = 0; i < dirs_read; i++) {
			if (fileItem[i].msdos.attributes & 0x10) {
				printf("drwx------ 1 root root 0 0 %s %d %.2d:%.2d ",
					months_of_year[((fileItem[i].msdos.modifiedDate >> 5) & 0x0F) - 1].c_str(),
					fileItem[i].msdos.modifiedDate & 0x1F, fileItem[i].msdos.modifiedTime >> 11,
                    (fileItem[i].msdos.modifiedTime >> 5) & 0x3F);
			} else {
				printf("-rwx------ 1 root root %d %s %d %.2d:%.2d ",
					fileItem[i].msdos.fileSize, months_of_year[((fileItem[i].msdos.modifiedDate >> 5) & 0x0F) - 1].c_str(),
					fileItem[i].msdos.modifiedDate & 0x1F, fileItem[i].msdos.modifiedTime >> 11,
                    (fileItem[i].msdos.modifiedDate >> 5) & 0x3F);
			}

			if (fileItem[i].long_file_name_count == 0) {
				if (fileItem[i].msdos.filename[0] == 0x2E) {
					printf(".");
					if (fileItem[i].msdos.filename[1] != ' ')
						printf(".");
				} else {
					print_name(fileItem[i].msdos.filename, 1, 8);
					print_name(fileItem[i].msdos.extension, 0, 3);
				}
			} else {
				for (int j = fileItem[i].long_file_name_count - 1; j >= 0; j--) {
					print_name(fileItem[i].long_file_name_list[j].name1, 0, 5);
					print_name(fileItem[i].long_file_name_list[j].name2, 0, 6);
					print_name(fileItem[i].long_file_name_list[j].name3, 0, 2);
				}
			}
			printf("\n");
		}	
	}
}

void merge(char* new_cwd){
	char* nwd = strdup(new_cwd);
	char* curr = strsep(&nwd, "/");

	while (curr != NULL) {
		if (strlen(curr) == 0) {
			curr = strsep(&nwd, "/");
			continue;
		}
		if (!strcmp(curr, "..")) {
			char* sign = strrchr(CWD, '/');
			*sign = '\0';
		} else {
			if (CWD[strlen(CWD) - 1] != '/')
				strcat(CWD, "/");
			strcat(CWD, curr);
		}

		curr = strsep(&nwd, "/");
	}

	if (strlen(CWD) == 0)
		strcat(CWD, "/");

	free(nwd);
}

void cd_command(char* new_cwd){
	int new_cwd_cluster = find_directory_cluster(new_cwd, 0, 0, 0, 1);
	if (new_cwd_cluster) {
		if (new_cwd[0] == '/') {
			free(CWD);
			CWD = strdup(new_cwd);
		} else {
			merge(new_cwd);
		}
		cluster = new_cwd_cluster;
	}
}

void cat_command(char* file){
	uint32_t file_cluster = find_directory_cluster(file, 0, 0, 0, 0);
	if (!file_cluster || file_cluster == bpb.extended.RootCluster)
		return;

	char* buffer = 0;
	int clusters_read = read_clusters(0, file_cluster, (void**) &buffer, -1);
	int chars_per_cluster = bpb.SectorsPerCluster * BPS;
	int i = 0;
	for (; i < clusters_read * chars_per_cluster; i++) {
		if (buffer[i] == 0)
			break;
		printf("%c", buffer[i]);
	}
	if (buffer[i - 1] != '\n')
		printf("\n");
}

uint8_t checksum_filename(uint8_t* filename){
	uint8_t sum = 0;
	for (int i = 11; i; i--)
		sum = ((sum & 1) << 7) + (sum >> 1) + *filename++;
	return sum;
}

void create_file_item(char* filename, file_item* fileItem, int is_dir){
	for (int i = 0; i < 8; i++) {
		if (i < strlen(filename))
			fileItem->msdos.filename[i] = filename[i];
		else
			fileItem->msdos.filename[i] = ' ';
	}
	if (filename[0] == 0xE5)
		fileItem->msdos.filename[0] = 0x05;

	char* extension = 0;
	if (strrchr(filename, '.') != NULL) {
		extension = strrchr(filename, '.');
		*extension = 0, extension++;
	}

	for (int i = 0; i < 3; i++) {
		if (extension && i < strlen(extension))
			fileItem->msdos.extension[i] = extension[i];
		else
			fileItem->msdos.extension[i] = ' ';
	}
	fileItem->msdos.attributes = 0x20 | (is_dir << 4);
	fileItem->msdos.reserved = 0;

	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime); // or gmtime()
	fileItem->msdos.creationDate = fileItem->msdos.modifiedDate =
		((timeinfo->tm_year - 80) << 9) | ((timeinfo->tm_mon << 5) + 1) | (timeinfo->tm_mday);
	fileItem->msdos.creationTime = fileItem->msdos.modifiedTime =
		((timeinfo->tm_hour << 11) | (timeinfo->tm_min << 5) | (timeinfo->tm_sec >> 1));

	fileItem->msdos.eaIndex = 0;
	fileItem->msdos.firstCluster = 0;
	fileItem->msdos.fileSize = 0;

	uint8_t checksum = checksum_filename(fileItem->msdos.filename);

	fileItem->long_file_name_count = strlen(filename) / 13 + 1;
	fileItem->long_file_name_list = (FatFileLFN*)malloc(fileItem->long_file_name_count * sizeof(FatFileLFN));
	uint8_t seq_num = 1;
	for (int i = 0; i < fileItem->long_file_name_count; i++) {
		fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].sequence_number = seq_num, seq_num++;
		fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].attributes = 0x0F;
		fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].firstCluster = 0x00;
		fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].checksum = checksum;
		fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].reserved = 0;
		for (int j = 0; j < 5; j++) {
			if (strlen(filename) < j + i * 13)
				fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].name1[j] = 0xFFFF;
			else
				fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].name1[j] = filename[j + i * 13];
		}

		for (int j = 0; j < 6; j++) {
			if (strlen(filename) < j + 5 + i * 13)
				fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].name2[j] = 0xFFFF;
			else
				fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].name2[j] = filename[j + 5 + i * 13];
		}

		for (int j = 0; j < 2; j++) {
			if (strlen(filename) < j + 11 + i * 13)
				fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].name3[j] = 0xFFFF;
			else
				fileItem->long_file_name_list[fileItem->long_file_name_count - i - 1].name3[j] = filename[j + 11 + i * 13];
		}
	}
	fileItem->long_file_name_list[0].sequence_number = (seq_num - 1) | 0x40;
}

void touch_command(char* file){
	char* dir = strdup(file);
	char* filename = strrchr(dir, '/');
	if (filename != NULL) {
		*filename = 0; 
		filename++;
	} else {
		filename = dir;
		dir = strdup(CWD);
	}

	if (filename == NULL || strlen(filename) > 255)
		return;

	file_item fileItem = {0};
	create_file_item(filename, &fileItem, 0);
	write_to_file_item(dir, &fileItem, 0);

	free(fileItem.long_file_name_list);
	free(dir);
}

void mkdir(char* file){
	char* dir = strdup(file);
	char* directory_name = strrchr(dir, '/');
	if (directory_name != NULL) {
		*directory_name = 0; 
		directory_name++;
	} else {
		directory_name = dir;
		dir = strdup(CWD);
	}

	if (directory_name == NULL || strlen(directory_name) > 255)
		return;

	file_item fileItem = {0};
	create_file_item(directory_name, &fileItem, 1);
	write_to_file_item(dir, &fileItem, 1);

	free(fileItem.long_file_name_list);
	free(dir);
}

void mv_command(char* src, char* dst){
	char* dst_dir = strdup(dst);
	char* dst_filename = strrchr(dst_dir, '/');
	if (dst_filename != NULL) {
		*dst_filename = 0;
		dst_filename++;
	} else {
		dst_filename = dst_dir;
		dst_dir = strdup(CWD);
	}

	int rename = 0;
	uint32_t dst_cluster = find_directory_cluster(dst, 0, 0, 0, 1);
	if (!dst_cluster) {
		rename = 1;
		dst_cluster = find_directory_cluster(dst_dir, 0, 0, 0, 1);
		if (!dst_cluster) {
			free(dst_dir);
			return;
		}
	} else {
		dst_dir = dst_filename;
		dst_filename = 0;
	}

	file_item* fileItem_src = 0;
	int dir_i, dirs_read;
	int is_dir = 0;
	uint32_t src_cluster = find_directory_cluster(src, &fileItem_src, &dir_i, &dirs_read, 0);
	if (!src_cluster) {
		src_cluster = find_directory_cluster(src, &fileItem_src, &dir_i, &dirs_read, 1);
		is_dir = 1;
		if (!src_cluster) {
			for (int i = 0; i < dirs_read; i++)
				free(fileItem_src[i].long_file_name_list);
			free(fileItem_src);
			//free(dst_dir);
			return;
		}
	}

	file_item fileItem = {0};
	if (dst_filename && strlen(dst_filename) > 0) {
		create_file_item(dst_filename, &fileItem, 0);
	} else {
		fileItem.long_file_name_count = fileItem_src[dir_i].long_file_name_count;
		fileItem.long_file_name_list = (FatFileLFN*)malloc(fileItem_src[dir_i].long_file_name_count * sizeof(FatFileLFN));
		memcpy(fileItem.long_file_name_list, fileItem_src[dir_i].long_file_name_list, fileItem_src[dir_i].long_file_name_count * sizeof(FatFileLFN));
		memcpy(fileItem.msdos.filename, fileItem_src[dir_i].msdos.filename, 8);
		memcpy(fileItem.msdos.extension, fileItem_src[dir_i].msdos.extension, 3);
	}

	fileItem.msdos.attributes = fileItem_src[dir_i].msdos.attributes;
	fileItem.msdos.creationDate = fileItem_src[dir_i].msdos.creationDate;
	fileItem.msdos.creationTime = fileItem_src[dir_i].msdos.creationTime;
	fileItem.msdos.modifiedDate = fileItem_src[dir_i].msdos.modifiedDate;
	fileItem.msdos.modifiedTime = fileItem_src[dir_i].msdos.modifiedTime;
	fileItem.msdos.eaIndex = fileItem_src[dir_i].msdos.eaIndex;
	fileItem.msdos.firstCluster = fileItem_src[dir_i].msdos.firstCluster;
	fileItem.msdos.fileSize = fileItem_src[dir_i].msdos.fileSize;

	uint32_t src_parent;
	if (fileItem_src[0].long_file_name_count == 0)
		src_parent = (fileItem_src[0].msdos.eaIndex << 16) | fileItem_src[0].msdos.firstCluster;
	else
		src_parent = bpb.extended.RootCluster;

	for (int i = 0; i < fileItem_src[dir_i].long_file_name_count; i++)
		fileItem_src[dir_i].long_file_name_list[i].sequence_number = 0xE5;
	fileItem_src[dir_i].msdos.filename[0] = 0xE5;
	write_to_directory(src_parent, fileItem_src, dirs_read);
	if (!is_dir)
		write_to_file_item(dst_dir, &fileItem, 0);
	else
		write_to_file_item(dst_dir, &fileItem, -1);

	for (int i = 0; i < dirs_read; i++)
		free(fileItem_src[i].long_file_name_list);
	free(fileItem_src);
	free(dst_dir);
}

void cpstr_del(char* str1, char* str2, int len){
	int i;
	for (i = 0; i < len; i++) {
		str1[i] = str2[i];
		str2[i] = 0;
	}
	str1[i] = '\0';
}

int main(int argc, char* argv[]){
	file_system_open(argv[1]);

	int i = 0;
	char curr;
	char strbuffer[256];
	
	char* cmd = 0;
	char** args = 0;
	int cmd_argc = 0;

	printf("%s> ", CWD);

	while ((curr = getchar()) != EOF && i < 256) {
		if (curr == ' ' || (curr == '\n' && i != 0)) {
			if (i == 0)
				continue;

			if (!cmd) {
				cmd = (char *)malloc((i + 1) * sizeof(char));
				cpstr_del(cmd, strbuffer, i);
			} else {
				args = (char **)realloc(args, (cmd_argc + 1) * sizeof(char*));
				args[cmd_argc] = (char *)malloc((i + 1) * sizeof(char));
				cpstr_del(args[cmd_argc], strbuffer, i);
				cmd_argc++;
			}

			i = 0;

			if (curr == ' ')
				continue;
		}

		if (curr == '\n') {
			if (!cmd) {
				printf("%s>", CWD);
				continue;
			}

			if (!strcmp(cmd, "quit")) {
				free(cmd);
				for (int j = 0; j < cmd_argc; j++)
					free(args[j]);
				free(args);

				return 0;
			} else if (!strcmp(cmd, "cd")) {
				if (cmd_argc > 0)
					cd_command(args[0]);
			} else if (!strcmp(cmd, "ls")) {
				if (cmd_argc > 0) {
					if (!strcmp(args[0], "-l")) {
						if (cmd_argc > 1)
							ls_command(args[1], 1);
						else
							ls_command(CWD, 1);
					} else {
						ls_command(args[0], 0);
					}
				} else {
					ls_command(CWD, 0);
				}
			} else if (!strcmp(cmd, "mkdir")) {
				if (cmd_argc > 0)
					mkdir(args[0]);
			} else if (!strcmp(cmd, "touch")) {
				if (cmd_argc > 0)
					touch_command(args[0]);
			} else if (!strcmp(cmd, "mv")) {
				if (cmd_argc > 1)
					mv_command(args[0], args[1]);
			} else if (!strcmp(cmd, "cat")) {
				if (cmd_argc > 0)
					cat_command(args[0]);
			} else {
				fprintf(stderr, "Unknown command\n");
			}

			i = 0;
			
			free(cmd);
			for (int j = 0; j < cmd_argc; j++)
				free(args[j]);
			free(args);

			cmd = 0;
			args = 0;
			cmd_argc = 0;

			printf("%s> ", CWD);
		} else {
			strbuffer[i] = curr;
			i++;
		}
	}
	return 0;
}
