/*---------------------------------------------------------------------

 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.

---------------------------------------------------------------------*/
/*
** MIGration Library Include
*/

/*
** Macros
*/
#define     ABS_SLEEP_YEAR                  0xf000
#define     ABS_SLEEP_MONTH                 0x0f00
#define     ABS_SLEEP_DAY                   0x007e
#define     ABS_SLEEP_AMPM                  0x0001

#define     ABS_SECONDS_IN_12_HOURS         43200

#define     ABS_TO_YEAR( x )    (((unsigned)(x & ABS_SLEEP_YEAR ) >> 12) + 80)
#define     ABS_TO_MONTH( x )   (((unsigned)(x & ABS_SLEEP_MONTH) >>  8) - 1)
#define     ABS_TO_DAY( x )     (((unsigned)(x & ABS_SLEEP_DAY  ) >>  1))
#define     ABS_PM( x )         ((unsigned)(x & ABS_SLEEP_AMPM))

#define     SECONDS_BETWEEN_1970_AND_1980   315532800

#define     MX_POOL_SIZE                    8
#define     MAX_FMATCH_PAT_LEN              132
#define     MAX_TNAME_LENGTH                132

/*
**  Symbolic constants for the lockf() function (C86)
*/
#define F_ULOCK 0  /* unlock a locked region */
#define F_LOCK  1  /* lock a region */
#define F_TLOCK 2  /* test and lock a region */
#define F_TEST  3  /* test a region for a lock */

/*
**  Segment accessability flags (create_seg)
*/
#define SEG_DATA_R      0x0000      /* read only data */
#define SEG_DATA_RW     0x0002      /* read/write data */
#define SEG_CODE_X      0x0008      /* execute only code */
#define SEG_CODE_XR     0x000A      /* execute/read code */

/*
**  Interrupt mask requests
*/
#define INT_DISABLE     0
#define INT_ENABLE      1
#define INT_QUERY       2

/*
** Structures
*/
struct msg_list
{
    void far        *msg;
    unsigned short   zero;
    unsigned short   size;
};

struct __iobuf;         /* for C++ */
struct dir_entry;       /* for C++ */

/*
**  Substitution Macros
*/
#define _ispermitr( p )                 qnx_valptr( 'r', p, sizeof int )
#define _ispermitw( p )                 qnx_valptr( 'w', p, sizeof int )
#define abort( p )                      abort()
#define cd( p )                         chdir( p )
#define cfree( p )                      free( p )
#define char_waiting( fp )              dev_ischars( fileno( fp ) )
#define equal( s1,s2 )                  (!strcmp( s1,s2 ))
#define finit()                         _fpreset()
#define fiseek( fp, off )               fseek( fp, (long) off, 1 )
#define fldcw( p,r,i )                  _control87( (i)<<12|(r)<<10|(p)<<8, 0x1f00 )
#define forward( fp )                   fseek( fp, 0L, 2 )
#define free_segment( p )               qnx_segment_free( p )
#define hold( tid )                     kill( tid, 23 )
#define inportb( p )                    ((int) inp( p ))
#define inportw( p )                    ((int) inpw( p ))
#define io_in( p )                      inp( p )
#define io_out( p, v )                  out( p, (int) (v) )
#define ltell( h )                      ltell( h )
#define move_file( o, n )               rename( o, n )
#define name_attach( nam, nid )         qnx_name_attach( nid, nam )
#define name_locate( nam, nid, size )   qnx_name_locate( nid, nam, size, (void *) 0 )
#define NP_OFF( p )                     FP_OFF( (void far *) p )
#define NP_SEG( p )                     FP_SEG( (void far *) p )
#define outportb( p, v )                (int outp( p, v ))
#define outportw( p, v )                outpw( p, v )
#define P_OFF( p )                      FP_OFF( (void far *) p )
#define P_SEG( p )                      FP_SEG( (void far *) p )
#define full_path( b, p )               qnx_fullpath( b, p )
#define relay( stid, dtid )             Relay( stid, dtid )
#define reply( tid, msg, size )         Reply( tid, msg, size )
#define shell( c )                      system( c )
#define shellb( b, c )                  system( c )
#define term_colour( p )                term_color( (unsigned) (p) << 8 )
#define term_load( s )                  (term_load() + 1)
#define term_scroll()                   term_scroll_up()
#define time_slice()                    Yield()
#define toascii( c )                    ((unsigned)(c) & 0x007f)
#define unhold( p )                     kill( tid, 25 )
#define ungetchar( c )                  ungetch( c )
#define wdlength()                      (sizeof int << 3)
#define zero( p, n )                    memset( p, 0, n )

