#include"model.h"

int main()
{
	num_events = 2;
	printf("Input mean interarrival, mean service and no. of delays required\n");
	scanf("%f %f %d", &mean_interarrival, &mean_service, &num_delays_required);
	printf("Single-erver queueing system\n\n");
	printf("Mean interarrival time%11.3f minutes\n\n", mean_interarrival);
	printf("Mean service time%16.3f minutes\n\n", mean_service);
	printf("Number of customers%14d\n\n", num_delays_required);
	initialize();
	while (num_custs_delayed < num_delays_required) {
		timing(); 
		update_time_avg_stats(); 
		switch (next_event_type) { 
		case 1: arrive(); break; 
		case 2: depart(); break;
		} 
	}
	/* invoke the report generator and end the simulation */
	report();
	return 0;
}



