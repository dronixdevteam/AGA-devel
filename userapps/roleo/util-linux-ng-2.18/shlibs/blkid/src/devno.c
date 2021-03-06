/*
 * devno.c - find a particular device by its device number (major/minor)
 *
 * Copyright (C) 2000, 2001, 2003 Theodore Ts'o
 * Copyright (C) 2001 Andreas Dilger
 *
 * %Begin-Header%
 * This file may be redistributed under the terms of the
 * GNU Lesser General Public License.
 * %End-Header%
 */

#include <stdio.h>
#include <string.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdlib.h>
#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#include <dirent.h>
#if HAVE_ERRNO_H
#include <errno.h>
#endif
#if HAVE_SYS_MKDEV_H
#include <sys/mkdev.h>
#endif
#include <fcntl.h>
#include <inttypes.h>

#include "blkidP.h"
#include "pathnames.h"

char *blkid_strndup(const char *s, int length)
{
	char *ret;

	if (!s)
		return NULL;

	if (!length)
		length = strlen(s);

	ret = malloc(length + 1);
	if (ret) {
		strncpy(ret, s, length);
		ret[length] = '\0';
	}
	return ret;
}

char *blkid_strdup(const char *s)
{
	return blkid_strndup(s, 0);
}

char *blkid_strconcat(const char *a, const char *b, const char *c)
{
	char *res, *p;
	size_t len, al, bl, cl;

	al = a ? strlen(a) : 0;
	bl = b ? strlen(b) : 0;
	cl = c ? strlen(c) : 0;

	len = al + bl + cl;
	if (!len)
		return NULL;
	p = res = malloc(len + 1);
	if (!res)
		return NULL;
	if (al) {
		memcpy(p, a, al);
		p += al;
	}
	if (bl) {
		memcpy(p, b, bl);
		p += bl;
	}
	if (cl) {
		memcpy(p, c, cl);
		p += cl;
	}
	*p = '\0';
	return res;
}

int blkid_fstatat(DIR *dir, const char *dirname, const char *filename,
			struct stat *st, int nofollow)
{
#ifdef HAVE_FSTATAT
	return fstatat(dirfd(dir), filename, st,
			nofollow ? AT_SYMLINK_NOFOLLOW : 0);
#else
	char path[PATH_MAX];
	int len;

	len = snprintf(path, sizeof(path), "%s/%s", dirname, filename);
	if (len < 0 || len + 1 > sizeof(path))
		return -1;

	return nofollow ? lstat(path, st) : stat(path, st);
#endif
}

int blkid_openat(DIR *dir, const char *dirname, const char *filename, int flags)
{
#ifdef HAVE_FSTATAT
	return openat(dirfd(dir), filename, flags);
#else
	char path[PATH_MAX];
	int len;

	len = snprintf(path, sizeof(path), "%s/%s", dirname, filename);
	if (len < 0 || len + 1 > sizeof(path))
		return -1;

	return open(path, flags);
#endif
}

/*
 * This function adds an entry to the directory list
 */
static void add_to_dirlist(const char *dir, const char *subdir,
				struct dir_list **list)
{
	struct dir_list *dp;

	dp = malloc(sizeof(struct dir_list));
	if (!dp)
		return;
	dp->name = subdir ? blkid_strconcat(dir, "/", subdir) :
			    blkid_strdup(dir);
	if (!dp->name) {
		free(dp);
		return;
	}
	dp->next = *list;
	*list = dp;
}

/*
 * This function frees a directory list
 */
static void free_dirlist(struct dir_list **list)
{
	struct dir_list *dp, *next;

	for (dp = *list; dp; dp = next) {
		next = dp->next;
		free(dp->name);
		free(dp);
	}
	*list = NULL;
}

void blkid__scan_dir(char *dirname, dev_t devno, struct dir_list **list,
		     char **devname)
{
	DIR	*dir;
	struct dirent *dp;
	struct stat st;

	if ((dir = opendir(dirname)) == NULL)
		return;

	while ((dp = readdir(dir)) != 0) {
#ifdef _DIRENT_HAVE_D_TYPE
		if (dp->d_type != DT_UNKNOWN && dp->d_type != DT_BLK &&
		    dp->d_type != DT_LNK && dp->d_type != DT_DIR)
			continue;
#endif
		if (dp->d_name[0] == '.' &&
		    ((dp->d_name[1] == 0) ||
		     ((dp->d_name[1] == '.') && (dp->d_name[2] == 0))))
			continue;

		if (blkid_fstatat(dir, dirname, dp->d_name, &st, 0))
			continue;

		if (S_ISBLK(st.st_mode) && st.st_rdev == devno) {
			*devname = blkid_strconcat(dirname, "/", dp->d_name);
			DBG(DEBUG_DEVNO,
			    printf("found 0x%llx at %s\n", (long long)devno,
				   *devname));
			break;
		}

		if (!list || !S_ISDIR(st.st_mode))
			continue;

		/* add subdirectory (but not symlink) to the list */
#ifdef _DIRENT_HAVE_D_TYPE
		if (dp->d_type == DT_LNK)
			continue;
		if (dp->d_type == DT_UNKNOWN)
#endif
		{
			if (blkid_fstatat(dir, dirname, dp->d_name, &st, 1) ||
			    !S_ISDIR(st.st_mode))
				continue;	/* symlink or lstat() failed */
		}

		if (strcmp(".udev", dp->d_name) == 0)
			/* udev private direcory is huge and uninteresting */
			continue;

		add_to_dirlist(dirname, dp->d_name, list);
	}
	closedir(dir);
	return;
}

