#include "fs_helper.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include "fat32.h"

using namespace std;

char* CWD;
BPB_struct bpb;
fat_item** fat_item_table;
uint32_t cluster;
int filesystem_fd = 0;

inline static void print_error_message(string errmsg){
	fprintf(stderr, "%s:\n%s\n", errmsg.c_str(), strerror(errno));
	exit(0);
}

void seek_data_cluster(uint32_t cluster){
	if (cluster == 0)
		cluster = bpb.extended.RootCluster;

	int rlseek = lseek(filesystem_fd, (bpb.ReservedSectorCount +
		bpb.NumFATs * bpb.extended.FATSize +
		(cluster - 2) * bpb.SectorsPerCluster) * BPS, SEEK_SET);

	if (rlseek == -1)
		print_error_message("Cannot find cluster");
}

int read_clusters(int fat_id, uint32_t cluster_num, void** data, int size){
	uint32_t curr_table_cluster = cluster_num;
	int i = 0;
	while ((i < size || size == -1) && curr_table_cluster < 0xFFFFFF8) {
		(*data) = realloc(*data, (i + 1) * bpb.SectorsPerCluster * BPS);

		seek_data_cluster(curr_table_cluster);
		int rcount = read(filesystem_fd,
			(void*) ((uint64_t)(*data) + i * bpb.SectorsPerCluster * BPS),
			bpb.SectorsPerCluster * BPS);
		if (rcount != bpb.SectorsPerCluster * BPS) {
			fprintf(stderr, "Cannot read cluster %d.\nBytes read: %d, bytes expected: %d\n",
				curr_table_cluster, rcount, bpb.extended.FATSize * BPS);
			exit(0);
		}

		curr_table_cluster = fat_item_table[fat_id][curr_table_cluster].address;
		i++;
	}

	return i;
}

void read_fat_item_tables(){
	int rlseek = lseek(filesystem_fd, bpb.ReservedSectorCount * BPS, SEEK_SET);
	if (rlseek == -1)
		print_error_message("Cannot read FAT tables");

	fat_item_table = (fat_item**)malloc(sizeof(fat_item*) * bpb.NumFATs);
	for (int i = 0; i < bpb.NumFATs; i++) {
		fat_item_table[i] = (fat_item*)malloc(bpb.extended.FATSize * BPS);
		int rcount = read(filesystem_fd, fat_item_table[i], bpb.extended.FATSize * BPS);
		if (rcount != bpb.extended.FATSize * BPS) {
			fprintf(stderr, "Cannot read FAT table %d.\nBytes read: %d, bytes expected: %d\n",
	   			i, rcount, bpb.extended.FATSize * BPS);
			exit(0);
		}
	}
}

int read_dir_tab(int cluster_num, file_item** directory){
	FatFileEntry* data = 0;
	int clusters_read = read_clusters(0, cluster_num, (void**) &data, -1);

	int files_read = 0;
	int parsed_lfn = 0;
	int entries_per_cluster = bpb.SectorsPerCluster * BPS / sizeof(FatFileEntry);
	for (int i = 0; i < clusters_read; i++) {
		for (int j = 0; j < entries_per_cluster; j++) {
			if (data[j + entries_per_cluster * i].lfn.sequence_number == 0xE5
				|| data[j + entries_per_cluster * i].lfn.sequence_number == 0)
				continue;

			if (data[j + entries_per_cluster * i].lfn.attributes != 0x0F) {
				if (!parsed_lfn) {
					*directory = (file_item *)realloc(*directory,(files_read + 1) * sizeof(file_item));

					(*directory)[files_read].long_file_name_list = 0;
				}

				(*directory)[files_read].msdos = data[j + entries_per_cluster * i].msdos;
				(*directory)[files_read].long_file_name_count = parsed_lfn;
				files_read++;
				parsed_lfn = 0;
			} else {
				*directory = (file_item*)realloc(*directory, 
			 		(files_read + 1) * sizeof(file_item));
				if (!parsed_lfn)
					(*directory)[files_read].long_file_name_list = 0;

				(*directory)[files_read].long_file_name_list = (FatFileLFN*)realloc((*directory)[files_read].long_file_name_list,(parsed_lfn + 1) * sizeof(FatFileLFN));

				(*directory)[files_read].long_file_name_list[parsed_lfn] = data[j + entries_per_cluster * i].lfn;
				parsed_lfn++;
			}
		}
	}

	free(data);
	return files_read;
}

