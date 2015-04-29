/*
  FUSE: Filesystem in Userspace
  Author: Lina Yi 
  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

const int MAXBLOCK = 10000;
const int BLOCKSIZE = 4096;
const int MAXFILESIZE = 1638400;
static const char FILEDATAPREFIX[] ="/fusedata/fusedata.";
static const char ROOTNAME[] = "/fusedata/fusedata.26";
static const char SUPERBLOCKNAME[] = "/fusedata/fusedata.0";
static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";
static int freelist[373];

//define a filetoinode and initialize this struct
struct filetoinode{
    char indicator; // file or directory
    int len;
    char name[50];
    int block_num;
};

static struct inode{
    int size, uid, gid, mode, linkcount,sub;
    int indirect;
    int location;
    time_t atime, ctime, mtime;
    struct filetoinode stu[400];
    }boy[10000];

int getpathaddress(char *path){
	char charpath[10];
	strcpy(charpath, path);  
	int lenth = strlen(charpath);
	int i =0;
	int a[10];
	for (i=0; i<10; i++){
		a[i]=0;
	}
	for (i=0; i<lenth;i++){
		if (charpath[i]=='/')
			a[i]= i;
	}
	int max = a[0];
	int j=0;
	for (j=0;j<10;j++){
		if (a[j]>max )
			max = a[j];
		}
	return max;
}

static int hello_getattr(const char *path, struct stat *stbuf)
{	int i= 0;
	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
		stbuf->st_size = 4096;
		stbuf->st_gid = 1000;
		stbuf->st_uid = 1000;
		stbuf->st_atime = 1323630836;
		stbuf->st_ctime = 1323630836;
		stbuf->st_mtime = 1323630836;
		return 0;
	}

	for (i=0;i<400;i++){
		int max = getpathaddress(path);
		if (strcmp(boy[26].stu[i].name, path+1+max) == 0)
		{
			if(boy[26].stu[i].indicator=='f'){
				stbuf->st_mode = S_IFREG | 0644;
				stbuf->st_nlink = 1;
				stbuf->st_size = 0;
				stbuf->st_gid = 1000;
				stbuf->st_uid = 1000;
				stbuf->st_atime = 1323630836;
				stbuf->st_ctime = 1323630836;
				stbuf->st_mtime = 1323630836;
			}
			else {
				stbuf->st_mode = S_IFDIR | 0755;
				stbuf->st_nlink = 2;
				stbuf->st_size = 4096;
				stbuf->st_gid = 1000;
				stbuf->st_uid = 1000;
				stbuf->st_atime = 1323630836;
				stbuf->st_ctime = 1323630836;
				stbuf->st_mtime = 1323630836;
			}
			return 0;

		}
	}

	return -ENOENT;

}


static int hello_create(const char *path , mode_t mode, struct fuse_file_info *fi) {

	int z= return_firstunzero();

	boy[z].size= 0;
	boy[z].uid = 1;
	boy[z].gid = 1;
	boy[z].mode = 33261;
	boy[z].atime = 1323630836;
	boy[z].ctime = 1323630836;
	boy[z].mtime = 1323630836;
	boy[z].linkcount= 1;
	int d = boy[26].linkcount++;
	boy[26].stu[d].indicator = 'f';
	strcpy (boy[26].stu[d].name, path+1);
	boy[26].stu[d].block_num = z;
	mode = boy[z].mode;
	return 0;
}

static int hello_mkdir(const char *path , mode_t mode, struct fuse_file_info *fi) {
	int z= return_firstunzero();
	boy[z].size= 0;
	boy[z].uid = 1;
	boy[z].gid = 1;
	boy[z].mode = 16877;
	boy[z].atime = 1323630836;
	boy[z].ctime = 1323630836;
	boy[z].mtime = 1323630836;
	boy[z].linkcount= 2;
	boy[z].stu[0].indicator = 'd';
	strcpy (boy[z].stu[0].name, ".");
	boy[z].stu[0].block_num = z;
	boy[z].stu[1].indicator = 'd';
	strcpy (boy[z].stu[1].name,".." );
	boy[z].stu[1].block_num = 26;
	int d = boy[26].linkcount++;
	boy[26].stu[d].indicator = 'd';
	strcpy (boy[26].stu[d].name, path+1);
	boy[26].stu[d].block_num = z;

	mode = boy[z].mode;
	return  0;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;
	int i=0;
	for(i;i<boy[26].linkcount;i++)
{ 
	filler(buf, boy[26].stu[i].name, NULL, 0);
}	

	return 0;
}
static int hello_releasedir(const char *path, struct fuse_file_info *fi){
	return 0;
}
static int hello_release(const char *path, struct fuse_file_info *fi){
	return 0;
}
static int hello_opendir(const char *path, struct fuse_file_info *fi){
	
	int i= 0;

	for (i=0;i<400;i++){	
		if (strcmp(boy[26].stu[i].name, path+1) == 0)
		{
			return 0;	
		}
	}

	return -ENOENT;
}
static int hello_open(const char *path, struct fuse_file_info *fi){

	int i= 0;

	for (i=0;i<400;i++){	
		if (strcmp(boy[26].stu[i].name, path+1) == 0)
		{
			return 0;	
		}
	}

	return -ENOENT;
}
// static int hello_open(const char *path, struct fuse_file_info *fi)
// {
// 	if (strcmp(path, hello_path) != 0)
// 		return -ENOENT;

// 	if ((fi->flags & 3) != O_RDONLY)
// 		return -EACCES;

// 	return 0;
// }

static int hello_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;
	
	len = strlen(hello_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, hello_str + offset, size);
	} else
		size = 0;

	return size;
}

// elliminate error coused by touch a file
int hello_chmod (const char *path, mode_t mode){
	return 0;
}
 
int hello_chown (const char *path, uid_t uid, gid_t gid ){
	return 0;
}
 
int hello_truncate (const char *path, off_t t){
	return 0;

}
int hello_utimens (const char *path, const struct timespec tv[2]){

	return 0;
}
// destroy function 
void hello_destroy(){
	int i;
	char name[50];
	for (i=0;i<10000;i++){
        sprintf(name, "/fusedata/fusedata.%d", i);
        remove(name);
	}
}


// to convert the block_num to file name and write file
void serialization(int block_num,struct inode* sth){
        char name[50];
        sprintf(name, "/fusedata/fusedata.%d", block_num);
        FILE *f = fopen(name, "w");
        fwrite(sth, sizeof(struct inode), 1, f);
        fclose(f);
    }

void filetoinode_init(struct filetoinode*a,char i, int l, const char n[], int num )
{
        a->indicator = i;
        a->len = l;
        strcpy(a->name, n);
        a->block_num = num;
        struct filetoinode* test[100];
}
// define super block
struct Super_block{
    time_t createTime;
    int mounted, devld, freeStart, freeEnd, root;
    int maxBlocks;
    int blcok_used;
};
struct rootmetadata{
	int size, uid,gid,mode,linkcount;
	time_t  atime, ctime, mtime;
	char filename_to_inode_dict[100][100];
};
// function to write derectory to file
void he(struct inode* a){
        char name[50];
        sprintf(name,"/fusedata/fusedata.%d", a->stu[400].block_num);
        FILE *f = fopen(name, "w");
        fwrite(a, sizeof(struct inode), 1, f);
        fclose(f);
}
//return first unzero in freelist 
int return_firstunzero(){
	int i = 0;
	for (i=0;i<373;i++){
		if (freelist[i]!=0){
			freelist[i]=0;
			return i;
		}
		else
			return 0;
	}
}

static int hello_statfs(const char *path , struct statvfs *stfbuf){
	
	stfbuf->f_bsize=4096;    /* Filesystem block size */
    stfbuf->f_frsize=4096;   /* Fragment size */
    stfbuf->f_blocks=10000;   /* Size of fs in f_frsize units */
    stfbuf->f_bfree=9973;    /* Number of free blocks */
    stfbuf->f_bavail=9973;   /* Number of free blocks for*/
    stfbuf->f_files=10000;   /* Number of inodes */
    stfbuf->f_ffree=9973;    /* Number of free inodes */
    stfbuf->f_favail=9973;   /* Number of free inodes for*/
    stfbuf->f_fsid=22;         /* Filesystem ID */                          
    stfbuf->f_flag=0;     /* Mount flags */
    stfbuf->f_namemax=100;       /* Maximum filename length */
}


