/* Import (extern) header for application - AppBuilder 1.14C */

#if defined(__cplusplus)
extern "C" {
#endif

#include "abdefine.h"

extern const ApEventLink_t appl_links[];
extern ApEventLink_t internal_links[];

extern ApWindowLink_t base;
extern const ApEventLink_t base_links[];
extern ApWidget_t dsbase[2];

extern ApWindowLink_t PRINCIPAL;
extern const ApEventLink_t PRINCIPAL_links[];
extern ApWidget_t dsPRINCIPAL[29];

extern ApWindowLink_t PRINCIPAL_X;
extern const ApEventLink_t PRINCIPAL_X_links[];
extern ApWidget_t dsPRINCIPAL_X[29];


#if defined(__cplusplus)
}
#endif

#ifdef __cplusplus
int ini_rel( int argc, char **argv );
int StartPrincipal( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Grupo( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Sair( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Timer( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int Pagina( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
#endif
