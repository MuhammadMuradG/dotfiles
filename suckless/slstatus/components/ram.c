/* See LICENSE file for copyright and license details. */
#include <stdio.h>

#include "../util.h"

#if defined(__linux__)
	#include <stdint.h>

	const char *
	ram_free(void)
	{
		uintmax_t free;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ju kB\n"
		           "MemFree: %ju kB\n"
		           "MemAvailable: %ju kB\n",
		           &free, &free, &free) != 3) {
			return NULL;
		}

		return fmt_human(free * 1024, 1024);
	}

	const char *
	ram_perc(void)
	{
		uintmax_t total, free, buffers, cached;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ju kB\n"
		           "MemFree: %ju kB\n"
		           "MemAvailable: %ju kB\n"
		           "Buffers: %ju kB\n"
		           "Cached: %ju kB\n",
		           &total, &free, &buffers, &buffers, &cached) != 5) {
			return NULL;
		}

		if (total == 0) {
			return NULL;
		}

		return bprintf("%d", 100 * ((total - free) - (buffers + cached))
                               / total);
	}

	const char *
	ram_total(void)
	{
		uintmax_t total;

		if (pscanf("/proc/meminfo", "MemTotal: %ju kB\n", &total)
		    != 1) {
			return NULL;
		}

		return fmt_human(total * 1024, 1024);
	}

	const char *
	ram_used(void)
	{
		uintmax_t total, free, buffers, cached;

		if (pscanf("/proc/meminfo",
		           "MemTotal: %ju kB\n"
		           "MemFree: %ju kB\n"
		           "MemAvailable: %ju kB\n"
		           "Buffers: %ju kB\n"
		           "Cached: %ju kB\n",
		           &total, &free, &buffers, &buffers, &cached) != 5) {
			return NULL;
		}

		return fmt_human((total - free - buffers - cached) * 1024,
		                 1024);
	}
#elif defined(__OpenBSD__)
	#include <stdlib.h>
	#include <sys/sysctl.h>
	#include <sys/types.h>
	#include <unistd.h>

	#define LOG1024 10
	#define pagetok(size, pageshift) (size_t)(size << (pageshift - LOG1024))

	inline int
	load_uvmexp(struct uvmexp *uvmexp)
	{
		int uvmexp_mib[] = {CTL_VM, VM_UVMEXP};
		size_t size;

		size = sizeof(*uvmexp);

		if (sysctl(uvmexp_mib, 2, uvmexp, &size, NULL, 0) >= 0) {
			return 1;
		}

		return 0;
	}

	const char *
	ram_free(void)
	{
		struct uvmexp uvmexp;
		int free_pages;

		if (load_uvmexp(&uvmexp)) {
			free_pages = uvmexp.npages - uvmexp.active;
			return fmt_human(pagetok(free_pages, uvmexp.pageshift) *
			                 1024, 1024);
		}

		return NULL;
	}

	const char *
	ram_perc(void)
	{
		struct uvmexp uvmexp;
		int percent;

		if (load_uvmexp(&uvmexp)) {
			percent = uvmexp.active * 100 / uvmexp.npages;
			return bprintf("%d", percent);
		}

		return NULL;
	}

	const char *
	ram_total(void)
	{
		struct uvmexp uvmexp;

		if (load_uvmexp(&uvmexp)) {
			return fmt_human(pagetok(uvmexp.npages,
			                         uvmexp.pageshift) * 1024,
			                 1024);
		}

		return NULL;
	}

	const char *
	ram_used(void)
	{
		struct uvmexp uvmexp;

		if (load_uvmexp(&uvmexp)) {
			return fmt_human(pagetok(uvmexp.active,
			                         uvmexp.pageshift) * 1024,
			                 1024);
		}

		return NULL;
	}
#elif defined(__FreeBSD__)
	#include <sys/sysctl.h>
	#include <sys/vmmeter.h>
	#include <unistd.h>
	#include <vm/vm_param.h>

	const char *
	ram_free(void) {
		struct vmtotal vm_stats;
		int mib[] = {CTL_VM, VM_TOTAL};
		size_t len;

		len = sizeof(struct vmtotal);
		if (sysctl(mib, 2, &vm_stats, &len, NULL, 0) == -1
				|| !len)
			return NULL;

		return fmt_human(vm_stats.t_free * getpagesize(), 1024);
	}

	const char *
	ram_total(void) {
		unsigned int npages;
		size_t len;

		len = sizeof(npages);
		if (sysctlbyname("vm.stats.vm.v_page_count", &npages, &len, NULL, 0) == -1
				|| !len)
			return NULL;

		return fmt_human(npages * getpagesize(), 1024);
	}

	const char *
	ram_perc(void) {
		unsigned int npages, inactive, free, cache, total_free, total_used;
		size_t len_pg, len_inact, len_cache, len_free;

		len_pg = sizeof(npages);
		if (sysctlbyname("vm.stats.vm.v_page_count", &npages, &len_pg, NULL, 0) == -1
				|| !len_pg)
			return NULL;

		len_free = sizeof(free);
		if (sysctlbyname("vm.stats.vm.v_free_count", &free, &len_free, NULL, 0) == -1
				|| !len_free)
			return NULL;

		len_inact = sizeof(inactive);
		if (sysctlbyname("vm.stats.vm.v_inactive_count", &inactive, &len_inact, NULL, 0) == -1
				|| !len_inact)
			return NULL;

		len_cache = sizeof(cache);
		if (sysctlbyname("vm.stats.vm.v_cache_count", &cache, &len_cache, NULL, 0) == -1
				|| !len_cache)
			return NULL;

		total_free = free + inactive + cache;
		total_used = npages - total_free;

		return bprintf("%d", total_used * 100 / npages);
	}

	const char *
	ram_used(void) {
		unsigned int npages, inactive, free, cache, total_free, total_used;
		size_t len_pg, len_inact, len_cache, len_free;

		len_pg = sizeof(npages);
		if (sysctlbyname("vm.stats.vm.v_page_count", &npages, &len_pg, NULL, 0) == -1
				|| !len_pg)
			return NULL;

		len_free = sizeof(free);
		if (sysctlbyname("vm.stats.vm.v_free_count", &free, &len_free, NULL, 0) == -1
				|| !len_free)
			return NULL;

		len_inact = sizeof(inactive);
		if (sysctlbyname("vm.stats.vm.v_inactive_count", &inactive, &len_inact, NULL, 0) == -1
				|| !len_inact)
			return NULL;

		len_cache = sizeof(cache);
		if (sysctlbyname("vm.stats.vm.v_cache_count", &cache, &len_cache, NULL, 0) == -1
				|| !len_cache)
			return NULL;

		total_free = free + inactive + cache;
		total_used = npages - total_free;

		return fmt_human(total_used * getpagesize(), 1024);
	}
#endif
