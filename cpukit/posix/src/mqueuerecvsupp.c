/*
 *  NOTE:  The structure of the routines is identical to that of POSIX
 *         Message_queues to leave the option of having unnamed message
 *         queues at a future date.  They are currently not part of the
 *         POSIX standard but unnamed message_queues are.  This is also 
 *         the reason for the apparently unnecessary tracking of 
 *         the process_shared attribute.  [In addition to the fact that
 *         it would be trivial to add pshared to the mq_attr structure
 *         and have process private message queues.]
 *
 *         This code ignores the O_RDONLY/O_WRONLY/O_RDWR flag at open
 *         time.
 *
 *  $Id$
 */

#include <stdarg.h>

#include <pthread.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>

#include <rtems/system.h>
#include <rtems/score/watchdog.h>
#include <rtems/posix/seterr.h>
#include <rtems/posix/mqueue.h>
#include <rtems/posix/time.h>

/*PAGE
 *
 *  _POSIX_Message_queue_Receive_support
 */
 
/* XXX be careful ... watch the size going through all the layers ... */

ssize_t _POSIX_Message_queue_Receive_support(
  mqd_t               mqdes,
  char               *msg_ptr,
  size_t              msg_len,
  unsigned int       *msg_prio,
  Watchdog_Interval   timeout
)
{
  register POSIX_Message_queue_Control *the_mq;
  Objects_Locations                     location;
  unsigned32                            status = 0;
  unsigned32                            length_out;
 
  the_mq = _POSIX_Message_queue_Get( mqdes, &location );
  switch ( location ) {
    case OBJECTS_ERROR:
      set_errno_and_return_minus_one( EINVAL );
    case OBJECTS_REMOTE:
      _Thread_Dispatch();
      return POSIX_MP_NOT_IMPLEMENTED();
      set_errno_and_return_minus_one( EINVAL );
    case OBJECTS_LOCAL:
      /* XXX need to define the options argument to this */
      length_out = msg_len;
      _CORE_message_queue_Seize(
        &the_mq->Message_queue,
        mqdes,
        msg_ptr,
        &length_out,
        /* msg_prio,    XXXX */
        the_mq->blocking,
        timeout
      );
      _Thread_Enable_dispatch();
      if ( !status )
        return length_out;
      /* XXX --- the return codes gotta be looked at .. fix this */
      return _Thread_Executing->Wait.return_code;
  }
  return POSIX_BOTTOM_REACHED();
}

