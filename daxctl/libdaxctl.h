/*
 * Copyright (c) 2016, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 */
#ifndef _LIBDAXCTL_H_
#define _LIBDAXCTL_H_

#include <stdarg.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

struct daxctl_ctx;
struct daxctl_ctx *daxctl_ref(struct daxctl_ctx *ctx);
void daxctl_unref(struct daxctl_ctx *ctx);
int daxctl_new(struct daxctl_ctx **ctx);
void daxctl_set_log_fn(struct daxctl_ctx *ctx,
		void (*log_fn)(struct daxctl_ctx *ctx, int priority,
			const char *file, int line, const char *fn,
			const char *format, va_list args));
int daxctl_get_log_priority(struct daxctl_ctx *ctx);
void daxctl_set_log_priority(struct daxctl_ctx *ctx, int priority);
void daxctl_set_userdata(struct daxctl_ctx *ctx, void *userdata);
void *daxctl_get_userdata(struct daxctl_ctx *ctx);

struct daxctl_region;
struct daxctl_region *daxctl_new_region(struct daxctl_ctx *ctx, int id,
		uuid_t uuid, const char *path);
void daxctl_region_ref(struct daxctl_region *region);
void daxctl_region_unref(struct daxctl_region *region);
void daxctl_region_get_uuid(struct daxctl_region *region, uuid_t uu);
int daxctl_region_get_id(struct daxctl_region *region);
struct daxctl_ctx *daxctl_region_get_ctx(struct daxctl_region *region);

struct daxctl_dev;
struct daxctl_dev *daxctl_dev_get_first(struct daxctl_region *region);
struct daxctl_dev *daxctl_dev_get_next(struct daxctl_dev *dev);
struct daxctl_region *daxctl_dev_get_region(struct daxctl_dev *dev);
int daxctl_dev_get_id(struct daxctl_dev *dev);
const char *daxctl_dev_get_devname(struct daxctl_dev *dev);
int daxctl_dev_get_major(struct daxctl_dev *dev);
int daxctl_dev_get_minor(struct daxctl_dev *dev);
unsigned long long daxctl_dev_get_size(struct daxctl_dev *dev);

#define daxctl_dev_foreach(region, dev) \
        for (dev = daxctl_dev_get_first(region); \
             dev != NULL; \
             dev = daxctl_dev_get_next(dev))

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
