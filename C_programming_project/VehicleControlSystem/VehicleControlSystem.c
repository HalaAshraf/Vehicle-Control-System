/*
 * VehicleControlSystem.c
 *
 *
 *      Author: Hala Ashraf Kamel
 */
#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1

enum state{
	ON,OFF
};

struct vehicle_state{

	enum state engine_state;
	enum state AC;
	enum state engine_temp_controller;

	int speed;
	int room_temp;
	int engine_temp;

};


//Declare structure
struct vehicle_state vehicle ={OFF,OFF,OFF,60,25,130};


// Function prototypes
char main_menu(void); // Ask User what to do

char turnoff_engine(void); // Turn off vehicle engine

char set_menu(void); // Show sensor set menu

void set_trafficlight(void); // Change vehicle speed according to traffic light

void set_roomtemp(int *ptr_temp); // Temperature sensor (AC control)

void set_enginetemp(int *ptr_temp); // Engine temperature sensor

const char* getstatename(enum state st); // Return OFF/ON instead of 0/1


int main(void){

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// Ask user
	char main_in = main_menu();

	while(main_in!='c'){

		// Turn on vehicle engine
		if(main_in == 'a'){

			vehicle.engine_state=ON;
			// Show Sensor set menu
			char set_in = set_menu();

			// Turn off engine
			if(set_in =='a'){
				main_in='b';
				continue;
			}

			// Set traffic light colour
			else if(set_in=='b'){
				set_trafficlight();
			}

			// Set room temperature
			else if(set_in=='c'){

				printf("Enter room temperature\n");
				scanf(" %d",&vehicle.room_temp);
				set_roomtemp(&vehicle.room_temp);

			}

			// Set the engine temperature
			else if(set_in=='d'){
#if WITH_ENGINE_TEMP_CONTROLLER
				printf("Enter engine temperature\n");
				scanf(" %d",&vehicle.engine_temp);

				set_enginetemp(&vehicle.engine_temp);

#endif

			}

			// When vehicle speed = 30 km/hr

			if (vehicle.speed==30){

				if(vehicle.AC==OFF){
					vehicle.room_temp = ((vehicle.room_temp)*5/4)+1;
					vehicle.AC=ON;

				}

#if WITH_ENGINE_TEMP_CONTROLLER

				if(vehicle.engine_temp_controller==OFF){
					vehicle.engine_temp = ((vehicle.engine_temp)*5/4)+1;
					vehicle.engine_temp_controller=ON;

				}

#endif
			}

			// Show vehicle state

			printf("Engine: %s\n",getstatename(vehicle.engine_state));
			printf("AC: %s\n",getstatename(vehicle.AC));
			printf("Vehicle Speed: %d km/hr\n",vehicle.speed);
			printf("Room Temperature: %d\n",vehicle.room_temp);
#if WITH_ENGINE_TEMP_CONTROLLER
			printf("Engine Temperature Controller State: %s\n",getstatename(vehicle.engine_temp_controller));
			printf("Engine Temperature: %d\n",vehicle.engine_temp);
#endif
		}

		// Turn off vehicle engine
		else if(main_in =='b'){
			main_in=turnoff_engine();
		}
	}

	// Quit the system
	printf("Quit the system\n");
	return 0;
}

// Functions

char turnoff_engine(void){

	vehicle.engine_state =OFF;
	printf("Turn off the vehicle engine\n\n");
	char input =main_menu();
	return input;
}

// Ask user what to do
char main_menu(void){
	char input;
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf(" %c",&input);
	return input;
}

// Show sensor set menu
char set_menu(void){
	char input;
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");

#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature\n\n");
#endif

	scanf(" %c",&input);
	return input;
}


// Ask user for traffic colour and change vehicle speed accordingly
void set_trafficlight(void){

	char light;
	printf("Enter traffic light\n");
	scanf(" %c",&light);

	switch(light){
	case 'g':
		vehicle.speed=100;
		break;
	case 'o':
		vehicle.speed = 30;
		break;
	case 'r':
		vehicle.speed=0;
		break;
	default:
		printf("Enter g or o or r\n");

	}
}


// Control AC state according to room temperature
void set_roomtemp(int *ptr_temp){

	if(*ptr_temp<10 || *ptr_temp>30){
		vehicle.AC = ON;
		*ptr_temp =20;
	}
	else{
		vehicle.AC=OFF;
	}

}


void set_enginetemp(int *ptr_temp){

	if(*ptr_temp<100 || *ptr_temp>150){
		vehicle.engine_temp_controller = ON;
		*ptr_temp=125;
	}
	else{
		vehicle.engine_temp_controller = OFF;
	}
}

// Get name of enum
const char* getstatename(enum state st){
	switch(st){
	case OFF: return "OFF";
	case ON: return "ON";
	default: return "OFF";
	}
}

