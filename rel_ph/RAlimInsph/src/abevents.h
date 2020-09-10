/* Event header for application - AppBuilder 1.14C */

#if defined(__cplusplus)
extern "C" {
#endif

const ApEventLink_t appl_links[] = {
	{ 3, 0, 0L, 0L, 0L, &base, base_links, NULL, 0, StartPrincipal, 1, 5, 6, 30, dsbase },
	{ 0, 0, 0L, 0L, 0L, NULL, NULL, NULL, 0, NULL, 0, 0, 0, 0, NULL }
	};

ApEventLink_t internal_links[] = {
	{ 3, 0, 0L, 0L, 0L, &PRINCIPAL, PRINCIPAL_links, NULL, 0, NULL, 0, 5, 6, 30, dsPRINCIPAL },
	{ 3, 0, 0L, 0L, 0L, &PRINCIPAL_X, PRINCIPAL_X_links, NULL, 0, NULL, 0, 5, 6, 42, dsPRINCIPAL_X },
	{ 0, 0, 0L, 0L, 0L, NULL, NULL, NULL, 0, NULL, 0, 0, 0, 0, NULL }
	};

const ApEventLink_t base_links[] = {
	{ 0, 0, 0L, 0L, 0L, NULL, NULL, NULL, 0, NULL, 0, 0, 0, 0, NULL }
	};

const ApEventLink_t PRINCIPAL_links[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PRINCIPAL_grupo", 2009, Grupo, 0, 0, 0, 0, NULL },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PRINCIPAL_sair", 2009, Sair, 0, 0, 0, 0, NULL },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PRINCIPAL_scrollbar", 29010, Pagina, 0, 0, 0, 0, NULL },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PRINCIPAL_timer", 41002, Timer, 0, 0, 0, 0, NULL },
	{ 0, 0, 0L, 0L, 0L, NULL, NULL, NULL, 0, NULL, 0, 0, 0, 0, NULL }
	};

const ApEventLink_t PRINCIPAL_X_links[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PRINCIPAL_X_sair", 2009, Sair, 0, 0, 0, 0, NULL },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PRINCIPAL_X_scrollbar", 29010, Pagina, 0, 0, 0, 0, NULL },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PRINCIPAL_X_grupo", 2009, Grupo, 0, 0, 0, 0, NULL },
	{ 0, 0, 0L, 0L, 0L, NULL, NULL, NULL, 0, NULL, 0, 0, 0, 0, NULL }
	};


#if defined(__cplusplus)
}
#endif

