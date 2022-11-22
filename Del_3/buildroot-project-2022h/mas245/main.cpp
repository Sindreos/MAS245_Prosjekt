// K. M. Knausgård / MAS234 2017
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <iostream>
#include <time.h>

int s;


// Can bus configuration.
const char *ifname = "can0";
int canSocketDescriptor;

// Task rate control.
const double periodicTaskRate = 2.0; // Run task at 0.5 Hz.
const int64_t periodicTaskDtNs = static_cast<int64_t>((1.0/0.5) * 1.0e9);


bool createCanSocket(int& socketDescriptor);
void sendCanMessage(int socketDescriptor);

void myPeriodicTask()
{
   static uint64_t ii(0U);
   ++ii;
   std::cout << "Tick " << ii << ".." << std::endl;
   sendCanMessage(canSocketDescriptor);
}



int main()
{
  std::cout << "Periodic tick example for MAS234 using clock_nanosleep.." << std::endl;

  // Set up CAN.
  if (!createCanSocket(canSocketDescriptor)) // Passed by reference; canSocketDescriptor is the output variable!
  {
     std::cout << "Could not create CAN socket" << std::endl;
     return 0;
  }

  bool running = true;
  while(running)
  {
    // USE CLOCK_MONOTONIC, and NOT NOT NOT CLOCK_REALTIME.
    // "Realtime" sounds tempting but is non-monotonic and actually a
    // wall-time-realtime, not usable for real time tasks.
    // For hard real time systems, use a RTOS or at least linux with real time extensions.
    // Note: This example has NO error checking (not good).

    // 1. Get current time stamp.
    struct timespec nextTimerDeadline;
    clock_gettime(CLOCK_MONOTONIC, &nextTimerDeadline);


    // 2. Run the periodic task.
    myPeriodicTask();


    // Add number of nanoseconds the task needs to sleep to the initial timestamp.
    // Could add logic here to check if the task used too much time.
    const int64_t nextTvNsec = static_cast<int64_t>(nextTimerDeadline.tv_nsec) + periodicTaskDtNs;
    std::cout << "  " << nextTvNsec << ", " << nextTimerDeadline.tv_nsec << std::endl;

    if (nextTvNsec >= 1000000000L)
    {
        // The timespec struct has one part for nanoseconds and one for seconds,
        // nsec part must be less than one second.
        nextTimerDeadline.tv_sec += static_cast<long int>(nextTvNsec / 1000000000L);
        nextTimerDeadline.tv_nsec = static_cast<long int>(nextTvNsec % 1000000000L);
    }

    // 3. Sleep until next deadline.
    // See http://man7.org/linux/man-pages/man2/clock_nanosleep.2.html for documentation.
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextTimerDeadline, NULL);
  }


  return 0;
}


bool createCanSocket(int& socketDescriptor)
{

  struct ifreq ifr;

  if((socketDescriptor = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
          perror("Error while opening CAN socket.");
          return false;
  }

  strcpy(ifr.ifr_name, ifname);
  ioctl(socketDescriptor, SIOCGIFINDEX, &ifr);

  struct sockaddr_can addr;
  addr.can_family  = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if(bind(socketDescriptor, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Error in socketcan bind.");
    return false;
  }

  return true;
}


void sendCanMessage(int socketDescriptor)
{
    struct can_frame frameread;
    struct can_frame frame;

    const int nbytes = read(socketDescriptor, &frameread, sizeof(struct can_frame));
if(frameread.data[0] == 0x02)
{
  frame.can_id  = 002;
  frame.can_dlc = 2;
  frame.data[0] = (0x02*0x02);
  const int bytesWritten = write(socketDescriptor, &frame, sizeof(struct can_frame));
  std::cout << "Message sent" << std::endl;
}
  // Should handle errors here...
}
