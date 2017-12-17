/*
 * Filename:    syscalls.h
 * Author:      Thomas van der Burgt <thomas@thvdburgt.nl>
 * Date:        03-MAY-2010
 *
 * The C Programming Language, second edition,
 * by Brian Kernighan and Dennis Ritchie
 *
 * Exercise 8-2, page 178
 *
 * Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed.
 */

#include <fcntl.h>
#include <stdlib.h>

#define NULL      0
#define EOF       (-1)
#define BUFSIZ    1024
#define OPEN_MAX  20 /* max #files open at once */

typedef struct _iobuf {
    int cnt;          /* characters left */
    char *ptr;        /* next character position */
    char *base;       /* location of buffer */
    struct {          /* mode of file access */
        unsigned int read  : 1;
        unsigned int write : 1;
        unsigned int unbuf : 1;
        unsigned int eof   : 1;
        unsigned int err   : 1;
    } flags;
    int fd;           /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];
#define stdin   (&iob[0])
#define stdout  (&iob[1])
#define stderr  (&iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)   (--(p)->cnt >= 0 \
               ? (unsigned char) *(p)->ptr++ : _fillbuff(p))
#define putc(p)   (--(p)->cnt >= 0 \
               ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar(x)  putc(x), stdout)

FILE _iob[OPEN_MAX] = {    /* stdin, stdout, stderr: */
    { 0, (char *) 0, (char *) 0, {1,0,0,0,0}, 0 },
    { 0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1 },
    { 0, (char *) 0, (char *) 0, {0,1,1,0,0}, 2 }
};



#define PERMS 0666   /* RW for owner, group, others*/

/* fopen:  open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flags.read == 0 || fp->flags.write == 0)
            break;        /* found free slot */
    if (fp >= _iob + OPEN_MAX)    /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)         /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->flags.read = 1;
    else
        fp->flags.write = 1;
    return fp;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (fp->flags.read == 1 && fp->flags.eof == 0 && fp->flags.err == 0)
        return EOF;
    bufsize = (fp->flags.unbuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL)     /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;       /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flags.eof = 1;
        else
            fp->flags.err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int main(void)
{
    FILE *fp;
    char mode;
    mode = 'w';
    fp = fopen("foo", &mode);
    return 0;
}
