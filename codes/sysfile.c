//
// File-system system calls.
// Mostly argument checking, since we don't trust
// user code, and calls into file.c and fs.c.
//

#include "types.h"
#include "defs.h"
#include "param.h"
#include "stat.h"
#include "mmu.h"
#include "proc.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"

// Fetch the nth word-sized system call argument as a file descriptor
// and return both the descriptor and the corresponding struct file.
static int
argfd(int n, int *pfd, struct file **pf)
{
  int fd;
  struct file *f;

  if(argint(n, &fd) < 0)
    return -1;
  if(fd < 0 || fd >= NOFILE || (f=myproc()->ofile[fd]) == 0)
    return -1;
  if(pfd)
    *pfd = fd;
  if(pf)
    *pf = f;
  return fd;
}

// Allocate a file descriptor for the given file.
// Takes over file reference from caller on success.
static int
fdalloc(struct file *f)
{
  int fd;
  struct proc *curproc = myproc();

  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd] == 0){
      curproc->ofile[fd] = f;
      return fd;
    }
  }
  return -1;
}

int
sys_dup(void)
{
  struct file *f;
  int fd;
  int result;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "dup";
  system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

  int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if((result = argfd(0, 0, &f)) < 0)
    return -1;


  if((fd=fdalloc(f)) < 0)
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[0][tcounter] = result;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][0]->char_value = "\0";
   // safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][0]->char_value, 
   //  "\0", strlen("\0") + 1);

 

  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][1]->type = "\0";
    // safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][1]->type, 
    // "\0", strlen("\0") + 1);

  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][1]->int_value = 0;
  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][1]->char_value = "\0";
   // safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][1]->char_value, 
   //  "\0", strlen("\0") + 1);

    // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][2]->type = "\0";
    // safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][2]->type, 
    // "\0", strlen("\0") + 1);

  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][2]->int_value = 0;
  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][2]->char_value = "\0";
   // safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][2]->char_value, 
   //  "\0", strlen("\0") + 1);



 
  // end/////////////////////////////////////////

  filedup(f);
  return fd;
}

int
sys_read(void)
{
  struct file *f;
  int n;
  char *p;
  int fd;
  int addr;
  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "read";
  system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;



  int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if((fd=argfd(0, 0, &f)) < 0 || argint(2, &n) < 0 || (addr=argptr(1, &p, n) < 0))
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[0][tcounter] = fd;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // cprintf("fd valueeeeeeee %d\n" , system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[0][tcounter]);

  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[1] = "void*";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter] = (uint)addr;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // cprintf("addr address valueeeeeeee %d\n" , system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter]);


  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[2] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[2][tcounter] = n;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // cprintf("n valueeeeeeee %d\n" , system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[2][tcounter]);

  // end/////////////////////////////////////////

  return fileread(f, p, n);
}

int
sys_write(void)
{
  struct file *f;
  int n;
  char *p;
  int fd;
  int addr;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "write";
  system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;
  int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if((fd = argfd(0, 0, &f)) < 0 || argint(2, &n) < 0 || (addr=argptr(1, &p, n)) < 0)
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[0][tcounter] = fd;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // cprintf("&&&1%s\n",system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][0]->type);


  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[1] = "void*";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter] = (uint)addr;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // cprintf("&&&2%s\n",system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][1]->type);


  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[2] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[2][tcounter] = n;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // cprintf("&&&3%s\n",system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][2]->type);

  // end/////////////////////////////////////////
  return filewrite(f, p, n);
}

int
sys_close(void)
{
  int fd;
  struct file *f;
  int p;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "close";
  system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

  int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if((p=argfd(0, &fd, &f)) < 0)
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[0][tcounter] = p;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // end ////////////////////////////////////////////
  myproc()->ofile[fd] = 0;
  fileclose(f);
  return 0;
}

int
sys_fstat(void)
{
  struct file *f;
  struct stat *st;
  int fd;
  int addr;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "fstat";
  system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

  int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if((fd=argfd(0, 0, &f)) < 0 || (addr = argptr(1, (void*)&st, sizeof(*st))) < 0)
    return -1;
  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[0][tcounter]= fd;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;

  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[1] = "struct stat*";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter] = (uint)addr;  
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // end ////////////////////////////////////////////

  return filestat(f, st);
}

// Create the path new as a link to the same inode as old.
int
sys_link(void)
{
  char name[DIRSIZ], *new, *old;
  struct inode *dp, *ip;
  // char* s;
  // char* s1;
  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "link";
    system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

    int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////


  if(argstr(0, &old) < 0 || argstr(1, &new) < 0)
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "char*";
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter], 
    old, strlen(old) + 1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;
  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][0]->char_value = s;

  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[1] = "char*";
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[1][tcounter],
   new, strlen(new) + 1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;
  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[time_index_fa][1]->char_value = new;  
  // end ////////////////////////////////////////////

  begin_op();
  if((ip = namei(old)) == 0){
    end_op();
    return -1;
  }

  ilock(ip);
  if(ip->type == T_DIR){
    iunlockput(ip);
    end_op();
    return -1;
  }

  ip->nlink++;
  iupdate(ip);
  iunlock(ip);

  if((dp = nameiparent(new, name)) == 0)
    goto bad;
  ilock(dp);
  if(dp->dev != ip->dev || dirlink(dp, name, ip->inum) < 0){
    iunlockput(dp);
    goto bad;
  }
  iunlockput(dp);
  iput(ip);

  end_op();

  return 0;