/* Directories where we will try to search for device numbers */
static const char *devdirs[] = { "/devices", "/devfs", "/dev", NULL };

/**
 * SECTION: misc
 * @title: Miscellaneous utils
 * @short_description: mix of various utils for low-level and high-level API
 */

/**
 * blkid_devno_to_devname:
 * @devno: device number
 *
 * This function finds the pathname to a block device with a given
 * device number.
 *
 * Returns: a pointer to allocated memory to the pathname on success,
 * and NULL on failure.
 */
char *blkid_devno_to_devname(dev_t devno)
{
	struct dir_list *list = NULL, *new_list = NULL;
	char *devname = NULL;
	const char **dir;

	/*
	 * Add the starting directories to search in reverse order of
	 * importance, since we are using a stack...
	 */
	for (dir = devdirs; *dir; dir++)
		add_to_dirlist(*dir, NULL, &list);

	while (list) {
		struct dir_list *current = list;

		list = list->next;
		DBG(DEBUG_DEVNO, printf("directory %s\n", current->name));
		blkid__scan_dir(current->name, devno, &new_list, &devname);
		free(current->name);
		free(current);
		if (devname)
			break;
		/*
		 * If we're done checking at this level, descend to
		 * the next level of subdirectories. (breadth-first)
		 */
		if (list == NULL) {
			list = new_list;
			new_list = NULL;
		}
	}
	free_dirlist(&list);
	free_dirlist(&new_list);

	if (!devname) {
		DBG(DEBUG_DEVNO,
		    printf("blkid: couldn't find devno 0x%04lx\n",
			   (unsigned long) devno));
	} else {
		DBG(DEBUG_DEVNO,
		    printf("found devno 0x%04llx as %s\n", (long long)devno, devname));
	}


	return devname;
}


/* returns basename and keeps dirname in the @path */
static char *stripoff_last_component(char *path)
{
	char *p = strrchr(path, '/');

	if (!p)
		return NULL;
	*p = '\0';
	return ++p;
}

/**
 * blkid_devno_to_wholedisk:
 * @dev: device number
 * @diskname: buffer to return diskname (or NULL)
 * @len: diskname buffer size (or 0)
 * @diskdevno: pointer to returns devno of entire disk (or NULL)
 *
 * This function uses sysfs to convert the @devno device number to the *name*
 * of the whole disk. The function DOES NOT return full device name. The @dev
 * argument could be partition or whole disk -- both is converted.
 *
 * For example: sda1, 0x0801 --> sda, 0x0800
 *
 * For conversion to the full disk *path* use blkid_devno_to_devname(), for
 * example:
 *
 * <informalexample>
 *  <programlisting>
 *
 *	dev_t dev = 0x0801, disk;		// sda1 = 8:1
 *	char *diskpath, diskname[32];
 *
 *	blkid_devno_to_wholedisk(dev, diskname, sizeof(diskname), &disk);
 *	diskpath = blkid_devno_to_devname(disk);
 *
 *	// print "0x0801: sda, /dev/sda, 8:0
 *	printf("0x%x: %s, %s, %d:%d\n",
 *		dev, diskname, diskpath, major(disk), minor(disk));
 *
 *	free(diskpath);
 *
 *  </programlisting>
 * </informalexample>
 *
 * Returns: 0 on success or -1 in case of error.
 */
