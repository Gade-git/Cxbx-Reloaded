// ******************************************************************
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2016 Patrick van Logchem <pvanlogchem@gmail.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#ifndef _EMU_KERNEL_LOGGING_H
#define _EMU_KERNEL_LOGGING_H

// prevent name collisions
namespace xbox
{

// Additional types, exclusively for logging (not really enums) :
enum  ALLOCATION_TYPE : int;
enum  CREATE_DISPOSITION : int;
enum  CREATE_OPTION : int;
//enum  NTSTATUS : int;
enum  KIRQL_TYPE : int; // fake enum, since KIRQL is an unsigned char, which clashes with BOOLEAN
enum  PROTECTION_TYPE : int;
};


#include <windows.h> // for PULONG
#include <sstream> // for std::ostream
#include "Logging.h"

// MinGW defines these as macros, which cause issues with overloads
#ifdef EXCEPTION_DISPOSITION
#undef EXCEPTION_DISPOSITION
#undef ExceptionContinueExecution
#undef ExceptionContinueSearch
#undef ExceptionNestedException
#undef ExceptionCollidedUnwind
#endif

#include <core\kernel\exports\xboxkrnl.h>

// prevent name collisions
namespace xbox
{

// Headers for rendering Xbox kernel enum types :

FLAGS2STR_HEADER(ALLOCATION_TYPE) // Not really an enum
ENUM2STR_HEADER(BUS_DATA_TYPE)
ENUM2STR_HEADER(CREATE_DISPOSITION) // Not really an enum
FLAGS2STR_HEADER(CREATE_OPTION) // Not really an enum
ENUM2STR_HEADER(EVENT_TYPE)
ENUM2STR_HEADER(EXCEPTION_DISPOSITION)
ENUM2STR_HEADER(FILE_INFORMATION_CLASS)
ENUM2STR_HEADER(FS_INFORMATION_CLASS)
ENUM2STR_HEADER(KINTERRUPT_MODE)
ENUM2STR_HEADER(KIRQL_TYPE) // Not really an enum
ENUM2STR_HEADER(KWAIT_REASON)
ENUM2STR_HEADER(KOBJECTS)
ENUM2STR_HEADER(MODE)
//ENUM2STR_HEADER(NTSTATUS) // Not really an enum
FLAGS2STR_HEADER(PROTECTION_TYPE) // Not really an enum
ENUM2STR_HEADER(RETURN_FIRMWARE)
ENUM2STR_HEADER(TIMER_TYPE)
ENUM2STR_HEADER(WAIT_TYPE)
ENUM2STR_HEADER(XC_VALUE_INDEX)

// Headers for rendering Xbox kernel types without pointer-to-type :
LOGRENDER_HEADER_BY_REF(BOOLEAN);
LOGRENDER_HEADER_BY_REF(PBYTE);
LOGRENDER_HEADER_BY_REF(PULONG);

// Headers for rendering functions of Xbox kernel type and pointer-to-type :

// TODO : Implement renderers for each usage of these types (and/or (P/LP) pointers to them)...
//
// TODO : LOGRENDER_HEADER(DEVICE_OBJECT)
// TODO : LOGRENDER_HEADER(DISPATCHER_HEADER)
// TODO : LOGRENDER_HEADER(DVDX2_AUTHENTICATION)
// TODO : LOGRENDER_HEADER(DVDX2_AUTHENTICATION_PAGE)
// TODO : LOGRENDER_HEADER(ERWLOCK)
// TODO : LOGRENDER_HEADER(ETHREAD)
// TODO : LOGRENDER_HEADER(EXCEPTION_RECORD)
LOGRENDER_HEADER(FILETIME)
// TODO : LOGRENDER_HEADER(FILE_DIRECTORY_INFORMATION)
// TODO : LOGRENDER_HEADER(FILE_FS_SIZE_INFORMATION)
// TODO : LOGRENDER_HEADER(IO_STATUS_BLOCK) // LOGRENDER_HEADER(PIO_STATUS_BLOCK ->u1.Pointer, ->Information
// TODO : LOGRENDER_HEADER(KDEVICE_QUEUE)
// TODO : LOGRENDER_HEADER(KDPC)
// TODO : LOGRENDER_HEADER(KEVENT)
// TODO : LOGRENDER_HEADER(KINTERRUPT)
// TODO : LOGRENDER_HEADER(KIRQL)
// TODO : LOGRENDER_HEADER(KPCR)
// TODO : LOGRENDER_HEADER(KPRCB)
// TODO : LOGRENDER_HEADER(KPROCESSOR_MODE)
// TODO : LOGRENDER_HEADER(KSEMAPHORE)
// TODO : LOGRENDER_HEADER(KSPIN_LOCK)
// TODO : LOGRENDER_HEADER(KSYSTEM_TIME)
// TODO : LOGRENDER_HEADER(KTHREAD)
// TODO : LOGRENDER_HEADER(KTIMER)
LOGRENDER_HEADER(LARGE_INTEGER)
LOGRENDER_HEADER(LAUNCH_DATA_HEADER)
LOGRENDER_HEADER(LAUNCH_DATA_PAGE)
// TODO : LOGRENDER_HEADER(LIST_ENTRY)
// TODO : LOGRENDER_HEADER(LPCCH)
// TODO : LOGRENDER_HEADER(LPCSTR)
// TODO : LOGRENDER_HEADER(LPCWSTR)
// TODO : LOGRENDER_HEADER(MEMORY_BASIC_INFORMATION)
LOGRENDER_HEADER(MM_STATISTICS)
// TODO : LOGRENDER_HEADER(MODE_PARAMETER_HEADER10)
// TODO : LOGRENDER_HEADER(NT_TIB)
// TODO : LOGRENDER_HEADER(NTSTATUS)
LOGRENDER_HEADER(OBJECT_ATTRIBUTES)
// TODO : LOGRENDER_HEADER(OBJECT_STRING)
// TODO : LOGRENDER_HEADER(OBJECT_TYPE)
// TODO : LOGRENDER_HEADER(PCI_COMMON_CONFIG)
// TODO : LOGRENDER_HEADER(PCI_SLOT_NUMBER)
// TODO : LOGRENDER_HEADER(PCHAR)
// TODO : LOGRENDER_HEADER(PKDEFERRED_ROUTINE)
// TODO : LOGRENDER_HEADER(PKDPC)
// TODO : LOGRENDER_HEADER(PKINTERRUPT)
// TODO : LOGRENDER_HEADER(PKSERVICE_ROUTINE)
// TODO : LOGRENDER_HEADER(PXDEVICE_PREALLOC_TYPE)
// TODO : LOGRENDER_HEADER(PXINPUT_CAPABILITIES)
// TODO : LOGRENDER_HEADER(PXINPUT_STATE)
// TODO : LOGRENDER_HEADER(PXPP_DEVICE_TYPE)
// TODO : LOGRENDER_HEADER(PXTHREAD_NOTIFICATION) // -> pfnNotifyRoutine
// TODO : LOGRENDER_HEADER(RTL_CRITICAL_SECTION)
// TODO : LOGRENDER_HEADER(SCSI_PASS_THROUGH_DIRECT)
// TODO : LOGRENDER_HEADER(SINGLE_LIST_ENTRY)
// TODO : LOGRENDER_HEADER(SLIST_HEADER)
LOGRENDER_HEADER(STRING) // Alias ANSI_STRING
// TODO : LOGRENDER_HEADER(TIME_FIELDS)
// TODO : LOGRENDER_HEADER(UCHAR)
// TODO : LOGRENDER_HEADER(ULARGE_INTEGER)
LOGRENDER_HEADER(UNICODE_STRING)
// TODO : LOGRENDER_HEADER(XBOX_HARDWARE_INFO)
// TODO : LOGRENDER_HEADER(XBOX_REFURB_INFO)

}; // end of namespace xbox

#endif _EMU_KERNEL_LOGGING_H
