
  /*\
   * $Xorg: utils.c,v 1.4 2000/08/17 19:54:33 cpqbld Exp $
   *
   *		              COPYRIGHT 1990
   *		        DIGITAL EQUIPMENT CORPORATION
   *		           MAYNARD, MASSACHUSETTS
   *			    ALL RIGHTS RESERVED.
   *
   * THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT NOTICE AND
   * SHOULD NOT BE CONSTRUED AS A COMMITMENT BY DIGITAL EQUIPMENT CORPORATION.
   * DIGITAL MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THIS SOFTWARE 
   * FOR ANY PURPOSE.  IT IS SUPPLIED "AS IS" WITHOUT EXPRESS OR IMPLIED 
   * WARRANTY.
   *
   * IF THE SOFTWARE IS MODIFIED IN A MANNER CREATING DERIVATIVE COPYRIGHT
   * RIGHTS, APPROPRIATE LEGENDS MAY BE PLACED ON THE DERIVATIVE WORK IN
   * ADDITION TO THAT SET FORTH ABOVE.
   *
   * Permission to use, copy, modify, and distribute this software and its
   * documentation for any purpose and without fee is hereby granted, provided
   * that the above copyright notice appear in all copies and that both that
   * copyright notice and this permission notice appear in supporting
   * documentation, and that the name of Digital Equipment Corporation not be
   * used in advertising or publicity pertaining to distribution of the 
   * software without specific, written prior permission.
  \*/

#include 	"utils.h"
#include	<ctype.h>
#ifndef X_NOT_STDC_ENV
#include <stdlib.h>
#else
char *malloc();
#endif

/***====================================================================***/

Opaque
#if NeedFunctionPrototypes
uAlloc(unsigned size)
#else
uAlloc(size)
    unsigned	size;
#endif
{
    return((Opaque)malloc(size));
}

/***====================================================================***/

Opaque
#if NeedFunctionPrototypes
uCalloc(unsigned n,unsigned size)
#else
uCalloc(n,size)
    unsigned	n;
    unsigned	size;
#endif
{
    return((Opaque)calloc(n,size));
}

/***====================================================================***/

Opaque
#if NeedFunctionPrototypes
uRealloc(Opaque old,unsigned newSize)
#else
uRealloc(old,newSize)
    Opaque	old;
    unsigned	newSize;
#endif
{
    if (old==NULL)
	 return((Opaque)malloc(newSize));
    else return((Opaque)realloc((char *)old,newSize));
}

/***====================================================================***/

Opaque
#if NeedFunctionPrototypes
uRecalloc(Opaque old,unsigned nOld,unsigned nNew,unsigned itemSize)
#else
uRecalloc(old,nOld,nNew,itemSize)
    Opaque	old;
    unsigned	nOld;
    unsigned	nNew;
    unsigned	itemSize;
#endif
{
char *rtrn;

    if (old==NULL)
	 rtrn= (char *)calloc(nNew,itemSize);
    else {
	rtrn= (char *)realloc((char *)old,nNew*itemSize);
   	if ((rtrn)&&(nNew>nOld)) {
	    bzero(&rtrn[nOld*itemSize],(nNew-nOld)*itemSize);
	}
    }
    return (Opaque)rtrn;
}

/***====================================================================***/

void
#if NeedFunctionPrototypes
uFree(Opaque ptr)
#else
uFree(ptr)
    Opaque ptr;
#endif
{
    if (ptr!=(Opaque)NULL)
	free((char *)ptr);
    return;
}

/***====================================================================***/
/***                  FUNCTION ENTRY TRACKING                           ***/
/***====================================================================***/

static	FILE	*entryFile=	stderr;
	int	 uEntryLevel;

Boolean
#if NeedFunctionPrototypes
uSetEntryFile(char *name)
#else
uSetEntryFile(name)
    char *name;
#endif
{
    if ((entryFile!=NULL)&&(entryFile!=stderr)) {
	fprintf(entryFile,"switching to %s\n",name?name:"stderr");
	fclose(entryFile);
    }
    if (name!=NullString)	entryFile=	fopen(name,"w");
    else			entryFile=	stderr;
    if (entryFile==NULL) {
	entryFile=	stderr;
	return(False);
    }
    return(True);
}

void
#if NeedFunctionPrototypes
uEntry(int l,char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,
								Opaque a6)