bad:
  ilock(ip);
  ip->nlink--;
  iupdate(ip);
  iunlockput(ip);
  end_op();
  return -1;
}
// Is the directory dp empty except for "." and ".." ?
static int
isdirempty(struct inode *dp)
{
  int off;
  struct dirent de;

  for(off=2*sizeof(de); off<dp->size; off+=sizeof(de)){
    if(readi(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
      panic("isdirempty: readi");
    if(de.inum != 0)
      return 0;
  }
  return 1;
}

//PAGEBREAK!
int
sys_unlink(void)
{
  struct inode *ip, *dp;
  struct dirent de;
  char name[DIRSIZ], *path;
  uint off;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "unlink";
    system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

    int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if(argstr(0, &path) < 0)
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "char*";
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter],
   path , strlen(path) +1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;
  // end///////////////////////////////////////////

  begin_op();
  if((dp = nameiparent(path, name)) == 0){
    end_op();
    return -1;
  }

  ilock(dp);

  // Cannot unlink "." or "..".
  if(namecmp(name, ".") == 0 || namecmp(name, "..") == 0)
    goto bad;

  if((ip = dirlookup(dp, name, &off)) == 0)
    goto bad;
  ilock(ip);

  if(ip->nlink < 1)
    panic("unlink: nlink < 1");
  if(ip->type == T_DIR && !isdirempty(ip)){
    iunlockput(ip);
    goto bad;
  }

  memset(&de, 0, sizeof(de));
  if(writei(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
    panic("unlink: writei");
  if(ip->type == T_DIR){
    dp->nlink--;
    iupdate(dp);
  }
  iunlockput(dp);

  ip->nlink--;
  iupdate(ip);
  iunlockput(ip);

  end_op();

  return 0;

bad:
  iunlockput(dp);
  end_op();
  return -1;
}

static struct inode*
create(char *path, short type, short major, short minor)
{
  uint off;
  struct inode *ip, *dp;
  char name[DIRSIZ];

  if((dp = nameiparent(path, name)) == 0)
    return 0;
  ilock(dp);

  if((ip = dirlookup(dp, name, &off)) != 0){
    iunlockput(dp);
    ilock(ip);
    if(type == T_FILE && ip->type == T_FILE)
      return ip;
    iunlockput(ip);
    return 0;
  }

  if((ip = ialloc(dp->dev, type)) == 0)
    panic("create: ialloc");

  ilock(ip);
  ip->major = major;
  ip->minor = minor;
  ip->nlink = 1;
  iupdate(ip);

  if(type == T_DIR){  // Create . and .. entries.
    dp->nlink++;  // for ".."
    iupdate(dp);
    // No ip->nlink++ for ".": avoid cyclic ref count.
    if(dirlink(ip, ".", ip->inum) < 0 || dirlink(ip, "..", dp->inum) < 0)
      panic("create dots");
  }

  if(dirlink(dp, name, ip->inum) < 0)
    panic("create: dirlink");

  iunlockput(dp);

  return ip;
}

int
sys_open(void)
{
  char *path;
  int fd, omode;
  struct file *f;
  struct inode *ip;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "open";
    system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

    int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if(argstr(0, &path) < 0 || argint(1, &omode) < 0)
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "char*";
  // cprintf("tcounter is :%d\n" , tcounter);
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter], 
    path, strlen(path) + 1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;
  // system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter] = &path;
  // strncpy(a , path , strlen(path) + 1);
  // cprintf("pathhhhhhhhhhhhhhhhhhhh : %s\n" , path);

  // cprintf("my pathhththththhtht %s\n" , system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter]);
  // cprintf("size of path is : %d\n" , strlen(path));
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[1] = "int";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter] = omode;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // end///////////////////////////////////////////

  begin_op();

  if(omode & O_CREATE){
    ip = create(path, T_FILE, 0, 0);
    if(ip == 0){
      end_op();
      return -1;
    }
  } else {
    if((ip = namei(path)) == 0){
      end_op();
      return -1;
    }
    ilock(ip);
    if(ip->type == T_DIR && omode != O_RDONLY){
      iunlockput(ip);
      end_op();
      return -1;
    }
  }

  if((f = filealloc()) == 0 || (fd = fdalloc(f)) < 0){
    if(f)
      fileclose(f);
    iunlockput(ip);
    end_op();
    return -1;
  }
  iunlock(ip);
  end_op();

  f->type = FD_INODE;
  f->ip = ip;
  f->off = 0;
  f->readable = !(omode & O_WRONLY);
  f->writable = (omode & O_WRONLY) || (omode & O_RDWR);
  return fd;
}

int
sys_mkdir(void)
{
  char *path;
  struct inode *ip;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "mkdir";
    system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;
    int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////


  begin_op();
  if(argstr(0, &path) < 0 || (ip = create(path, T_DIR, 0, 0)) == 0){
    end_op();
    return -1;
  }

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "char*";
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter], 
    path, strlen(path) + 1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;
  // end///////////////////////////////////////////

  iunlockput(ip);
  end_op();
  return 0;
}

