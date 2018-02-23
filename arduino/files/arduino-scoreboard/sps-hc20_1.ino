const int TX_PIN = 2;

const int BIT_WIDTH = 14; // microseconds (us)
                          // should be 20, but we must take into account
                          // the digitalWrite function execution time

const int TX_PERIOD = 15; // milliseconds (ms)

const int BUFFER_SIZE = 12;
uint8_t tx_buffer[BUFFER_SIZE]; // data to be transmitted to the SPS HC20

unsigned long last_tx_time = 0;

void setup()
{
    pinMode(TX_PIN, OUTPUT);
    digitalWrite(TX_PIN, HIGH);

    tx_buffer[ 0] = 0x3f; // 0
    tx_buffer[ 1] = 0x00; //
    tx_buffer[ 2] = 0x00; //
    tx_buffer[ 3] = 0x3f; // 0
    tx_buffer[ 4] = 0x06; // 1
    tx_buffer[ 5] = 0xfd; // 6.
    tx_buffer[ 6] = 0x6d; // 5
    tx_buffer[ 7] = 0x6f; // 9
    tx_buffer[ 8] = 0x00; //
    tx_buffer[ 9] = 0x00; //
    tx_buffer[10] = 0x3f; // 0
    tx_buffer[11] = 0x3f; // 0
}

void transmit_bit(int value)
{
    if (value)
        digitalWrite(TX_PIN, HIGH);
    else
        digitalWrite(TX_PIN, LOW);

    delayMicroseconds(BIT_WIDTH);
}

void transmit_byte(uint8_t value)
{
    for (int i = 0; i < 8; i++)
        transmit_bit(value & (0x80 >> i));
}

void transmit_buffer(const uint8_t* buffer, int size)
{
    for (int i = 0; i < size; i++)
        transmit_byte(buffer[i]);
}

void loop()
{
    unsigned long curr_time = millis();

    if (curr_time - last_tx_time >= TX_PERIOD) {
        transmit_buffer(tx_buffer, BUFFER_SIZE);
        digitalWrite(TX_PIN, HIGH);
        last_tx_time = curr_time;
    }
}