int blkid_devno_to_wholedisk(dev_t dev, char *diskname,
			size_t len, dev_t *diskdevno)
{
	char path[PATH_MAX];
	char linkpath[PATH_MAX];
	struct stat info;
	char *name;
	int rc, linklen;

	if (!dev)
		goto err;

	/* check if dev is a partition */
	rc = snprintf(path, sizeof(path), "/sys/dev/block/%d:%d/partition",
			major(dev), minor(dev));
	if (rc < 0 || rc + 1 > sizeof(path))
		goto err;

	rc = stat(path, &info);		/* 'rc == 0' means partitioned dev */

	 /* aka dirname (remove "/partition" from the path*/
	stripoff_last_component(path);

	/*
	 * Unpartitioned device:
	 *	- readlink /sys/dev/block/8:0 = ../../block/sda
	 *	- basename ../../block/sda    = sda
	 *
	 * Partitioned device:
	 *	- readlink /sys/dev/block/8:1   = ../../block/sda/sda1
	 *	- dirname  ../../block/sda/sda1 = ../../block/sda
	 *	- basename ../../block/sda      = sda
	 */
	linklen = readlink(path, linkpath, sizeof(linkpath) - 1);
	if (linklen < 0)
		goto err;
	linkpath[linklen] = '\0';

	if (rc == 0)
		/* partitioned device */
		stripoff_last_component(linkpath);	/* dirname */

	name = stripoff_last_component(linkpath);	/* basename */
	if (!name)
		goto err;

	if (diskname && len) {
		strncpy(diskname, name, len);
		diskname[len - 1] = '\0';
	}

	if (diskdevno) {
		int maj, min;
		FILE *f;

		/* read wholedisk devno */
		rc = snprintf(path, sizeof(path), "/sys/block/%s/dev", name);
		if (rc < 0 || rc + 1 > sizeof(path))
			goto err;

		f = fopen(path, "r");
		if (!f)
			goto err;

		rc = fscanf(f, "%d:%d", &maj, &min);
		fclose(f);
		if (rc != 2)
			goto err;

		*diskdevno = makedev(maj, min);
	}

	DBG(DEBUG_DEVNO,
	    printf("found entire diskname for devno 0x%04llx as %s\n",
	    (long long) dev, name));
	return 0;
err:
	DBG(DEBUG_DEVNO,
	    printf("failed to convert 0x%04llx to wholedisk name, errno=%d\n",
	    (long long) dev, errno));
	return -1;
}

/*
 * Returns 1 if the @major number is associated with @drvname.
 */
int blkid_driver_has_major(const char *drvname, int major)
{
	FILE *f;
	char buf[128];
	int match = 0;

	f = fopen(_PATH_PROC_DEVICES, "r");
	if (!f)
		return 0;

	while (fgets(buf, sizeof(buf), f)) {	/* skip to block dev section */
		if (strncmp("Block devices:\n", buf, sizeof(buf)) == 0)
			break;
	}

	while (fgets(buf, sizeof(buf), f)) {
		unsigned int maj;
		char name[64];

		if (sscanf(buf, "%u %64[^\n ]", &maj, name) != 2)
			continue;

		if (maj == major && strcmp(name, drvname) == 0) {
			match = 1;
			break;
		}
	}

	fclose(f);

	DBG(DEBUG_DEVNO, printf("major %d %s associated with '%s' driver\n",
			major, match ? "is" : "is NOT", drvname));
	return match;
}

static char *mk_devno_attribute_path(char *buf, size_t buflen,
				dev_t devno, const char *attr)
{
	int len = snprintf(buf, buflen, "/sys/dev/block/%d:%d/%s",
			major(devno), minor(devno), attr);

	if (len < 0 || len + 1 > buflen)
		return NULL;

	return buf;
}

int blkid_devno_has_attribute(dev_t devno, const char *attribute)
{
	char path[PATH_MAX];
	struct stat info;

	if (!mk_devno_attribute_path(path, sizeof(path), devno, attribute))
		return 0;

	if (stat(path, &info) == 0)
		return 1;

	return 0;
}

int blkid_devno_get_u64_attribute(dev_t devno, const char *attribute, uint64_t *result)
{
	FILE *f;
	char path[PATH_MAX];
	int rc = 0;

	if (!mk_devno_attribute_path(path, sizeof(path), devno, attribute))
		return -1;

	f = fopen(path, "r");
	if (f) {
		rc = fscanf(f, "%" SCNu64, result);
		fclose(f);
	}

	return rc == 1 ? 0 : -1;
}

int blkid_devno_get_s64_attribute(dev_t devno, const char *attribute, int64_t *result)
{
	FILE *f;
	char path[PATH_MAX];
	int rc = 0;

	if (!mk_devno_attribute_path(path, sizeof(path), devno, attribute))
		return -1;

	f = fopen(path, "r");
	if (f) {
		rc = fscanf(f, "%" SCNd64, result);
		fclose(f);
	}

	return rc == 1 ? 0 : -1;
}

#ifdef TEST_PROGRAM
int main(int argc, char** argv)
{
	char	*devname, *tmp;
	int	major, minor;
	dev_t	devno;
	const char *errmsg = "Couldn't parse %s: %s\n";

	blkid_init_debug(DEBUG_ALL);
	if ((argc != 2) && (argc != 3)) {
		fprintf(stderr, "Usage:\t%s device_number\n\t%s major minor\n"
			"Resolve a device number to a device name\n",
			argv[0], argv[0]);
		exit(1);
	}
	if (argc == 2) {
		devno = strtoul(argv[1], &tmp, 0);
		if (*tmp) {
			fprintf(stderr, errmsg, "device number", argv[1]);
			exit(1);
		}
	} else {
		major = strtoul(argv[1], &tmp, 0);
		if (*tmp) {
			fprintf(stderr, errmsg, "major number", argv[1]);
			exit(1);
		}
		minor = strtoul(argv[2], &tmp, 0);
		if (*tmp) {
			fprintf(stderr, errmsg, "minor number", argv[2]);
			exit(1);
		}
		devno = makedev(major, minor);
	}
	printf("Looking for device 0x%04llx\n", (long long)devno);
	devname = blkid_devno_to_devname(devno);
	free(devname);
	return 0;
}
#endif
