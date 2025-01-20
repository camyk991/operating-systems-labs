#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/cpufreq.h>
#include <linux/tick.h>

static unsigned int log_interval = 5000;
module_param(log_interval, uint, 0644);


static struct timer_list cpu_timer;
static unsigned long long prev_idle_time = 0, prev_total_time = 0;

void log_cpu_usage(struct timer_list *t) {
    unsigned long long idle_time, total_time, busy_time, diff_idle, diff_total;

    idle_time = get_cpu_idle_time_us(0, NULL);
    
    total_time = jiffies_to_usecs(jiffies);

    busy_time = total_time - idle_time;
    diff_idle = idle_time - prev_idle_time;
    diff_total = total_time - prev_total_time;

    prev_idle_time = idle_time;
    prev_total_time = total_time;

    if (diff_total > 0) {
        pr_info("CPU Usage: %llu%%\n", ((diff_total - diff_idle) * 100) / diff_total);
    } else {
        pr_info("CPU Usage: Nie można obliczyć, brak zmian w czasie\n");
    }

    mod_timer(&cpu_timer, jiffies + msecs_to_jiffies(log_interval));
}

static int __init monitor_init(void) {
    pr_info("CPU Monitor: Start modułu\n");

    timer_setup(&cpu_timer, log_cpu_usage, 0);
    mod_timer(&cpu_timer, jiffies + msecs_to_jiffies(log_interval));

    return 0;
}

static void __exit monitor_exit(void) {
    pr_info("CPU Monitor: Zatrzymanie modułu\n");
    del_timer(&cpu_timer);
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CPU Usage Monitor");
MODULE_AUTHOR("kamyk");
