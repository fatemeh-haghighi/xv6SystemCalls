// Per-CPU state
struct cpu {
  uchar apicid;                // Local APIC ID
  struct context *scheduler;   // swtch() here to enter scheduler
  struct taskstate ts;         // Used by x86 to find stack for interrupt
  struct segdesc gdt[NSEGS];   // x86 global descriptor table
  volatile uint started;       // Has the CPU started?
  int ncli;                    // Depth of pushcli nesting.
  int intena;                  // Were interrupts enabled before pushcli?
  struct proc *proc;           // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };


struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

//Start////////////////////////////////////////////////////////////////////////////////////////////
struct argument{
  char *type;
  int int_value;
  char char_value[10];
};
struct syscall {
  char* name;
  int number;
  struct rtcdate* time[TSIZE];
  int time_index;
  int counter;
  int pid;

  int char_cnt;
  int value_cnt;


  char* arg_name[3];
  int arg_value[3][TSIZE];
  char arg_char[3][TSIZE][10];
};

struct syscall system_calls[NPROC][NSYS];

int index_of_syscall_ftm;
int index_of_process_aln;



struct info_for_log
{
  int pid;
  struct rtcdate* time;
  char* name;
  int is_killed;
};

struct info_for_log log_info[NLOG];
int total_counter;

// End ///////////////////////////////////////////////////////////////////////


// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)
};


// Process memory is laid out contiguously, low addresses first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap
