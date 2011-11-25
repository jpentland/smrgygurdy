#include "Pedal.h"
#include "Controller.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

Pedal::Pedal(Controller *controller){

  this->controller = controller; 
  ret = hid_init();
  hid = 0x0;

}

void Pedal::run(){
  int flag;
  signed short svalue;
  int temp;
  __u8 channel, gain;
  int interface, i;
  double finalVal=0;
  double val[] = {0.6, 0.64, 0.68, 0.72, 0.76, 0.8, 0.84, 0.88, 0.92, 0.96, 1.0, 1.04, 1.08, 1.12, 1.16, 1.20, 1.24, 1.28, 1.32, 1.36, 1.40, 1.44, 1.48, 1.52, 1.56, 1.60};
  
  while (ret != HID_RET_SUCCESS) {
        sleep(1000);
  }

  while ((interface = PMD_Find_Interface(&hid, 0, MINILAB1008_PID)) < 0) {
        sleep(1000);
  } 
  temp = 0;
  channel = (__u8) temp;
  gain = SE_10_00V;
  flag = fcntl(fileno(stdin), F_GETFL);
  fcntl(0, F_SETFL, flag | O_NONBLOCK);
  do {
	  sleep(10);
    svalue = usbAIn_miniLAB1008(hid, channel, gain);
	/* Changed this number from 25 to 200 */
    i = ((volts_LS(gain, svalue)/5)*200); 
    if (finalVal != val[i]){ 
      finalVal = val[i];
      controller->speedChange(finalVal);
    }
  } while (1);
}
