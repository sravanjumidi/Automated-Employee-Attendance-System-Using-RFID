/// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

int main()
{

	/*Start og Program*/

	int i,j,f;
	char id[13],time[30];
	//123456789111 01:01:12 01/12/2024


	// Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
	while(1)
	{
		int serial_port = open("/dev/ttyUSB0", O_RDWR);

		// Create new termios struct, we call it 'tty' for convention
		struct termios tty;

		// Read in existing settings, and handle any error
		if(tcgetattr(serial_port, &tty) != 0) {
			printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
		tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
		tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
		tty.c_cflag |= CS8; // 8 bits per byte (most common)
		tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
		tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

		tty.c_lflag &= ~ICANON;
		tty.c_lflag &= ~ECHO; // Disable echo
		tty.c_lflag &= ~ECHOE; // Disable erasure
		tty.c_lflag &= ~ECHONL; // Disable new-line echo
		tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
		tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
		tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

		tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
		tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
		// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)  // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
		// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

		tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
		tty.c_cc[VMIN] = 33;

		// Set in/out baud rate to be 9600
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);

		// Save tty settings, also checking for error
		if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
			printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
			return 1;
		}

		// Write to serial port
		// unsigned char msg[50] ={'v','e','c','t','o','r','\n'};
		// write(serial_port, msg, sizeof(msg));
		// int i;
		// usleep(100);
		// Allocate memory for read buffer, set size according to your needs
		char read_buf [256];

		// Normally you wouldn't do this memset() call, but since we will just receive
		// ASCII data for this example, we'll set everything to 0 so we can
		// call printf() easily.
		memset(&read_buf, '\0', sizeof(read_buf));

		// Read bytes. The behaviour of read() (e.g. does it block?,
		// how long does it block for?) depends on the configuration
		// settings above, specifically VMIN and VTIME
		int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

		// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
		if (num_bytes < 0) {
			printf("Error reading: %s", strerror(errno));
			return 1;

		}


		printf("%s\n",read_buf);
		// close(serial_port);


		for(i=0;i<12;i++)
			id[i]=read_buf[i];           //RFID number
		id[i]='\0';
               //  printf("%s ",id);

			for(j=13;j<30;j++)
			time[j-13]=read_buf[j];                     // Remaining date and time
			time[j-13]='\0';
	//	for(j=13,i=0;j<30;j++,i++)
	//		time[i]=read_buf[j];
	//	time[i]='\0';
		//	time[j-13]='\0';
				printf("%s\n",time);

		int c=0,k;
		char s1[50],s2[50],name[20];

		FILE *fp=fopen("data","r");
		while(fgets(s1,50,fp))
		{     
			if(strstr(s1,id))
			{   
                               f=1;
				for(k=13;s1[k]!='\n';k++)
					name[k-13]=s1[k];
				name[k-13]=0;
				printf("%s\n",name);

				FILE *fq=fopen("log_file","a+");
				while(fscanf(fq,"%s",s2)!=-1)
				{  

					if(strcmp(s2,name)==0)
						c++;
				}
				if(c%2==0)
				{
					fprintf(fq,"ID= %s NAME= %s IN-TIME %s \n",id,name,time);
					fclose(fq);
					break;
				}
				else
				{
					fprintf(fq,"ID= %s NAME= %s OUT-TIME %s \n",id,name,time);
					fclose(fq);
					break;
				}
				//	rewind(fq);
}
}
/*if(f==0)
{
                                printf("CARD NOT FOUND\r\nPLEASE ENTER THE NEW EMPLOYEE NAME\n");
				printf("enetr the name for the rfid\n");
				scanf("%s",name);
				FILE *file=fopen("database","a+");
				fprintf(file,"%s %s\n",id,name);
				fclose(file);
				FILE *log_file=fopen("log_file","a+");
				fprintf(log_file,"%s %s %s\n",id,name,time);
				fclose(log_file);
				printf("new rfid and name added in database and log_file\n");

		}*/
		fclose(fp);
	}

}


