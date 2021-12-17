#include <stdlib.h>
#include "ros/ros.h"
#include "second_assignment/Velocity.h"
#include "std_srvs/Empty.h"
using namespace std;

//declaring clients for change_velocity request
//and for reset position request
ros::ServiceClient client1;
ros::ServiceClient client2;

int main(int argc, char **argv)
{
    //initialization of the velocity node
	ros::init(argc, argv, "change_velocity_node");
	ros::NodeHandle nh;

    //defining clients for change_velocity request
    //and for reset position request
	client1 = nh.serviceClient<second_assignment::Velocity>("/velocity");
    client2 = nh.serviceClient<std_srvs::Empty>("/reset_positions");
    //initializing variables: one for value to pass to the server
    //and the other one for case handling 
    float val;
    char choice;

    second_assignment::Velocity vel_srv;
    std_srvs::Empty res_pos;

    //while loop for contantly asking the user to insert a command 
    while(1)
    {
        cout << "\nRobot controller, press:" <<endl;
        cout << "w) if you want to increase linear velocity " <<endl;
        cout << "s) if you want to decrease linear velocity" <<endl;
        cout << "a) if you want to increase angular velocity " <<endl;
        cout << "d) if you want to decrease angular velocity " <<endl;
        cout << "r) if you want to reset the position " <<endl;
        cout << "q) if you want to quit the program " <<endl;
        cout << "command chosen: ";
        //getting the user choice from the keyboard
        cin >> choice;
        //choice handling:
        //- choose A/a to increase velocity 
        //- choose D/d to decrease velocity 
        //- choose R/r to reset robot position
        //- choose Q/q to quit the program
        switch(choice)
        {
            case 'A':
            case 'a':
                //cout << "\nVelocity has been increased"<<endl;
                val = 1.0;
                vel_srv.request.req_change_velocity = val;
                client1.waitForExistence();
                client1.call(vel_srv);
                if (vel_srv.response.succeded)
                {
                    cout<<"Velocity has been increased: "<<endl;
                    cout<<"linear velocity: "<<vel_srv.response.resp_change_velocityx<< "  " <<"angular velocity: "<<vel_srv.response.resp_change_velocityz<<endl;
                }
                else
                {
                    cout<<"Maximum velocity reached"<<endl;
                }
                break;
            case 'D':
            case 'd':
                //cout<<"\nVelocity has been decreased"<<endl;
                val = 2.0;
                vel_srv.request.req_change_velocity = val;
                client1.waitForExistence();
                client1.call(vel_srv);
                if (vel_srv.response.succeded)
                {
                    cout<<"Velocity has been decreased: "<<endl;
                    cout<<"linear velocity: "<<vel_srv.response.resp_change_velocityx<< "  " <<"angular velocity: "<<vel_srv.response.resp_change_velocityz<<endl;
                }
                else
                {
                    cout<<"Minimum velocity reached"<<endl;
                }
                break;
            case 'R':
            case 'r':
                cout << "\nThe position has been resetted"<<endl;
                client2.waitForExistence();
                client2.call(res_pos);
                break;
            case 'Q':
            case 'q':
                cout << "\nProgram exiting..."<<endl;
                return 1;
                break;
            default:
                cout<<"\nInvalid input, retry\n"<<endl;
                break;
        }
    }
    return 0;
}