int cmp_directory_name(char* directory_name, file_item* fileItem, int is_dir){
	if (!(fileItem->msdos.attributes & 0x10) && is_dir == 1)
		return 0;
	else if (fileItem->msdos.attributes & 0x10 && is_dir == 0)
		return 0;

	if (fileItem->long_file_name_count == 0) {
		if (strlen(directory_name) > 7)
			return 0;
		for (int i = 0; i < 7; i++) {
			if (fileItem->msdos.filename[i] == ' ' && strlen(directory_name) < i)
				continue;
			if (strlen(directory_name) < i || directory_name[i] != fileItem->msdos.filename[i + 1])
				return 0;
		}
		return 1;
    }

	int str_i = 0;
	for (int lfn_i = fileItem->long_file_name_count - 1; lfn_i >= 0; lfn_i--) {
		for (int i = 0; i < 5; i++) {
			uint16_t c = fileItem->long_file_name_list[lfn_i].name1[i];
			if (c == 0xFFFF || c == ' ' || c == 0)
				continue;
			if (directory_name[str_i] != c)
				return 0;
			if (str_i++ >= strlen(directory_name))
				return 0;
		}

		for (int i = 0; i < 6; i++) {
			uint16_t c = fileItem->long_file_name_list[lfn_i].name2[i];
			if (c == 0xFFFF || c == ' ' || c == 0)
				continue;
			if (directory_name[str_i] != c)
				return 0;
			if (str_i++ >= strlen(directory_name))
				return 0;
		}
		
		for (int i = 0; i < 2; i++) {
			uint16_t c = fileItem->long_file_name_list[lfn_i].name3[i];
			if (c == 0xFFFF || c == ' ' || c == 0)
				continue;
			if (directory_name[str_i] != c)
				return 0;
			if (str_i++ >= strlen(directory_name))
				return 0;
		}
	}

	return 1;
}

int cmp_parent(char* directory_name, file_item* fileItem){
	if (fileItem->msdos.filename[0] != 0x2E ||
		fileItem->msdos.filename[1] != 0x2E ||
		strcmp(directory_name, ".."))
		return 0;

	return 1;
}

uint32_t find_directory_cluster(char* dir, file_item **fileItem_return_parent, int* dir_i_return, int* dirs_read_return, int is_dir)
{
	if (!strcmp(dir, "/"))
		return bpb.extended.RootCluster;
	if (!strcmp(dir, CWD))
		return cluster;
	else if (dir[strlen(dir) - 1] == '/' && !strncmp(dir, CWD, strlen(dir) - 1))
		return cluster;

	uint32_t directory_cluster;
	char* dir_cp = strdup(dir);
	char* directory_name;
	if (dir_cp[0] == '/') {
		directory_cluster = bpb.extended.RootCluster;
		directory_name = strsep(&dir_cp, "/");
	} else {
		directory_cluster = cluster;
	}

	while ((directory_name = strsep(&dir_cp, "/")) != NULL) {
		if (!strlen(directory_name))
			break;
		file_item* fileItem = 0;
		int dirs_read = read_dir_tab(directory_cluster, &fileItem);
		int dir_found = 0;
		int dir_i = 0;
		int is_curr_dir = is_dir;
		if (!(strrchr(dir, '/') && !strcmp(directory_name, strrchr(dir, '/') + 1)))
			is_curr_dir = is_dir;

		for (; dir_i < dirs_read; dir_i++) {
			if (cmp_directory_name(directory_name, &fileItem[dir_i], is_curr_dir)
				|| cmp_parent(directory_name, &fileItem[dir_i])) {
				dir_found = 1;
				break;
			}
		}

		if (!dir_found) {
			free(fileItem->long_file_name_list);
			free(fileItem);
			//free(dir_cp);
			if (fileItem_return_parent)
				*fileItem_return_parent = 0;
			return 0;
		}

		directory_cluster = (fileItem[dir_i].msdos.eaIndex << 16) | fileItem[dir_i].msdos.firstCluster;
		if (directory_cluster == 0)
			directory_cluster = bpb.extended.RootCluster;

		if (!fileItem_return_parent) {
			free(fileItem->long_file_name_list);
			free(fileItem);
		} else {
			*fileItem_return_parent = fileItem;
			*dir_i_return = dir_i;
			*dirs_read_return = dirs_read;
		}
	}

	free(dir_cp);
	return directory_cluster;
}

