
#ifndef __DS_H
#define __DS_H

#ifdef __cplusplus
extern "C" {
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif


#define DS_PERM 1

typedef int ds_t;

int ds_register(void);
int ds_deregister(ds_t dsdes);
int ds_create(ds_t dsdes, char *variable_name, char flags, struct sigevent *sigevent);
int ds_clear(ds_t dsdes, char *variable_name);
int ds_set(ds_t dsdes, char *variable_name, char *variable_data, int data_len);
int ds_get(ds_t dsdes, char *variable_name, char *variable_data, int data_len); 
int ds_flags(ds_t dsdes, char *variable_name, char flags);


#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
};
#endif
#endif

