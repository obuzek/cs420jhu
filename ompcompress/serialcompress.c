/*******************************************************************************
*
*  Serial main() function to call compress
*
********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

#include "compress.h"

/*------------------------------------------------------------------------------
* Name:  main
* Action:  
*-----------------------------------------------------------------------------*/
int main ( int argc, char** argv )
{
  int rc;             // Return code
  int ind, outd;      // input and output directory file desriptors

  char * res;         // Result code for realpath
  char inpath [PATH_MAX];  // Buffers for path names
  char outpath [PATH_MAX];

  if ( argc != 3 )
  {
    printf ( "Usage: compresstree inputdir outputdir\n" );
    printf ( "\t inputdir must exist\n" );
    printf ( "\t outputdir cannot exist\n" );
    exit (-1);
  }

  /* Get realpaths */
  res = realpath ( argv[1], inpath );
  res = realpath ( argv[2], outpath );

  // Make the output directory
  rc = mkdir ( outpath, S_IRUSR | S_IWUSR | S_IXUSR );
  if ( rc != 0 )
  {
    printf ("Failed to mkdir %s.\n", argv[2], errno, strerror(errno) );
    exit (-1);
  }

  // Check to make sure input directory exists
  if ( 0 != chdir ( inpath ))
  {
    printf ("Failed to change to directory %s. Errno %d %s\n", argv[1], errno, strerror(errno) );
    exit (-1);
  }

  return CompressTree ( inpath, outpath );
}
