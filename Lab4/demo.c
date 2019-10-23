#include <stdio.h>
#include <stdlib.h>
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
	infile_fp = fopen(argv[0], "r+");
	outfile_fp = fopen(argv[1], "w+");
	diagnostics_fp = fopen(argv[2], "w+");
	if(diagnostics_fp == NULL){
		printf("diagnostics file can't open - Exiting\n");
		fclose(diagnostics_fp);
		return 0;
	}else{
		fprintf(diagnostics_fp, "Openning Diagnostic file for output\n");
		if(infile_fp == NULL){
			fprintf(diagnostics_fp, "Diagnostic: fail to open infile for input\n");
			fprintf(diagnostics_fp, "Diagnostic: Closing infile\n");
			fprintf(diagnostics_fp, "Diagnostic: Closing Diagnostic\n");
			fprintf(diagnostics_fp, "Diagnostic: Exiting - could not open all files\n");
			fclose(infile_fp);
			fclose(diagnostics_fp);
			return 0;
		}
		if(outfile_fp == NULL){
			fprintf(diagnostics_fp, "Diagnostic: fail to open outfile for output\n");
			fprintf(diagnostics_fp, "Diagnostic: Closing outfile\n");
			fprintf(diagnostics_fp, "Diagnostic: Closing Diagnostic\n");
			fprintf(diagnostics_fp, "Diagnostic: Exiting - could not open all files\n");
			fclose(outfile_fp);
			fclose(diagnostics_fp);
			return 0;
		}
	}
	fprintf(diagnostics_fp, "Diagnostic: Openning infile for intput\n");
	fprintf(diagnostics_fp, "Diagnostic: Openning outfile for output\n");
	fprintf(diagnostics_fp, "Diagnostic: Openning diagnostics for output\n");

	/*Read and write files*/
	int i1, i2, i3, i4, i5, i6;
	while(fscanf(infile_fp,"%d %d %d %d %d %d",&i1,&i2,&i3,&i4,&i5,&i6)==6){
		fprintf(outfile_fp, "%d %d %d %d %d %d\n", i1,i2,i3,i4,i5,i6);
	}
	fprintf(diagnostics_fp, "Writing finished\n");
	fprintf(diagnostics_fp, "Diagnostic: Closing infile\n");
	fprintf(diagnostics_fp, "Diagnostic: Closing outfile\n");
	fprintf(diagnostics_fp, "Diagnostic: Closing Diagnostic\n");
	fclose(infile_fp);
	fclose(outfile_fp);
	fclose(diagnostics_fp);
}