#else
uEntry(l,s,a1,a2,a3,a4,a5,a6)
int	l;
char	*s;
Opaque	a1,a2,a3,a4,a5,a6;
#endif
{
int	i;

    for (i=0;i<uEntryLevel;i++) {
	putc(' ',entryFile);
    }
    fprintf(entryFile,s,a1,a2,a3,a4,a5,a6);
    uEntryLevel+= l;
    return;
}

void
#if NeedFunctionPrototypes
uExit(int l,char *rtVal)
#else
uExit(l,rtVal)
    int		l;
    char *	rtVal;
#endif
{
int	i;

    uEntryLevel-= l;
    if (uEntryLevel<0)	uEntryLevel=	0;
    for (i=0;i<uEntryLevel;i++) {
	putc(' ',entryFile);
    }
    fprintf(entryFile,"---> 0x%x\n",rtVal);
    return;
}

/***====================================================================***/
/***			PRINT FUNCTIONS					***/
/***====================================================================***/

	FILE	*uDebugFile=		stderr;
	int	 uDebugIndentLevel=	0;
	int	 uDebugIndentSize=	4;

Boolean
#if NeedFunctionPrototypes
uSetDebugFile(char *name)
#else
uSetDebugFile(name)
    char *name;
#endif
{
    if ((uDebugFile!=NULL)&&(uDebugFile!=stderr)) {
	fprintf(uDebugFile,"switching to %s\n",name?name:"stderr");
	fclose(uDebugFile);
    }
    if (name!=NullString)	uDebugFile=	fopen(name,"w");
    else			uDebugFile=	stderr;
    if (uDebugFile==NULL) {
	uDebugFile=	stderr;
	return(False);
    }
    return(True);
}

void
#if NeedFunctionPrototypes
uDebug(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,Opaque a6)
#else
uDebug(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
int	i;

    for (i=(uDebugIndentLevel*uDebugIndentSize);i>0;i--) {
	putc(' ',uDebugFile);
    }
    fprintf(uDebugFile,s,a1,a2,a3,a4,a5,a6);
    fflush(uDebugFile);
    return;
}

void
#if NeedFunctionPrototypes
uDebugNOI(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,Opaque a6)
#else
uDebugNOI(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
    fprintf(uDebugFile,s,a1,a2,a3,a4,a5,a6);
    fflush(uDebugFile);
    return;
}

/***====================================================================***/

static	FILE	*errorFile=	stderr;
static	int	 outCount=	0;
static	char	*preMsg=	NULL;
static	char	*postMsg=	NULL;
static	char	*prefix=	NULL;

Boolean
#if NeedFunctionPrototypes
uSetErrorFile(char *name)
#else
uSetErrorFile(name)
    char *name;
#endif
{
    if ((errorFile!=NULL)&&(errorFile!=stderr)) {
	fprintf(errorFile,"switching to %s\n",name?name:"stderr");
	fclose(errorFile);
    }
    if (name!=NullString)	errorFile=	fopen(name,"w");
    else			errorFile=	stderr;
    if (errorFile==NULL) {
	errorFile=	stderr;
	return(False);
    }
    return(True);
}

void
#if NeedFunctionPrototypes
uInformation(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,
								Opaque a6)
#else
uInformation(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
    fprintf(errorFile,s,a1,a2,a3,a4,a5,a6);
    fflush(errorFile);
    return;
}

/***====================================================================***/

void
#if NeedFunctionPrototypes
uAction(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,Opaque a6)
#else
uAction(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
    if (prefix!=NULL)
	fprintf(errorFile,"%s",prefix);
    fprintf(errorFile,"                  ");
    fprintf(errorFile,s,a1,a2,a3,a4,a5,a6);
    fflush(errorFile);
    return;
}

/***====================================================================***/

void
#if NeedFunctionPrototypes
uWarning(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,Opaque a6)
#else
uWarning(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
    if ((outCount==0)&&(preMsg!=NULL))
	fprintf(errorFile,"%s\n",preMsg);
    if (prefix!=NULL)
	fprintf(errorFile,"%s",prefix);
    fprintf(errorFile,"Warning:          ");
    fprintf(errorFile,s,a1,a2,a3,a4,a5,a6);
    fflush(errorFile);
    outCount++;
    return;
}

/***====================================================================***/

