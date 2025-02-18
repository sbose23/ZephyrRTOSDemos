/* main.c - Priority Based Preemptive Scheduling Demo */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACK_SIZE 1024
#define NUM_ITERATIONS 3
#define OBSTACLE_DELAY K_MSEC(80) // Obstacle task begins at 80 ms

#define OBSTACLE_TASK_PRIORITY 1
#define AUDIO_TASK_PRIORITY 3
#define NAVIGATION_TASK_PRIORITY 3

#define OBSTACLE_TASK_DURATION 250
#define AUDIO_TASK_DURATION 50
#define NAVIGATION_TASK_DURATION 200

K_THREAD_STACK_DEFINE(obstacle_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(audio_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(navigation_stack, STACK_SIZE);

struct k_thread obstacle_thread, navigation_thread, audio_thread, monitor_thread;

void print_message_with_time(const char *message) {
	printk("{Time: %lld ms} %s\n", k_uptime_get(), message);
}

void obstacle_detection(void *arg1, void *arg2, void *arg3) {
    for (int i = 1; i <= NUM_ITERATIONS; i++) {

        print_message_with_time("[Obstacle Detection]: Starting Object Detection Task 🚨");
		k_busy_wait(OBSTACLE_TASK_DURATION * 1000);
		print_message_with_time("Finished Obstacle Detection Task 🚨");
    }
}

void navigation_system(void *arg1, void *arg2, void *arg3) {

    for (int i = 1; i <= NUM_ITERATIONS; i++) {

		print_message_with_time("[Navigation System]: Starting Navigation System Task 🗺️");
		k_busy_wait(NAVIGATION_TASK_DURATION * 1000);
		print_message_with_time("Finished Navigation System Task 🗺️");
    }
}

void audio_logging(void *arg1, void *arg2, void *arg3) {

    for (int i = 1; i <= NUM_ITERATIONS; i++) {

        print_message_with_time("[Audio Processing]: Processing audio 🥁");
		k_busy_wait(AUDIO_TASK_DURATION * 1000);
		print_message_with_time("Finished Audio Processing Task 🥁");
    }
}

void main(void) {
    printk("\n*** 🚗 Autonomous Car Task Scheduling Demo 🚗 ***\n");

    k_thread_create(&obstacle_thread, obstacle_stack, STACK_SIZE, obstacle_detection, NULL, NULL, NULL, OBSTACLE_TASK_PRIORITY, 0, OBSTACLE_DELAY);

    k_thread_create(&audio_thread, audio_stack, STACK_SIZE, audio_logging, NULL, NULL, NULL, AUDIO_TASK_PRIORITY, 0, K_NO_WAIT);
    k_thread_create(&navigation_thread, navigation_stack, STACK_SIZE, navigation_system, NULL, NULL, NULL, NAVIGATION_TASK_PRIORITY, 0, K_NO_WAIT);

    // Changing the order makes navigation go first

    //k_thread_create(&navigation_thread, navigation_stack, STACK_SIZE, navigation_system, NULL, NULL, NULL, NAVIGATION_TASK_PRIORITY, 0, K_NO_WAIT);
	//k_thread_create(&audio_thread, audio_stack, STACK_SIZE, audio_logging, NULL, NULL, NULL, AUDIO_TASK_PRIORITY, 0, K_NO_WAIT);

    // Set the deadlines for the threads to reverse the order back to the original

    //k_thread_deadline_set(&navigation_thread, 500);
    //k_thread_deadline_set(&audio_thread, 100);

}