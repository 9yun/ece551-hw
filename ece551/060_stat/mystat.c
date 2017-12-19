#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
//This function is for Step 4

char get_type(int x){
  switch(x){
  case 0:
    return 'b';
    break;
  case 1:
    return 'c';
    break;
  case 2:
    return 'd';
    break;
  case 3:
    return 'p';
    break;
  case 4:
    return 'l';
    break;
  case 5:
    return '-';
    break;
  case 6:
    return 's';
    break;
  }
  return '\0';
}
char get_read(int x){
  if(x!=0){
    return 'r';
  }
  return '-';
}

char get_write(int x){
  if(x!=0){
    return 'w';
  }
  return '-';
}

char get_execute(int x){
  if(x!=0){
    return 'x';
  }
  return '-';
}

char * time2str(const time_t * when, long ns);
void stat_print(struct stat *mystat,char *myfile);
int main(int argc,char ** argv){
  if(argc<2){
    fprintf(stderr,"stat: missing operand\nTry 'stat --help' for more information.\n");
    exit(EXIT_FAILURE);
  }
  for(int i=1;i<argc;i++){
    struct stat mystat;
    if(lstat(argv[i],&mystat)==-1){
      fprintf(stderr,"stat: cannot stat '%s': No such file or directory\n",argv[i]);
      exit(EXIT_FAILURE);
    }
    stat_print(&mystat,argv[i]);
  }
  exit(EXIT_SUCCESS);
}
void stat_print(struct stat *mystat,char * myfile){
  if(S_ISLNK(mystat->st_mode)){
    char linktarget[256];
    ssize_t len=readlink(myfile, linktarget, 256);
    char *link_point=&linktarget[len];
      *link_point='\0';
      printf("  File: '%s' -> '%s'\n",myfile,linktarget);
    }
    //printf("  File: '%s'\n",myfile);
  printf("  File: '%s'\n",myfile);
  const char *s;
  int judge =-1;
  switch(mystat->st_mode & S_IFMT){
  case S_IFBLK :s= "block special file";judge=0;break;
  case  S_IFCHR:  s= "character special file";judge=1;break;
  case  S_IFDIR:  s= "directory";judge=2;break;
  case S_IFIFO:  s= "fifo";judge=3;break;
  case  S_IFLNK:  s= "symbolic link";judge=4;break;
  case S_IFREG:  s= "regular file";judge=5;break;
  case S_IFSOCK: s= "socket"; judge =6;break;
  default: s="unknown?\n";break;
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",(unsigned long)mystat->st_size,(unsigned long)mystat->st_blocks,(unsigned long)mystat->st_blksize,s);
  if (S_ISCHR(mystat->st_mode) || S_ISBLK(mystat->st_mode)){
    printf( "Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",(long)(mystat->st_dev),(long)(mystat->st_dev),(unsigned long)mystat->st_ino,(unsigned long)mystat->st_nlink,major(mystat->st_dev),minor(mystat->st_dev));
  }
  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",(long)mystat->st_dev,(long)mystat->st_dev,(long)mystat->st_ino,(long)mystat->st_nlink);
  //int octal_permission=octal_num(judge);
  char description[11];
  for(int i=0;i<11;i++){
    description[i]='\0';
  }
  description[0]=get_type(judge);
  description[1]=get_read(mystat->st_mode & S_IRUSR);
  description[2]=get_write(mystat->st_mode & S_IWUSR);
  description[3]=get_execute(mystat->st_mode & S_IXUSR);
  description[4]=get_read(mystat->st_mode & S_IRGRP);
  description[5]=get_write(mystat->st_mode & S_IWGRP);
  description[6]=get_execute(mystat->st_mode & S_IXGRP);
  description[7]=get_read(mystat->st_mode & S_IROTH);
  description[8]=get_write(mystat->st_mode & S_IWOTH);
  description[9]=get_execute(mystat->st_mode & S_IXOTH);
  
  
  struct passwd *user_file= getpwuid(mystat->st_uid);
  char *user_name=user_file->pw_name;
  struct group *group_file=getgrgid(mystat->st_gid);
  char *group_name=group_file->gr_name;
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",(mystat->st_mode & ~S_IFMT),description,mystat->st_uid,user_name,mystat->st_gid,group_name);
  char *timestr_a= time2str(&(mystat->st_atime),(long)mystat->st_atim.tv_nsec);
  char *timestr_m= time2str(&(mystat->st_mtime),(long)mystat->st_mtim.tv_nsec);
  char *timestr_c= time2str(&(mystat->st_ctime),(long)mystat->st_ctim.tv_nsec);
  printf("Access: %s\n",timestr_a);
  printf("Modify: %s\n",timestr_m);
  printf("Change: %s\n",timestr_c);
  printf(" Birth: -\n");
  free(timestr_a);
  free(timestr_m);
  free(timestr_c);
}
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}


