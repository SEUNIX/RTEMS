/*
 *  Multiprocessing Manager
 *
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#include <rtems/system.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/mp.h>
#include <rtems/score/mpci.h>

/*PAGE
 *
 *  _Multiprocessing_Manager_initialization
 *
 */

void _Multiprocessing_Manager_initialization ( void )
{
}

/*PAGE
 *
 *  rtems_multiprocessing_announce
 *
 */

void rtems_multiprocessing_announce ( void )
{
  _MPCI_Announce();
}

/* end of file */
