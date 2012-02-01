/*******************************************************************************
*
*  Recursively compress a directory tree into another directory tree
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
#include <zlib.h>

#define GZ_READLEN 1024 
unsigned char gzbuf[GZ_READLEN];

/*------------------------------------------------------------------------------
* Name:  CompressFile
* Action: Compress the actual file
*-----------------------------------------------------------------------------*/
int CompressFile ( char* inf, char* outf )
{
  int len;
  gzFile gzi, gzo;
  
  printf ( "Compressing %s to %s\n", inf, outf );
  strcat ( outf, ".gz" );
  gzi = gzopen(inf, "rb");
  gzo = gzopen(outf, "wb");
  do {
    len = gzread ( inf, gzbuf, GZ_READLEN );
    gzwrite ( outf, gzbuf, len );
  } while ( len == GZ_READLEN );

  gzclose(gzi);
  gzclose(gzo);
  return 0;
}

/*------------------------------------------------------------------------------
* Name:  CompressTree
* Action: Compress the subtree in inname into outname
*-----------------------------------------------------------------------------*/
int CompressTree ( char* inname, char* outname )
{
  int i;
  int filecount;
  struct dirent** filenames;
  struct stat statinfo;

  /* Get info on inname */
  stat ( inname, &statinfo );

  /* Compress and output if it's a file */
  if ( S_ISREG ( statinfo.st_mode ) )
  {
    CompressFile ( inname, outname );
  }
  /* Enumerate the contents if it is a directory */
  else  if ( S_ISDIR ( statinfo.st_mode ) )
  { 
    printf ( "Directory %s\n", inname );
    mkdir ( outname, S_IRUSR | S_IWUSR | S_IXUSR );

    /* Get a sorted list of all files */
    filecount = scandir ( inname, &filenames, NULL, alphasort );

    /* Look at all files in this directory */
    // RBTODO Hack to get rid of . and .. ??better way?? 
    //   starting at 2 instead of 0, . is 0 .. is 1
    /* Need to ignore . and .. */
    for ( i=2; i<filecount; i++ )
    { 
      /* Call recursively if it's a directory */
      char innext[PATH_MAX];    
      char outnext[PATH_MAX];   
      strcpy ( innext, inname);
      strcat ( innext, "/" );
      strcat ( innext, filenames[i]->d_name );
      strcpy ( outnext, outname);
      strcat ( outnext, "/" );
      strcat ( outnext, filenames[i]->d_name );
      CompressTree ( innext, outnext ); 
    }  
  }
  else
  {
    printf ( "Ignoring other file %s\n", filenames[i]->d_name );
  }

  return 0;
}


