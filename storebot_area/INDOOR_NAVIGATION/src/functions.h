#include "lpc_types.h"

void port_init (void);
void led_on (void);
void led_off (void);
void twos_comp_to_binary(int x);
int dec_to_bin(int dec);

void UART1_Init(int baudrate);
void UART1_Sendchar(char c);
char UART1_Getchar();
void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal );
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir );
uint32_t GPIOGetValue (uint32_t portNum, uint32_t bitPosi);

void delay_ms(unsigned int ms);
void print_hex_in_ascii_16(int x);
void print_hex_in_ascii(int x);
void print_dec_no_in_ascii(int y);
void print_string(char* s);
int binary_to_dec (int num);

void LSM303_init (void);
int magnetometer_reading(void);
//void magnetometer_reading(void);
//void accelerometer_reading(void);
double accelerometer_reading(void);
//unsigned char Read_I2C(unsigned char *Data,unsigned char Len);
//void GetXYZAcc(void);
int hexadecimalToDecimal(int hex);
int acc_by_1000(int dec);
void disp_acc(float y);
float motion_check(void);
float callibrate_acc(void);

void ultra_init(void);
long int getPulseWidth_usfront();
long int ultrasonic_front(void);
long int getPulseWidth_usright();
long int ultrasonic_right(void);
long int getPulseWidth_usleft();
long int ultrasonic_left(void);
void delay_us(int delay);
void hc020k_init(void);
int speed_encoder_start(void);
void motor_init(void);
int *forward(int xy[2]);
void roboticarm_init(void);
void updownleft (unsigned int ms);
void updownright (unsigned int ms);
void bottom (unsigned int ms);
void pick (unsigned int ms);
void front(void);
void stop(void);
void robot_turn(int turn);
void right(void);
void left(void);
void back(void);
void delay_ms_motor(unsigned int ms);
int ultra_leftright_check(int side);
