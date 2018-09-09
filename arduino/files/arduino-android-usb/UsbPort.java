package org.jolly_handball.sps_hc20;

import android.content.Context;
import android.hardware.usb.UsbConstants;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;

public class UsbPort {

    private static final int CDC_SET_LINE_CODING        = 0x20;
    private static final int CDC_REQTYPE_HOST2DEVICE    = 0x21;
    private static final int CDC_SET_CONTROL_LINE_STATE = 0x22;

    private static final int CDC_CONTROL_LINE_OFF       = 0x0000;
    private static final int CDC_CONTROL_LINE_ON        = 0x0003;

    private static final int USB_TIMEOUT                = 5000; // ms

    private UsbManager usbManager;
    private UsbDevice usbDevice;
    private UsbEndpoint usbInEndpoint;
    private UsbEndpoint usbOutEndpoint;
    private UsbInterface usbInterface;
    private UsbDeviceConnection usbConnection;

    public UsbPort(UsbManager manager) {
        usbManager = manager;
        reset();
    }

    public boolean isConnected() {
        return usbDevice != null;
    }

    public boolean connect(UsbDevice device) {

        if (attach(device) && configure())
            return true;

        reset();
        return false;
    }

    public void disconnect() {
        detach();
    }

    public int send(byte[] data, int timeout) {

        if (usbConnection == null)
            return 0;

        return usbConnection.bulkTransfer(
            usbOutEndpoint, data, data.length, timeout);
    }

    public int getSuggestedInputBufferSize() {
        return usbInEndpoint.getMaxPacketSize();
    }

    public int receive(byte[] buffer, int timeout) {

        if (usbConnection == null)
            return -1;

        return usbConnection.bulkTransfer(
            usbInEndpoint, buffer, buffer.length, timeout);
    }

    private boolean attach(UsbDevice device) {

        usbInEndpoint = null;
        usbOutEndpoint = null;

        // search for a suitable interface,
        // i.e. one that supports bidirectional bulk transfers
        for (int i = 0; i < device.getInterfaceCount(); i++) {

            UsbInterface iface = device.getInterface(i);
            int numOfEndpoints = iface.getEndpointCount();

            if (numOfEndpoints > 1) {
                for (int j = 0; j < numOfEndpoints; j++) {
                    if (iface.getEndpoint(j).getType() ==
                            UsbConstants.USB_ENDPOINT_XFER_BULK) {
                        if (iface.getEndpoint(j).getDirection()
                                == UsbConstants.USB_DIR_IN) {
                            usbInEndpoint = iface.getEndpoint(j);
                        } else if (iface.getEndpoint(j).getDirection()
                                == UsbConstants.USB_DIR_OUT) {
                            usbOutEndpoint = iface.getEndpoint(j);
                        }
                    }
                }

                if (usbInEndpoint != null && usbOutEndpoint != null)
                    usbInterface = iface;
            }
        }

        if (usbInterface == null)
            return false;

        usbDevice = device;
        usbConnection = usbManager.openDevice(usbDevice);

        if (usbConnection == null)
            return false;

        return usbConnection.claimInterface(usbInterface, true);
    }

    private boolean configure() {
        final byte[] portConfigData = new byte[] {
                (byte) 0x00, // baud rate: 57600
                (byte) 0xE1,
                (byte) 0x00,
                (byte) 0x00,
                (byte) 0x00, // 1 stop bit
                (byte) 0x00, // no parity
                (byte) 0x08  // 8 data bits
        };

        setControlCommand(
                CDC_SET_LINE_CODING,
                0,
                portConfigData);

        setControlCommand(
                CDC_SET_CONTROL_LINE_STATE,
                CDC_CONTROL_LINE_ON,
                null);

        return true;
    }

    private int setControlCommand(int request, int value, byte[] data) {
        return usbConnection.controlTransfer(
                CDC_REQTYPE_HOST2DEVICE,
                request,
                value,
                0,
                data,
                (data == null) ? 0 : data.length,
                USB_TIMEOUT);
    }

    private void detach() {

        if (usbConnection == null)
            return;

        setControlCommand(
                CDC_SET_CONTROL_LINE_STATE,
                CDC_CONTROL_LINE_OFF,
                null);

        usbConnection.releaseInterface(usbInterface);
        usbConnection.close();

        reset();
    }

    private void reset() {
        usbConnection = null;
        usbInEndpoint = null;
        usbOutEndpoint = null;
        usbInterface = null;
        usbDevice = null;
    }
}