void flush_fat_item_table(int alloc_cl){
	int curr_pos = lseek(filesystem_fd, 0, SEEK_CUR);
	int rlseek = lseek(filesystem_fd, bpb.ReservedSectorCount * BPS, SEEK_SET);
	if (rlseek == -1)
		print_error_message("Cannot find FAT tables");

	int size = bpb.extended.FATSize * BPS;
	for (int i = 0; i < bpb.NumFATs; i++) {
		int wcount = write(filesystem_fd, fat_item_table[i], size);
		if (wcount != size) {
			fprintf(stderr, "Cannot write FT entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, size);
		}
	}

	if (alloc_cl > 0) {
		rlseek = lseek(filesystem_fd, bpb.extended.FSInfo * BPS + 0x1E8, SEEK_SET);
		int free_cl;
		int rrcount = read(filesystem_fd, &free_cl, 4);
		if (rrcount != 4)
			print_error_message("Cannot read free cluster count");
		free_cl -= alloc_cl;
		rlseek = lseek(filesystem_fd, bpb.extended.FSInfo * BPS + 0x1E8, SEEK_SET);
		int wcount = write(filesystem_fd, &free_cl, 4);
		if (rrcount != 4)
			print_error_message("Cannot write free cluster count");
	}

	rlseek = lseek(filesystem_fd, curr_pos, SEEK_SET);
	if (rlseek == -1)
		print_error_message("Cannot return to original position");
}

uint32_t allocate_clusters(int num_entries, int flush){
	uint32_t first_cluster = 0;
	int cluster = 0, old_cluster = 0, i = 0;
	int num_clusters = bpb.extended.FATSize * BPS / sizeof(fat_item);
	for (; cluster < num_clusters && i < num_entries; cluster++) {
		if (fat_item_table[0][cluster].address == 0) {
			if (!i) {
				first_cluster = cluster;
				old_cluster = cluster;
				for (int j = 0; j < bpb.NumFATs; j++)
					fat_item_table[j][cluster].address = 0xFFFFFF8;
				i++;
				continue;
			}

			for (int j = 0; j < bpb.NumFATs; j++) {
				fat_item_table[j][old_cluster].address = cluster;
				fat_item_table[j][cluster].address = 0xFFFFFF8;
			}
			old_cluster = cluster;
			i++;
		}
	}

	if (flush)
		flush_fat_item_table(i);

	return first_cluster;
}

int sizeof_dir_entry(file_item* fileItem, int dir_num){
	int size = 0;
	for (int i = 0; i < dir_num; i++)
		size += fileItem[i].long_file_name_count * sizeof(FatFileLFN) + sizeof(FatFile83);
	return size;
}

uint32_t get_last_cluster(uint32_t cluster){
	uint32_t lc = cluster;
	while (fat_item_table[0][lc].address < 0xFFFFFF8) {
		lc = fat_item_table[0][lc].address;
	}
	return lc;
}

void write_to_directory(uint32_t directory_cluster, file_item* fileItem_dir, int dir_size){
	int entries_written = 0;
	int entries_per_cluster = bpb.BytesPerSector * BPS / sizeof(FatFileEntry);

	seek_data_cluster(directory_cluster);
	for (int i = 0; i < dir_size; i++) {
		for (int j = 0; j < fileItem_dir[i].long_file_name_count; j++) {
			int wcount = write(filesystem_fd, &fileItem_dir[i].long_file_name_list[j], sizeof(FatFileLFN));
			if (wcount != sizeof(FatFileLFN)) {
				fprintf(stderr, "Cannot write LFN entry.\nBytes read: %d, bytes expected: %d\n",
					wcount, (int) sizeof(FatFileLFN));
			}
			entries_written++;
			if (entries_written >= entries_per_cluster) {
				entries_written = 0;
				directory_cluster = fat_item_table[0][directory_cluster].address;
				seek_data_cluster(directory_cluster);
			}
		}

		int wcount = write(filesystem_fd, &fileItem_dir[i].msdos, sizeof(FatFile83));
		if (wcount != sizeof(FatFile83)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFile83));
		}
		entries_written++;
		if (entries_written >= entries_per_cluster) {
			entries_written = 0;
			directory_cluster = fat_item_table[0][directory_cluster].address;
			seek_data_cluster(directory_cluster);
		}
	}
}

