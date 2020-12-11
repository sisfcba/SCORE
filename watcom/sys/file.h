#ifndef _FILE_H_INCLUDED
#define _FILE_H_INCLUDED

#include <unistd.h>
#include <fcntl.h>

#define LOCK_SH         F_RDLCK         /* shared lock */
#define LOCK_EX         F_WRLCK         /* exclusive lock */
#define LOCK_UN         F_UNLCK         /* unlock */
#define LOCK_NB         4               /* don't block when locking */

#ifdef __cplusplus
extern "C" {
#endif
extern int flock(int fd, int operation);
#ifdef __cplusplus
};
#endif
#endif
