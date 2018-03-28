#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmdline-lsb.h"
#include "lsbdecode.h"

int main (int argc, char * argv[]) {
  struct gengetopt_args_info args_info;
  if (cmdline_parser(argc, argv, &args_info) != 0) exit(EXIT_FAILURE);
  char * infile = strdup(args_info.infile_arg);
  char * outfile = strdup(args_info.outfile_arg);
  int num_lsb = args_info.num_lsb_arg;
  if (args_info.decode_given && args_info.encode_given) {
    fprintf(stderr, "Conflicting options\n");
    cmdline_parser_free(&args_info);
    exit(EXIT_FAILURE);
  }
  int mode = 0;
  if (args_info.decode_given) mode = 1;
  if (args_info.encode_given) mode = 2;
  char * data = NULL;
  FILE * out = NULL;
  if (mode == 1) {
    data = lsb_decode(infile, LSB_DECODE_FILETYPE_BMP, num_lsb);
    if (data == NULL) {
      fprintf(stderr, "Decoding error: %s\n", lsb_decode_err());
      exit(EXIT_FAILURE);
    }
    if (strcmp(outfile, "-") == 0) {
      printf("%s", data);
    } else {
      out = fopen(outfile, "w");
      fprintf(out, "%s", data);
      fclose(out);
    }
  } else if (mode == 2) {
  } else {
    fprintf(stderr, "No mode specified\n");
  }
  cmdline_parser_free(&args_info);
  free(data);
  exit(EXIT_SUCCESS);
}