void
#if NeedFunctionPrototypes
uError(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,Opaque a6)
#else
uError(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
    if ((outCount==0)&&(preMsg!=NULL))
	fprintf(errorFile,"%s\n",preMsg);
    if (prefix!=NULL)
	fprintf(errorFile,"%s",prefix);
    fprintf(errorFile,"Error:            ");
    fprintf(errorFile,s,a1,a2,a3,a4,a5,a6);
    fflush(errorFile);
    outCount++;
    return;
}

/***====================================================================***/

void
#if NeedFunctionPrototypes
uFatalError(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,Opaque a6)
#else
uFatalError(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
    if ((outCount==0)&&(preMsg!=NULL))
	fprintf(errorFile,"%s\n",preMsg);
    if (prefix!=NULL)
	fprintf(errorFile,"%s",prefix);
    fprintf(errorFile,"Fatal Error:      ");
    fprintf(errorFile,s,a1,a2,a3,a4,a5,a6);
    fprintf(errorFile,"                  Exiting\n");
    fflush(errorFile);
    outCount++;
    exit(1);
    /* NOTREACHED */
}

/***====================================================================***/

void
#if NeedFunctionPrototypes
uInternalError(char *s,Opaque a1,Opaque a2,Opaque a3,Opaque a4,Opaque a5,
								Opaque a6)
#else
uInternalError(s,a1,a2,a3,a4,a5,a6)
char *s;
Opaque a1,a2,a3,a4,a5,a6;
#endif
{
    if ((outCount==0)&&(preMsg!=NULL))
	fprintf(errorFile,"%s\n",preMsg);
    if (prefix!=NULL)
	fprintf(errorFile,"%s",prefix);
    fprintf(errorFile,"Internal error:   ");
    fprintf(errorFile,s,a1,a2,a3,a4,a5,a6);
    fflush(errorFile);
    outCount++;
    return;
}

void
#if NeedFunctionPrototypes
uSetPreErrorMessage(char *msg)
#else
uSetPreErrorMessage(msg)
    char *msg;
#endif
{
    outCount= 0;
    preMsg= msg;
    return;
}

void
#if NeedFunctionPrototypes
uSetPostErrorMessage(char *msg)
#else
uSetPostErrorMessage(msg)
    char *msg;
#endif
{
    postMsg= msg;
    return;
}

void
#if NeedFunctionPrototypes
uSetErrorPrefix(char *pre)
#else
uSetErrorPrefix(pre)
    char *pre;
#endif
{
    prefix= pre;
    return;
}

void
#if NeedFunctionPrototypes
uFinishUp(void)
#else
uFinishUp()
#endif
{
    if ((outCount>0)&&(postMsg!=NULL))
	fprintf(errorFile,"%s\n",postMsg);
    return;
}

/***====================================================================***/

#ifndef HAVE_STRDUP
char *
#if NeedFunctionPrototypes
uStringDup(char *str)
#else
uStringDup(str)
    char *str;
#endif
{
char *rtrn;

    if (str==NULL)
	return NULL;
    rtrn= (char *)uAlloc(strlen(str)+1);
    strcpy(rtrn,str);
    return rtrn;
}
#endif

#ifndef HAVE_STRCASECMP
int
#if NeedFunctionPrototypes
uStrCaseCmp(char *str1,char *str2)
#else
uStrCaseCmp(str1, str2)
    char *str1, *str2;
#endif
{
    char buf1[512],buf2[512];
    char c, *s;
    register int n;

    for (n=0, s = buf1; (c = *str1++); n++) {
	if (isupper(c))
	    c = tolower(c);
	if (n>510)
	    break;
	*s++ = c;
    }
    *s = '\0';
    for (n=0, s = buf2; (c = *str2++); n++) {
	if (isupper(c))
	    c = tolower(c);
	if (n>510)
	    break;
	*s++ = c;
    }
    *s = '\0';
    return (strcmp(buf1, buf2));
}

int
#if NeedFunctionPrototypes
uStrCasePrefix(char *prefix,char *str)
#else
uStrCasePrefix(prefix, str)
    char *prefix, *str;
#endif
{
    char c1;
    char c2;
    while (((c1=*prefix)!='\0')&&((c2=*str)!='\0')) {
	if (isupper(c1))	c1= tolower(c1);
	if (isupper(c2))	c2= tolower(c2);
	if (c1!=c2)
	    return 0;
	prefix++; str++;
    }
    if (c1!='\0')
	return 0;
    return 1;
}

#endif
