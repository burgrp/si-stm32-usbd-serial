namespace usbdSerial
{

	class UsbSimpleSerialConfiguration : public usbd::UsbConfiguration{
		public :
		usbdSerial::UartBridgeCommInterface commInterface;
		usbdSerial::UartBridgeDataInterface dataInterface;

		void init()
		{
			commInterface.dataInterface = &dataInterface;
			dataInterface.commInterface = &commInterface;
			interfaces[0] = &commInterface;
			interfaces[1] = &dataInterface;
			dataInterface.interfaceNumber = 1;
			UsbConfiguration::init();
		}};

	class UsbSimpleSerialDevice : public usbd::UsbDevice, public usbdSerial::ComPort{
		public :

		UsbSimpleSerialConfiguration configuration;

		void init()
		{
			configuration.commInterface.setPort(this);
			configurations[0] = &configuration;
			UsbDevice::init();
		}

		void handleNonStandardRequest(usbd::SetupPacket* packet, int counter, unsigned char* data, int len)
		{
			configuration.commInterface.handleControlRequest(packet, counter, data, len, &defaultEndpoint);
		}

		void setLineCoding(int bitRate, int charFormat, int parity, int dataBits)
		{
		}

		void getLineCoding(int* bitRate, int* charFormat, int* parity, int* dataBits)
		{
		}

		void setControlLineState(int dtr, int rts)
		{
		}

		void sendDataOut(unsigned char* data, int len)
		{
			dataSentOut();
		}};

}