void write_to_file_item(char* dir, file_item* fileItem, int create_dir){
	uint32_t directory_cluster = find_directory_cluster(dir, 0, 0, 0, 1);
	if (!directory_cluster)
		return;

	uint32_t first_directory_cluster = directory_cluster;
	file_item* fileItem_dir = 0;
	int dirs_read = read_dir_tab(directory_cluster, &fileItem_dir);

	int initial_size = sizeof_dir_entry(fileItem_dir, dirs_read);
	int new_size = initial_size + sizeof_dir_entry(fileItem, 1);
	int clusters_needed = new_size / (bpb.SectorsPerCluster * BPS) -
		initial_size / (bpb.SectorsPerCluster * BPS);
	if (clusters_needed) {
		uint32_t alloc_cluster = allocate_clusters(clusters_needed, 0);
		uint32_t lc = get_last_cluster(directory_cluster);
		for (int i = 0; i < bpb.NumFATs; i++)
			fat_item_table[i][lc].address = alloc_cluster;
		flush_fat_item_table(alloc_cluster);
	}

	int entries_written = 0;
	int entries_per_cluster = bpb.SectorsPerCluster * BPS / sizeof(FatFileEntry);
	seek_data_cluster(directory_cluster);
	for (int i = 0; i < dirs_read; i++) {
		for (int j = 0; j < fileItem_dir[i].long_file_name_count; j++) {
			int wcount = write(filesystem_fd, &fileItem_dir[i].long_file_name_list[j], sizeof(FatFileLFN));
			if (wcount != sizeof(FatFileLFN)) {
				fprintf(stderr, "Cannot write LFN entry.\nBytes read: %d, bytes expected: %d\n",
					wcount, (int) sizeof(FatFileLFN));
			}
			entries_written++;
			if (entries_written >= entries_per_cluster) {
				entries_written = 0;
				directory_cluster = fat_item_table[0][directory_cluster].address;
				(directory_cluster);
			}
		}

		int wcount = write(filesystem_fd, &fileItem_dir[i].msdos, sizeof(FatFile83));
		if (wcount != sizeof(FatFile83)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFile83));
		}
		entries_written++;
		if (entries_written >= entries_per_cluster) {
			entries_written = 0;
			directory_cluster = fat_item_table[0][directory_cluster].address;
			seek_data_cluster(directory_cluster);
		}
	}
	for (int j = 0; j < fileItem->long_file_name_count; j++) {
		int wcount = write(filesystem_fd, &fileItem->long_file_name_list[j], sizeof(FatFileLFN));
		if (wcount != sizeof(FatFileLFN)) {
			fprintf(stderr, "Cannot write LFN entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFileLFN));
		}
		entries_written++;
		if (entries_written >= entries_per_cluster) {
			entries_written = 0;
			directory_cluster = fat_item_table[0][directory_cluster].address;
			seek_data_cluster(directory_cluster);
		}
	}

	if (create_dir == 1) {
		uint32_t new_directory_cluster = allocate_clusters(1, 1);
		fileItem->msdos.eaIndex = new_directory_cluster >> 16;
		fileItem->msdos.firstCluster = new_directory_cluster & 0xFFFF;
		int wcount = write(filesystem_fd, &fileItem->msdos, sizeof(FatFile83));
		if (wcount != sizeof(FatFile83)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFile83));
		}

		FatFile83 fileItem_dot = fileItem->msdos;
		for (int i = 11; i; i--)
			fileItem_dot.filename[i] = ' ';
		fileItem_dot.filename[0] = 0x2E;
		fileItem_dot.attributes = 0x30;
		seek_data_cluster(new_directory_cluster);
		wcount = write(filesystem_fd, &fileItem_dot, sizeof(FatFile83));
		if (wcount != sizeof(FatFile83)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFile83));
		}

		fileItem_dot.filename[1] = 0x2E;
		if (first_directory_cluster == bpb.extended.RootCluster)
			first_directory_cluster = 0;
		fileItem_dot.eaIndex = first_directory_cluster >> 16;
		fileItem_dot.firstCluster = first_directory_cluster & 0xFFFF;
		wcount = write(filesystem_fd, &fileItem_dot, sizeof(FatFile83));
		if (wcount != sizeof(FatFile83)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFile83));
		}
	} else if (create_dir == -1) {
		int wcount = write(filesystem_fd, &fileItem->msdos, sizeof(FatFile83));
		if (wcount != sizeof(FatFile83)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFile83));
		}

		directory_cluster = (fileItem->msdos.eaIndex << 16) | fileItem->msdos.firstCluster;
		seek_data_cluster(directory_cluster);
		
		int rlseek = lseek(filesystem_fd, sizeof(FatFile83) + offsetof(FatFile83, eaIndex), SEEK_CUR);
		if (rlseek == -1)
			print_error_message("Cannot seek to msdos entry.");
		uint16_t eaIndex = first_directory_cluster >> 16;
		wcount = write(filesystem_fd, &eaIndex, sizeof(uint16_t));
		if (wcount != sizeof(uint16_t)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(uint16_t));
		}
		
		rlseek = lseek(filesystem_fd, 2 * sizeof(uint16_t), SEEK_CUR);
		if (rlseek == -1)
			print_error_message("Cannot seek to msdos entry.");
		uint16_t firstCluster = first_directory_cluster & 0xFFFF;
		wcount = write(filesystem_fd, &firstCluster, sizeof(uint16_t));
		if (wcount != sizeof(uint16_t)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(uint16_t));
		}
	} else {
		int wcount = write(filesystem_fd, &fileItem->msdos, sizeof(FatFile83));
		if (wcount != sizeof(FatFile83)) {
			fprintf(stderr, "Cannot write msdos entry.\nBytes read: %d, bytes expected: %d\n",
				wcount, (int) sizeof(FatFile83));
		}
	}
}

void file_system_open(char* fsname){
	filesystem_fd = open(fsname, O_RDWR);
	if (filesystem_fd == -1)
		print_error_message("Cannot open filesystem");

	int rcount = read(filesystem_fd, &bpb, sizeof(BPB_struct));
	if (rcount != sizeof(bpb)) {
		fprintf(stderr, "Cannot read BPB.\nBytes read: %d, bytes expected: %d\n",rcount, (int) sizeof(BPB_struct));
		exit(0);
	}

	CWD = strdup("/");
	cluster = bpb.extended.RootCluster;

	read_fat_item_tables();
}
