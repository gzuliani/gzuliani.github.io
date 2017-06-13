class CentronixPort {
    const int nStrobe_;
    const int data0_;
    const int data1_;
    const int data2_;
    const int data3_;
    const int data4_;
    const int data5_;
    const int data6_;
    const int data7_;
    const int nAck_;
    const int busy_;
public:
    CentronixPort(
        int nStrobe,
        int data0, int data1, int data2, int data3,
        int data4, int data5, int data6, int data7,
        int nAck,
        int busy)
            : nStrobe_(nStrobe)
            , data0_(data0), data1_(data1), data2_(data2), data3_(data3)
            , data4_(data4), data5_(data5), data6_(data6), data7_(data7)
            , nAck_(nAck)
            , busy_(busy) {
        pinMode(nStrobe, OUTPUT);
        pinMode(data0, OUTPUT);
        pinMode(data1, OUTPUT);
        pinMode(data2, OUTPUT);
        pinMode(data3, OUTPUT);
        pinMode(data4, OUTPUT);
        pinMode(data5, OUTPUT);
        pinMode(data6, OUTPUT);
        pinMode(data7, OUTPUT);
        pinMode(nAck, INPUT);
        pinMode(busy, INPUT);
    }
    void send_char(byte value) {
        apply_data(value);
        while(is_busy())
            ;
        assert_strobe();
        delayMicroseconds(1);
        deassert_strobe();
    }
    bool is_busy() {
        return digitalRead(busy_) == HIGH;
    }
private:
    void apply_data(byte value) {
        digitalWrite(data0_, bit_at(value, 0));
        digitalWrite(data1_, bit_at(value, 1));
        digitalWrite(data2_, bit_at(value, 2));
        digitalWrite(data3_, bit_at(value, 3));
        digitalWrite(data4_, bit_at(value, 4));
        digitalWrite(data5_, bit_at(value, 5));
        digitalWrite(data6_, bit_at(value, 6));
        digitalWrite(data7_, bit_at(value, 7));
    }
    void assert_strobe() {
        set_strobe(LOW);
    }
    void deassert_strobe() {
        set_strobe(HIGH);
    }
    void set_strobe(int level) {
        digitalWrite(nStrobe_, level);
    }
    int bit_at(byte value, int pos) {
        return value & (0x01 << pos) ? HIGH : LOW;
    }
};

CentronixPort port(
    2,   // nStrobe
    3,   // data0
    4,   // data1
    5,   // data2
    6,   // data3
    7,   // data4
    8,   // data5
    9,   // data6
    10,  // data7
    11,  // nAck
    12); // busy

void setup() {
    Serial.begin(9600);
}

void loop() {
    while (Serial.available())
        port.send_char(static_cast<byte>(Serial.read()));
}
