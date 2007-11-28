/*
 *  $Id$
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <pthread.h>

#include <rtems/system.h>
#include <rtems/score/coremutex.h>
#include <rtems/score/watchdog.h>
#include <rtems/posix/mutex.h>
#include <rtems/posix/priority.h>
#include <rtems/posix/time.h>

/*PAGE
 *
 *  11.3.1 Mutex Initialization Attributes, P1003.1c/Draft 10, p. 81
 */

int pthread_mutexattr_init(
  pthread_mutexattr_t *attr
)
{
  if ( !attr )
    return EINVAL;

  *attr = _POSIX_Mutex_Default_attributes;
  return 0;
}
