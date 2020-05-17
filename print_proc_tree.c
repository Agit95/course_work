#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/list.h>


struct list_head* pList;


asmlinkage long sys_print_proc_tree(int pid)
{
    read_lock(&tasklist_lock);
    struct task_struct* pTask = pid_task(find_get_pid(pid), PIDTYPE_PID);
    //
    /// Invalid PID
    if (!pTask) return 1;
    //
    /// print process BSD tree
    //
    print_tree_node(pTask, 0);
	read_unlock(&tasklist_lock);
    //
    return 0;
}

void print_tree_node(struct task_struct* pTask, int root_depth)
{
    if (!pTask) return;
    //
    /// print |- ProcName and PID
    for (int i = 0; i < root; ++i) 
    {
        if (0 == i % 2 || 0 == i)
            printk("%c", 179);
        else
            printk(" ");
    }

    printk("%c%c%s PID ->%d\n", 195, 196, pTask->comm, (long)get_pid_nr(pTask));
    list_for_each(pList, &pTask->children)
    {
        print_tree_node(list_entry(pList, struct task_struct, sibling), root_depth + 2)
    }
}