#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

int main(int argc, char *argv[])
{
	/*Check the arguments*/
	if(argc != 3){
		printf("Please enter three arguments\n");
		return 0;
	}

	FILE * infile_fp;
	FILE * outfile_fp;
	FILE * diagnostics_fp;

	char *append = ".txt";
	strcat(argv[0],append);
	strcat(argv[1],append);
	strcat(argv[2],append);
	/*Open files*/
	diagnostics_fp = fopen(argv[2], "w+");
	if(diagnostics_fp == NULL){
		printf("diagnostics file can't open - Exiting\n");
		fclose(diagnostics_fp);
		return 0;
	}else{
		fprintf(diagnostics_fp, "Openning Diagnostic file for output");
		infile_fp = fopen(argv[0], "w+");
		outfile_fp = fopen(argv[1], "w+");
		if(infile_fp == NULL){
			fprintf(diagnostics_fp, "Diagnostic: fail to open infile for input");
			fprintf(diagnostics_fp, "Diagnostic: Closing infile");
			fprintf(diagnostics_fp, "Diagnostic: Closing Diagnostic");
			fprintf(diagnostics_fp, "Diagnostic: Exiting - could not open all files");
			fclose(infile_fp);
			fclose(diagnostics_fp);
			return 0;
		}
		if(outfile_fp == NULL){
			fprintf(diagnostics_fp, "Diagnostic: fail to open outfile for output");
			fprintf(diagnostics_fp, "Diagnostic: Closing outfile");
			fprintf(diagnostics_fp, "Diagnostic: Closing Diagnostic");
			fprintf(diagnostics_fp, "Diagnostic: Exiting - could not open all files");
			fclose(outfile_fp);
			fclose(diagnostics_fp);
			return 0;
		}
	}
	fprintf(diagnostics_fp, "Openning infile for intput");
	fprintf(diagnostics_fp, "Openning outfile for output");

	/*Read and write files*/


}