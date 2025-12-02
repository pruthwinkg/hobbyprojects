import sched
import time
import threading
import logging
from functools import partial

'''
    Common code to start a set of task or schedule tasks etc
'''
class VDTaskManager():
    def __init__(self, thread_funcs):
        self.thread_functions = thread_funcs        

    '''
        Usage:
            task_list = [
                (task1, delay, interval, priority, *args, **kwargs),
                (task2, delay, interval, priority, *args, **kwargs),
        ]
        self.schedule_device_tasks(task_list)
    '''
    def schedule_device_tasks(self, task_list, run_in_new_thread=False):
        if run_in_new_thread:
            # If run_in_new_thread is True, create a new thread for the scheduler
            scheduler_thread = threading.Thread(target=self.run_scheduler, args=(task_list,), name="Scheduler_Thread")
            scheduler_thread.start()
        else:
            # If run_in_new_thread is False, run the scheduler in the current thread
            self.run_scheduler(task_list)

    def run_scheduler(self, task_list):
        # Create a scheduler instance
        scheduler = sched.scheduler(time.time, time.sleep)

        def run_task(task_fn, interval, priority, *args, **kwargs):
            # Execute the task function with the provided arguments
            task_fn(*args, **kwargs)

            # If interval is specified and not None, reschedule the task
            if interval is not None:
                scheduler.enter(interval, priority, run_task, (partial(task_fn, self), interval, priority) + args + (kwargs,))      

         # Schedule each task in the task_list
        for task_info in task_list:
            task_fn, delay, interval, priority, *args, kwargs = task_info
            # Use functools.partial to pass self as the first argument
            scheduler.enter(delay, priority, run_task, (partial(task_fn, self), interval, priority) + tuple(args) + (kwargs,))

        scheduler.run()

    def start(self):
        # Create threads for each thread function
        threads = [threading.Thread(target=func, args=args, name=f"{func.__name__}_Thread") for func, args in self.thread_functions]

        # Start all threads
        for thread in threads:
            thread.start()

        # Wait for all threads to finish
        for thread in threads:
            thread.join()