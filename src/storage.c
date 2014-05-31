/*
 * storage
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <errno.h>

#include "log.h"
#include "common.h"

#define MEMORY_MEGABYTE_VALUE		1048576
#define MEMORY_RESERVE_VALUE		(100*MEMORY_MEGABYTE_VALUE)
#define MEMORY_STATUS_USR_PATH		"/opt/usr"

/* it's for 32bit file offset */
struct statvfs_32 {
	unsigned long int f_bsize;
	unsigned long int f_frsize;
	unsigned long int f_blocks;
	unsigned long int f_bfree;
	unsigned long int f_bavail;
	unsigned long int f_files;
	unsigned long int f_ffree;
	unsigned long int f_favail;
	unsigned long int f_fsid;
#ifdef _STATVFSBUF_F_UNUSED
	int __f_unused;
#endif
	unsigned long int f_flag;
	unsigned long int f_namemax;
	int __f_spare[6];
};

API int storage_get_internal_memory_size(struct statvfs *buf)
{
	struct statvfs s;
	struct statvfs_32 temp = {0,};
	unsigned long reserved;
	int ret;

	_D("storage_get_internal_memory_size");
	if (!buf) {
		_E("input param error");
		return -EINVAL;
	}

	ret = statvfs(MEMORY_STATUS_USR_PATH, &s);
	if (ret) {
		_E("fail to get memory size");
		return -errno;
	}

	temp.f_bsize  = s.f_bsize;
	temp.f_frsize = s.f_frsize;
	temp.f_blocks = (unsigned long)s.f_blocks;
	temp.f_bfree  = (unsigned long)s.f_bfree;
	temp.f_bavail = (unsigned long)s.f_bavail;
	temp.f_files  = (unsigned long)s.f_files;
	temp.f_ffree  = (unsigned long)s.f_ffree;
	temp.f_favail = (unsigned long)s.f_favail;
	temp.f_fsid = s.f_fsid;
	temp.f_flag = s.f_flag;
	temp.f_namemax = s.f_namemax;

	reserved = MEMORY_RESERVE_VALUE/s.f_bsize;
	if (temp.f_bavail < reserved)
		temp.f_bavail = 0;
	else
		temp.f_bavail -= reserved;

	memcpy(buf, &temp, sizeof(temp));
	return 0;
}

API int storage_get_internal_memory_size64(struct statvfs *buf)
{
	unsigned long reserved;
	int ret;

	_D("storage_get_internal_memory_size64");
	if (!buf) {
		_E("input param error");
		return -EINVAL;
	}

	ret = statvfs(MEMORY_STATUS_USR_PATH, buf);
	if (ret) {
		_E("fail to get memory size");
		return -errno;
	}

	reserved = MEMORY_RESERVE_VALUE/buf->f_bsize;
	if (buf->f_bavail < reserved)
		buf->f_bavail = 0;
	else
		buf->f_bavail -= reserved;
	return 0;
}
