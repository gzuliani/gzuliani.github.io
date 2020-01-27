function mode_A() {
    if (motor_state == 1) {
        forward()
        prev_motor_state = motor_state
    }
    if (motor_state == 2) {
        backward()
        prev_motor_state = motor_state
    }
    if (motor_state == 4) {
        turn_left()
        prev_motor_state = motor_state
    }
    if (motor_state == 8) {
        turn_right()
        prev_motor_state = motor_state
    }
    if (motor_state == 0) {
        if (prev_motor_state != motor_state) {
            stop()
            prev_motor_state = motor_state
        }
    }
}
function mode_B() {
    distance = maqueen.Ultrasonic(PingUnit.Centimeters)
    if (distance > 40 || distance == 0) {
        forward()
    } else {
        if (distance > 15) {
            if (Math.randomRange(1, 2) == 1) {
                turn_left()
            } else {
                turn_right()
            }
            basic.pause(300)
        } else {
            if (Math.randomRange(1, 2) == 1) {
                backward_and_turn_left()
            } else {
                backward_and_turn_right()
            }
            basic.pause(800)
        }
    }
    basic.pause(100)
}
function mode_C() {
    if (speed > 230) {
        speed = 230
    }
    tracking_left = maqueen.readPatrol(maqueen.Patrol.PatrolLeft)
    tracking_right = maqueen.readPatrol(maqueen.Patrol.PatrolRight)
    if (tracking_left == 0 && tracking_right == 0) {
        tracking_flag = 10
        forward()
    }
    if (tracking_left == 0 && tracking_right == 1) {
        if (tracking_flag > 1) {
            tracking_flag += -1
            forward()
        }
    }
    if (tracking_left == 1 && tracking_right == 0) {
        if (tracking_flag < 20) {
            tracking_flag += 1
            forward()
        }
    }
    if (tracking_left == 1 && tracking_right == 1) {
        if (tracking_flag < 10) {
            turn_left()
        }
        if (tracking_flag == 10) {
            backward()
        }
        if (tracking_flag > 10) {
            turn_right()
        }
    }
}
maqueen.IR_callbackUser(function (message) {
    if (message == 69) {
        speed = 200
        mode = 0
        stop()
        music.playTone(294, music.beat(BeatFraction.Whole))
        rgb_strip.showColor(neopixel.colors(NeoPixelColors.White))
    }
    if (message == 70) {
        speed = 200
        mode = 1
        stop()
        music.playTone(330, music.beat(BeatFraction.Whole))
        rgb_strip.showColor(neopixel.colors(NeoPixelColors.Green))
    }
    if (message == 71) {
        speed = 120
        mode = 2
        stop()
        music.playTone(349, music.beat(BeatFraction.Whole))
        rgb_strip.showColor(neopixel.colors(NeoPixelColors.Blue))
    }
    if (message == 64) {
        motor_state = 1
        rgb_strip.showColor(neopixel.colors(NeoPixelColors.Yellow))
    }
    if (message == 25) {
        motor_state = 2
        rgb_strip.showColor(neopixel.colors(NeoPixelColors.Red))
    }
    if (message == 9) {
        motor_state = 8
        rgb_1.showColor(neopixel.colors(NeoPixelColors.Black))
        rgb_2.showColor(neopixel.colors(NeoPixelColors.Black))
        rgb_3.showColor(neopixel.colors(NeoPixelColors.Yellow))
        rgb_4.showColor(neopixel.colors(NeoPixelColors.Yellow))
    }
    if (message == 7) {
        motor_state = 4
        rgb_1.showColor(neopixel.colors(NeoPixelColors.Yellow))
        rgb_2.showColor(neopixel.colors(NeoPixelColors.Yellow))
        rgb_3.showColor(neopixel.colors(NeoPixelColors.Black))
        rgb_4.showColor(neopixel.colors(NeoPixelColors.Black))
    }
    if (message == 74) {
        change_gear(9)
        music.playTone(659, music.beat(BeatFraction.Whole))
    }
    if (message == 82) {
        change_gear(8)
        music.playTone(587, music.beat(BeatFraction.Whole))
    }
    if (message == 66) {
        change_gear(7)
        music.playTone(523, music.beat(BeatFraction.Whole))
    }
    if (message == 90) {
        change_gear(6)
        music.playTone(494, music.beat(BeatFraction.Whole))
    }
    if (message == 28) {
        change_gear(5)
        music.playTone(440, music.beat(BeatFraction.Whole))
    }
    if (message == 8) {
        change_gear(4)
        music.playTone(392, music.beat(BeatFraction.Whole))
    }
    if (message == 94) {
        change_gear(3)
        music.playTone(349, music.beat(BeatFraction.Whole))
    }
    if (message == 24) {
        change_gear(2)
        music.playTone(330, music.beat(BeatFraction.Whole))
    }
    if (message == 12) {
        change_gear(1)
        music.playTone(294, music.beat(BeatFraction.Whole))
    }
    if (message == 21) {
        motor_state = 0
    }
})
function stop() {
    rgb_strip.showColor(neopixel.colors(NeoPixelColors.Black))
    maqueen.motorStop(maqueen.Motors.All)
}
function forward() {
    maqueen.motorRun(maqueen.Motors.All, maqueen.Dir.CW, speed)
}
function turn_left() {
    maqueen.motorRun(maqueen.Motors.M1, maqueen.Dir.CW, speed / 5)
    maqueen.motorRun(maqueen.Motors.M2, maqueen.Dir.CW, speed)
}
function backward() {
    maqueen.motorRun(maqueen.Motors.All, maqueen.Dir.CCW, speed)
}
function turn_right() {
    maqueen.motorRun(maqueen.Motors.M1, maqueen.Dir.CW, speed)
    maqueen.motorRun(maqueen.Motors.M2, maqueen.Dir.CW, speed / 5)
}
function backward_and_turn_left() {
    maqueen.motorRun(maqueen.Motors.M1, maqueen.Dir.CCW, speed / 8)
    maqueen.motorRun(maqueen.Motors.M2, maqueen.Dir.CCW, speed)
}
function backward_and_turn_right() {
    maqueen.motorRun(maqueen.Motors.M1, maqueen.Dir.CCW, speed)
    maqueen.motorRun(maqueen.Motors.M2, maqueen.Dir.CCW, speed / 8)
}
function change_gear(gear: number) {
    speed = gear * gear_factor + min_speed
}
let tracking_right = 0
let tracking_left = 0
let distance = 0
let min_speed = 0
let gear_factor = 0
let speed = 0
let tracking_flag = 0
let prev_motor_state = 0
let motor_state = 0
let mode = 0
let rgb_4: neopixel.Strip = null
let rgb_3: neopixel.Strip = null
let rgb_2: neopixel.Strip = null
let rgb_1: neopixel.Strip = null
let rgb_strip: neopixel.Strip = null
rgb_strip = neopixel.create(DigitalPin.P15, 4, NeoPixelMode.RGB)
stop()
rgb_1 = rgb_strip.range(0, 1)
rgb_2 = rgb_strip.range(1, 1)
rgb_3 = rgb_strip.range(2, 1)
rgb_4 = rgb_strip.range(3, 1)
// 0=A
//
// 1=B
//
// 2=C
//
mode = 0
// 0=Stop
//
// 1=Forward
//
// 2=Backward
//
// 4=Left
//
// 8=Right
//
motor_state = 0
prev_motor_state = 0
tracking_flag = 0
speed = 200
gear_factor = 23
min_speed = 48
rgb_strip.showColor(neopixel.colors(NeoPixelColors.Red))
music.playTone(294, music.beat(BeatFraction.Whole))
basic.pause(300)
rgb_strip.showColor(neopixel.colors(NeoPixelColors.Green))
music.playTone(330, music.beat(BeatFraction.Whole))
basic.pause(300)
rgb_strip.showColor(neopixel.colors(NeoPixelColors.Blue))
music.playTone(349, music.beat(BeatFraction.Whole))
basic.pause(300)
rgb_strip.showColor(neopixel.colors(NeoPixelColors.White))
basic.forever(function () {
    if (input.buttonIsPressed(Button.A)) {
        mode = (mode + 1) % 3
        if (mode == 0) {
            speed = 200
            stop()
            music.playTone(294, music.beat(BeatFraction.Whole))
            rgb_strip.showColor(neopixel.colors(NeoPixelColors.White))
        }
        if (mode == 1) {
            speed = 200
            stop()
            music.playTone(330, music.beat(BeatFraction.Whole))
            rgb_strip.showColor(neopixel.colors(NeoPixelColors.Green))
        }
        if (mode == 2) {
            speed = 120
            stop()
            music.playTone(349, music.beat(BeatFraction.Whole))
            rgb_strip.showColor(neopixel.colors(NeoPixelColors.Blue))
        }
    }
    if (mode == 0) {
        mode_A()
    }
    if (mode == 1) {
        mode_B()
    }
    if (mode == 2) {
        mode_C()
    }
})
