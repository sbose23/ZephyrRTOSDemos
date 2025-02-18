/* main.c - Priority Based Preemptive Scheduling Demo */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACK_SIZE 1024
#define NUM_ITERATIONS 3
#define OBSTACLE_DELAY K_MSEC(80) // Obstacle task begins at 80 ms

#define OBSTACLE_TASK_PRIORITY 1
#define NAVIGATION_TASK_PRIORITY 3
#define TELEMETRY_TASK_PRIORITY 3

#define OBSTACLE_TASK_DURATION 250
#define NAVIGATION_TASK_DURATION 200
#define TELEMETRY_TASK_DURATION 50

K_THREAD_STACK_DEFINE(obstacle_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(navigation_stack, STACK_SIZE);
K_THREAD_STACK_DEFINE(telemetry_stack, STACK_SIZE);

struct k_thread obstacle_thread, navigation_thread, telemetry_thread, monitor_thread;

void print_message_with_time(const char *message) {
	printk("{Time: %lld ms} %s\n", k_uptime_get(), message);
}

void obstacle_detection(void *arg1, void *arg2, void *arg3) {
    for (int i = 1; i <= 3; i++) {

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

void telemetry_logging(void *arg1, void *arg2, void *arg3) {
    for (int i = 1; i <= NUM_ITERATIONS; i++) {

        print_message_with_time("[Telemetry Logging]: Collecting sensor data 📊");
		k_busy_wait(TELEMETRY_TASK_DURATION * 1000);
		print_message_with_time("Finished Telemetry Logging Task 📊");
    }
}

void main(void) {
    printk("\n*** 🚗 Autonomous Car Task Scheduling Demo 🚗***\n");

	k_thread_create(&telemetry_thread, telemetry_stack, STACK_SIZE,
					telemetry_logging, NULL, NULL, NULL,
					TELEMETRY_TASK_PRIORITY, 0, K_NO_WAIT);

    k_thread_create(&navigation_thread, navigation_stack, STACK_SIZE,
                    navigation_system, NULL, NULL, NULL,
                    NAVIGATION_TASK_PRIORITY, 0, K_NO_WAIT);

    k_thread_create(&obstacle_thread, obstacle_stack, STACK_SIZE,
                    obstacle_detection, NULL, NULL, NULL,
                    OBSTACLE_TASK_PRIORITY, 0, OBSTACLE_DELAY);
}