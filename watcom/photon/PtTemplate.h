#ifndef __Pt_TEMPLATE_INCLUDED
#define __Pt_TEMPLATE_INCLUDED

#include <PtBasic.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtTemplate;

#define	Pt_ARG_TEMPLATE_1 	Pt_RESOURCE( Pt_USER(1), 0 )
#define	Pt_ARG_TEMPLATE_2	Pt_RESOURCE( Pt_USER(1), 1 )

/* Widget structure */
struct pt_template{
	PtBasic_t	basic;
	PhRect_t 	rect1;
	short		foo;
} PtTemplate_t;

/* Widget union */
typedef union Pt_template_union {
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtTemplate_t		template;
} PtTemplateUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
