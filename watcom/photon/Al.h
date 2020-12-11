
typedef struct Al_db AlDataBase_t;

typedef struct {
	const char		*wgt_name;
	unsigned long	res_value;
	const char		*res_descr;
	unsigned long	res_index;
	const char		*wgt_font;
	const char		*str_original;
	const char		*str_translated;
	unsigned long	res_flags;
	}
		AlTextEntry_t;

enum AlResFlags {
	Al_MULTILINE = 1,
	Al_ACCELERATOR = 2,
	Al_ISMESSAGE = 4
	};

extern AlDataBase_t *AlOpenDBase( const char *path );  /* Read database file into memory */
extern int AlReadTranslation( AlDataBase_t *db, const char *path );  /* Read translation file into memory */
extern int AlSaveTranslation( AlDataBase_t const *db, const char *path );  /* Save translation file */
extern void AlClearTranslation( AlDataBase_t *db );
extern void AlCloseDBase( AlDataBase_t *db );  /* Free memory */
extern int AlGetVersion( AlDataBase_t const *db );

extern unsigned AlGetSize( AlDataBase_t const *db );
extern const AlTextEntry_t *AlGetEntry( AlDataBase_t const *db, unsigned index );
extern int AlSetEntry( AlDataBase_t *db, unsigned index, const char *string );
extern int AlSetVersion( AlDataBase_t *db, int version ); /* Set format for saving */

