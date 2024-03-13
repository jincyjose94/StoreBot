#define size_array 40

void port_init (void);
void led_on (void);
void led_off (void);
void twos_comp_to_binary(int x);
int dec_to_bin(int dec);

void UART1_Init(int baudrate);
void UART1_Sendchar(char c);
char UART1_Getchar();

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
void ultrasonic_front(void);
long int getPulseWidth_usright();
void ultrasonic_right(void);
long int getPulseWidth_usleft();
void ultrasonic_left(void);
void delay_us(int delay);
char obst_to_grid(int x[100],int y[100],int d_x, int d_y);

