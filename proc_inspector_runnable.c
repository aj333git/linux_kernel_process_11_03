#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kernel Toolkit Pro");
MODULE_DESCRIPTION("Runnable Process Inspector via /proc");
MODULE_VERSION("1.0");

/* ================= PROCFS HANDLER ================= */
static int proc_show(struct seq_file *m, void *v)
{
    struct task_struct *task;

    seq_printf(m, "=== Runnable Processes ===\n");

    for_each_process(task) {
        if (task_state_to_char(task) == 'R') {
            seq_printf(m, "PID: %d\tName: %s\tState: %c\n",
                       task->pid, task->comm, task_state_to_char(task));
        }
    }

    return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_show, NULL);
}

static const struct proc_ops proc_fops = {
    .proc_open    = proc_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

/* ================= MODULE INIT / EXIT ================= */
static int __init inspector_init(void)
{
    if (!proc_create("proc_runnable_inspector", 0444, NULL, &proc_fops)) {
        pr_err("Failed to create /proc/proc_runnable_inspector\n");
        return -ENOMEM;
    }

    pr_info("Runnable Process Inspector loaded – read from /proc/proc_runnable_inspector\n");
    return 0;
}

static void __exit inspector_exit(void)
{
    remove_proc_entry("proc_runnable_inspector", NULL);
    pr_info("Runnable Process Inspector unloaded\n");
}

module_init(inspector_init);
module_exit(inspector_exit);