// initialize file system
void* hello_init(){

	boy[0].location=26;
	//initrilize super block
	struct Super_block *superBlock=malloc(sizeof(struct Super_block));
	superBlock->blcok_used = 0;
	superBlock->createTime = 1376483073;
	superBlock->mounted = 50;
	superBlock->devld = 20;
	superBlock->freeStart = 1;
	superBlock->freeEnd =25;
	superBlock->root = 26;
	superBlock->maxBlocks = 10000;
	//initialize root dir info
	
	boy[26].size = 0;
	boy[26].gid = 1;
	boy[26].mode = 16877;
	boy[26].atime = 1323630836;
	boy[26].ctime = 1323630836;
	boy[26].mtime = 1323630836;
	boy[26].linkcount = 2;	
	strcpy (boy[26].stu[0].name, ".");
	boy[26].stu[0].block_num = 26;
	boy[26].stu[1].indicator = 'd';
	strcpy (boy[26].stu[1].name,".." );
	boy[26].stu[1].block_num = 26;
	// init block information
	int i = 26;
	for (i ;i < MAXBLOCK;i ++) {
		int a[BLOCKSIZE / sizeof(int)];
	    memset(a, 0, sizeof(a));
	    char buffer[50];
	    sprintf(buffer, "/fusedata/fusedata.%d", i);
	    FILE *f = fopen(buffer, "w");
	    fwrite(a, sizeof(int), BLOCKSIZE / sizeof(int), f);
	    fclose(f);
	}
	printf("block info ok\n");
	FILE *f;
	//init free block list 1-25, 400 per file, fusedata.1 contain from 27~399
	f = fopen("/fusedata/fusedata.1", "w");

	int j=0;
	for (j;j <= 373;j ++){
		freelist[j] = j + 27;
	}
	fwrite(freelist, sizeof(int), 373, f);
	fclose(f);
	int h=2;
	for (h;h <= 25;h ++){
		char buffer[50];
		sprintf(buffer, "/fusedata/fusedata.%d", h);
		FILE *f = fopen(buffer, "w");
		int a[400];
		int k=0;
		for (k ;k < 400;k ++){
	            a[k] = (k - 1) * 400 + k;
	            }
	            fwrite(a, sizeof(int), 400, f);
	            fclose(f);
	        }
		return NULL;
}

static struct fuse_operations hello_oper = {
	.getattr	= hello_getattr,
	.readdir	= hello_readdir,
	.open       = hello_open,
	.opendir	= hello_opendir,	
	.read		= hello_read,
	.init       = hello_init,
	.create     = hello_create,
	.mkdir 		= hello_mkdir,
	.release     = hello_release,
	.releasedir  = hello_releasedir,
	.chmod       = hello_chmod,
	.chown        = hello_chown,
	.truncate     = hello_truncate,
	.utimens      = hello_utimens,
	.statfs       = hello_statfs,
	.destroy      = hello_destroy,
};

int main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &hello_oper, NULL);
}
