#ifndef _NLIST_H
#define _NLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
struct nlist {
    char    n_name[12];
    long    n_value;
    short   n_type;
};
#pragma pack()

#ifdef __cplusplus
};
#endif

#endif
