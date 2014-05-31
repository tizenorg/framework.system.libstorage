/*
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of SAMSUNG
 * ELECTRONICS ("Confidential Information"). You agree and acknowledge that
 * this software is owned by Samsung and you shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms
 * of the license agreement you entered into with SAMSUNG ELECTRONICS. SAMSUNG
 * make no representations or warranties about the suitability of the software,
 * either express or implied, including but not limited to the implied
 * warranties of merchantability, fitness for a particular purpose, or
 * non-infringement. SAMSUNG shall not be liable for any damages suffered by
 * licensee arising out of or related to this software.
 *
 */
#include <storage.h>

#define API_NAME_STORAGE_GET_INTERNAL_MEMORY_SIZE "storage_get_internal_memory_size"

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;


static void utc_system_storage_get_internal_memory_size_p(void);
static void utc_system_storage_get_internal_memory_size_n(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_system_storage_get_internal_memory_size_p, POSITIVE_TC_IDX },
	{ utc_system_storage_get_internal_memory_size_n, NEGATIVE_TC_IDX },
	{ NULL, 0 },
};


static void startup(void)
{
}

static void cleanup(void)
{
}

/**
 * @brief Positive test case of storage_get_internal_memory_size()
 */
static void utc_system_storage_get_internal_memory_size_p(void)
{
	struct statvfs s;
	int ret;

	ret = storage_get_internal_memory_size(&s);
	dts_check_eq(API_NAME_STORAGE_GET_INTERNAL_MEMORY_SIZE, ret, 0);
}

/**
 * @brief Negative test case of storage_get_internal_memory_size()
 */
static void utc_system_storage_get_internal_memory_size_n(void)
{
	int ret;

	ret = storage_get_internal_memory_size(NULL);
	dts_check_ne(API_NAME_STORAGE_GET_INTERNAL_MEMORY_SIZE, ret, 0);
}