int
sys_mknod(void)
{
  struct inode *ip;
  char *path;
  int major, minor;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "mknod";
    system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

    int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  begin_op();
  if((argstr(0, &path)) < 0 ||
     argint(1, &major) < 0 ||
     argint(2, &minor) < 0 ||
     (ip = create(path, T_DEV, major, minor)) == 0){
    end_op();
    return -1;
  }

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "char*";
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter], 
    path, strlen(path) + 1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;

  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[1] = "short";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter] = major;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;

  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[2] = "short";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[2][tcounter] = minor;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // end///////////////////////////////////////////

  iunlockput(ip);
  end_op();
  return 0;
}

int
sys_chdir(void)
{
  char *path;
  struct inode *ip;
  struct proc *curproc = myproc();
  
  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "chdir";
    system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

    int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  begin_op();
  if(argstr(0, &path) < 0 || (ip = namei(path)) == 0){
    end_op();
    return -1;
  }

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "char*";
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter], 
    path, strlen(path) + 1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;
  // end///////////////////////////////////////////

  ilock(ip);
  if(ip->type != T_DIR){
    iunlockput(ip);
    end_op();
    return -1;
  }
  iunlock(ip);
  iput(curproc->cwd);
  end_op();
  curproc->cwd = ip;
  return 0;
}

int
sys_exec(void)
{
  char *path, *argv[MAXARG];
  int i;
  uint uargv, uarg;
  // char* s;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "exec";
  system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

  int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////
  if(argstr(0, &path) < 0 || argint(1, (int*)&uargv) < 0){
    return -1;
  }
  // start///////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "char*";
  safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arg_char[0][tcounter], 
    path, strlen(path) + 1);
  system_calls[index_of_process_aln][index_of_syscall_ftm].char_cnt ++;
  // cprintf(":::::::::::size of char is : \n" , sizeof(path));

  // cprintf("******char1value: %s\n" ,system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][0]->char_value);

  // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][0]->char_value = s;

  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[1] = "char**";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter] = (uint)uargv;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // cprintf("in execcccccccccccccc third value is :%d\n" , system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[1][tcounter]);
  /////// safestrcpy(system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][1]->char_value, 
  //   "\0", strlen("\0") + 1);

  // cprintf("******char2value: %s\n" ,system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][1]->char_value);

   // system_calls[index_of_process_aln][index_of_syscall_ftm].arguments[tcounter][2]->int_value = 0;

  // end///////////////////////////////////////////

  memset(argv, 0, sizeof(argv));
  for(i=0;; i++){
    if(i >= NELEM(argv))
      return -1;
    if(fetchint(uargv+4*i, (int*)&uarg) < 0)
      return -1;
    if(uarg == 0){
      argv[i] = 0;
      break;
    }
    if(fetchstr(uarg, &argv[i]) < 0)
      return -1;
  }
  return exec(path, argv);
}

int
sys_pipe(void)
{
  int *fd;
  struct file *rf, *wf;
  int fd0, fd1;
  int addr;

  // start//////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].name = "pipe";
    system_calls[index_of_process_aln][index_of_syscall_ftm].counter++;

    int tcounter = system_calls[index_of_process_aln][index_of_syscall_ftm].time_index;
    cmostime(system_calls[index_of_process_aln][index_of_syscall_ftm].time[tcounter]);
    system_calls[index_of_process_aln][index_of_syscall_ftm].time_index ++;

  // end////////////////////////////////////////

  if((addr = argptr(0, (void*)&fd, 2*sizeof(fd[0]))) < 0)
    return -1;

  // start////////////////////////////////////////
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_name[0] = "int*";
  system_calls[index_of_process_aln][index_of_syscall_ftm].arg_value[0][tcounter] = addr;
  system_calls[index_of_process_aln][index_of_syscall_ftm].value_cnt ++;
  // end////////////////////////////////////////


  if(pipealloc(&rf, &wf) < 0)
    return -1;
  fd0 = -1;
  if((fd0 = fdalloc(rf)) < 0 || (fd1 = fdalloc(wf)) < 0){
    if(fd0 >= 0)
      myproc()->ofile[fd0] = 0;
    fileclose(rf);
    fileclose(wf);
    return -1;
  }
  fd[0] = fd0;
  fd[1] = fd1;
  return 0;
}
