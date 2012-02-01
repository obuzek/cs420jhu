/*******************************************************************************
*
*  Recursively compress a directory tree into another directory tree
*
*******************************************************************************/

#ifndef _h_compress
#define _h_compress

/*------------------------------------------------------------------------------
* Name:  CompressFile
* Action: Compress the actual file and write to outf
*-----------------------------------------------------------------------------*/
int CompressFile ( char* inf, char* outf );

/*------------------------------------------------------------------------------
* Name:  CompressTree
* Action: Compress the subtree in inname into outname
*-----------------------------------------------------------------------------*/
int CompressTree ( char* inname, char* outname );

#endif
