
/*
 * This depends on a ffs mounts
 * What data does ufs_args hold?
 * fspec <- This is a char * ? To what?
 * export_args <- I know this is used for network maybe server side shares
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/mount.h>
#include <sys/ucred.h>
#include <unistd.h>
#include <err.h>

int main(void) {
   
    struct statfs *mntbuf;
    int mntsize_len = 0;
   
    mntsize_len = getmntinfo(&mntbuf, MNT_NOWAIT);
   
    if (mntsize_len == 0)
        err(1, "retrieving information on mounted file systems");

    for (int i = 0; i < mntsize_len; i++) {
        printf("\n----------Data:%d---------------\n",i);
        printf("flags:%d\n",mntbuf[i].f_flags);    /* copy of mount flags */
        printf("bsize:%d\n",mntbuf[i].f_bsize);    /* file system block size */
        printf("iosize:%d\n\n",mntbuf[i].f_iosize);    /* optimal transfer block size */

        /* unit is f_bsize */
        printf("block:%llu\n",mntbuf[i].f_blocks);    /* total data blocks in file system */
        printf("bfree:%llu\n",mntbuf[i].f_bfree);    /* free blocks in fs */
        printf("bavail:%llu\n\n",mntbuf[i].f_bavail);    /* free blocks avail to non-superuser */

        printf("files:%llu\n",mntbuf[i].f_files);    /* total file nodes in file system */
        printf("ffree:%llu\n",mntbuf[i].f_ffree);    /* free file nodes in fs */
        printf("favail:%llu\n\n",mntbuf[i].f_favail);    /* free file nodes avail to non-root */

        printf("syncwrites:%llu\n",mntbuf[i].f_syncwrites);    /* count of sync writes since mount */
        printf("syncreads:%llu\n",mntbuf[i].f_syncreads);    /* count of sync reads since mount */
        printf("asyncwrites:%llu\n",mntbuf[i].f_asyncwrites);    /* count of async writes since mount */
        printf("asyncreads:%llu\n\n",mntbuf[i].f_asyncreads);    /* count of async reads since mount */

        printf("fsid1:%d\n",mntbuf[i].f_fsid.val[0]);        /* file system id */
        printf("fsid2:%d\n",mntbuf[i].f_fsid.val[1]);        /* only set if root */
       
        printf("namemax:%u\n",mntbuf[i].f_namemax);      /* maximum filename length */
        printf("owner:%u\n",mntbuf[i].f_owner);    /* user that mounted the file system */
        printf("ctime:%llu\n",mntbuf[i].f_ctime);    /* last mount [-u] time */

        printf("fstypename:%s\n",mntbuf[i].f_fstypename);    /* fs type name */
        printf("mntonname:%s\n",mntbuf[i].f_mntonname);    /* directory on which mounted */
        printf("mntfromname:%s\n",mntbuf[i].f_mntfromname);    /* mounted file system */
        printf("mntfromspec:%s\n",mntbuf[i].f_mntfromspec);    /* special for mount request */
        if (strcmp(mntbuf[i].f_fstypename, "ffs") == 0) { //check for ufs it points to ffs.
            puts("----------Start mount_info.ufs_args (aka ffs)-------------");
            //Data seem to be garbage. Why and what would they be?
            printf("ex_spec:%p\n", mntbuf[i].mount_info.ufs_args.fspec);
            printf("ex_addr:%p\n", mntbuf[i].mount_info.ufs_args.export_info.ex_addr);
            printf("ex_addrlen:%d\n", mntbuf[i].mount_info.ufs_args.export_info.ex_addrlen);
            printf("ex_flags:%d\n", mntbuf[i].mount_info.ufs_args.export_info.ex_flags);
            printf("ex_masklen:%d\n", mntbuf[i].mount_info.ufs_args.export_info.ex_masklen);
            printf("ex_root:%d\n", mntbuf[i].mount_info.ufs_args.export_info.ex_root);
            printf("ex_anon.cr_uid:%u\n", mntbuf[i].mount_info.ufs_args.export_info.ex_anon.cr_uid);
            printf("ex_anon.cr_gid:%u\n", mntbuf[i].mount_info.ufs_args.export_info.ex_anon.cr_gid);
            printf("ex_anon.cr_ngroups:%hd\n", mntbuf[i].mount_info.ufs_args.export_info.ex_anon.cr_ngroups);
            for (int j = 0; j < mntbuf[i].mount_info.ufs_args.export_info.ex_anon.cr_ngroups; j++) {
             printf("%d)ex_anon.cr_gid:%u\n", j, mntbuf[i].mount_info.ufs_args.export_info.ex_anon.cr_groups[j]);
            }
        }    
    }
}
