/** @file wmassert.c
*
*  @brief Assert Functions
*
*  (C) Copyright 2008-2019 Marvell International Ltd. All Rights Reserved
*
*  MARVELL CONFIDENTIAL
*  The source code contained or described herein and all documents related to
*  the source code ("Material") are owned by Marvell International Ltd or its
*  suppliers or licensors. Title to the Material remains with Marvell
*  International Ltd or its suppliers and licensors. The Material contains
*  trade secrets and proprietary and confidential information of Marvell or its
*  suppliers and licensors. The Material is protected by worldwide copyright
*  and trade secret laws and treaty provisions. No part of the Material may be
*  used, copied, reproduced, modified, published, uploaded, posted,
*  transmitted, distributed, or disclosed in any way without Marvell's prior
*  express written permission.
*
*  No license under any patent, copyright, trade secret or other intellectual
*  property right is granted to or conferred upon you by disclosure or delivery
*  of the Materials, either expressly, by implication, inducement, estoppel or
*  otherwise. Any license under such intellectual property rights must be
*  express and approved by Marvell in writing.
*
*/
/** wmassert.c: Assert Functions
 */
#include <string.h>

#include <wm_os.h>
#include <wmstdio.h>
#include <wmassert.h>

void _wm_assert(const char *filename, int lineno, 
	    const char* fail_cond)
{
	ll_printf("\n\n\r*************** PANIC *************\n\r");
	ll_printf("Filename  : %s ( %d )\n\r", filename, lineno);
	ll_printf("Condition : %s\n\r", fail_cond);
	ll_printf("***********************************\n\r");
	os_enter_critical_section();
	for( ;; );
}