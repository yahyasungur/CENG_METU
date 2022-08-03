#include "hash.h"
#include <stdio.h>
#include <string.h>

void hash_handler(unsigned char *input_char, unsigned char *output_char){
	
	long lower, higher, switchh, switch_lower, switch_higher;
	char chara, *charapointer;
	int i;

	charapointer = input_char;
	for (i = 0; i < 2000; i++) {
		lower = 5381;
		higher = 0;
		while ((chara = *charapointer++)) {
			switch_higher = (higher << 5) + ((lower & 0xF8000000) >> 27);
			switch_lower = lower << 5;
			switchh = lower + switch_lower;
			if ((switchh < lower) || (switchh < switch_lower)){
				switch_higher += 1;
			}
			switch_lower = switchh;
			switch_higher = higher + switch_higher;
			switchh = switch_lower + chara;
			if ((switchh < chara) || (switchh < switch_lower)){
				switch_higher += 1;
			}
			switch_lower = switchh;
			lower = switch_lower;
			higher = switch_higher;
		}
		sprintf(output_char, "%08lx%08lx", higher, lower);
		charapointer = output_char;
	}
}
