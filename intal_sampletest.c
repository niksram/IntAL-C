#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

int main(int argc, char const *argv[]) {
	char intal1[100] = "1000110";
	char intal2[100] = "30";
	char *result1;
	int i1;

	result1 = intal_add(intal1, intal2);
	if(!result1) {
		printf("Test Add FAILED.\n");
	} else {
		if(0 == strcmp(result1, "1000140")) {
			printf("Test Add PASSED\n");
		} else {
			printf("Test Add FAILED.\n");
		}
		free(result1);
	}

	i1 = intal_compare(intal1, intal2);
	if(-1 == i1) {
		printf("Test Diff PASSED\n");
	} else {
		printf("Test Diff FAILED.\n");
	}

	result1 = intal_diff(intal1, intal2);
	if(!result1) {
		printf("Test Diff FAILED.\n");
	} else {
		if(0 == strcmp(result1, "543214197641976419764197641976")) {
			printf("Test Diff PASSED\n");
		} else {
			printf("Test Diff FAILED.\n");
		}
		free(result1);
	}

	return 0;
}
