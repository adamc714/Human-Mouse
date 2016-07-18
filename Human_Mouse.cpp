 ConsoleApplication1.cpp  Defines the entry point for the console application.


#define WINVER 0x0500
#include stdafx.h
#include windows.h
#include iostream
#include NeuronDataReader.h
#include DataType.h

struct point {
	float x;
	float y;
};

static void __stdcall bvhFrameDataReceived(void customedObj, SOCKET_REF sender, BvhDataHeader header, float data)
{
	cast customedObj to the point type
	point position = (point)customedObj;

	six times the index of the desired bone for BVH data
	int index = 0;
	index = 616;

	offset in case data has a reference
	if (header-WithReference)
	{
		index += 6;
	}

	get x and y position
	position-x = data[index];
	position-y = data[index + 1];

	review data being received
	for (int i = 0; i  200; i += 3)
		stdcout  i     data[i]      
		 i + 1     data[i + 1]      
		 i + 2     data[i + 2]  nn;


	return;
}

static void __stdcall CalcFrameDataReceive(void customObje, SOCKET_REF sender, CalcDataHeader header, float data)
{
	point position = (point)customObje;

	sixteen times the index of the desired bone for calculation data
	int index = 0;
	index = 16  10;

	get x and y position
	position-x = data[index + 3];
	position-y = data[index + 4];

	review data being received
	for (int i = 0; i  200; i += 3)
		stdcout  i     data[i]       
		           i+1     data[i+1]      
		           i+2     data[i+2]  nn;


	return;
}

int main()
{
	register data socket
	SOCKET_REF UDPReference;
	UDPReference = BRStartUDPServiceAt(7001);
	SocketStatus status = BRGetSocketStatus(UDPReference);
	stdcout  Running   status  n;

	position is the custome object used for data transfer
	point position = new point;
	position-x = 0;
	position-y = 0;
	
	NOTE I think this function should register bvhFrameDataReceived
	      to be called, but the event that should call
	      bvhFrameDataReceived never occurs. This is at the center
	      of our problem. 
	BRRegisterFrameDataCallback(position, bvhFrameDataReceived);

	mouse movment setup
	int x = 400;
	int y = 400;
	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dx = x(65536  GetSystemMetrics(SM_CXSCREEN));x being coord in pixels
	ip.mi.dy = y(65536  GetSystemMetrics(SM_CYSCREEN));y being coord in pixels
	ip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE  MOUSEEVENTF_MOVE;

	
	attempt to use data to move mouse
	for (int i = 0; i  5; i++)
		{
			 Pause and place cursor
			Sleep(5000  5);
			SendInput(1, &ip, sizeof(ip)); this function actually moves the mouse
			
			x += (position-x  10000);
			y += (position-y  10000);
			BRRegisterFrameDataCallback(&position, bvhFrameDataReceived);
			stdcout  X   position-x  nY   position-y  nn;
			

			ip.mi.dx = x(65536  GetSystemMetrics(SM_CXSCREEN));x coord in pixels
			ip.mi.dy = y(65536  GetSystemMetrics(SM_CYSCREEN));y coord in pixels
		}
	
	
	demonstration of mouse movement without received BVH data
	
	int scale = 30;
	for (int j = scale; j  1000; j += 2scale)
	{

		LEFT
		for (int i = 1; i  j; i++)
		{
			Sleep(1);
			x += 1;
			ip.mi.dx = x(65536  GetSystemMetrics(SM_CXSCREEN));x being coord in pixels
			SendInput(1, &ip, sizeof(ip));
		}

		DOWN
		for (int i = 1; i  j; i++)
		{
			Sleep(1);
			y += 1;
			ip.mi.dy = y(65536  GetSystemMetrics(SM_CYSCREEN));y being coord in pixels
			SendInput(1, &ip, sizeof(ip));
		}

		RIGHT
		for (int i = 1; i  j+scale; i++)
		{
			Sleep(1);
			x -= 1;
			ip.mi.dx = x(65536  GetSystemMetrics(SM_CXSCREEN));x being coord in pixels
			SendInput(1, &ip, sizeof(ip));
		}

		UP
		for (int i = 1; i  j+scale; i++)
		{
			Sleep(1);
			y -= 1;
			ip.mi.dy = y(65536  GetSystemMetrics(SM_CYSCREEN));y being coord in pixels
			SendInput(1, &ip, sizeof(ip));
		}

	}
	

	close data socket
	BRCloseSocket(UDPReference);
	 Exit normally
	return 0;
}