#define tprintf                         printf
#define tfprintf                        fprintf
#define tsprintf                        sprintf
#define tscanf                          scanf
#define tsscanf                         sscanf
#define tfscanf                         fscanf
#define term_tprintf                    term_printf


#ifdef __cplusplus
extern "C" {
#endif

/*
**  External Variables
*/
extern int  Break_count;


/*
**  Function Prototypes
*/
extern void abend( int );
extern int abs_sleep( unsigned int * );
extern void *alloc( unsigned int );
extern unsigned int alloc_segment( unsigned int );
extern unsigned int alloc_perm_segment( unsigned int );
extern void breakable( void );
extern int chain( char *);
extern int chainb( char *, char * );
extern void cli( void );
extern void sti( void );
extern char *concat( char *,const char *,... );
extern char *cpath( const char * );
extern char *cpathid( char * );
extern char *cqtime( signed long * );
extern void __far *create_seg( unsigned long, unsigned int, unsigned int );
extern int destroy_seg( void __far * );
extern int drop_line( struct __iobuf * );
extern void error( const char *, ... );
extern int fget( void *, int, struct __iobuf * );
extern int fgetline( struct __iobuf *, char *, int );
extern int fgetstr( struct __iobuf *, char *, int );
extern unsigned int find_admin( int, char *, int, unsigned int );
extern int fmatch( char *, char * );
extern int fput( void *, int, struct __iobuf * );
extern int frec( struct __iobuf * );
extern int ftty( struct __iobuf * );
extern int getline( char *, int );
extern int getstr( char *, int );
extern int getwd( struct __iobuf * );
extern int insert_char( struct __iobuf *, unsigned int );
extern char *itoh( int ,char * );
extern int lockf( int, int, long );
extern char *ltoa( long, char *, int );
extern char *memsetw( char *, int, unsigned int );
extern char *memxcpy( unsigned int, char *, unsigned int, char *,int );
extern char *memxset( unsigned int, char *, char, int );
extern char *memxsetw( unsigned int, char *, char, unsigned int );
extern char *mktemp( char * );
extern int name_detach( char *, unsigned int );
extern int putwd(int, struct __iobuf * );
extern int creceive( int, void *, unsigned int );
extern int creceivem( int, int, struct msg_list __far * );
extern int receivem( int, int, struct msg_list __far * );
extern int read_msg( int, char *, unsigned int );
extern int read_msgm( int, int, struct msg_list __far * );
extern int receive(int, void *, unsigned int );
extern int register_name( int, char *, unsigned int );
extern int replym(int, int, struct msg_list __far * );
extern int setexit( void );
extern void reset( void );
extern int send_break( struct __iobuf * );
extern int set_priority( int );
extern void sig_disable( void );
extern void sig_enable( void );
extern int sig_hold( int );
extern int sig_unhold( int );
extern int set_int_mask( unsigned int, unsigned int );
extern void sleep_abs( unsigned long );
extern char *substring( char *, char *, const char *);
extern char *tempnam( char *, char * );
extern char *term_input( int, int, char *, int, const char *, unsigned int, int, unsigned int );
extern int toint( int );
extern int truncate_file( struct __iobuf * );
extern int sendm(int, int, int, struct msg_list __far *, struct msg_list __far * );
extern void unbreakable( void );
extern int write_msg( int, void *, unsigned int );
extern int write_msgm(int, int, struct msg_list __far * );
extern int send(int, void *, void *, unsigned int, unsigned int );
extern void video_get_line( int devno, int row, int col, char *buffer, int len );
extern void video_put_cursor( int devno, int row, int col );
extern void video_put_line( int devno, int row, int col, char *text, int length, unsigned attr );
extern int  video_restore_image( int devno, int row, int col, char *buffer, int length );
extern int  video_save_image( int devno, int row, int col, char *buffer, int length );
extern int  video_tty( unsigned console );

/*
**  QNX 2.0 File Support
*/
extern _qnx2_open( char *path );
extern _qnx2_get_dir_entry( int fd, struct dir_entry *buf );
extern _qnx2_file_size( int fd );
extern _qnx2_close( unsigned fdesc );
extern _qnx2_read( int fdesc, void *bufp, int bytes );
extern _qnx2_lseek( unsigned fdesc, long position, short mode );
extern _qnx2_mount( char *pname, int driveno );
extern _qnx2_umount( int driveno );

#ifdef __cplusplus
};
#endif

/* End of File */
