#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#pragma warning(disable:4996)
#define BUSY 1
#define Q_LIMIT 50
#define IDLE 0 //����
int
num_events,
num_delays_required,//Number of customers
num_custs_delayed,
next_event_type,//��һ���¼�״̬
num_in_q,
server_status;
float
mean_interarrival,//Mean interarrival time
mean_service,//Mean service time
current_time,
time_last_event,
total_of_delays,
area_num_in_q, area_server_status,
time_next_event[2],
time_arrival[50];
float expon(float mean_interarrival) {
	return mean_interarrival;
}
void initialize(void) { /* initialise the simulation clock */
	current_time = 0.0; /* initialise the state variables */
	server_status = IDLE;//������״̬
	num_in_q = 0;			//��������
	time_last_event = 0.0; /* initialise the statistical counters */
	num_custs_delayed = 0;//�ȴ��˿���
	total_of_delays = 0.0;//�ܵȴ�ʱ��
	area_num_in_q = 0.0;//�������
	area_server_status = 0.0;//������״̬���
	time_next_event[1] = current_time + expon(mean_interarrival);
	time_next_event[2] = 1.0e+30;
}

void timing(void)
{
	int i;
	float min_time_next_event = 1.0e+29; 
	next_event_type = 0; /* determine the event type of the next event to occur */
	for (i = 1; i <= num_events; ++i) {
		if (time_next_event[i] < min_time_next_event) {
			min_time_next_event = time_next_event[i];
			next_event_type = i;
		}
	} /* check to see whether the event list is empty */
	if (next_event_type == 0) { /* the event list is empty, so stop the simulation */
		printf("\nEvent list empty at time %f", current_time);
		exit(1);
	} /* the list is not empty, so advance the simulation clock */
	current_time = min_time_next_event;
}
void depart() {
	int i;
	float delay;
	if (num_in_q == 0) {
		//�ն��У�ʹ����������
		server_status = IDLE;
		time_next_event[2] = 1.0e+30;
		}
	else
	{
		//�����뿪
		--num_in_q;
		//���㽫Ҫ��ʼ����Ĺ˿͵ĵȴ�ʱ��
		delay = current_time - time_arrival[1];
		total_of_delays += delay;
		//���ӵȴ��Ĺ˿���Ŀ
		++num_custs_delayed;
		printf("Depart:%d person is served and leaving\n", num_custs_delayed);
	}
}
void update_time_avg_stats() {

}
void report(){

}
void arrive(void) {
	float delay;
	//schedule next arrival
	time_next_event[1] = current_time + expon(mean_interarrival);
	//check to see whether server is busy
	if (server_status == BUSY) {
		//������æµ�����Ӷ����Ŷӹ˿���
		++num_in_q;
		//check to see whether an overflow condition exists
		if (num_in_q > Q_LIMIT) {
			//���������ֹͣ����
			printf("\nOverflow of the array time_arrival at time %f\n", current_time);
			exit(2);
			/*there is still room in the queue,so store the time of arrival of the 
			arriving customer at the (new) end of time_arrival*/
			time_arrival[num_in_q] = current_time;
		}
	}
}